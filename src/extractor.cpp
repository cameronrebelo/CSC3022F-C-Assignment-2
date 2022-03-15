#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "extractor.h"


int main(int argc, char* argv[])
{
    std::cout << "start" << std::endl;
    std::string filename = argv[1];
    int beginX; 
    int beginY; 
    int endX;
    int endY;
    int frameWidth;
    int frameHeight;
    
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
    std::cout << "cli ok" << std::endl;

    // std::cout << filename << std::endl;
    // std::cout << beginX << std::endl;
    // std::cout << beginY << std::endl;
    // std::cout << endX << std::endl;
    // std::cout << endY << std::endl;
    // std::cout << frameHeight << std::endl;
    // std::cout << frameWidth << std::endl;

    // for (size_t i = 0; i < writeOptions.size(); ++i)
    // {
    //     std::cout << writeOptions[i][0] << std::endl;
    //     std::cout << writeOptions[i][1] << std::endl;
    // }
    

    std::string line = "";
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios_base::skipws);
    std::stringstream ss;
    int width,height;

    unsigned char *** pixelPtr;

    getline(file,line);
    // std::cout << line << std::endl;
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
        unsigned char ** fileRead = new unsigned char *[height];
        // file.read(reinterpret_cast<char *>(fileRead), length);

        // ss << file.rdbuf();          //https://stackoverflow.com/questions/8126815/how-to-read-in-data-from-a-pgm-file-in-c
        for (size_t i = 0; i < height; i++)
        {
            fileRead[i] = new unsigned char[width];
            for (size_t j = 0; j < width; j++)
            {
                file >> fileRead[i][j];
            }
        }
        file.close();

        for (size_t i = 0; i < writeOptions.size(); i++)
        {

            std::cout << writeOptions.size() << std::endl;
            RBLCAM001::FrameSequence fs;
            fs.setHeight(frameHeight);
            fs.setWidth(frameWidth);
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
            // for (size_t i = beginX; i < endX; i++)
            // {
            //     fs.insertFrame(RBLCAM001::image(i, i, frameWidth, frameHeight, fileRead));
            //     // std::cout << "adding" << std::endl;
            // }
        }
        

        
    }
    
}

unsigned char** RBLCAM001::image(int beginX, int beginY, int width, int height, unsigned char ** bigFrame)
{
    unsigned char** frame = new unsigned char*[height];
    int x,y;
    // std::cout << beginX << std::endl;
    // std::cout << beginY << std::endl;
    // std::cout << width << std::endl;
    // std::cout << height << std::endl;
    // std::stringstream ss;

    for (size_t i = 0; i < height; i++)
    {
        frame[i] = new unsigned char[width];
        // ss << i;
        // std::string t;
        // ss >> t;
        // std::cout << i << std::endl;

        for (size_t j = 0; j < width; j++)
        {
            // std::cout << j << std::endl;
            // std::cout << bigFrame[i][j] << std::endl;
            // std::cout << "j:"+j << std::endl;
            frame[i][j] = bigFrame[beginY+i][beginX+j];
            //  std::cout << int(frame[i][j]) << std::endl;

            // x++;
        }
        // y++;
        // std::cout << "success" << std::endl;
    }
    return frame;    
}