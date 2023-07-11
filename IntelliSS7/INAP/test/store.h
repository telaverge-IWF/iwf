// This is a local header file in the DIN DLL. DLL users do not care about this 
// file.
#include <windows.h>



#define MAX_NUM_MSGS_PNDG 100
#define MAX_MSG_SIZE 1024

// A structure that represents a message.
typedef struct _applMessage {
	unsigned int	size;
	char			data[MAX_MSG_SIZE];
	struct _applMessage *next;
} ApplMessage;

// Global data store used to exchange "messages" between threads.
typedef struct _dataStore {
	ApplMessage *first_msg;
} DataStore;

extern DataStore dataStore;

// Helper functions.
void ClearDataStore(void);
int AddMsgToDataStore(char *data, int size);
ApplMessage *GetMessageFromDataStore(void);
void FreeDataStore(void);

// Return codes
enum MsgReturnCodes {
	MSG_OK,
	MSG_FULL,
	MSG_EMPTY,
	MSG_MEM_ERROR
};

