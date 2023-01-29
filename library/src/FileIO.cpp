#include "FileIO.h"

int readFile()
{
    std::ifstream ifile("file.txt");
    int number;

    // using exception
    try
    {
        if(ifile.is_open())
        {
            ifile >> number;
            if(number!=NULL)
                std::cout<<"Your highest score: "<< number<<'\n';
                ifile.close();
        } 
        else
        {
            throw std::runtime_error( "Error occured while opening the file!" );
        }
        
    }
    catch(std::runtime_error& e)
    {
        std::cout<<"Error! Cannot open the file.";
    }
        return number;
}

void writeToFile()
{
    State state;
    std::ofstream ifile("file.txt");
    try
    {
        if(ifile.is_open())
        {
            if(state.get_score()>readFile())
            {
                ifile << state.get_score();
                ifile.close();
            }
        } 
        else
        {
            throw std::runtime_error( "Error occured while opening the file!" );
        }
    }
    catch(std::runtime_error& e)
    {
        std::cout<<"Error! Cannot open the file.";
    }
}
