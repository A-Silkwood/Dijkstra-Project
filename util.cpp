#include <iostream>
#include <string>
#include <sstream>

// convert string to integer
int stoi(std::string str) {
    std::stringstream stream(str);
    int num;
    stream >> num;
    return num;
}

// convert string to float
int stof(std::string str) {
    std::stringstream stream(str);
    float num;
    stream >> num;
    return num;
}

// split a string using a deliminator
std::string split(std::string str, char delim, int start, int end) {
    // end and start are invalid or colliding
    if(end <= start) {return "";}

    // indices of delims found
    int startIx;
    int endIx;
    if(start == 0) {startIx = -1;} // begin at start of string

    // search for delims
    int delimCount = 0;
    int ix = 0;
    while(ix < str.length() && delimCount < end) {
        // found delim
        if(str[ix] == delim) {
            delimCount++;
            if(start == delimCount) {startIx = ix;} // start delim found
        }
        ix++;
    }

    if(start > delimCount) {startIx = str.length();} // start delim out of bounds
    if(end > delimCount) {endIx = ix;} else {endIx = ix-1;} // end delim

    // return string split
    return str.substr(startIx + 1, endIx - startIx - 1);
}
