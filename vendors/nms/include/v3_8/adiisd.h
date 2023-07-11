/***************************************************************************
*                                  ADIISD.H
*
*  Structures definition for AG ISDN Layer 4
*
*  Copyright (c)1998 Natural MicroSystems Corporation. All rights reserved.
****************************************************************************/

#ifndef ADIISD_INCLUDED
#define ADIISD_INCLUDED

#ifdef __sparc
#define ADIDWORDLE(v)\
        (((v) << 24) | ((v) << 8 & 0x00ff0000) |\
	 ((v) >> 24 & 0x000000ff) | ((v) >> 8 & 0x0000ff00))
#define ADIWORDLE(v) ((((v) & 0x00ff ) << 8) | ((v) >> 8 & 0x00ff))
#else
#define ADIDWORDLE(v) (v)
#define ADIWORDLE(v) (v)
#endif

#define ADI_ISD_PARMID 0x1001e


/*------ ISD PARMS --(isdn)---------------------------------------------*/

typedef struct                    /* passed with adiStartProtocol("ISDN")    */
{
    DWORD size;                   /*  Size of this structure.                */
    WORD exclusive;               /*  0 exclusive or prefered                */
                                  /*     0 = non-exclusive                   */
                                  /*     1 = exclusive                       */
    WORD direction;               /*  1 inbound, outbound or both            */
                                  /*     0 = both                            */
                                  /*     1 = inbound                         */
                                  /*     2 = outbound                        */
    WORD networkstream;           /*  2 network stream (dflt: infer from DSP)*/
    WORD networkslot;             /*  3 net time slot  (dflt: infer from DSP)*/
    WORD ringampl;                /*  4 amplitude of ring tone               */
    WORD freqringlow;             /*  5 low frequency of ring tone           */
    WORD freqringhigh;            /*  6 high frequency of ring tone          */
    WORD ringontime;              /*  7 ring on time                         */
    WORD ringofftime1;            /*  8 1st ring off time                    */
    WORD ringofftime2;            /*  9 2nd ring off time                    */
    WORD busyampl;                /* 10 amplitude of busy tone               */
    WORD freqbusylow;             /* 11 low frequency of busy tone           */
    WORD freqbusyhigh;            /* 12 high frequency of busy tone          */
    WORD busytimeon;              /* 13 busy on time                         */
    WORD busytimeoff;             /* 14 busy off time                        */
    WORD freqreorderlow;          /* 15 low frequency of reorder tone        */
    WORD freqreorderhigh;         /* 16 high frequency of reorder tone       */
    WORD reordertimeon;           /* 17 reorder on time                      */
    WORD reordertimeoff;          /* 18 reorder off time                     */
    WORD waitforPCtime;           /* 19 time to wait for PC                  */
    WORD defaulttone;             /* 20 default tone to play on reject       */
                                  /*     0 = reorder (fast busy)             */
                                  /*     1 = ringing                         */
                                  /*     2 = busy                            */
    WORD startCP;                 /* 21 Start call progress from the TCP     */
				  /*    when a PROGRESS or a CONNECT message */
                                  /*    is received                          */
    WORD flags;                   /* 22 miscellaneous flags                  */
    WORD blockrejectmode;         /* 23 how to reject calls when the channel */
        #define ISD_BLOCK_REJ_FORCE_IMMEDIATE 0 /* reject immediate          */
        #define ISD_BLOCK_REJ_MAKEBUSY        1 /* play busy tone            */ 
} ADI_ISD_PARMS;


/* Supplementary services calling number extensions:                       */
typedef struct
{
    char digits[33];
    char plan;
    char type;
    char screen;
    char presentation;
    char pad[3];
} ISDN_CALLINGNUMBER;


/* Supplementary services redirecting number extensions:                   */
typedef struct
{
    char digits[33];
    char plan;
    char type;
    char screen;
    char presentation;
    char reason;
    char pad[2];
} ISDN_REDIRECTINGNUMBER;

/* Supplementary services called number extensions:                        */
typedef struct
{
    char plan;
    char type;
    char pad[2];
} ISDN_CALLEDNUMBER;

