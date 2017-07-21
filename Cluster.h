#ifndef CLUSTER_H_INCLUDED
#define CLUSTER_H_INCLUDED
#include <Image.h>
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
#include<Histogram.h>
#include <algorithm>
#include <Perceptron.h>

class Cluster{
public:
    Cluster();
    Cluster(const Cluster &clust);
    Cluster& operator=(const Cluster &clust);
    ~Cluster();
    vector<Image*>& getVectorOfImages();
    void addImage(Image* image);
    void printFileName();
    void createHistogram(Image* image);
    void createPixelArr(Image* image);
    void createYValues(vector<Perceptron*>& p);
    Histogram getHistogram();
    double compareHistogram(Cluster* clust, Image* image);
    double compareYValues(Cluster* clust, vector<Perceptron*>& p, Image* image);
    void merge(Cluster* cluster);
    void printHist();
    double* getClustHist();
    int* getPixelArr();
    void getNumbers();
    int findDominance();
    int frequency();
    vector<Image*> listI;
    void deleteArrays();
    int getImageVectorSize();
    
    
private:
    
    int counter;
    int numImages;
    double* arrHist;
    int* pixelArr;
    vector<int> n;
};
#endif
