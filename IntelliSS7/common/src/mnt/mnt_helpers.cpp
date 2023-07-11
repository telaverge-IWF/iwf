///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: mnt_helpers.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.4  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/09 20:58:32  hdivoux
// LOG: Port to GNU g++.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_helpers.cpp,v 9.1 2005/03/23 12:53:31 cvsadmin Exp $"

//
//
// mnt_helpers.cpp: MNT helpers implementation.
//
//


#include <mnt_helpers.h>

#include <stdarg.h>

#include <mnt_options.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)


static const size_t MaxBufferSize = 1024;

string 
GetVarArgsString(const char* format, ...)
{
    char buf[MaxBufferSize];

    string result;

    va_list alist;
    va_start(alist, format);
    vsprintf(buf, format, alist);
    result.append(buf);
    va_end(alist);

    // Check for buffer overrun.
    ITS_ASSERT(result.size() < MaxBufferSize);

    return result;
}


string 
ByteValueToString(unsigned char value)
{
    char buffer[32];
    sprintf(buffer, "0x%02X", value);
    return buffer;
}

string 
IntegerValueToString(long value)
{
    char buffer[32];
    sprintf(buffer, "%ld", value);
    return buffer;
}

string 
BooleanValueToString(bool value)
{
    if (value)
    {
        return "true";
    }
    else
    { 
        return "false";
    }
}

string 
StringValueToString(const string& value)
{
    string result;
    result.reserve(value.size() * 2 + 2);

    result.append("\"");

    for (size_t i = 0; i < value.size(); i++)
    {
        switch (value[i])
        {
        case '\n':
            result.append("\\n");
            break;

        case '\r':
            result.append("\\r");
            break;

        case '\t':
            result.append("\\t");
            break;

        case '\v':
            result.append("\\v");
            break;

        case '"':
            result.append("\\\"");
            break;

        case '\'':
            result.append("'");
            break;

        case '\\':
            result.append("\\\\");
            break;

        default:
            result.append(1, value[i]);
        }
    }

    result.append("\"");

    return result;
}

string 
ByteArrayValueToString(const vector<unsigned char>& value)
{
    string result;
    result.reserve(value.size() * 6 + 16);

    result.append("<<");

    for (size_t i = 0; i < value.size(); i++)
    {
        result.append(ByteValueToString(value[i]));

        if (i != value.size() - 1)
        {
            result.append(", ");
        }
    }

    result.append(">>");

    return result;
}

string 
IntegerArrayValueToString(const vector<long>& value)
{
    string result;
    result.reserve(value.size() * 8 + 16);

    result.append("<<");

    for (size_t i = 0; i < value.size(); i++)
    {
        result.append(IntegerValueToString(value[i]));

        if (i != value.size() - 1)
        {
            result.append(", ");
        }
    }

    result.append(">>");

    return result;
}

string 
BooleanArrayValueToString(const vector<bool>& value)
{
    string result;
    result.reserve(value.size() * 7 + 16);

    result.append("<<");

    for (size_t i = 0; i < value.size(); i++)
    {
        result.append(BooleanValueToString(value[i]));

        if (i != value.size() - 1)
        {
            result.append(", ");
        }
    }

    result.append(">>");

    return result;
}

string 
StringArrayValueToString(const vector<string>& value)
{
    string result;
    result.reserve(value.size() * 16 + 16);

    result.append("<<");

    for (size_t i = 0; i < value.size(); i++)
    {
        result.append(StringValueToString(value[i]));

        if (i != value.size() - 1)
        {
            result.append(", ");
        }
    }

    result.append(">>");

    return result;
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


