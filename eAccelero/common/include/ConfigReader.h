/* 
 * File:   ConfigReader.h
 * Author: adey
 *
 * Created on August 20, 2012, 3:43 PM
 */

#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>


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

#endif  /* CONFIGREADER_H */

