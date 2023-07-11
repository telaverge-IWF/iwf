/* ********************************-*-C-*-************************************
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


#ifndef CONFIGREADER_H
#define	CONFIGREADER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>

#if 0
#ifdef CACHE_SERVICE_STANDALONE_TESTING
#define DRE_TRACE_CRITICAL(x)   printf x
#define DRE_TRACE_DEBUG(x)      printf x
#else
#include "dre_trace.h"
#endif

#endif

std::istream& operator >>(std::istream& is, std::map<std::string, std::string>& configMap);
std::ostream& operator <<(std::ostream& os, const std::map<std::string, std::string>& configMap);

// The configuration file is expected to be a listing of key-value pairs,
// one per line.
//
// The key is separated from the value by an equal sign '='.
// A line is a comment if the first non-whitespace character is a '#' or ';'.
//
// The configuration file does not allow a trailing comment.
//

class ConfigReader {
public:

    // The filename consists of the complete path to the file.

    ConfigReader(const char* filename, bool &isConfigFileOpenSuccessful) {
        std::ifstream ifs(filename, std::ifstream::in);

        if (ifs.fail()) {
            std::cout << "\nCould not open configuration file for reading \n" << std::endl;
            isConfigFileOpenSuccessful = false; 
        } else {
            std::cout << "\nOpened configuration file for reading \n" << std::endl;
            ifs >> m_objConfigMap;
            isConfigFileOpenSuccessful = true;
        }

        ifs.close();
    }

    // Get the STL map object containing the configuration items,
    // read from the configuration file.

    std::map<std::string, std::string>& getConfigMap() {
        return m_objConfigMap;
    }

    friend std::istream& operator >>(std::istream& is, std::map<std::string, std::string>& configMap);
    friend std::ostream& operator <<(std::ostream& os, const std::map<std::string, std::string>& configMap);

private:
    std::map<std::string, std::string> m_objConfigMap;
};

#endif	/* CONFIGREADER_H */

