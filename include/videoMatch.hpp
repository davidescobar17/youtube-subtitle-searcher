#ifndef VIDEOMATCH_H
#define VIDEOMATCH_H

class videoMatch{

    private:
        std::string time;
        std::vector<std::string> passage;
    
    public:

        videoMatch(std::string t, std::vector<std::string> p);

        // print time and matching lines for the searched term
        void printPassage(std::string vidName);
};

#endif /*VIDEOMATCH_H*/