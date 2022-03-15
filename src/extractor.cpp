#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "extractor.h"


int main(int argc, char* argv[])
{
    //readin CLI's
    std::string filename = argv[1];
    int beginX; 
    int beginY; 
    int endX;
    int endY;
    int frameWidth;
    int frameHeight;
    
    //amount of operations to be done stored in vector with corresponding file name
    std::vector<std::vector<std::string>> writeOptions;
    int writes = 0;

    for (size_t i = 2; i < argc; i++)
    {
        if(std::string(argv[i]) == "-t")
        {
            beginX = stoi(std::string(argv[i+1]));
            beginY = stoi(std::string(argv[i+2]));
            endX = stoi(std::string(argv[i+3]));
            endY = stoi(std::string(argv[i+4]));
            
        }
        if(std::string(argv[i]) == "-s")
        {
            
            frameWidth = stoi(std::string(argv[i+1]));
            frameHeight = stoi(std::string(argv[i+2]));
            
        }
        if (std::string(argv[i]) == "-w")
        { 
            std::string operation = argv[i + 1];
            std::string writeFileName = argv[i + 2];
            std::vector<std::string> temp = {operation, writeFileName};
            writeOptions.push_back(temp);
           
        }
    }
    
    //begin reading in data from file
    std::string line = "";
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios_base::skipws);
    std::stringstream ss;
    int width,height;

    getline(file,line);
    if(line.compare("P5") != 0) 
    {
        std::cerr << "error" << std::endl;
    }
    else
    {
        getline(file,line);
        while(line[0]=='#' ){getline(file,line);}
        ss << line;
        ss >> width >> height;
        int length = width*height;
        getline(file >> std::ws,line);
        unsigned char ** fileRead = new unsigned char *[height]; // array to store all pixel data
        for (size_t i = 0; i < height; i++)
        {
            fileRead[i] = new unsigned char[width];
            for (size_t j = 0; j < width; j++)
            {
                file >> fileRead[i][j];
            }
        }
        file.close();
        std::cout << "here" << std::endl;

        //iterate over options
        for (size_t i = 0; i < writeOptions.size(); i++)
        {
            RBLCAM001::FrameSequence fs;
            fs.setHeight(frameHeight);
            fs.setWidth(frameWidth);
            //itereate over a trajectory from start to finish and send a frame to the FrameSequence vector each time
            int x,y=beginX,beginY;
            while(x!=endX&& y!=endY)
            {
                fs.insertFrame(RBLCAM001::image(x, y, frameWidth, frameHeight, fileRead));
                if(x<endX){x++;}
                if(y<endY){y++;}
                if(endX<x){x--;}
                if(endY<y){y--;}
            }
            fs.doOperation(writeOptions[i][0], writeOptions[i][1]);
        }
        //delete array with large pixel data
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                fileRead[i][j] = 0;
            }
            delete fileRead[i];
        }
        delete fileRead;
    }
}

//extracts a single frame with desired ranges from the large pixel array
unsigned char** RBLCAM001::image(int beginX, int beginY, int width, int height, unsigned char ** bigFrame)
{
    unsigned char** frame = new unsigned char*[height];
    for (size_t i = 0; i < height; i++)
    {
        frame[i] = new unsigned char[width];
        for (size_t j = 0; j < width; j++)
        {
            frame[i][j] = bigFrame[beginY+i][beginX+j];
        }
    }
    return frame;    
}