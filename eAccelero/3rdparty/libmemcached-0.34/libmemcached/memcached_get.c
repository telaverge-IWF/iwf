#include "common.h"
#include "memcached_io.h"

/* 
  What happens if no servers exist?
*/
char *memcached_get(memcached_st *ptr, const char *key, 
                    size_t key_length, 
                    size_t *value_length, 
                    uint32_t *flags,
                    memcached_return *error)
{
  return memcached_get_by_key(ptr, NULL, 0, key, key_length, value_length, 
                              flags, error);
}

static memcached_return memcached_mget_by_key_real(memcached_st *ptr, 
                                       const char *master_key, 
                                       size_t master_key_length,
                                       const char **keys, 
                                       size_t *key_length, 
                                       size_t number_of_keys,
				       bool mget_mode);

char *memcached_get_by_key(memcached_st *ptr, 
                           const char *master_key, 
                           size_t master_key_length, 
                           const char *key, size_t key_length,
                           size_t *value_length, 
                           uint32_t *flags,
                           memcached_return *error)
{
  char *value;
  size_t dummy_length;
  uint32_t dummy_flags;
  memcached_return dummy_error;

  unlikely (ptr->flags & MEM_USE_UDP)
  {
    *error= MEMCACHED_NOT_SUPPORTED;
    return NULL;
  }

  /* Request the key */
  *error= memcached_mget_by_key_real(ptr, 
                                master_key, 
                                master_key_length, 
                                (const char **)&key, &key_length, 1, false);

  value= memcached_fetch(ptr, NULL, NULL, 
                         value_length, flags, error);
  /* This is for historical reasons */
  if (*error == MEMCACHED_END)
    *error= MEMCACHED_NOTFOUND;

  if (value == NULL)
  {
    if (ptr->get_key_failure && *error == MEMCACHED_NOTFOUND)
    {
      memcached_return rc;

      memcached_result_reset(&ptr->result);
      rc= ptr->get_key_failure(ptr, key, key_length, &ptr->result);
      
      /* On all failure drop to returning NULL */
      if (rc == MEMCACHED_SUCCESS || rc == MEMCACHED_BUFFERED)
      {
        if (rc == MEMCACHED_BUFFERED)
        {
          uint64_t latch; /* We use latch to track the state of the original socket */
          latch= memcached_behavior_get(ptr, MEMCACHED_BEHAVIOR_BUFFER_REQUESTS);
          if (latch == 0)
            memcached_behavior_set(ptr, MEMCACHED_BEHAVIOR_BUFFER_REQUESTS, 1);

          rc= memcached_set(ptr, key, key_length, 
                            memcached_result_value(&ptr->result),
                            memcached_result_length(&ptr->result),
                            0, memcached_result_flags(&ptr->result));

          if (rc == MEMCACHED_BUFFERED && latch == 0)
            memcached_behavior_set(ptr, MEMCACHED_BEHAVIOR_BUFFER_REQUESTS, 0);
        }
        else
        {
          rc= memcached_set(ptr, key, key_length, 
                            memcached_result_value(&ptr->result),
                            memcached_result_length(&ptr->result),
                            0, memcached_result_flags(&ptr->result));
        }

        if (rc == MEMCACHED_SUCCESS || rc == MEMCACHED_BUFFERED)
        {
          *error= rc;
          *value_length= memcached_result_length(&ptr->result);
          *flags= memcached_result_flags(&ptr->result);
          return memcached_string_c_copy(&ptr->result.value);
        }
      }
    }

    return NULL;
  }

  (void)memcached_fetch(ptr, NULL, NULL, 
                        &dummy_length, &dummy_flags, 
                        &dummy_error);
  WATCHPOINT_ASSERT(dummy_length == 0);

  return value;
}

memcached_return memcached_mget(memcached_st *ptr, 
                                const char **keys, size_t *key_length, 
                                size_t number_of_keys)
{
  return memcached_mget_by_key(ptr, NULL, 0, keys, key_length, number_of_keys);
}

static memcached_return binary_mget_by_key(memcached_st *ptr,
                                           unsigned int master_server_key,
                                           bool is_master_key_set,
                                           const char **keys, size_t *key_length,
                                           size_t number_of_keys,
					   bool mget_mode);

