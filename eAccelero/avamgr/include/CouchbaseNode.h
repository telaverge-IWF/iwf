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
#ifndef _COUCHBASE_NODE_H_
#define _COUCHBASE_NODE_H_
#include"Node.h"

namespace eAccelero {

class CouchbaseNode: public Node{
    public:
    CouchbaseNode()
    {
    }
    ~CouchbaseNode(){};
    void setOtpNode(std::string otpNode){m_otpNode = otpNode;};
    void setUserName(std::string username){m_userName= username;};
    void setPassword(std::string password){m_password= password;};
    std::string getOtpNode(){return m_otpNode;};
    std::string getUserName(){return m_userName;};
    std::string getPassword(){return m_password;};
    private:
    std::string m_otpNode;
    std::string m_userName;
    std::string m_password;
};

}

#endif //_COUCHBASE_NODE_H_
