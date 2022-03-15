#ifndef _EXTRACTOR_H
#define _EXTRACTOR_H

#include <vector>
namespace RBLCAM001
{

    class FrameSequence
    {

    //instance variables
    private:
        std::vector<unsigned char **> imageSequence;
        int width,height;
        bool isReversed;

    public:
        // Constructor and Destructor
        FrameSequence(void);
        ~FrameSequence();

        //Utilities
        void insertFrame(unsigned char ** frame);
        void setHeight(int h);
        void setWidth(int w);
        void doOperation(std::string operation, std::string fileName);
        void invert();
        void writeVector(std::string filename);
        std::string toString();
        };

    unsigned char** image(int beginX, int beginY, int endX, int endY, unsigned char ** bigFrame);
}
#endif