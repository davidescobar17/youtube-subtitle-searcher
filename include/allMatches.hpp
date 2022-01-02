#ifndef ALLMATCHES_H
#define ALLMATCHES_H

#include "../include/video.hpp"

class allMatches{

    private:
        std::vector<video> videos;
        int totalVideos;
        int totalMatches;

    public:
        allMatches();

        void reset();

        void addVideo(video v);

        void listAllResults();

        void listVideoNames();

        void listForVideo(int index);

        void listForVideoTerm(std::string term);

        int getTotalVideos();

        int getTotalMatches();
};

#endif /*ALLMATCHES_H*/