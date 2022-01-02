#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../include/utility.hpp"

using std::cout;
using std::endl;

// stores all matches and global counts, let's user view these

bool isTime(std::string line){
    
    if (line.find("-->") != std::string::npos){
        // cout << "time found" << endl;
        return true;
    }

    return false;
}

// for phrases, needs to be whole word match
bool containsTarget(std::string line, std::string target){

    bool result = false;
    
    line = toLowerString(line);
    target = toLowerString(target);

    // Note: needed because /b is backspace character
    std::regex e("\\b" + target + "\\b");
    std::smatch match;

    result = std::regex_search (line,match,e);

    return result;
}

std::string removeTags(std::string s){

    std::regex e("<.*?>");
    std::string result;

    result = std::regex_replace (s,e,"");

    return result;
}

std::string toLowerString(std::string s){

    for(int i = 0; i < s.size(); i++){
        
        s[i] = std::tolower(s[i]);
    }

    return s;
}

bool videoTitleContainsTarget(std::string line, std::string target){
    if (toLowerString(line).find(toLowerString(target)) != std::string::npos){

        return true;
    }
    return false;
}