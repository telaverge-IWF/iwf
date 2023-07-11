/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.notify.conf,v 1.1 2008/12/24 04:50:35 nvijikumar Exp $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "subagent.h"
#include "dremib.h"

using namespace dre;
static oid snmptrap_oid[] = {1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0};
static int seqNum;

#define MAX_SEQUENCE_NUMBER 5000

int
send_dreClearedNotification_trap(AlarmInfo *Info,char* alarmText)
{
    netsnmp_variable_list  *var_list = NULL;
    oid dreClearedNotification_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,0 };
    oid dreAlarmId_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1007, 0 };
    oid dreNotificationSequenceNum_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1000, 0 };
    oid dreFaultName_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1001, 0 };
    oid dreAlarmTime_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1002, 0 };
    oid dreAlarmType_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1003, 0 };
    oid dreAlarmProbableCause_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1004, 0 };
    oid dreAlarmSeverity_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1005, 0 };
    oid dreAddText_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1006, 0 };

    unsigned long alarmTime;
    seqNum++;
    if (seqNum >= MAX_SEQUENCE_NUMBER)
    {
        seqNum = 1;
    }

    alarmTime = time(NULL);
    int severity = Info->GetAlarmSeverity();
    int cause = Info->GetAlarmProbableCause();
    int type = Info->GetAlarmType();
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        dreClearedNotification_oid, sizeof(dreClearedNotification_oid));
    
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        dreAlarmId_oid, OID_LENGTH(dreAlarmId_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAlarmId */
        (unsigned char *)Info->GetAlarmId().c_str(), Info->GetAlarmId().length());
    snmp_varlist_add_variable(&var_list,
        dreNotificationSequenceNum_oid, OID_LENGTH(dreNotificationSequenceNum_oid),
        ASN_COUNTER,
        /* Set an appropriate value for dreNotificationSequenceNum */
        (unsigned char*)&seqNum, sizeof(seqNum));
    snmp_varlist_add_variable(&var_list,
        dreFaultName_oid, OID_LENGTH(dreFaultName_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreFaultName */
        (unsigned char*)(Info->GetFaultName().c_str()), Info->GetFaultName().length());
    snmp_varlist_add_variable(&var_list,
        dreAlarmTime_oid, OID_LENGTH(dreAlarmTime_oid),
        ASN_UNSIGNED,
        /* Set an appropriate value for dreAlarmTime */
        (unsigned char*)&alarmTime, sizeof(alarmTime));
    snmp_varlist_add_variable(&var_list,
        dreAlarmType_oid, OID_LENGTH(dreAlarmType_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmType */
        (unsigned char*)&(type), sizeof(type));
    snmp_varlist_add_variable(&var_list,
        dreAlarmProbableCause_oid, OID_LENGTH(dreAlarmProbableCause_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmProbableCause */
        (unsigned char*)&(cause), sizeof(cause));
    snmp_varlist_add_variable(&var_list,
        dreAlarmSeverity_oid, OID_LENGTH(dreAlarmSeverity_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmSeverity */
        (unsigned char*)&severity, sizeof(severity));
    snmp_varlist_add_variable(&var_list,
        dreAddText_oid, OID_LENGTH(dreAddText_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAddText */
        alarmText, strlen(alarmText));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
int
send_dreWarningNotification_trap( AlarmInfo *Info,char* alarmText)
{
    netsnmp_variable_list  *var_list = NULL;
    oid dreWarningNotification_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1 };
    oid dreAlarmId_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1007, 0 };
    oid dreNotificationSequenceNum_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1000, 0 };
    oid dreFaultName_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1001, 0 };
    oid dreAlarmTime_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1002, 0 };
    oid dreAlarmType_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1003, 0 };
    oid dreAlarmProbableCause_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1004, 0 };
    oid dreAlarmSeverity_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1005, 0 };
    oid dreAddText_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1006, 0 };

    unsigned long alarmTime;
    seqNum++;
    if (seqNum >= MAX_SEQUENCE_NUMBER)
    {
        seqNum = 1;
    }

    alarmTime = time(NULL);
    int severity = Info->GetAlarmSeverity();
    int cause = Info->GetAlarmProbableCause();
    int type = Info->GetAlarmType();
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        dreWarningNotification_oid, sizeof(dreWarningNotification_oid));
    
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        dreAlarmId_oid, OID_LENGTH(dreAlarmId_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAlarmId */
        (unsigned char *)Info->GetAlarmId().c_str(), Info->GetAlarmId().length());
    snmp_varlist_add_variable(&var_list,
        dreNotificationSequenceNum_oid, OID_LENGTH(dreNotificationSequenceNum_oid),
        ASN_COUNTER,
        /* Set an appropriate value for dreNotificationSequenceNum */
        (unsigned char*)&seqNum, sizeof(seqNum));
    snmp_varlist_add_variable(&var_list,
        dreFaultName_oid, OID_LENGTH(dreFaultName_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreFaultName */
        (unsigned char*)(Info->GetFaultName().c_str()), Info->GetFaultName().length());
    snmp_varlist_add_variable(&var_list,
        dreAlarmTime_oid, OID_LENGTH(dreAlarmTime_oid),
        ASN_UNSIGNED,
        /* Set an appropriate value for dreAlarmTime */
        (unsigned char*)&alarmTime, sizeof(alarmTime));
    snmp_varlist_add_variable(&var_list,
        dreAlarmType_oid, OID_LENGTH(dreAlarmType_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmType */
        (unsigned char*)&(type), sizeof(type));
    snmp_varlist_add_variable(&var_list,
        dreAlarmProbableCause_oid, OID_LENGTH(dreAlarmProbableCause_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmProbableCause */
        (unsigned char*)&(cause), sizeof(cause));
    snmp_varlist_add_variable(&var_list,
        dreAlarmSeverity_oid, OID_LENGTH(dreAlarmSeverity_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmSeverity */
        (unsigned char*)&severity, sizeof(severity));
    snmp_varlist_add_variable(&var_list,
        dreAddText_oid, OID_LENGTH(dreAddText_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAddText */
        alarmText, strlen(alarmText));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
int
send_dreMinorNotification_trap( AlarmInfo *Info,char* alarmText )
{
    netsnmp_variable_list  *var_list = NULL;
    oid dreMinorNotification_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,2 };
    oid dreAlarmId_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1007, 0 };
    oid dreNotificationSequenceNum_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1000, 0 };
    oid dreFaultName_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1001, 0 };
    oid dreAlarmTime_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1002, 0 };
    oid dreAlarmType_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1003, 0 };
    oid dreAlarmProbableCause_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1004, 0 };
    oid dreAlarmSeverity_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1005, 0 };
    oid dreAddText_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1006, 0 };

    unsigned long alarmTime;
    seqNum++;
    if (seqNum >= MAX_SEQUENCE_NUMBER)
    {
        seqNum = 1;
    }

    alarmTime = time(NULL);
    int severity = Info->GetAlarmSeverity();
    int cause = Info->GetAlarmProbableCause();
    int type = Info->GetAlarmType();
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        dreMinorNotification_oid, sizeof(dreMinorNotification_oid));
    
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        dreAlarmId_oid, OID_LENGTH(dreAlarmId_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAlarmId */
        (unsigned char *)Info->GetAlarmId().c_str(), Info->GetAlarmId().length());
    snmp_varlist_add_variable(&var_list,
        dreNotificationSequenceNum_oid, OID_LENGTH(dreNotificationSequenceNum_oid),
        ASN_COUNTER,
        /* Set an appropriate value for dreNotificationSequenceNum */
        (unsigned char*)&seqNum, sizeof(seqNum));
    snmp_varlist_add_variable(&var_list,
        dreFaultName_oid, OID_LENGTH(dreFaultName_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreFaultName */
        (unsigned char*)(Info->GetFaultName().c_str()), Info->GetFaultName().length());
    snmp_varlist_add_variable(&var_list,
        dreAlarmTime_oid, OID_LENGTH(dreAlarmTime_oid),
        ASN_UNSIGNED,
        /* Set an appropriate value for dreAlarmTime */
        (unsigned char*)&alarmTime, sizeof(alarmTime));
    snmp_varlist_add_variable(&var_list,
        dreAlarmType_oid, OID_LENGTH(dreAlarmType_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmType */
        (unsigned char*)&(type), sizeof(type));
    snmp_varlist_add_variable(&var_list,
        dreAlarmProbableCause_oid, OID_LENGTH(dreAlarmProbableCause_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmProbableCause */
        (unsigned char*)&(cause), sizeof(cause));
    snmp_varlist_add_variable(&var_list,
        dreAlarmSeverity_oid, OID_LENGTH(dreAlarmSeverity_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmSeverity */
        (unsigned char*)&severity, sizeof(severity));
    snmp_varlist_add_variable(&var_list,
        dreAddText_oid, OID_LENGTH(dreAddText_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAddText */
        alarmText, strlen(alarmText));
    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
int
send_dreMajorNotification_trap( AlarmInfo *Info,char* alarmText)
{
    netsnmp_variable_list  *var_list = NULL;
    oid dreMajorNotification_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,3 };
    oid dreAlarmId_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1007, 0 };
    oid dreNotificationSequenceNum_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1000, 0 };
    oid dreFaultName_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1001, 0 };
    oid dreAlarmTime_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1002, 0 };
    oid dreAlarmType_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1003, 0 };
    oid dreAlarmProbableCause_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1004, 0 };
    oid dreAlarmSeverity_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1005, 0 };
    oid dreAddText_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1006, 0 };

    unsigned long alarmTime;
    seqNum++;
    if (seqNum >= MAX_SEQUENCE_NUMBER)
    {
        seqNum = 1;
    }

    alarmTime = time(NULL);
    int severity = Info->GetAlarmSeverity();
    int cause = Info->GetAlarmProbableCause();
    int type = Info->GetAlarmType();
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        dreMajorNotification_oid, sizeof(dreMajorNotification_oid));
    
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        dreAlarmId_oid, OID_LENGTH(dreAlarmId_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAlarmId */
        (unsigned char *)Info->GetAlarmId().c_str(), Info->GetAlarmId().length());
    snmp_varlist_add_variable(&var_list,
        dreNotificationSequenceNum_oid, OID_LENGTH(dreNotificationSequenceNum_oid),
        ASN_COUNTER,
        /* Set an appropriate value for dreNotificationSequenceNum */
        (unsigned char*)&seqNum, sizeof(seqNum));
    snmp_varlist_add_variable(&var_list,
        dreFaultName_oid, OID_LENGTH(dreFaultName_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreFaultName */
        (unsigned char*)(Info->GetFaultName().c_str()), Info->GetFaultName().length());
    snmp_varlist_add_variable(&var_list,
        dreAlarmTime_oid, OID_LENGTH(dreAlarmTime_oid),
        ASN_UNSIGNED,
        /* Set an appropriate value for dreAlarmTime */
        (unsigned char*)&alarmTime, sizeof(alarmTime));
    snmp_varlist_add_variable(&var_list,
        dreAlarmType_oid, OID_LENGTH(dreAlarmType_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmType */
        (unsigned char*)&(type), sizeof(type));
    snmp_varlist_add_variable(&var_list,
        dreAlarmProbableCause_oid, OID_LENGTH(dreAlarmProbableCause_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmProbableCause */
        (unsigned char*)&(cause), sizeof(cause));
    snmp_varlist_add_variable(&var_list,
        dreAlarmSeverity_oid, OID_LENGTH(dreAlarmSeverity_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmSeverity */
        (unsigned char*)&severity, sizeof(severity));
    snmp_varlist_add_variable(&var_list,
        dreAddText_oid, OID_LENGTH(dreAddText_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAddText */
        alarmText, strlen(alarmText));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
int
send_dreCriticalNotification_trap( AlarmInfo *Info,char* alarmText)
{
    netsnmp_variable_list  *var_list = NULL;
    oid dreCriticalNotification_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,4 };
    oid dreAlarmId_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1007, 0 };
    oid dreNotificationSequenceNum_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1000, 0 };
    oid dreFaultName_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1001, 0 };
    oid dreAlarmTime_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1002, 0 };
    oid dreAlarmType_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1003, 0 };
    oid dreAlarmProbableCause_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1004, 0 };
    oid dreAlarmSeverity_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1005, 0 };
    oid dreAddText_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1006, 0 };

    unsigned long alarmTime;
    seqNum++;
    if (seqNum >= MAX_SEQUENCE_NUMBER)
    {
        seqNum = 1;
    }

    alarmTime = time(NULL);
    int severity = Info->GetAlarmSeverity();
    int cause = Info->GetAlarmProbableCause();
    int type = Info->GetAlarmType();

    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        dreCriticalNotification_oid, sizeof(dreCriticalNotification_oid));
    
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        dreAlarmId_oid, OID_LENGTH(dreAlarmId_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAlarmId */
        (unsigned char *)Info->GetAlarmId().c_str(), Info->GetAlarmId().length());
    snmp_varlist_add_variable(&var_list,
        dreNotificationSequenceNum_oid, OID_LENGTH(dreNotificationSequenceNum_oid),
        ASN_COUNTER,
        /* Set an appropriate value for dreNotificationSequenceNum */
        (unsigned char*)&seqNum, sizeof(seqNum));
    snmp_varlist_add_variable(&var_list,
        dreFaultName_oid, OID_LENGTH(dreFaultName_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreFaultName */
        (unsigned char*)(Info->GetFaultName().c_str()), Info->GetFaultName().length());
    snmp_varlist_add_variable(&var_list,
        dreAlarmTime_oid, OID_LENGTH(dreAlarmTime_oid),
        ASN_UNSIGNED,
        /* Set an appropriate value for dreAlarmTime */
        (unsigned char*)&alarmTime, sizeof(alarmTime));
    snmp_varlist_add_variable(&var_list,
        dreAlarmType_oid, OID_LENGTH(dreAlarmType_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmType */
        (unsigned char*)&(type), sizeof(type));
    snmp_varlist_add_variable(&var_list,
        dreAlarmProbableCause_oid, OID_LENGTH(dreAlarmProbableCause_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmProbableCause */
        (unsigned char*)&(cause), sizeof(cause));
    snmp_varlist_add_variable(&var_list,
        dreAlarmSeverity_oid, OID_LENGTH(dreAlarmSeverity_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmSeverity */
        (unsigned char*)&severity, sizeof(severity));
    snmp_varlist_add_variable(&var_list,
        dreAddText_oid, OID_LENGTH(dreAddText_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAddText */
        alarmText, strlen(alarmText));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
int
send_dreInfoNotification_trap( AlarmInfo *Info,char* alarmText )
{
    netsnmp_variable_list  *var_list = NULL;
    oid dreInfoNotification_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,5 };
    oid dreAlarmId_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1007, 0 };
    oid dreNotificationSequenceNum_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1000, 0 };
    oid dreFaultName_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1001, 0 };
    oid dreAlarmTime_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1002, 0 };
    oid dreAlarmType_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1003, 0 };
    oid dreAlarmProbableCause_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1004, 0 };
    oid dreAlarmSeverity_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1005, 0 };
    oid dreAddText_oid[] = { 1,3,6,1,4,1,2763,1,2,1,1,1006, 0 };

    unsigned long alarmTime;
    seqNum++;
    if (seqNum >= MAX_SEQUENCE_NUMBER)
    {
        seqNum = 1;
    }

    alarmTime = time(NULL);
    int severity = Info->GetAlarmSeverity();
    int cause = Info->GetAlarmProbableCause();
    int type = Info->GetAlarmType();
    /*
     * Set the snmpTrapOid.0 value
     */
    snmp_varlist_add_variable(&var_list,
        snmptrap_oid, OID_LENGTH(snmptrap_oid),
        ASN_OBJECT_ID,
        dreInfoNotification_oid, sizeof(dreInfoNotification_oid));
    
    /*
     * Add any objects from the trap definition
     */
    snmp_varlist_add_variable(&var_list,
        dreAlarmId_oid, OID_LENGTH(dreAlarmId_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAlarmId */
        (unsigned char *)Info->GetAlarmId().c_str(), Info->GetAlarmId().length());
    snmp_varlist_add_variable(&var_list,
        dreNotificationSequenceNum_oid, OID_LENGTH(dreNotificationSequenceNum_oid),
        ASN_COUNTER,
        /* Set an appropriate value for dreNotificationSequenceNum */
        (unsigned char*)&seqNum, sizeof(seqNum));
    snmp_varlist_add_variable(&var_list,
        dreFaultName_oid, OID_LENGTH(dreFaultName_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreFaultName */
        (unsigned char*)(Info->GetFaultName().c_str()), Info->GetFaultName().length());
    snmp_varlist_add_variable(&var_list,
        dreAlarmTime_oid, OID_LENGTH(dreAlarmTime_oid),
        ASN_UNSIGNED,
        /* Set an appropriate value for dreAlarmTime */
        (unsigned char*)&alarmTime, sizeof(alarmTime));
    snmp_varlist_add_variable(&var_list,
        dreAlarmType_oid, OID_LENGTH(dreAlarmType_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmType */
        (unsigned char*)&(type), sizeof(type));
    snmp_varlist_add_variable(&var_list,
        dreAlarmProbableCause_oid, OID_LENGTH(dreAlarmProbableCause_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmProbableCause */
        (unsigned char*)&(cause), sizeof(cause));    
    snmp_varlist_add_variable(&var_list,
        dreAlarmSeverity_oid, OID_LENGTH(dreAlarmSeverity_oid),
        ASN_INTEGER,
        /* Set an appropriate value for dreAlarmSeverity */
        (unsigned char*)&severity, sizeof(severity));
    snmp_varlist_add_variable(&var_list,
        dreAddText_oid, OID_LENGTH(dreAddText_oid),
        ASN_OCTET_STR,
        /* Set an appropriate value for dreAddText */
        alarmText, strlen(alarmText));

    /*
     * Add any extra (optional) objects here
     */

    /*
     * Send the trap to the list of configured destinations
     *  and clean up
     */
    send_v2trap( var_list );
    snmp_free_varbind( var_list );

    return SNMP_ERR_NOERROR;
}
