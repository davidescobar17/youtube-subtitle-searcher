#ifndef UTILITY_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define UTILITY_H

bool isTime(std::string line);

bool containsTarget(std::string line, std::string target);

std::string removeTags(std::string s);

std::string toLowerString(std::string s);

// for phrases, needs to be whole word match
bool videoTitleContainsTarget(std::string line, std::string target);

#endif /*UTILITY_H*/