static memcached_return memcached_mget_by_key_real(memcached_st *ptr, 
                                       const char *master_key, 
                                       size_t master_key_length,
                                       const char **keys, 
                                       size_t *key_length, 
                                       size_t number_of_keys,
				       bool mget_mode)
{
  unsigned int x;
  memcached_return rc= MEMCACHED_NOTFOUND;
  const char *get_command= "get ";
  uint8_t get_command_length= 4;
  unsigned int master_server_key= (unsigned int)-1; /* 0 is a valid server id! */
  bool is_master_key_set= false;

   unlikely (ptr->flags & MEM_USE_UDP)
    return MEMCACHED_NOT_SUPPORTED;

  LIBMEMCACHED_MEMCACHED_MGET_START();
  ptr->cursor_server= 0;

  if (number_of_keys == 0)
    return MEMCACHED_NOTFOUND;

  if (ptr->number_of_hosts == 0)
    return MEMCACHED_NO_SERVERS;

  if ((ptr->flags & MEM_VERIFY_KEY) && (memcached_key_test(keys, key_length, number_of_keys) == MEMCACHED_BAD_KEY_PROVIDED))
    return MEMCACHED_BAD_KEY_PROVIDED;

  if (master_key && master_key_length)
  {
    if ((ptr->flags & MEM_VERIFY_KEY) && (memcached_key_test((const char **)&master_key, &master_key_length, 1) == MEMCACHED_BAD_KEY_PROVIDED))
      return MEMCACHED_BAD_KEY_PROVIDED;
    master_server_key= memcached_generate_hash(ptr, master_key, master_key_length);
    is_master_key_set= true;
  }

  /* 
    Here is where we pay for the non-block API. We need to remove any data sitting
    in the queue before we start our get.

    It might be optimum to bounce the connection if count > some number.
  */
  for (x= 0; x < ptr->number_of_hosts; x++)
  {
    if (memcached_server_response_count(&ptr->hosts[x]))
    {
      char buffer[MEMCACHED_DEFAULT_COMMAND_SIZE];

      if (ptr->flags & MEM_NO_BLOCK)
        (void)memcached_io_write(&ptr->hosts[x], NULL, 0, 1);

      while(memcached_server_response_count(&ptr->hosts[x]))
        (void)memcached_response(&ptr->hosts[x], buffer, MEMCACHED_DEFAULT_COMMAND_SIZE, &ptr->result);
    }
  }
  
  if (ptr->flags & MEM_BINARY_PROTOCOL)
    return binary_mget_by_key(ptr, master_server_key, is_master_key_set, keys, 
                              key_length, number_of_keys, mget_mode);

  if (ptr->flags & MEM_SUPPORT_CAS)
  {
    get_command= "gets ";
    get_command_length= 5;
  }

  /* 
    If a server fails we warn about errors and start all over with sending keys
    to the server.
  */
  for (x= 0; x < number_of_keys; x++)
  {
    unsigned int server_key;

    if (is_master_key_set)
      server_key= master_server_key;
    else
      server_key= memcached_generate_hash(ptr, keys[x], key_length[x]);

    if (memcached_server_response_count(&ptr->hosts[server_key]) == 0)
    {
      rc= memcached_connect(&ptr->hosts[server_key]);

      if (rc != MEMCACHED_SUCCESS)
        continue;

      if ((memcached_io_write(&ptr->hosts[server_key], get_command, get_command_length, 0)) == -1)
      {
        rc= MEMCACHED_SOME_ERRORS;
        continue;
      }
      WATCHPOINT_ASSERT(ptr->hosts[server_key].cursor_active == 0);
      memcached_server_response_increment(&ptr->hosts[server_key]);
      WATCHPOINT_ASSERT(ptr->hosts[server_key].cursor_active == 1);
    }

    /* Only called when we have a prefix key */
    if (ptr->prefix_key[0] != 0)
    {
      if ((memcached_io_write(&ptr->hosts[server_key], ptr->prefix_key, ptr->prefix_key_length, 0)) == -1)
      {
        memcached_server_response_reset(&ptr->hosts[server_key]);
        rc= MEMCACHED_SOME_ERRORS;
        continue;
      }
    }

    if ((memcached_io_write(&ptr->hosts[server_key], keys[x], key_length[x], 0)) == -1)
    {
      memcached_server_response_reset(&ptr->hosts[server_key]);
      rc= MEMCACHED_SOME_ERRORS;
      continue;
    }

    if ((memcached_io_write(&ptr->hosts[server_key], " ", 1, 0)) == -1)
    {
      memcached_server_response_reset(&ptr->hosts[server_key]);
      rc= MEMCACHED_SOME_ERRORS;
      continue;
    }
  }

  /*
    Should we muddle on if some servers are dead?
  */
  for (x= 0; x < ptr->number_of_hosts; x++)
  {
    if (memcached_server_response_count(&ptr->hosts[x]))
    {
      /* We need to do something about non-connnected hosts in the future */
      if ((memcached_io_write(&ptr->hosts[x], "\r\n", 2, 1)) == -1)
      {
        rc= MEMCACHED_SOME_ERRORS;
      }
    }
  }

  LIBMEMCACHED_MEMCACHED_MGET_END();
  return rc;
}

