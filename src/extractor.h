#ifndef _EXTRACTOR_H
#define _EXTRACTOR_H

#include <utility>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
namespace RBLCAM001
{

    class FrameSequence
    {
    private:
        std::vector<unsigned char **> imageSequence;
        int width,height;
        bool isReversed;

    public:
        // Constructor and Destructor
        FrameSequence(void){}
        ~FrameSequence()
        {
            for (size_t i = 0; i < imageSequence.size(); i++)
            {
                if (imageSequence[i] != nullptr)
                {
                    delete imageSequence[i];
                    //go deeper
                }
            }
        }

        //Utilities
        void insertFrame(unsigned char ** frame){
            imageSequence.push_back(frame);
        }
        void setHeight(int h){
            height=h;
        }
        void setWidth(int w){
            width=w;
        }

        void doOperation(std::string operation, std::string fileName){
            std::cout <<"doing op" << std::endl;
            if(operation=="none"){
                std::cout <<"doing op: none" << std::endl;
            }
            else if(operation=="invert"){
                std::cout <<"doing op: invert" << std::endl;
                invert();
            }
            else if(operation=="reverse"){
                std::cout <<"doing op: reverse" << std::endl;
                isReversed = true;
            }
            else if(operation=="reinvert"){
                std::cout <<"doing op: reinvert" << std::endl;
                isReversed = true;
                invert();
            }
            writeVector(fileName);
        }

        void invert(){
            for (size_t i = 0; i < imageSequence.size(); i++)
            {
                for (size_t j = 0; j < height; j++)
                {
                    for (size_t k = 0; k < width; k++)
                    {
                        char temp = imageSequence[i][j][k];
                        imageSequence[i][j][k] = char(255 - int(temp));
                    }   
                }
            }
        }

        void reverse(){

        }

        void writeVector(std::string filename)
        {
            if (isReversed)
            {
                for (size_t i = imageSequence.size() - 1; i > -1; i--)
                {
                    char buffer[100];
                    int count = 0;
                    std::string fileNumber;
                    std::stringstream ss;;
                    std::string temp;
                    temp = sprintf(buffer,"%04d", count);
                    ss << buffer;
                    ss >> fileNumber;
                    std::ofstream out(filename + fileNumber + ".pgm", std::ios::binary);
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
                    count++;
                }
            }
            else
            {
                for (size_t i = 0; i < imageSequence.size(); i++)
                {
                    char buffer[100];
                    int count = 0;
                    std::string fileNumber;
                    std::stringstream ss;;
                    std::string temp;
                    temp = sprintf(buffer,"%04d", count);
                    ss << buffer;
                    ss >> fileNumber;
                    std::ofstream out(filename + fileNumber + ".pgm", std::ios::binary);
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
                    count++;
                }
            }
        }

        std::string toString(){
            std::string temp="";
            for (size_t i = 0; i < imageSequence.size(); i++)
            {
                for (size_t j = 0; j < height; j++)
                {
                    for (size_t k = 0; k < width; k++)
                    {
                        temp+=imageSequence[i][j][k]+"\n";
                    }   
                }
            }
            return temp;
        }
    };

    unsigned char** image(int beginX, int beginY, int endX, int endY, unsigned char ** bigFrame);
}
#endif