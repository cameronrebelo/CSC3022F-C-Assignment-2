RBLCAM001

extractor.cpp:
    main class of the program, handles all input from the command line and reads in data from the large pgm.
    contains function to extract a single frame given the starting point and dimensions
    will iterate over all operations given to it and invoke FrameSequence to write output files

FrameSequence.cpp:
    class that contains a vector of all the unsigned char arrays that represent each frame in a video sequence
    contains:
        - default non paramatized Constructor
        - Destructor
        - insertFrame function to insert a char array parsed to it into the vector
        - setters for height and width
        - doOperation that will direct the program which operations to perform
        - invert pixel data function
        - write frames in sequence function(can do reverse as well)

extractor.h:
    header file for the project, conatains all class and function declarations

Makefile:
    compiles class files found in src and places their object files in bin
        make test: 
        - runs one of the cases from frametester.sh once the program has been compiled
        make clean:
        - removes object files in bin, generated *pgm files and the extractor executable file