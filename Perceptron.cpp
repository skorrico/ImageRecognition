#include <Perceptron.h>

 Perceptron::Perceptron(){
     weights = new double[65];
     for(int i = 0; i < 65; i++){
         weights[i] = 0.0;
     }
     bias = 0.0;
 }
 
 Perceptron::Perceptron(const Perceptron &p){
     this->weights = new double[65];
     for(int i = 0; i < 65; i++){
         this->weights[i] = p.weights[i];
     }
     this->bias = p.bias;
 }

 
 Perceptron::~Perceptron(){
     delete[] weights;
     weights = NULL;
 }
 
 void Perceptron::generalPerceptron(vector<Image*> images, int num){     
     for(unsigned int i = 0; i < images.size(); i++){
        weight(images[i], num); //calculate and set weights and bias
     }
 }
 
//  void Perceptron::weight(Image* image, int num){
//      double* normHist = new double[64];
//      for(int i = 0; i < 64; i++){
//          normHist[i] = image->getHist().getAtIndex(i);
//      }
//      int classNum = image->getClassNumber();
//      int d = setD(classNum, num);
//      double temp = 0.0;
//      double y = 0.0;
//      
//      for(int i = 0; i < 64; i++){
//          temp += normHist[i] * weights[i];
//      }
//      y = bias + temp;
//     
//      for(int i = 0; i < 64; i++){
//          weights[i] = weights[i] + ((d - y) * normHist[i]); //sets weights 
//      }
//      
//      bias = bias + (d - y); //sets bias 
//      weights[64] = bias;
//      delete[] normHist;
//  }
//  
  int Perceptron::setD(int classNum, int num){
     int x = 0;
     if(classNum == num){
         x = 1;
     }
     else
         x = -1;
     return x;
 }
 
 double* Perceptron::getWeights(){
     return weights;
 }
 
 double Perceptron::getWeightsAt(int i){
     return weights[i];
 }
 
 void Perceptron::weight(Image* image, int num){
     //cout << "first bias: " << bias << endl;
     double* normHist = new double[64];
     for(int i = 0; i < 64; i++){
         normHist[i] = image->getHist().getAtIndex(i);
     }
     
     int classNum = image->getClassNumber();
     int d = setD(classNum, num);
     double temp = 0.0;
     double y = 0.0;
     
     for(int i = 0; i < 64; i++){
         temp += normHist[i] * weights[i];
     }
     y = bias + temp;
    
     for(int i = 0; i < 64; i++){
         weights[i] = weights[i] + ((d - y) * normHist[i]); //sets weights 
     }
     
     bias = bias + (d - y); //sets bias 
     //cout << "bias: " << bias << endl;
     weights[64] = bias;
     //y = 0;
     //cout << "bias: " << bias << endl;
     delete[] normHist;
 }
 

 
 int Perceptron::checkClassNumber(Image* image, int num){
     int counter = 0;
     int classNum = image->getClassNumber();
     if(classNum == num){
         counter++;
     }
     else{
     }

     return counter;
 }
 
 void Perceptron::printWeightsAndBias(){
     for(int i = 0; i < 65; i++){
         cout << weights[i] << " ";
     }
     cout << endl;
     //cout << bias << endl;
 }
