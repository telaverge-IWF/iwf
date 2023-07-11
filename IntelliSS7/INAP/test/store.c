#include "store.h"
#include <stdio.h>

DataStore dataStore;

void ClearDataStore(void)
{
	ZeroMemory(&dataStore, sizeof(DataStore));
}

int AddMsgToDataStore(char *data, int size)
{
	ApplMessage *pApplMessage;
	ApplMessage *pTemp, *pPrev;

	pApplMessage = (ApplMessage *) calloc(1, sizeof(ApplMessage));
	if (pApplMessage == NULL)
		return MSG_MEM_ERROR;

	// initialize the node.
	pApplMessage->size = size;
	memcpy(pApplMessage->data, data, size);
	pApplMessage->next = NULL;

	// if first message then its easy!
	if (dataStore.first_msg == NULL)
	{
		dataStore.first_msg = pApplMessage;
		return MSG_OK;
	}

	for (pTemp = dataStore.first_msg, pPrev = NULL; 
			pTemp != NULL; pPrev = pTemp, pTemp = pTemp->next)
		;
	pPrev->next = pApplMessage;

	return MSG_OK;
}

ApplMessage *GetMessageFromDataStore(void)
{
	ApplMessage *f_message;

	f_message = dataStore.first_msg;
	
	if (dataStore.first_msg != NULL)
		dataStore.first_msg = dataStore.first_msg->next;

	return f_message;
}

void FreeDataStore(void)
{
	ApplMessage *this_message;
	ApplMessage *next_message;

	this_message = dataStore.first_msg;

	while (this_message != NULL)
	{
		next_message = this_message->next;
		free(this_message);
		this_message = next_message;
	}
	return;
}