memcached_return memcached_mget_by_key(memcached_st *ptr, 
                                       const char *master_key, 
                                       size_t master_key_length,
                                       const char **keys, 
                                       size_t *key_length, 
                                       size_t number_of_keys)
{
  return memcached_mget_by_key_real(ptr, master_key, master_key_length, keys, 
                                    key_length, number_of_keys, true);
}

static memcached_return simple_binary_mget(memcached_st *ptr,
                                           unsigned int master_server_key,
                                           bool is_master_key_set,
                                           const char **keys, size_t *key_length, 
                                           size_t number_of_keys, bool mget_mode)
{
  memcached_return rc= MEMCACHED_NOTFOUND;
  uint32_t x;

  int flush= number_of_keys == 1;

  /* 
    If a server fails we warn about errors and start all over with sending keys
    to the server.
  */
  for (x= 0; x < number_of_keys; x++) 
  {
    unsigned int server_key;

    if (is_master_key_set)
      server_key= master_server_key;
    else
      server_key= memcached_generate_hash(ptr, keys[x], key_length[x]);

    if (memcached_server_response_count(&ptr->hosts[server_key]) == 0) 
    {
      rc= memcached_connect(&ptr->hosts[server_key]);
      if (rc != MEMCACHED_SUCCESS) 
        continue;
    }
     
    protocol_binary_request_getk request= {.bytes= {0}};
    request.message.header.request.magic= PROTOCOL_BINARY_REQ;
    if (mget_mode)
      request.message.header.request.opcode= PROTOCOL_BINARY_CMD_GETKQ;
    else
      request.message.header.request.opcode= PROTOCOL_BINARY_CMD_GETK;

    memcached_return vk;
    vk= memcached_validate_key_length(key_length[x],
                                      ptr->flags & MEM_BINARY_PROTOCOL);
    unlikely (vk != MEMCACHED_SUCCESS)
    {
      if (x > 0)
        memcached_io_reset(&ptr->hosts[server_key]);
      return vk;
    }

    request.message.header.request.keylen= htons((uint16_t)key_length[x]);
    request.message.header.request.datatype= PROTOCOL_BINARY_RAW_BYTES;
    request.message.header.request.bodylen= htonl((uint32_t) key_length[x]);
    
    if ((memcached_io_write(&ptr->hosts[server_key], request.bytes,
                            sizeof(request.bytes), 0) == -1) ||
        (memcached_io_write(&ptr->hosts[server_key], keys[x], 
                            key_length[x], (char) flush) == -1)) 
    {
      memcached_server_response_reset(&ptr->hosts[server_key]);
      rc= MEMCACHED_SOME_ERRORS;
      continue;
    }
    
    /* We just want one pending response per server */
    memcached_server_response_reset(&ptr->hosts[server_key]); 
    memcached_server_response_increment(&ptr->hosts[server_key]);    
    if ((x > 0 && x == ptr->io_key_prefetch) &&
        memcached_flush_buffers(ptr) != MEMCACHED_SUCCESS)
      rc= MEMCACHED_SOME_ERRORS;
  }

  if (mget_mode) 
  {
    /*
     * Send a noop command to flush the buffers
     */
    protocol_binary_request_noop request= {.bytes= {0}};
    request.message.header.request.magic= PROTOCOL_BINARY_REQ;
    request.message.header.request.opcode= PROTOCOL_BINARY_CMD_NOOP;
    request.message.header.request.datatype= PROTOCOL_BINARY_RAW_BYTES;
    
    for (x= 0; x < ptr->number_of_hosts; x++)
      if (memcached_server_response_count(&ptr->hosts[x])) 
      {
        if (memcached_io_write(&ptr->hosts[x], NULL, 0, 1) == -1) 
        {
          memcached_server_response_reset(&ptr->hosts[x]);
          memcached_io_reset(&ptr->hosts[x]);
          rc= MEMCACHED_SOME_ERRORS;
        }

        if (memcached_io_write(&ptr->hosts[x], request.bytes, 
			       sizeof(request.bytes), 1) == -1) 
        {
          memcached_server_response_reset(&ptr->hosts[x]);
          memcached_io_reset(&ptr->hosts[x]);
          rc= MEMCACHED_SOME_ERRORS;
        }
      }
    }


  return rc;
}

