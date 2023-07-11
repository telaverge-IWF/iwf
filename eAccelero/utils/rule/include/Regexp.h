/*********************************-*-H-*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
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
 ****************************************************************************/
#ifndef __RegExp_h__
#define __RegExp_h__

#include <pcre.h>
#include <string>

#include "Exception.h"

/**
 * @file Regexp.h
 * 
 * Regexp provides a simple C++ wrapper over the PCRE library, to be used for
 * the expression parsing and also a regex expression within an expression tree
 */

namespace eAccelero
{

/**
 * This structure is used ot extract the PCRE output and store it in a vector
 * PCRE only proivdes the match in the form offsets in the original string.
 */
struct MatchElement
{
    
    /**
     * @brief Empty constructor, does nothing
     */
    MatchElement()
        : start(),
          end()
    {
    }
    
    /**
     * @brief Forms the match string from the offsets provided by PCRE
     * @param st    start offset of the match string in the original string
     * @param en    end offset of the match string in the original string
     * @param orgStr    the string which is being searched
     */
    MatchElement(int st, int en, const char *orgStr)
        : start(st),
          end(en),
          matchStr(orgStr + st, en - st)
    {
    }
    
    /**
     * @brief Copy constructor
     * @param rhs  Right hand side object
     */
    MatchElement(const MatchElement& rhs)
        : start(rhs.start),
          end(rhs.end),
          matchStr(rhs.matchStr)
    {
    }
    
    /**
     * @brief Assignement operator
     * @param rhs   Rhight hand side object
     */
    MatchElement& operator=(const MatchElement& rhs)
    {
        start = rhs.start;
        end   = rhs.end;
        matchStr = rhs.matchStr;
        return *this;
    }

    int start;
    int end;
    std::string matchStr;
};

/** A list of matched elements in the search string */
typedef std::vector<MatchElement> MatchList;

/**
 * @class Regexp
 * @brief Simple C++ wrapper over the PCRE regular expression library
 * 
 * This needs the packages pcre, pcre-devel to be installed in the 
 * development setup.
 */
class Regexp
{
 public:
    /** Maximum regular expression matches possible*/
    static const int RE_MATCH_VEC_SZ = 64;

    /**
     * @brief Construct a regular expression object
     * @param regex  Regular expression string
     * 
     * For more information on regular expressions do a `man pcrepattern`.
     * The link http://perldoc.perl.org/perlre.html also has more information
     * on regular expressions.
     * 
     *  - [A-Za-z]+ is a regular expression for an alphabet basedword
     *  - "intelli.*\\.com" will match "intellinet.com" and also 
     *    "intelligent.xyz.abc.com"
     *  - "^12345.*" will match all numbers starting with 12345
     */
    Regexp(const char *regex)
        : m_re(NULL),
          m_reExtra(NULL)
    {
        int errOff = 0;
        const char *err = NULL;
        
        // convert the regualr expression into a DFA or NFA
        m_re = pcre_compile(regex, 0, &err, &errOff, NULL);
        if (m_re == NULL)
        {
            throw RuntimeException("Regex Compile Failed");
        }

        // More opmization
        m_reExtra = pcre_study(m_re, 0, &err);
        if (err != NULL)
        {
            throw RuntimeException("Pcre study failed");
        }
    }
    
    /**
     * @brief Destructor, destroys the PCRE objects maintained
     */
    ~Regexp()
    {
        // cleanup the pcre data
        if (m_reExtra) pcre_free(m_reExtra);
        if (m_re) pcre_free(m_re);
    }

    /**
     * @brief Given the string, find a match with the regular expression
     * @param [in]  str   Search string on which a regex match to be performed
     * @param [in]  len   length of the search string
     * @param [out] list  list of matched string groups with their offsets in
     *                    in the original string
     * @return Number of string groups matched
     */
    int Match(const char *str, int len, MatchList &list)
    {
        int matchVec[RE_MATCH_VEC_SZ];
        int ret;
        list.clear();
        ret = pcre_exec(m_re, m_reExtra, str, len, 0, 0, matchVec, RE_MATCH_VEC_SZ);
        if (ret < 0)
        {
            return ret;
        }
    
        for (int i = 0; i < ret; i++)
        {
            list.push_back(MatchElement(matchVec[2*i], matchVec[2*i+1], str));
        }
        
        return ret;
    }
    
    /**
     * @brief Does a simple match and checks if a match if found.
     * @param str   string to be matched with the regular expression
     * @param len   length of the search string
     * @return A non zero value if a match is found otherwise zero
     * 
     * Does not return the matched string. Just returns if a match is found
     * or not.
     */
    int Match(const char *str, int len)
    {
        int matchVec[RE_MATCH_VEC_SZ];
        int ret = pcre_exec(m_re, m_reExtra, str, len, 0, 0, matchVec, RE_MATCH_VEC_SZ);
        if (ret <= 0)
        {
            return ret;
        }
        return ret;
    }
    /**
     * @brief Given the string, find a match with the regular expression
     * @param str
     * @return A non zero value if a match is found otherwise zero
     * 
     * Does not return the matched string. Just returns if a match is found
     * or not.
     */
    int Match(std::string &str)
    {
        return this->Match(str.c_str(), str.size());
    }

    /**
     * @brief Given the string, find a full match
     * @param str
     * @param len
     * @return 
     * 
     * A partial match will return zero. For example if the regular expression is 
     * "1234??" it will match "123456", but will not match "1234567", where as the
     * other Match() methods will match both.
     */
    int FullMatch(const char *str, int len)
    {
        int matchVec[RE_MATCH_VEC_SZ];
        int ret = pcre_exec(m_re, m_reExtra, str, len, 0, PCRE_PARTIAL, matchVec, RE_MATCH_VEC_SZ);
        if (ret < 0)
        {
            return ret;
        }
        return ret;
    }

 protected:
    pcre* m_re;             /**< Pointer to the pcre object */
    pcre_extra* m_reExtra;  /**< Pointer to the pcre extra object */
};

} // namespace eAccelero

#endif // __RegExp_h__
