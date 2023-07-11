/*
   Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef HA_NDB_INDEX_STAT_H
#define HA_NDB_INDEX_STAT_H

#include "ndb_component.h"

/* for NdbIndexScanOperation::IndexBound */
#include <ndbapi/NdbIndexScanOperation.hpp>

/* forward declarations */
struct st_key_range;
typedef struct st_key_range key_range;
struct st_key;
typedef struct st_key KEY;

class Ndb_index_stat_thread : public Ndb_component
{
public:
  Ndb_index_stat_thread();
  virtual ~Ndb_index_stat_thread();

  int running;
  pthread_mutex_t LOCK;
  pthread_cond_t COND;
  pthread_cond_t COND_ready;

  /*
    protect stats entry lists where needed
    protect and signal changes in stats entries
  */
  pthread_mutex_t stat_mutex;
  pthread_cond_t stat_cond;

  /* are we setup */
  bool is_setup_complete();
private:
  virtual int do_init() { return 0;}
  virtual void do_run();
  virtual int do_deinit() { return 0;}
};

/* free entries from share or at end */
extern void ndb_index_stat_free(NDB_SHARE*, int iudex_id, int index_version);
extern void ndb_index_stat_free(NDB_SHARE*);
extern void ndb_index_stat_end();

/* these have to live in ha_ndbcluster.cc */
extern bool ndb_index_stat_get_enable(THD *thd);
extern const char* g_ndb_status_index_stat_status;
extern long g_ndb_status_index_stat_cache_query;
extern long g_ndb_status_index_stat_cache_clean;

void
compute_index_bounds(NdbIndexScanOperation::IndexBound & bound,
                     const KEY *key_info,
                     const key_range *start_key, const key_range *end_key,
                     int from);

/* error codes local to ha_ndb */

/* stats thread is not open for requests (should not happen) */
#define Ndb_index_stat_error_NOT_ALLOW          9001

/* stats entry for existing index not found (should not happen) */
#define Ndb_index_stat_error_NOT_FOUND          9002

/* request on stats entry with recent error was ignored */
#define Ndb_index_stat_error_HAS_ERROR          9003
 
/* stats thread aborted request on stats entry */
#define Ndb_index_stat_error_ABORT_REQUEST      9004

#endif
