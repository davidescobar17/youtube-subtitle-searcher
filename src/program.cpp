#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "../include/allMatches.hpp"
#include "../include/video.hpp"
#include "../include/videoMatch.hpp"
#include "../include/utility.hpp"

namespace fs = std::experimental::filesystem;

using std::cin;
using std::cout;
using std::endl;

void parseFile(std::string file, std::string target, allMatches *a) {
    
    std::string line;
    std::ifstream infile(file);
    std::string time;
    std::vector<std::string> passage;
    bool found = false;
    bool foundOnce = false;
    int foundCount = 0;

    std::vector<videoMatch> matches;

    while (std::getline(infile, line)) {

        std::istringstream iss(line);

        line = removeTags(line);

        // parse the line, it can be time or the text (or blank line)
        if (isTime(line)) {
            
            time = line;

            // if found target, print the time and the passage
            if (found) {

                // create new match item
                videoMatch match(time, passage);
                matches.push_back(match);
                foundOnce = true;
                foundCount++;
            }
            
            found = false;
            passage.clear();
        }
        else {

            if (containsTarget(line, target)) {

                found = true;
            }

            // add to passage for this time
            passage.push_back(line);
        }
    }

    if (foundCount > 0) {
        // this gets filled with all matches, then stored to the results
        video newVideo(file, matches);
        a->addVideo(newVideo);
    }
}

void prompt(allMatches *a);
void search(allMatches *a);

void prompt(allMatches *a) {

    std::string option = "";

    while(true) {

          // calls the method that lists out the times and passages
        cout << a->getTotalMatches() << " matches were found across " << a->getTotalVideos() << " video(s):" << endl << endl;
        a->listVideoNames();
        cout << "(Results will output to out.txt, until option is made)" << endl;
        cout << "1: View all" << endl;
        cout << "2: For specific video" << endl;
        cout << "3: For videos with title containing a specified phrase" << endl;
        cout << "4: Search again" << endl;
        cout << "q: Quit" << endl;
        cout << endl;

        getline(std::cin, option); // note, cin >> only for int values

        // restore output to terminal
        std::ofstream out("out.txt");
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf

        if (option == "1") {

            // redirect output to file
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            a->listAllResults();
            std::cout.rdbuf(coutbuf); //reset to standard output again
        }
        else if (option == "2") {

            int videoOption;

            cout << "Enter the number of the video you want to view:" << endl;

            cin >> videoOption;

            cin.ignore();
            
            // redirect output to file
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            a->listForVideo(videoOption);
            std::cout.rdbuf(coutbuf); //reset to standard output again
        }
        else if (option == "3") {

            std::string term;

            cout << "Enter the video phrase of videos to search for:" << endl;
            std::getline(cin, term);

            // redirect output to file
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
            a->listForVideoTerm(term);
            std::cout.rdbuf(coutbuf); //reset to standard output again
        }
        else if (option == "4") {

            std::cout.rdbuf(coutbuf); //reset to standard output again

            a->reset();
            search(a);
        }
        else if (option == "q") {

            exit(0);
        }
    }
}

void search(allMatches *a) {

    std::string inputFolder = "input";

    std::string path = fs::current_path().string() + "/" + inputFolder;
    
    // cout << path << endl;
    std::string ext(".vtt");

    std::string toFind = "";
    std::string termInTitle = "";

    // ask the user what they are searching for in the subtitles
    cout << ">>" << path << endl;
    cout << "Enter phrase to search: ";
    getline(cin, toFind);

    cout << "Enter phrase in title to filter search (leave empty to search all videos): ";
    getline(cin, termInTitle);

    cout << "Output result to file? (add this option)" << endl;

    for (auto &p : fs::recursive_directory_iterator(path)) {

        if (videoTitleContainsTarget(p.path().stem().string(), termInTitle) || termInTitle == "") {

            if (p.path().extension() == ext) {

                // std::cout << p.path().stem().string() << '\n';

                // parse the contents
                parseFile(inputFolder + "/" + p.path().stem().string() + ext, toFind, a);
            }
        }
    }

    cout << endl;
    prompt(a);
}

int main() {
    
    allMatches* results = new allMatches();

    search(results);

    return 0;
}