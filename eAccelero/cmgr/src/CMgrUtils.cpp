/*******************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************/

/*
 * FILE:   CMgrUtils.cpp
 * Author: Hemanth
 *
 * Created on Dec 03, 2014, 10:00 PM
 */


#include <CMgrUtils.h>

using namespace std;

int updatePattern(string& subject, const string& search, const string& replace)
{
    size_t pos = 0;

    try
    {
        while ((pos = subject.find(search, pos)) != string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }
    catch(...)
    {
        perror("Exception on updatePattern().");
        return -1;
    }

    return 0;
}

