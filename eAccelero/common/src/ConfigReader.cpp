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





