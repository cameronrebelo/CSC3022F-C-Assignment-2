#ifndef _EXTRACTOR_H
#define _EXTRACTOR_H

#include <utility>
#include <cstring>
#include <iostream>
#include <vector>
namespace RBLCAM001
{

    class FrameSequence
    {
    private:
        std::vector<unsigned char **> imageSequence;

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
    };

    unsigned char** image(int beginX, int beginY, int endX, int endY, unsigned char ** & array){};
}
#endif