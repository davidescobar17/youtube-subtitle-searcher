#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../include/videoMatch.hpp"

// for brevity
namespace fs = std::experimental::filesystem;

int extractTime(std::string str){

    int h, m, s = 0;
    int seconds = 0;

    std::regex e("^[0-9]{2}:[0-9]{2}:[0-9]{2}");
    std::smatch match;
    std::regex_search (str,match,e);
    std::string timeString;

    timeString = match[0];

    if (sscanf(timeString.c_str(), "%d:%d:%d", &h, &m, &s) >= 2){
        
        seconds = h *3600 + m*60 + s;
    }

    // move the seconds a bit back (overwise the played clip is slightly too late)
    if (seconds >= 5){

        seconds = seconds - 5;
    }
    else{

        seconds = 0;
    }

    std::cout << "time part is " << timeString << std::endl;

    // get each field
    return seconds;
}

// NOTE: the subtitle file must have the id in the name
std::string extractVidId(std::string str){
    
    std::cout << ">>>*trim out folder at the start*>>>" << str << std::endl;

    std::regex e(".{11}(?=\\.(.*)$)");
    std::smatch match;
    std::regex_search (str,match,e);
    std::string vidId;

    vidId = match[0];

    std::cout << "vid id part is " << vidId << std::endl;

    // get each field
    return vidId;
}

videoMatch::videoMatch(std::string t, std::vector<std::string> p){

    time = t;
    passage = p;
}

void videoMatch::printPassage(std::string vidName){

    std::cout << time << std::endl;

    // get the time (first 12 characters)
    // convert to seconds to add in link (requires playlist link)
    // extract video link from vtt title

    int seconds = extractTime(time);
    std::string vidId = extractVidId(vidName);
    
    std::string url = "https://youtu.be/" + vidId + "?t=" + std::to_string(seconds);

    std::cout << url << std::endl;

    for(auto x: passage){ 

        std::cout << x << std::endl;
    }
}