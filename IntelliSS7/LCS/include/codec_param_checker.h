/////////////////////////////////-*-C++-*-////////////////////////////////////
//                                                                          //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    //
//             Manufactured in the United States of America.                //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                          //
//   This product and related documentation is protected by copyright and   //
//   distributed under licenses restricting its use, copying, distribution  //
//   and decompilation.  No part of this product or related documentation   //
//   may be reproduced in any form by any means without prior written       //
//   authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                          //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CONTRACT: INTERNAL                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: codec_param_checker.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
// LOG: $Log: codec_param_checker.h,v $
// LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
// LOG: Adding Codec files to LCS folder
// LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ITN_UTIL_PARAMETERCHECKER_H
#define ITN_UTIL_PARAMETERCHECKER_H

#include <set>

/**
 * A utility to check for mandatory and optional components in a protocol data
 * unit.
 *
 * This is a template class. Template parameter C is the type of the STL
 * container that contains the components to check for; parameter P is the type
 * of the components; parameters M and O are the sizes of mandatory and optional
 * component id arrays, respectively.
 *
 * The component id type must be defined as P::Type.
 */
template <class C, class P, int M, int O>
class ParameterChecker
{
    typedef typename P::Type Type;

public:
    enum Result
    {
        SUCCESSFUL = 0,
        MISSING_MANDATORY = 1,
        ILLEGAL_PARAMETER = 2
    };

    /**
     * Constucts a checker object for messaegs with both mandatory and optional
     * components.
     *
     * The argument {\tt mandatory} must not be destroyed before this object is
     * destroyed.
     */
    ParameterChecker(Type *mandatory = 0, Type *optional = 0)
    : _mandatory(mandatory)
    {
        for (int i = 0; i < M; ++i) _legal.insert(mandatory[i]);
        for (int j = 0; j < O; ++j) _legal.insert(optional[j]);
    }

    /**
     * Checks whether all mandatory components are present and all present
     * components are permitted.
     */
    Result CheckParameters(const C &table) const
    {
        // check for mandatory components
        for (int i = 0; i < M; ++i)
        {
            if (table.find(_mandatory[i]) == table.end())
            {
                return MISSING_MANDATORY;
            }
        }

        // check for validity of all components
        for (C::const_iterator it = table.begin(); it != table.end(); ++it)
        {
            if (_legal.find(it->first) == _legal.end())
            {
                return ILLEGAL_PARAMETER;
            }
        }

        return SUCCESSFUL;
    }

private:
    Type *_mandatory;
    std::set<Type> _legal;
};

#endif//ITN_UTIL_PARAMETERCHECKER_H
