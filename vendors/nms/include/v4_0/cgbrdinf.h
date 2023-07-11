/*******************************************************************************
   cgbrdinf.h

   Description:
     header file for CG board info

 Copyright (c) 2003 NMS Communciations. All rights reserved.
 *******************************************************************************/

WORD GetAssemblyNum(INT32 Bus, INT32 Slot);
BYTE GetTestLevelRev(INT32 Bus, INT32 Slot);
WORD GetTestLevel(INT32 Bus, INT32 Slot);
