#include <MysqlInterface.h>

using namespace std;
void ReplicationManagerConfigTQuery::sql_RepMgrConfig_Create_Check_Modifcation_Query(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq,char *pStatement)
{

    sprintf(pStatement,"select ComponentID from ReplicationManagerConfigT where ComponentID=%d",RepMgrReplStateConfigReq->ReplStateKeyInfo.ComponentID);

}


void ReplicationManagerConfigTQuery::sql_RepMgrConfig_Create_Add_Query(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq,char *pStatement)
{


    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    sprintf(pStatement,"insert into ReplicationManagerConfigT");
    strcpy(sFieldName,"(ComponentID");
    sprintf(sFieldValue,"(%d",RepMgrReplStateConfigReq->ReplStateKeyInfo.ComponentID);


    if(RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState != INVALID_NUM)
    {
        strcat(sFieldName,",ReplicationState");
        sprintf(sFieldValue + strlen(sFieldValue),",%d",RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState);
    }

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    strcat(sFieldName,")");
    strcat(sFieldValue,")");

    sprintf(pStatement + strlen(pStatement),"%s value %s",sFieldName,sFieldValue);


    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

}

void ReplicationManagerConfigTQuery::sql_RepMgrConfig_Create_Mod_Query(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq,char *pStatement)
{

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    sprintf(pStatement,"update ReplicationManagerConfigT set "); 
    if(RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState != INVALID_NUM)
    {
        sprintf(pStatement + strlen(pStatement),"ReplicationState=%d,",RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState);
    }
    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    pStatement[strlen(pStatement) -1] = ' ';

    sprintf(pStatement + strlen(pStatement),"where ComponentID=%d",RepMgrReplStateConfigReq->ReplStateKeyInfo.ComponentID);

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


void ReplicationManagerConfigTQuery::sql_RepMgrConfig_Create_Delete_Query(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq,char *pStatement)
{

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    sprintf(pStatement,"delete from ReplicationManagerConfigT where ComponentID=%d",RepMgrReplStateConfigReq->ReplStateKeyInfo.ComponentID); 

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
}


DbStatus_e ReplicationManagerConfigTQuery::sql_RepMgrConfig_Payload_Validation(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq)
{
    if(RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState == INVALID_NUM)
    {
        return DRE_DB_FAIL; 
    }

    return DRE_DB_SUCCESS;

}


void ReplicationManagerConfigTQuery::sql_RepMgrConfig_Create_Select_Query(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq,char *pStatement)
{

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    sprintf(pStatement,"select * from  ReplicationManagerConfigT"); 

    sprintf(sWhereStatement,"where ");

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    if(RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState != INVALID_NUM)
    {
        iFlag = 1;
        sprintf(sWhereStatement + strlen(sWhereStatement),"ReplicationState=%d and ",RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState);
    }

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    if(RepMgrReplStateConfigReq->ReplStateKeyInfo.ComponentID != INVALID_NUM)
    {
        iFlag = 1;
        sprintf(sWhereStatement + strlen(sWhereStatement),"ComponentID=%d and ",RepMgrReplStateConfigReq->ReplStateKeyInfo.ComponentID);
    }

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        sprintf(pStatement + strlen(pStatement)," %s ",sWhereStatement);
    }
}

void ReplicationManagerConfigTQuery::set_RepMgrConfig_Set_TableName()
{
    memset(sRepMgrConfigTableName,0,sizeof(sRepMgrConfigTableName));
    sprintf(sRepMgrConfigTableName + strlen(sRepMgrConfigTableName),"%cReplicationManagerConfigT",TABLE_DELIMITER);
}

void ReplicationManagerConfigTQuery::set_RepMgrConfig_Set_FieldName()
{
    memset(sRepMgrConfigFieldNames,0,sizeof(sRepMgrConfigFieldNames));  
    sprintf(sRepMgrConfigFieldNames + strlen(sRepMgrConfigFieldNames),"%cReplicationState%cComponentID%c",FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);

}

DbStatus_e ReplicationManagerConfigTQuery::sql_RepMgrConfig_Check_All_Invalid(RepMgrReplStateConfigPayload *RepMgrReplStateConfigReq)
{

    if(RepMgrReplStateConfigReq->ReplStateConfigInfo.ReplicationState != INVALID_NUM)
    {
        return DRE_DB_FAIL;
    }

    return DRE_DB_SUCCESS;
}
