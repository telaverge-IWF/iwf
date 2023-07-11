/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************/
#ifndef _NODE_H_
#define _NODE_H_
#include <string>
namespace eAccelero{

enum NodeState{
    CLUSTER_NODE_STATE_UNKNOWN = 0,
    CLUSTER_NODE_STATE_UP,
    CLUSTER_NODE_STATE_DOWN
};

class Node {
    public:
        Node()
        {
            failureCount = 0;
            nodeStatus = CLUSTER_NODE_STATE_UNKNOWN;
        }
        std::string hostName;
        uint32_t nodeStatus;
        uint32_t failureCount;

};

}

#endif //_NODE_H_
