#ifndef _EXTRACTOR_H
#define _EXTRACTOR_H

#include <utility>
#include <cstring>
#include <iostream>

class FrameSequence
{
    private:
        std::vector<unsigned char **> imageSequence;

    public:

        //Constructor and Destructor
        FrameSequence() : imageSequence(std::vector<unsigned char>){}
        ~FrameSequence(){
            for(size_t i = 0; i < imageSequence.size;i++){
                if(imageSequence[i]!=nullptr){
                    delete imageSequence[i];
                }
            }
        }

}



#endif