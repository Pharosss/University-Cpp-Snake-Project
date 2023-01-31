#include "io/FileIO.h"

#include <iostream>
#include <cstdio>
#include <fstream>

int Files::load_highscore(std::string path)
{
    std::ifstream ifile(path);
    int number = -1;

    try {
        if(!ifile.is_open())
            throw std::runtime_error( "Error occured while opening the file!" );
        
        ifile >> number;
    }
    catch(std::runtime_error& e) {
        
    }

    ifile.close();
    return number;
}

int Files::save_highscore(std::string path, int in)
{
    std::ofstream ifile(path);
    int out = 0;
    try {
        if(!ifile.is_open())
            throw std::runtime_error( "Error occured while opening the file!" );
        ifile << in;
    }
    catch(std::runtime_error& e) {
        int out = -1;
    }
    ifile.close();
    return out;
}
