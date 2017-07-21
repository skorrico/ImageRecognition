#ifndef PERCEPTRON_H_INCLUDED
#define PERCEPTRON_H_INCLUDED
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

class Perceptron{
public:
    
    Perceptron();
    Perceptron(const Perceptron &p);
    ~Perceptron();
    void weight(Image* image, int num);
    int setD(int classNum, int num);
    void printWeightsAndBias();
    int checkClassNumber(Image* image, int num);
    double* getWeights();
    void generalPerceptron(vector<Image*> images, int num);
    double getWeightsAt(int i);
    
    
private:
    double* weights;
    double bias;
    
};
#endif
