#ifndef DATASET_H_INCLUDED
#define DATASET_H_INCLUDED

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
#include<Image.h>
#include<Cluster.h>
#include<Perceptron.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<iterator>
using std::remove;

class dataSet{
public:
    dataSet();
    dataSet(const dataSet &dset);
    ~dataSet();
    bool readFile(string fileName);
    void printOneCluster();
    void printOnePerLine();
    int getSize();
    void createClusters();
    void clustering1(unsigned int k);
    void clustering2(unsigned int k);
//     void clustering3(unsigned int k);
//     void clustering4(unsigned int k);
    void printClusters();
    void eraseCluster(int simIndex);  
    int getClusterSize();
    void callDelete();
    void printQuality();
    bool checkFileName();
    bool checkPerceptron(int num);
    void createPerceptron(int num);
    void createPerceptronVec();
    void fillClassNumVec();
    void setPerceptron(vector<Perceptron*> p);
    vector<Perceptron*> perceptrons;
    int getVecSize();
    bool checkClassNumVec();
    int checkPerceptron() {return perceptrons.size();}
    
   
    
private:
    vector<Image*> listImages;
    vector<string> fileNames;
    vector<Cluster*> clusters;
    vector<int> classNumbers;
    
    int counter;
    int size;
};
#endif 
