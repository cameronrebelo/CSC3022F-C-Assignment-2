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
            i+=5;
        }
        if(std::string(argv[i]) == "-s")
        {
            
            frameWidth = stoi(std::string(argv[i+1]));
            frameHeight = stoi(std::string(argv[i+2]));
            i += 3;
        }
        if (std::string(argv[i]) == "-w")
        { 
            std::string operation = argv[i + 1];
            std::string writeFileName = argv[i + 2];
            std::vector<std::string> temp = {operation, writeFileName};
            writeOptions.push_back(temp);
            i += 3;
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
        // pixelPtr = & fileRead;
        RBLCAM001::FrameSequence fs;
        for (size_t i = beginX; i < endX; i++)
        {
            
            fs.insertFrame(RBLCAM001::image(i,i,frameWidth,frameHeight,fileRead));
            std::cout << "adding" << std::endl;
        }
    }
    file.close();
}

unsigned char** RBLCAM001::image(int beginX, int beginY, int width, int height, unsigned char * & array)
{
    unsigned char** temp;
    int x,y;
    std::cout << beginX << std::endl;
    std::cout << beginY << std::endl;
    std::cout << width << std::endl;
    std::cout << height << std::endl;


    for (size_t i = beginY; i < (beginY+height); i++)
    {
        // std::cout << "i:"+i << std::endl;
        for (size_t j = beginX; j < (beginX+width); j++)
        {
            std::cout << array[i*width+j] << std::endl;
            // std::cout << "j:"+j << std::endl;


            // temp[x][y] = array[i*width+j];
            x++;
        }
        y++;
        // std::cout << "success" << std::endl;
    }
    return temp;    
}

/*
void addUnrev(unsigned char**&frame)
    {
        int newX = x1;
        int newY = y1;

        int i_count = 0;
        int j_count = 0;

        int num = 1;
        string fname = "sequence2";

        //frame = new unsigned char * [frameH];

        while((newX+frameH)<=height && ((newY+frameW)<=width) && newX<x2 && newY<y2)
        {
            i_count = 0;
            j_count = 0;
            //i_count & j_count used for the new frame
            for(int i = 0; i<height; i++)
            {
                frame[i_count] = new unsigned char[frameW];
                for(int j = 0; j<width; j++)
                {
                    if(i>=newX && i<newX+frameH)
                    {
                        if(j>=newY && j<newY+frameW)
                        {
                            if(n==true)
                            {
                                frame[i_count][j_count] = pixel_array[i][j];
                            }
                            else if(in== true)
                            {
                                frame[i_count][j_count] = 255-(pixel_array[i][j]);
                            }

                            j_count++;
                        }
                        else if (j>=newY+frameW)
                        {
                            i_count++;
                            j_count = 0;
                            break;
                        }
                    }
                }
                if (i>=newX+frameH)
                {
                    break;
                }
            }
            imageSequence.push_back(frame);
            newX++;
            newY++;

            printSingleFrame(num, frame);
            num++;
        }
    }
*/