static memcached_return replication_binary_mget(memcached_st *ptr,
                                             uint32_t* hash, bool* dead_servers,
                                             const char **keys, size_t *key_length,
                                             size_t number_of_keys, bool mget_mode)
{
  memcached_return rc= MEMCACHED_NOTFOUND;
  uint32_t x;

  int flush= number_of_keys == 1;

  for (uint32_t replica= 0; replica <= ptr->number_of_replicas; ++replica)
  {
    bool success= true;    
    
    for (x= 0; x < number_of_keys; ++x)
    {
      if (hash[x] == ptr->number_of_hosts)
        continue; /* Already successfully sent */

      uint32_t server= hash[x] + replica;
      while (server >= ptr->number_of_hosts)
        server -= ptr->number_of_hosts;

      if (dead_servers[server])
        continue;

      if (memcached_server_response_count(&ptr->hosts[server]) == 0)
      {
        rc= memcached_connect(&ptr->hosts[server]);
        if (rc != MEMCACHED_SUCCESS)
        {
          memcached_io_reset(&ptr->hosts[server]);
          dead_servers[server]= true;
          success= false;
          continue;
        }
      }

      protocol_binary_request_getk request= {.bytes= {0}};
      request.message.header.request.magic= PROTOCOL_BINARY_REQ;
      if (mget_mode)
        request.message.header.request.opcode= PROTOCOL_BINARY_CMD_GETKQ;
      else
        request.message.header.request.opcode= PROTOCOL_BINARY_CMD_GETK;

      request.message.header.request.keylen= htons((uint16_t)key_length[x]);
      request.message.header.request.datatype= PROTOCOL_BINARY_RAW_BYTES;
      request.message.header.request.bodylen= htonl((uint32_t) key_length[x]);

      if ((memcached_io_write(&ptr->hosts[server], request.bytes,
                              sizeof(request.bytes), 0) == -1) ||
          (memcached_io_write(&ptr->hosts[server], keys[x],
                              key_length[x], (char) flush) == -1))
      {
        memcached_io_reset(&ptr->hosts[server]);
        dead_servers[server]= true;
        success= false;
        continue;
      }
      /* we just want one pending response per server */
      memcached_server_response_reset(&ptr->hosts[server]); 
      memcached_server_response_increment(&ptr->hosts[server]);
    }

    if (mget_mode)
    {
      /*
       * Send a noop command to flush the buffers
       */
      protocol_binary_request_noop request= {.bytes= {0}};
      request.message.header.request.magic= PROTOCOL_BINARY_REQ;
      request.message.header.request.opcode= PROTOCOL_BINARY_CMD_NOOP;
      request.message.header.request.datatype= PROTOCOL_BINARY_RAW_BYTES;

      for (x= 0; x < ptr->number_of_hosts; x++)
        if (memcached_server_response_count(&ptr->hosts[x]))
        {
          if (memcached_io_write(&ptr->hosts[x], request.bytes,
                                 sizeof(request.bytes), 1) == -1)
          {
            memcached_io_reset(&ptr->hosts[x]);
            dead_servers[x]= true;
            success= false;
          }

          /* mark all of the messages bound for this server as sent! */
          for (x= 0; x < number_of_keys; ++x)
            if (hash[x] == x)
              hash[x]= ptr->number_of_hosts;
        }
    }

    if (success)
      break;
  }

  return rc;
}

static memcached_return binary_mget_by_key(memcached_st *ptr,
                                           unsigned int master_server_key,
                                           bool is_master_key_set,
                                           const char **keys, size_t *key_length,
                                           size_t number_of_keys, bool mget_mode)
{
  memcached_return rc;

  if (ptr->number_of_replicas == 0) 
  {
    rc= simple_binary_mget(ptr, master_server_key, is_master_key_set,
                           keys, key_length, number_of_keys, mget_mode);
  } 
  else 
  {
    uint32_t* hash;
    bool* dead_servers;

    hash= ptr->call_malloc(ptr, sizeof(uint32_t) * number_of_keys);
    dead_servers= ptr->call_calloc(ptr, ptr->number_of_hosts, sizeof(bool));

    if (hash == NULL || dead_servers == NULL)
    {
      ptr->call_free(ptr, hash);
      ptr->call_free(ptr, dead_servers);
      return MEMCACHED_MEMORY_ALLOCATION_FAILURE;
    }

    if (is_master_key_set)
      for (unsigned int x= 0; x < number_of_keys; x++)
        hash[x]= master_server_key;
    else
      for (unsigned int x= 0; x < number_of_keys; x++)
        hash[x]= memcached_generate_hash(ptr, keys[x], key_length[x]);

    rc= replication_binary_mget(ptr, hash, dead_servers, keys, 
                                key_length, number_of_keys, mget_mode);

    ptr->call_free(ptr, hash);
    ptr->call_free(ptr, dead_servers);

    return MEMCACHED_SUCCESS;
  }

  return rc;
}