/* Supplementary services place call extensions:                           */
typedef struct
{
    DWORD size;    
    char  uui[132];
    ISDN_CALLEDNUMBER      callednumber;
    ISDN_CALLINGNUMBER     callingnumber;
    ISDN_REDIRECTINGNUMBER redirectingnumber;
    char  service;
    char  nsf_present;
    char  nsf_service_feature;
    char  nsf_facility_coding;
} ISDNPLACECALL_EXTARGS;

#define isdn_placecall_					((ISDNPLACECALL_EXTARGS *) (p_data)) ->

#define set_isdn_placecall_size(v)			((void) (isdn_placecall_ size = ADIDWORDLE(v)))
#define get_isdn_placecall_size     			(ADIDWORDLE(isdn_placecall_ size))

#define isdn_placecall_a_uui	       			(isdn_placecall_ uui)


#define set_isdn_placecall_called_nb_plan(v)		((void) isdn_placecall_ callednumber.plan = (v))
#define get_isdn_placecall_called_nb_plan		(isdn_placecall_ callednumber.plan)
#define set_isdn_placecall_called_nb_type(v)		((void) isdn_placecall_ callednumber.type = (v))
#define get_isdn_placecall_called_nb_type		(isdn_placecall_ callednumber.type)


#define isdn_placecall_calling_nb_a_digits		(isdn_placecall_ callingnumber.digits)
#define set_isdn_placecall_calling_nb_plan(v)		((void) isdn_placecall_ callingnumber.plan = (v))
#define get_isdn_placecall_calling_nb_plan		(isdn_placecall_ callingnumber.plan)
#define set_isdn_placecall_calling_nb_type(v)		((void) isdn_placecall_ callingnumber.type = (v))
#define get_isdn_placecall_calling_nb_type		(isdn_placecall_ callingnumber.type)
#define set_isdn_placecall_calling_nb_screen(v)		((void) isdn_placecall_ callingnumber.screen = (v))
#define get_isdn_placecall_calling_nb_screen		(isdn_placecall_ callingnumber.screen)
#define set_isdn_placecall_calling_nb_presentation(v)	((void) isdn_placecall_ callingnumber.presentation = (v))
#define get_isdn_placecall_calling_nb_presentation	(isdn_placecall_ callingnumber.presentation)


#define isdn_placecall_redirecting_nb_a_digits			(isdn_placecall_ redirectingnumber.digits)
#define set_isdn_placecall_redirecting_nb_plan(v)		((void) isdn_placecall_ redirectingnumber.plan = (v))
#define get_isdn_placecall_redirecting_nb_plan			(isdn_placecall_ redirectingnumber.plan)
#define set_isdn_placecall_redirecting_nb_type(v)	      	((void) isdn_placecall_ redirectingnumber.type = (v))
#define get_isdn_placecall_redirecting_nb_type			(isdn_placecall_ redirectingnumber.type)
#define set_isdn_placecall_redirecting_nb_screen(v)    		((void) isdn_placecall_ redirectingnumber.screen = (v))
#define get_isdn_placecall_redirecting_nb_screen       		(isdn_placecall_ redirectingnumber.screen)
#define set_isdn_placecall_redirecting_nb_presentation(v)	((void) isdn_placecall_ redirectingnumber.presentation = (v))
#define get_isdn_placecall_redirecting_nb_presentation		(isdn_placecall_ redirectingnumber.presentation)
#define set_isdn_placecall_redirecting_nb_reason(v)		((void) isdn_placecall_ redirectingnumber.reason = (v))
#define get_isdn_placecall_redirecting_nb_reason		(isdn_placecall_ redirectingnumber.reason)


#define set_isdn_placecall_service(v)			((void) (isdn_placecall_ service = ADIWORDLE(v)))
#define get_isdn_placecall_serivce	      		(ADIWORDLE(isdn_placecall_ service))

