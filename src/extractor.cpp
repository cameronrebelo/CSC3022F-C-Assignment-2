#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

int main(int argc, char* argv[])
{
    std::cout << "um hi" << std::endl;
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
        if(std::string(argv[i]) == "-w")
        {
            std::cout << argv[i] << std::endl;
            std::cout << argv[i+1] << std::endl;
            std::cout << argv[i+2] << std::endl;

                // std::cout << operation << std::endl;
                std::string writeName(argv[i+2]);
                std::cout << writeName << std::endl;
                std::vector<std::string> temp;
                // temp.push_back(operation);
                // temp.push_back(writeName);
            std::string operation = argv[i+1];
            std::string writeFileName = argv[i+2];
            std::vector<std::string> temp = {operation, writeFileName};
            writeOptions.push_back(temp);
            // writeOptions.push_back(writeFileName);

            i += 3;
        }

    }

    std::cout << filename << std::endl;
    std::cout << beginX << std::endl;
    std::cout << beginY << std::endl;
    std::cout << endX << std::endl;
    std::cout << endY << std::endl;
    std::cout << frameHeight << std::endl;
    std::cout << frameWidth << std::endl;

    for (size_t i = 0; i < writeOptions.size(); ++i)
    {
        std::cout << writeOptions[i][0] << std::endl;
        std::cout << writeOptions[i][1] << std::endl;
    }
    

    std::string line = "";
    ifstream myfile(filename);
    stringstream ss



}