#include <utility>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "extractor.h"


// Constructor
RBLCAM001::FrameSequence::FrameSequence()
{
    width = 0;
    height = 0;
    isReversed=false;
}
//Destructor
RBLCAM001::FrameSequence::~FrameSequence()
{
    for (size_t i = 0; i < imageSequence.size(); i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            for (size_t k = 0; k < width; k++)
            {
                if (imageSequence[i] != nullptr)
                {
                    imageSequence[i][j][k] = 0;
                }
            }
            delete imageSequence[i][j];
        }
        delete imageSequence[i];
    }
}

// Utilities

//Function to insert a frame into the vector
void RBLCAM001::FrameSequence::insertFrame(unsigned char **frame)
{
    imageSequence.push_back(frame);
}

//setters for height and width
void RBLCAM001::FrameSequence::setHeight(int h){height = h;}
void RBLCAM001::FrameSequence::setWidth(int w){width = w;}

//Function to choose which operation to be executed on the frames
void RBLCAM001::FrameSequence::doOperation(std::string operation, std::string fileName)
{
    if (operation == "none"){}
    else if (operation == "invert"){invert();}
    else if (operation == "reverse"){isReversed = true;}
    else if (operation == "reinvert"){invert();}
    writeVector(fileName);
}

//inverts the pixel data
void RBLCAM001::FrameSequence::invert()
{
    for (size_t i = 0; i < imageSequence.size(); i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            for (size_t k = 0; k < width; k++)
            {
                int temp = int(imageSequence[i][j][k]);
                imageSequence[i][j][k] = char(255 - temp);
            }
        }
    }
}

//writes the frame data to output pgm files with the supplied filename in order
void RBLCAM001::FrameSequence::writeVector(std::string filename)
{
    int count = 0;
    if (isReversed)
    {
        for (size_t i = imageSequence.size() - 1; i > -1; i--)
        {
            char buffer[100];
            std::string fileNumber;
            std::stringstream ss;
            std::string temp;
            temp = sprintf(buffer, "%04d", count);
            ss << buffer;
            ss >> fileNumber;
            
            std::string fileFinal = filename + fileNumber + ".pgm";
            std::ofstream out(fileFinal, std::ios::binary);
            //begin writing the file
            out << "P5" << std::endl;
            out << "#RBLCAM001 Extractor" << std::endl;
            out << width << "  " << height << std::endl;
            out << "255" << std::endl;
            for (size_t j = 0; j < height; j++)
            {
                for (size_t k = 0; k < width; k++)
                {
                    out << imageSequence[i][j][k];
                }
            }
            out.close();
            count++;
        }
    }
    else
    {
        for (size_t i = 0; i < imageSequence.size(); i++)
        {
            char buffer[100];
            std::string fileNumber;
            std::stringstream ss;
            std::string temp;
            temp = sprintf(buffer, "%04d", count);
            ss << buffer;
            ss >> fileNumber;
            std::string fileFinal = filename + fileNumber + ".pgm";
            std::ofstream out(fileFinal, std::ios::binary);
            //begin writing the file
            out << "P5" << std::endl;
            out << "#RBLCAM001 Extractor" << std::endl;
            out << width << " " << height << std::endl;
            out << "255" << std::endl;
            for (size_t j = 0; j < height; j++)
            {
                for (size_t k = 0; k < width; k++)
                {
                    out << imageSequence[i][j][k];
                }
            }
            out.close();
            count++;
        }
    }
}
