#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include<iostream>
using std::cerr;
using std::endl;
using std::cout;
#include<fstream>
using std::ifstream;
using std::istream;
#include<string>
using std::string;
#include<math.h>
#include<vector>
using namespace std;
#include <Histogram.h>

class Image {
public:
    Image(); 
    Image(const Image &image);
    Image& operator=(const Image &image);
    ~Image();
    bool Read(string fileName); //read pgm file
    bool checkSize(int counter, int size);
    const Histogram& getHist();
    bool Empty(int counter);
    int* getPixels();
    void squareSumTo(Image& image2);
    string getFileName();
    int getSize();
    double histogramCompare(string file1, string file2);
    void imageHistogram();
    int getPixelsAt(int i);
    int getClassNumber();
    int setClassNumber();
    
private:
    int size;
    int counter;
    int* pixelValues;
    string fileName2;
    int classNum;
    Histogram hist1;
    Histogram h1;
    Histogram h2;
    Histogram h3;
    Histogram h4;
    Histogram h11;
    Histogram h22;
    Histogram h33;
    Histogram h44;
    Histogram h55;
    Histogram h66;
    Histogram h77;
    Histogram h88;
    Histogram h99;
};

#endif
