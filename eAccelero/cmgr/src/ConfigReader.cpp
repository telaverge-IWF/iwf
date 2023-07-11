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


#include "ConfigReader.h"

std::istream& operator >>(std::istream& is, std::map<std::string, std::string>& configMap) {
    std::string str, key, value;

    // For each (key, value) pair in the file
    while (std::getline(is, str)) {
        std::string::size_type begin = str.find_first_not_of(" \f\t\v");

        // Skip blank lines
        if (begin == std::string::npos) continue;

        // Skip commentary
        if (std::string("#;").find(str[begin]) != std::string::npos) continue;

        // Extract the key value
        std::string::size_type end = str.find('=', begin);
        key = str.substr(begin, end - begin);

        // (No leading or trailing whitespace allowed)
        key.erase(key.find_last_not_of(" \f\t\v") + 1);

        // No blank keys allowed
        if (key.empty()) continue;

        // Extract the value (no leading or trailing whitespace allowed)
        begin = str.find_first_not_of(" \f\n\r\t\v", end + 1);
        end = str.find_last_not_of(" \f\n\r\t\v") + 1;

        value = str.substr(begin, end - begin);

        // Insert the properly extracted (key, value) pair into the map
        configMap[key] = value;
    }

    return is;
}

std::ostream& operator <<(std::ostream& os, const std::map<std::string, std::string>& configMap) {
    std::map<std::string, std::string>::const_iterator iter;

    for (iter = configMap.begin(); iter != configMap.end(); iter++)
        os << iter->first << " = " << iter->second << std::endl;

    return os;
}

// TBD

bool isKey(const std::string& str) {
    return false;
}



