/*****************************************************************************
 *                                  EVAD.H
 *
 *  Header for eVAD Commands, Events and parameters
 *
 *
 *  Copyright (c) 2002 NMS Communications  All rights reserved.
 *****************************************************************************/

#include "math.h"    // for epsilon

/*
* EVAD timers format conversion
*/
#define EPSILON(a)  (int) (32767 * (float)(1.0 - (float) exp((double)((-1.0 * 10)/ (float)a))) )

/*
* EVAD default parameters
*/
#define EVAD_SNR             14              /* dB */
#define EVAD_HOLD            1000            /* mseconds */
#define EVAD_MIN_NOISE       (-65)           /* dBm */
#define EVAD_MAX_NOISE       (-40)           /* dBm */
#define EVAD_SIGNAL_ATTACK   30              /* mseconds */
#define EVAD_SIGNAL_RELEASE  60              /* mseconds */
#define EVAD_NOISE_ATTACK    3000            /* mseconds */
#define EVAD_NOISE_RELEASE   600             /* mseconds */
           

/*
* Min and Max for each eVAD parameter
*/
#define MIN_EVAD_SNR             5          /* dB */
#define MAX_EVAD_SNR             30         /* dB */ 
#define MIN_EVAD_HOLD            300        /* mseconds */
#define MAX_EVAD_HOLD            2000       /* mseconds */    
#define MIN_EVAD_MIN_NOISE       (-100)     /* dBm */     
#define MAX_EVAD_MIN_NOISE       (-40)      /* dBm */
#define MIN_EVAD_MAX_NOISE       (-65)      /* dBm */
#define MAX_EVAD_MAX_NOISE       (-25)      /* dBm */
#define MIN_EVAD_SIGNAL_ATTACK   10         /* mseconds */
#define MAX_EVAD_SIGNAL_ATTACK   200        /* mseconds */
#define MIN_EVAD_SIGNAL_RELEASE  10         /* mseconds */
#define MAX_EVAD_SIGNAL_RELEASE  200        /* mseconds */
#define MIN_EVAD_NOISE_ATTACK    500        /* mseconds */
#define MAX_EVAD_NOISE_ATTACK    5000       /* mseconds */
#define MIN_EVAD_NOISE_RELEASE   100        /* mseconds */
#define MAX_EVAD_NOISE_RELEASE   2000       /* mseconds */

           


/*
* EVAD parameters structure
*/
typedef struct EVAD_PARMS
{
    INT16   snr;                /* SNR delta trigger */
    INT16   hold_stop;          /* hold speech buffer before End Of Speech Notification */
    INT16   min_noise;          /* noise estimate minimum */
    INT16   max_noise;          /* noise estimate maximum */
    INT16   signal_attack;      /* time constant of signal integrator when increasing */
    INT16   signal_release;     /* Time constant of signal integrator when decreasing */
    INT16   noise_attack;       /* Time constant of noise integrator when increasing */
    INT16   noise_release;      /* Time constant of noise integrator when decreasing */
}EVAD_PARMS;

/*
* EVAD Events
*/
#define EVAD_EVN_SPEECH_BEGIN           0x0001  /* Speech Begin detected by eVAD algorithm */
#define EVAD_EVN_SPEECH_END             0x0002  /* Speech End detected by eVAD algorithm */
#define EVAD_EVN_FUNCTION_ENABLED       0x0003  /* eVAD function was sucessfully started */
#define EVAD_EVN_FUNCTION_DISABLED      0x0004  /* eVAD function was sucessfully stopped */
#define EVAD_EVN_STREAMING_PAUSED       0x0005  /* Pause voice streaming from Board to Host */
#define EVAD_EVN_STREAMING_RESUMED      0x0006  /* Resume voice streaming from Board to Host */
#define EVAD_EVN_SIGNALLING_DISABLED    0x0007  /* Disable sending eVAD signalling events to the Host */
#define EVAD_EVN_SIGNALLING_ENABLED     0x0008  /* Enable sending eVAD signalling events to the Host */

#define EVAD_EVN_FUNCTION_ERROR         0x0009  /* Error while starting eVAD function (so eVAD is now disabled */

/*
* EVAD Commands
*/
#define EVAD_CDE_FUNCTION_DISABLE       0x0000  /* Stop the eVAD function */
#define EVAD_CDE_FUNCTION_ENABLE        0x0001  /* Start the eVAD function with new parameters */
#define EVAD_CDE_DEFAULT_ENABLE         0x0002  /* Start the eVAD function with default parameters */
#define EVAD_CDE_STREAMING_PAUSE        0x0003  /* Pause voice streaming from Board to Host */
#define EVAD_CDE_STREAMING_RESUME       0x0004  /* Resume voice streaming from Board to Host */
#define EVAD_CDE_SIGNALLING_DISABLE     0x0005  /* Disable sending eVAD signalling events to the Host */
#define EVAD_CDE_SIGNALLING_ENABLE      0x0006  /* Enable sending eVAD signalling events to the Host */

/*
* EVAD Commands size
*/
#define EVAD_CDE_FUNCTION_SIZE                      1   /* size of eVAD commands without parameters */
#define EVAD_CDE_FUNCTION_WITH_PARAMETERS_SIZE      9   /* size of eVAD commands with parameters */