#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

extern SIP_MSG *sip_last_msg;
extern SIP_MSG *sip_prov_msg;

/* Function Declaration */
int
APP_Send180Ringing(ITS_HANDLE handle, SIP_MSG *msg);
int
APP_Send200Ok(ITS_HANDLE handle, SIP_MSG *msg);
int
APP_SendAck(ITS_HANDLE handle, SIP_MSG *msg);
int
APP_Send3XX(ITS_HANDLE handle, SIP_MSG *msg);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

