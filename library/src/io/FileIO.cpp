#include "io/FileIO.h"

#include <iostream>
#include <cstdio>
#include <fstream>

int load_highscore(std::string path)
{
    std::ifstream ifile(path);
    int number = -1;

    // using exception
    try {
        if(!ifile.is_open())
            throw std::runtime_error( "Error occured while opening the file!" );
        
        ifile >> number;
    }
    catch(std::runtime_error& e) {
        //std::cout<<"Error! Cannot open the file.";
    }

    ifile.close();
    return number;
}

int save_highscore(std::string path, int in)
{
    std::ofstream ifile(path);
    int out = 0;
    try {
        if(!ifile.is_open())
            throw std::runtime_error( "Error occured while opening the file!" );
        ifile << in;
    }
    catch(std::runtime_error& e) {
        //std::cout<<"Error! Cannot open the file.";
        out = -1;
    }
    ifile.close();
    return out;
}
