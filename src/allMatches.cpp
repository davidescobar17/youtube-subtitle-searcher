#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../include/video.hpp"
#include "../include/allMatches.hpp"
#include "../include/utility.hpp"

// for brevity
namespace fs = std::experimental::filesystem;

using std::cout;
using std::endl;

allMatches::allMatches() {

    totalMatches = 0;
}

void allMatches::reset() {

    videos.clear();
    totalVideos = 0;
    totalMatches = 0;
}

void allMatches::addVideo(video v) {

    videos.push_back(v);
    totalVideos++;
    totalMatches = totalMatches + v.getMatchesInVideo();
}

void allMatches::listAllResults() {

    for (auto x: videos) { 

        x.printVideoMatches();
    }
}

void allMatches::listVideoNames() {

    int count = 1;

    for (auto x: videos) { 

        cout << "video " << count << ": " << x.getName() << endl;

        count++;
    }

    cout << endl;
}

void allMatches::listForVideo(int index) {

    if (index >= 0 && index <= totalVideos) {

        videos[index - 1].printVideoMatches();
    }
    else {

        cout << "Invalid input" << endl;
    }
}

void allMatches::listForVideoTerm(std::string term) {

    for (auto x: videos) { 

        if(videoTitleContainsTarget(x.getName(), term)) {

            x.printVideoMatches();
        }
    }
}

int allMatches::getTotalMatches() {

    return totalMatches;
}

int allMatches::getTotalVideos() {

    return totalVideos;
}