#define set_isdn_placecall_nsf_present(v)		((void) (isdn_placecall_ nsf_present = ADIWORDLE(v)))
#define get_isdn_placecall_nsf_present         		(ADIWORDLE(isdn_placecall_ nsf_present))

#define set_isdn_placecall_nsf_service_feature(v)	((void) (isdn_placecall_ nsf_service_feature = ADIWORDLE(v)))
#define get_isdn_placecall_nsf_service_feature	   		(ADIWORDLE(isdn_placecall_ nsf_service_feature))

#define set_isdn_placecall_nsf_facility_coding(v)	((void) (isdn_placecall_ nsf_facility_coding = ADIWORDLE(v)))
#define get_isdn_placecall_nsf_facility_coding     		(ADIWORDLE(isdn_placecall_ nsf_facility_coding))

/* Supplementary services answer call extensions:                          */
typedef struct
{
    DWORD size;    
    char uui [132];
} ISDNANSWERCALL_EXTARGS;

#define isdn_answercall_				((ISDNANSWERCALL_EXTARGS *) (p_data)) ->

#define set_isdn_answercall_size(v)			((void) (isdn_answercall_ size = ADIDWORDLE(v)))
#define get_isdn_answercall_size           		(ADIDWORDLE(isdn_answercall_ size))

#define isdn_answercall_a_uui		      		(isdn_answercall_ uui)


/* Supplementary services release call extensions:                         */
typedef struct
{
    DWORD size;   
    char  uui [132];
    WORD  cause;
    char pad[2];
} ISDNRELEASECALL_EXTARGS;

#define isdn_releasecall_				((ISDNRELEASECALL_EXTARGS *) (p_data)) ->

#define set_isdn_releasecall_size(v)			((void) (isdn_releasecall_ size = ADIDWORDLE(v)))
#define get_isdn_releasecall_size	           	(ADIDWORDLE(isdn_releasecall_ size))

#define isdn_releasecall_a_uui			      	(isdn_releasecall_ uui)

#define set_isdn_releasecall_cause(v)       		((void) (isdn_releasecall_ cause = ADIWORDLE(v)))
#define get_isdn_releasecall_cause			(ADIWORDLE(isdn_releasecall_ cause))


/* Supplementary services accept call extensions:                          */
typedef struct
{
    DWORD size;    
    char uui [132];
    WORD  cause;
    WORD  progressdescription;
} ISDNACCEPTCALL_EXTARGS;

#define isdn_acceptcall_				((ISDNACCEPTCALL_EXTARGS *) (p_data)) ->

#define set_isdn_acceptcall_size(v)			((void) (isdn_acceptcall_ size = ADIDWORDLE(v)))
#define get_isdn_acceptcall_size           		(ADIDWORDLE(isdn_acceptcall_ size))

#define isdn_acceptcall_a_uui			      	(isdn_acceptcall_ uui)

#define set_isdn_acceptcall_cause(v)       		((void) (isdn_acceptcall_ cause = ADIWORDLE(v)))
#define get_isdn_acceptcall_cause			(ADIWORDLE(isdn_acceptcall_ cause))

#define set_isdn_acceptcall_progressdescription(v)      ((void) (isdn_acceptcall_ progressdescription = ADIWORDLE(v)))
#define get_isdn_acceptcall_progressdescription		(ADIWORDLE(isdn_acceptcall_ progressdescription))


#define ISDNREJECTCALL_EXTARGS ISDNRELEASECALL_EXTARGS

#define isdn_rejectcall_				((ISDNREJECTCALL_EXTARGS *) (p_data)) ->

#define set_isdn_rejectcall_size(v)			((void) (isdn_rejectcall_ size = ADIDWORDLE(v)))
#define get_isdn_rejectcall_size	           	(ADIDWORDLE(isdn_rejectcall_ size))

#define isdn_rejectcall_a_uui			      	(isdn_rejectcall_ uui)

#define set_isdn_rejectcall_cause(v)       		((void) (isdn_rejectcall_ cause = ADIWORDLE(v)))
#define get_isdn_rejectcall_cause			(ADIWORDLE(isdn_rejectcall_ cause))

#endif

