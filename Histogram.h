#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

/* this file reader.h will declare the reader class
*/
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

class Histogram {
public:
    Histogram();
    Histogram(const Histogram &histogram);
    ~Histogram();
    void createHistogram(int* pixelValues, int size);
    void Normalize(int size);
    inline double* getHistArray(){return hist;}
    int getSize();
    double compareTo(Histogram& hist2);
    void addTo(Histogram& hist2, int size);
    double getAtIndex(int i) const;
    void setHist(double* array) {hist = array;}
    void createEmptyHist();
    void printHist();
    int findQuad(int indexOfPixel);
    int findNinth(int indexOfPixel);

private:
    double* hist;
};

#endif //READER_H_INCLUDE
