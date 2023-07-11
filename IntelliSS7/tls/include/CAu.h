/*********************************-*-H-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#ifndef CAU_H
#define CAU_H

#include "CRL.h"

#define ERRCLOOKOBJ -1
#define ERRLCRLF    -2

namespace its
{
    class CertificateAuthority 
    {
     public:
        enum CertificateType 
        {
            CERT_TYPE_PEM = 1,
            CERT_TYPE_DER
        };

        CertificateAuthority();
        CertificateAuthority(std::string &certFileName, CertificateType certType);
        CertificateAuthority(std::string &certFileName, CertificateType certType, CRL crl);

        CertificateType GetCertType();
        void SetCertType(CertificateType certType);
        
        std::string GetCertificateFileName();
        void SetCertificateFileName(std::string &fileName);

        void SetCRL(CRL crl);
        CRL GetCRL();

     private:
        std::string certificateFileName;
        CertificateType certType;
        CRL crl;
    };

    inline CertificateAuthority::CertificateType CertificateAuthority::GetCertType()
    {
        return certType;
    }

    inline void CertificateAuthority::SetCertType(CertificateType certType)
    {
        this->certType = certType;
    }

    inline std::string CertificateAuthority::GetCertificateFileName()
    {
        return certificateFileName;
    }

    inline void CertificateAuthority::SetCertificateFileName(std::string &fileName)
    {
        this->certificateFileName = fileName;
    }

    inline void CertificateAuthority::SetCRL(CRL crl)
    {
        this->crl = crl;
    }

    inline CRL CertificateAuthority::GetCRL()
    {
        return this->crl;
    }
};

#endif //#ifndef CAU_H
