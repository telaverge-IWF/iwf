/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * $Id: print.c,v 1.2 2005/05/25 12:33:32 mmanikandan Exp $
 *
 * $Log: print.c,v $
 * Revision 1.2  2005/05/25 12:33:32  mmanikandan
 * Changes for CCITT Compilation.
 *
 * Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * Initial Commit Multiple Application Binding.
 *
 *****************************************************************************/

#include<mab_client.h>

void
PrintComponent( TCAP_CPT *cpt)
{

   ITS_UINT i;

   printf("\nlast component is : %x\n",cpt->last_component);
   printf("ptype : %d\n",cpt->ptype);
   switch(cpt->ptype)
   {

       case TCPPT_TC_INVOKE:
       {
   
           printf("printing invoke details....\n");
           printf("cpt->u.invoke.invoke_id.len : %d \n",cpt->u.invoke.invoke_id.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.invoke.invoke_id.len; i++)
           {
               printf(" %x ",cpt->u.invoke.invoke_id.data[i]);
           }
           printf("\n");

           printf("cpt->u.invoke.operation.len : %d \n",cpt->u.invoke.operation.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.invoke.operation.len; i++)
           {
               printf(" %x ",cpt->u.invoke.operation.data[i]);
           }
           printf("\n");
           printf("cpt->u.invoke.param.len :  %d \n",cpt->u.invoke.param.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.invoke.param.len; i++)
           {
               printf(" %x ",cpt->u.invoke.param.data[i]);
           }
           printf("\n");

           printf("cpt->u.invoke.timeout : %d\n",cpt->u.invoke.timeout);
           printf("cpt->u.invoke.linked_id.len :%d\n",cpt->u.invoke.linked_id.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.invoke.linked_id.len; i++)
           {
               printf(" %x ",cpt->u.invoke.linked_id.data[i]);
           }
           printf("\n");
           break;
       }
  
       case TCPPT_TC_RESULT_NL:
       case TCPPT_TC_RESULT_L:
       {
   
           printf("printing  result comppnent details....\n");
           printf("cpt->u.result.invoke_id.len : %d \n",cpt->u.result.invoke_id.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.result.invoke_id.len; i++)
           {
               printf(" %x ",cpt->u.result.invoke_id.data[i]);
           }
           printf("\n");
           printf("cpt->u.result.param.len :  %d \n",cpt->u.result.param.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.result.param.len; i++)
           {
               printf(" %x ",cpt->u.result.param.data[i]);
           }
           printf("\n");
           break;
       } 
#ifdef ANSI
       case TCPPT_TC_ERROR:
#elif defined (CCITT)
       case TCPPT_TC_U_ERROR:
#endif
       {
 
           printf("printing  error  comppnent details....\n");
           printf("cpt->u.error.invoke_id.len : %d \n",cpt->u.error.invoke_id.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.error.invoke_id.len; i++)
           {
               printf(" %x ",cpt->u.error.invoke_id.data[i]);
           }
           printf("\n");
           printf("cpt->u.error.error.len : %d \n",cpt->u.error.error.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.error.error.len; i++)
           {
               printf(" %x ",cpt->u.error.error.data[i]);

           }
           printf("\n");
           printf("cpt->u.error.param.len :  %d \n",cpt->u.error.param.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.error.param.len; i++)
           {
               printf(" %x ",cpt->u.error.param.data[i]);
           }
           printf("\n");
           break;
       }   
#ifdef ANSI
       case TCPPT_TC_REJECT:
#elif defined (CCITT)
       case TCPPT_TC_L_REJECT:
       case TCPPT_TC_U_REJECT:
       case TCPPT_TC_R_REJECT:
#endif
       {
           printf("printing reject  comppnent details....\n");
           printf("cpt->u.reject.invoke_id.len : %d \n",cpt->u.reject.invoke_id.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.reject.invoke_id.len; i++)
           {
               printf(" %x ",cpt->u.reject.invoke_id.data[i]);
           }
           printf("\n");
           printf("cpt->u.reject.problem.len : %d \n",cpt->u.reject.problem.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.reject.problem.len; i++)
           {
               printf(" %x ",cpt->u.reject.problem.data[i]);
           }
           printf("\n");
#ifdef ANSI
           printf("cpt->u.reject.param.len :  %d \n",cpt->u.reject.param.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.reject.param.len; i++)
           {
               printf(" %x ",cpt->u.reject.param.data[i]);
           }
           printf("\n");
#endif
           break;
       }

       default:
       { 
           printf("cpt->u.cancel.invoke_id.len : %d \n",cpt->u.cancel.invoke_id.len);
           printf("data part ...\n");
           for(i=0 ; i<cpt->u.cancel.invoke_id.len; i++)
           {
               printf(" %x ",cpt->u.cancel.invoke_id.data[i]);

           }
           printf("\n");
       }

   }

}
void
PrintDialoge( TCAP_DLG * dlg)
{

   int i;
   printf(" dlg->ptype : %x\n", dlg->ptype);

   switch(dlg->ptype)
   {
   
   case TCPPT_TC_UNI:
     {
         printf(" dlg->u.uni.cpt_present :%d\n",dlg->u.uni.cpt_present);
         printf(" dlg->u.uni.qos.indicator : %x \n",dlg->u.uni.qos.indicator);
         printf(" dlg->u.uni.qos.sls_key : %x \n",dlg->u.uni.qos.sls_key);
         printf(" dlg->u.uni.qos.priority : %x \n",dlg->u.uni.qos.priority);
         printf(" dlg->u.uni.qos.networkInd : %x \n",dlg->u.uni.qos.networkInd);
         printf(" dlg->u.uni.ac_name.len : %d \n",dlg->u.uni.ac_name.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.uni.ac_name.len; i++)
         {
             printf(" %x ",dlg->u.uni.ac_name.data[i]);
         }
         printf("\n");
         printf(" dlg->u.uni.user_info.len : %d\n",dlg->u.uni.user_info.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.uni.user_info.len; i++)
         {
             printf(" %x ",dlg->u.uni.user_info.data[i]);
         }
         printf("\n");
         printf(" dlg->u.uni.orig_addr.len : %d\n",dlg->u.uni.orig_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.uni.orig_addr.len; i++)
         {
             printf(" %x ",dlg->u.uni.orig_addr.data[i]);
         }
         printf("\n");
         printf(" dlg->u.uni.dest_addr.len : %d\n",dlg->u.uni.dest_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.uni.dest_addr.len; i++)
         {
             printf(" %x ",dlg->u.uni.dest_addr.data[i]);
         }
         printf("\n");
         printf(" opc : %x %x %x \n",dlg->u.uni.opc.data[0],
                               dlg->u.uni.opc.data[1],
                               dlg->u.uni.opc.data[2]);

         printf(" dpc : %x %x %x \n",dlg->u.uni.dpc.data[0],
                               dlg->u.uni.dpc.data[1],
                               dlg->u.uni.dpc.data[2]);

         break;
     } 
#ifdef ANSI
     case TCPPT_TC_QUERY_W_PERM:
     case TCPPT_TC_QUERY_WO_PERM:
#elif defined (CCITT)
     case TCAP_PT_TC_BEGIN_CCITT:
#endif
     { 
         printf("\n\n printing the begin dialoge contentes...\n");
         printf(" dlg->u.begin.cpt_present :%d\n",dlg->u.begin.cpt_present);
         printf(" dlg->u.begin.qos.indicator : %x \n",dlg->u.begin.qos.indicator);
         printf(" dlg->u.begin.qos.sls_key : %x \n",dlg->u.begin.qos.sls_key);
         printf(" dlg->u.begin.qos.priority : %x \n",dlg->u.begin.qos.priority);
         printf(" dlg->u.begin.qos.networkInd : %x \n",dlg->u.begin.qos.networkInd);
         printf(" dlg->u.begin.ac_name.len : %d \n",dlg->u.begin.ac_name.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.begin.ac_name.len; i++)
         {
             printf(" %x ",dlg->u.begin.ac_name.data[i]);
         }
         printf("\n");
         printf(" dlg->u.begin.user_info.len : %d\n",dlg->u.begin.user_info.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.begin.user_info.len; i++)
         {
             printf(" %x ",dlg->u.begin.user_info.data[i]);
         }
         printf("\n");
         printf(" dlg->u.begin.orig_addr.len : %d\n",dlg->u.begin.orig_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.begin.orig_addr.len; i++)
         {
             printf(" %x ",dlg->u.begin.orig_addr.data[i]);
         }
         printf("\n");
         printf(" dlg->u.begin.dest_addr.len : %d\n",dlg->u.begin.dest_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.begin.dest_addr.len; i++)
         {
             printf(" %x ",dlg->u.begin.dest_addr.data[i]);
         }
         printf("\n");
         printf(" opc : %x %x %x \n",dlg->u.begin.opc.data[0],
                               dlg->u.begin.opc.data[1],
                               dlg->u.begin.opc.data[2]);

         printf(" dpc : %x %x %x \n",dlg->u.begin.dpc.data[0],
                               dlg->u.begin.dpc.data[1],
                               dlg->u.begin.dpc.data[2]);

         break;
     }
#if defined(ANSI)
     case TCPPT_TC_CONV_WO_PERM:
     case TCPPT_TC_CONV_W_PERM:
#elif defined (CCITT)
     case TCAP_PT_TC_CONTINUE_CCITT:
#endif
     {

         printf("\n\n printing the continue dialoge contentes...\n");
         printf(" dlg->u.cont.cpt_present :%d\n",dlg->u.cont.cpt_present);
         printf(" dlg->u.cont.qos.indicator : %x \n",dlg->u.cont.qos.indicator);
         printf(" dlg->u.cont.qos.sls_key : %x \n",dlg->u.cont.qos.sls_key);
         printf(" dlg->u.cont.qos.priority : %x \n",dlg->u.cont.qos.priority);
         printf(" dlg->u.cont.qos.networkInd : %x \n",dlg->u.cont.qos.networkInd);
         printf(" dlg->u.cont.ac_name.len : %d \n",dlg->u.cont.ac_name.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.cont.ac_name.len; i++)
         {
             printf(" %x ",dlg->u.cont.ac_name.data[i]);
         }
         printf("\n");
         printf(" dlg->u.cont.user_info.len : %d\n",dlg->u.cont.user_info.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.cont.user_info.len; i++)
         {
             printf(" %x ",dlg->u.cont.user_info.data[i]);
         }
         printf("\n");
         printf(" dlg->u.cont.orig_addr.len : %d\n",dlg->u.cont.orig_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.cont.orig_addr.len; i++)
         {
             printf(" %x ",dlg->u.cont.orig_addr.data[i]);
         }
         printf("\n");
         printf(" opc : %x %x %x \n",dlg->u.cont.opc.data[0],
                               dlg->u.cont.opc.data[1],
                               dlg->u.cont.opc.data[2]);

         break;
     }
#if defined (ANSI)
     case TCPPT_TC_RESP:
#elif defined (CCITT)
     case TCAP_PT_TC_END_CCITT:
#endif
     {
      
         printf("\n\n printing the end components  contentes...\n");
         printf(" dlg->u.end.cpt_present :%d\n",dlg->u.end.cpt_present);
         printf(" dlg->u.end.qos.indicator : %x \n",dlg->u.end.qos.indicator);
         printf(" dlg->u.end.qos.sls_key : %x \n",dlg->u.end.qos.sls_key);
         printf(" dlg->u.end.qos.priority : %x \n",dlg->u.end.qos.priority);
         printf(" dlg->u.end.qos.networkInd : %x \n",dlg->u.end.qos.networkInd);
         printf(" dlg->u.end.ac_name.len : %d \n",dlg->u.end.ac_name.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.end.ac_name.len; i++)
         {
             printf(" %x ",dlg->u.end.ac_name.data[i]);
         }
         printf("\n");
         printf(" dlg->u.end.user_info.len : %d\n",dlg->u.end.user_info.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.end.user_info.len; i++)
         {
             printf(" %x ",dlg->u.end.user_info.data[i]);
         }
         printf("\n");
         printf("dlg->u.end.termination : %x\n",dlg->u.end.termination);
         break;

     }
#if defined (ANSI)
     case TCPPT_TC_ABORT:
#elif defined (CCITT)
     case TCAP_PT_TC_P_ABORT_CCITT:
     case TCAP_PT_TC_U_ABORT_CCITT:
#endif
     {
         printf("\n\n printing the abort  dialoge contentes...\n");
         printf("dlg->u.abort.abort_reason : %d\n",dlg->u.abort.abort_reason);
         printf(" dlg->u.abort.qos.indicator : %x \n",dlg->u.abort.qos.indicator);
         printf(" dlg->u.abort.qos.sls_key : %x \n",dlg->u.abort.qos.sls_key);
         printf(" dlg->u.abort.qos.priority : %x \n",dlg->u.abort.qos.priority);
         printf(" dlg->u.abort.qos.networkInd : %x \n",dlg->u.abort.qos.networkInd);
         printf(" dlg->u.abort.ac_name.len : %d \n",dlg->u.abort.ac_name.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.abort.ac_name.len; i++)
         {
             printf(" %x ",dlg->u.abort.ac_name.data[i]);
         }
         printf("\n");
         printf(" dlg->u.abort.user_info.len : %d\n",dlg->u.abort.user_info.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.abort.user_info.len; i++)
         {
             printf(" %x ",dlg->u.abort.user_info.data[i]);
         }
         printf(" dlg->u.abort.abort_info.len : %d\n",dlg->u.abort.abort_info.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.abort.abort_info.len; i++)
         {
             printf(" %x ",dlg->u.abort.abort_info.data[i]);
         }
         break;

     }
   
     default :
     { 
         printf("\n\n printing the notice  dialoge contentes...\n");
         printf("dlg->u.notice.report_cause : %x\n", dlg->u.notice.report_cause);
         printf("dlg->u.notice.user_data_len  %d\n",dlg->u.notice.user_data_len);
         printf(" dlg->u.notice.orig_addr.len : %d\n",dlg->u.notice.orig_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.notice.orig_addr.len; i++)
         {
             printf(" %x ",dlg->u.notice.orig_addr.data[i]);
         }
         printf("\n");
         printf(" dlg->u.notice.dest_addr.len : %d\n",dlg->u.notice.dest_addr.len);
         printf("data part ...\n");
         for(i=0 ; i<dlg->u.notice.dest_addr.len; i++)
         {
             printf(" %x ",dlg->u.notice.dest_addr.data[i]);
         }
         printf("\n");

         printf(" printing the SCCP_DATA ..\n");
         for(i=0 ; i<SCCP_MAX_DATA; i++)
         {
             printf(" %x ",dlg->u.notice.user_data.data[i]);
         }
         printf("\n");
     }
   }/* switch end */

}

