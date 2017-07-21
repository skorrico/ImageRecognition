#include <Histogram.h>

Histogram::Histogram(){
    hist = new double[64];
    for(int i = 0; i < 64; i++){
        hist[i] = 0;
    }
}

Histogram::Histogram(const Histogram &histogram){
    this->hist = new double[64];
    for(int i = 0; i < 64; i++){
        this->hist[i] = histogram.hist[i];
    }
    //look at memcpy()
}

Histogram::~Histogram(){
    delete[] hist;
}

void Histogram::createHistogram(int* pixelValues, int size){
    int flooredNum = 0;
    for(int i = 0; i < 64; i++){
        hist[i] = 0;
    }
    for(int i = 0; i < size; i++){
        flooredNum = floor(pixelValues[i] / 4);
        hist[flooredNum]++;
    }
}

void Histogram::createEmptyHist(){
    for(int i = 0; i < 64; i++){
        hist[i] = 0;
    }
}

void Histogram::Normalize(int size){
    for(int i = 0; i < 64; i++){
        hist[i] = hist[i] / size;
    }
}

// double* Histogram::getHistArray(){
//     return hist;
// }

void Histogram::printHist(){
    for(int i = 0; i < 64; i++){
        cout << hist[i];
    }
    cout << endl;
}

double Histogram::getAtIndex(int i) const{
    return hist[i];
}


double Histogram::compareTo(Histogram& hist2){
    double finalOutput = 0.0;    
    double* secondNumOut = new double[64];
    double* temp = new double[64];
    secondNumOut = hist2.getHistArray();
    
    for(int i = 0; i < 64; i++){
        temp[i] = std::min(hist[i], secondNumOut[i]);
    }
    
    for(int i = 0; i < 64; i++){
        finalOutput += temp[i];
    }
    return finalOutput;
}

