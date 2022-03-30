#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../include/video.hpp"

// for brevity
namespace fs = std::experimental::filesystem;

video::video(std::string n, std::vector<videoMatch> v) {

    vidName = n;
    vidMatches = v;
}

std::string video::getName() {
    return vidName;
}

int video::getMatchesInVideo() {
    return vidMatches.size();
}

void video::printVideoMatches() {

    int current = 1;
    int total = getMatchesInVideo();

    std::cout << getName() << std::endl;

    // calls the method that lists out the times and passages
    for (auto x: vidMatches) { 
        
        std::cout << current << "/" << total << std::endl;
        x.printPassage(vidName);
        current++;
    }
}