#include <utility>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "extractor.h"


// Constructor and Destructor
RBLCAM001::FrameSequence::FrameSequence(void)
{
    width = 0;
    height = 0;
}
RBLCAM001::FrameSequence::~FrameSequence()
{
    for (size_t i = 0; i < imageSequence.size(); i++)
    {
        if (imageSequence[i] != nullptr)
        {
            delete imageSequence[i];
            // go deeper
        }
    }
}

// Utilities
void RBLCAM001::FrameSequence::insertFrame(unsigned char **frame)
{
    imageSequence.push_back(frame);
}
void RBLCAM001::FrameSequence::setHeight(int h)
{
    height = h;
}
void RBLCAM001::FrameSequence::setWidth(int w)
{
    width = w;
    std::cout << width << std::endl;
}

void RBLCAM001::FrameSequence::doOperation(std::string operation, std::string fileName)
{
    std::cout << "doing op" + operation << std::endl;

    if (operation == "none")
    {
        std::cout << "doing op: none" << std::endl;
    }
    else if (operation == "invert")
    {
        std::cout << "doing op: invert" << std::endl;
        invert();
    }
    else if (operation == "reverse")
    {
        std::cout << "doing op: reverse" << std::endl;
        isReversed = true;
    }
    else if (operation == "reinvert")
    {
        std::cout << "doing op: reinvert" << std::endl;
        isReversed = true;
        invert();
    }
    writeVector(fileName);
}

void RBLCAM001::FrameSequence::invert()
{
    std::cout << "inverting" << std::endl;
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
    std::cout << "done inverting" << std::endl;
}

void RBLCAM001::FrameSequence::writeVector(std::string filename)
{
    int count = 0;
    std::cout << "writing" << std::endl;
    if (isReversed)
    {
        for (size_t i = imageSequence.size() - 1; i > -1; i--)
        {
            char buffer[100];
            std::string fileNumber;
            std::stringstream ss;
            ;
            std::string temp;
            temp = sprintf(buffer, "%04d", count);
            ss << buffer;
            ss >> fileNumber;
            std::string fileFinal = filename + fileNumber + ".pgm";
            std::ofstream out(fileFinal, std::ios::binary);
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
        std::cout << "else" << std::endl;
        for (size_t i = 0; i < imageSequence.size(); i++)
        {
            char buffer[100];

            // std::cout <<"fileopened" << std::endl;
            std::string fileNumber;
            std::stringstream ss;
            ;
            std::string temp;
            temp = sprintf(buffer, "%04d", count);
            ss << buffer;
            ss >> fileNumber;
            std::string fileFinal = filename + fileNumber + ".pgm";
            std::ofstream out(fileFinal, std::ios::binary);

            out << "P5" << std::endl;
            out << "#RBLCAM001 Extractor" << std::endl;
            out << width << " " << height << std::endl;
            out << "255" << std::endl;
            for (size_t j = 0; j < height; j++)
            {
                for (size_t k = 0; k < width; k++)
                {
                    // std::cout <<j<<" "<< k<< " in loop" << std::endl;

                    out << imageSequence[i][j][k];
                }
            }
            out.close();
            count++;
        }
    }
}

std::string RBLCAM001::FrameSequence::toString()
{
    std::string temp = "";
    for (size_t i = 0; i < imageSequence.size(); i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            for (size_t k = 0; k < width; k++)
            {
                temp += imageSequence[i][j][k] + "\n";
            }
        }
    }
    return temp;
}
