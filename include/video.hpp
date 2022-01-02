#ifndef VIDEO_H
#define VIDEO_H

#include "videoMatch.hpp"

class video{

    private:
        std::string vidName;
        std::vector<videoMatch> vidMatches;

    public:
        video(std::string n, std::vector<videoMatch> v);
        
        std::string getName();

        int getMatchesInVideo();

        void printVideoMatches();
};

#endif /*VIDEO_H*/