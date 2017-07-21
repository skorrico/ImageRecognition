#include <Cluster.h>

Cluster::Cluster(){
    //cout << "copnstructor this " << this << endl;
    counter = 0;
    numImages = 0;
    arrHist = new double[64]; //LOST
    
    for(int i = 0; i < 64; i++){
        arrHist[i] = 0;
    }
    pixelArr = new int[16384];  //LOST
    for(int i = 0; i < 16384; i++){
        pixelArr[i] = 0;
    }
}

Cluster::Cluster(const Cluster &clust){
    //cout << "copy constructor this " << this << endl;
    this->counter = clust.counter;
    this->numImages = clust.numImages;
    this->listI = clust.listI;
    this->arrHist = new double[64]; //LOST
    for(int i = 0; i < 64; i++){
        this->arrHist[i] = clust.arrHist[i];
    }
    this->pixelArr = new int[16384]; //LOST
    for(int i = 0; i < 16384; i++){
        this->pixelArr[i] = clust.pixelArr[i];
    }
}

Cluster& Cluster::operator=(const Cluster &clust){
    numImages = clust.numImages;
    counter = clust.counter;
    n = clust.n;
//     listI.reserve(clust.listI.size());
//     for(unsigned int i = 0; i < clust.listI.size(); i++){
//         listI[i] = clust.listI[i];
//         if(listI.size() < clust.listI.size()){
//             listI.push_back(new Image());
//         }
//         else{
//             break;
//         }
//     }
    
    listI.clear();
    for(unsigned int i = 0; i < clust.listI.size(); i++){
        listI.push_back(new Image());
        listI[i] = clust.listI[i];
    }
    
    //arrHist 
    delete[] arrHist;
    arrHist = new double[64];
    for(int i = 0; i < 64; i++){
       arrHist[i] = clust.arrHist[i];
    }
    delete[] pixelArr;
    pixelArr = new int[16384];
    for(int i = 0; i < 16384; i++){
       pixelArr[i] = clust.pixelArr[i];
    }
    return *this;
}

Cluster::~Cluster(){
    //cout << "clust destructor " << this << endl; 
    //cout << "destructor " << this << endl;
    delete[] arrHist;
    delete[] pixelArr;
}

void Cluster::deleteArrays(){
    //delete[] arrHist;
    //delete[] pixelArr;
}

void Cluster::addImage(Image* image){
    listI.push_back(image);
    createHistogram(image);
    createPixelArr(image);
    numImages++;
}

void Cluster::createHistogram(Image* image){
    for(int i = 0; i < 64; i++){ 
        arrHist[i] = arrHist[i] * numImages;
        //arrHist1[i] = arrHist1[i] * numImages;
        
    }
    for(int i = 0; i < 64; i++){
        arrHist[i] += image->getHist().getAtIndex(i);
        arrHist[i] = arrHist[i] / (numImages + 1);
    }
}

// void Cluster::createYValues(vector<Perceptron*>& p){
//     double temp;
//     double y;
//     double* w = new double[65];
//     
//     
//     for(unsigned int i = 0; i < p.size(); i++){
//         for(int j = 0; j < 65; j++){
//             w[j] = p[i]->getWeightsAt(j);
//         }
//         for(int j = 0; j < 64; j++){
//             temp += arrHist[j] * w[j];
//         }
//         y = temp;
//         y += w[64];
//         yValues.push_back(y);
//     }
//     cout << "done creating Y's: " << this << endl;
//     
//     delete[] w;
// }

void Cluster::createPixelArr(Image* image){
    for(int i = 0; i < 16384; i++){
        pixelArr[i] += image->getPixelsAt(i);
        pixelArr[i] = pixelArr[i] / (numImages + 1);
    }
}

double Cluster::compareHistogram(Cluster* clust, Image* image){
    double ans = 0.0;
    clust->createHistogram(image);
    
    for(int i = 0; i < 64; i++){
        ans += std::min(arrHist[i], clust->arrHist[i]);
    }
    //cout << "ans " << ans << endl;
    return ans;
    
}

double Cluster::compareYValues(Cluster* clust, vector<Perceptron*>& p, Image* image){
    double y1 = 0.0;
    double y2 = 0.0;
    double ans = 0.0;
    clust->createHistogram(image);
    
    //for(vector<Perceptron>::iterator it = p.begin(); it != p.end(); it++)
    for(unsigned int i = 0; i < p.size(); i++){
	Perceptron* ptr = p[i];
	double* arrHistPtr = arrHist;
	double* clustArrHistPtr = clust->arrHist;
        for(int j = 0; j < 64; j++){
	    double weightJ = ptr->getWeightsAt(j);
            y1 += (*arrHistPtr++) * weightJ;
            y2 += (*clustArrHistPtr++) * weightJ;
        }
        y1 += ptr->getWeightsAt(64);
        y2 += ptr->getWeightsAt(64);
//         cout << "y1: " << y1 << endl;
//         cout << "y2: " << y2 << endl;
        double x = y1 - y2;
        ans += x * x;
        y1 = 0.0;
        y2 = 0.0;
    }
    ans = 1 / ans;
    return ans;
}

void Cluster::merge(Cluster* cluster){
    //cout << "in merge" << endl;
    for(unsigned int i = 0; i < cluster->listI.size(); i++){
        listI.push_back(cluster->listI[i]);
    }    
}


void Cluster::printHist(){
    cout << "Cluster Histogram" << endl;
    for(int i = 0; i < 64; i++){
        cout << arrHist[i];
    }
    cout << endl;
}

vector<Image*>& Cluster::getVectorOfImages(){
    return listI;
}

void Cluster::printFileName(){
    for(unsigned int i = 0; i < listI.size(); i++){
        cout << listI.at(i)->getFileName() << " ";
    }
    cout << endl;
}

void Cluster::getNumbers(){
    string className = "";
    int under = 0;
    for(unsigned int i = 0; i < listI.size(); i++){
        className = listI.at(i)->getFileName(); //contains the pgm filename 
        under = className.find("_");
        under = under - 5;
        string s = className.substr(5,under);
        int a = atoi(s.c_str());
        n.push_back(a);
    }
    sort(n.begin(), n.end());//sorts vector of integers
    for(unsigned int i = 0; i < n.size(); i++){
        //cout << "n: " << n[i] << endl;
    }
}

//iterate through vector to see which one appeared the most return that number
int Cluster::findDominance(){
    int dominant = n[0];
    //int mode = dominant;
    int counter = 1;
    int max = 1;
    for(unsigned int i = 1; i < n.size(); i++){
        if(n[i] == dominant){
            //cout<< "n[" <<i<<"]: " << n[i] << " dominant: " << dominant << endl;
            max++;
        }
        else{
            if(counter > max){
                max = counter;
                //mode = dominant;
                //cout << "in else" << endl;;
            }
            counter = 1;
            dominant = n[i];
            //cout << "new dominant: " << dominant << endl;
        }
    }
    //cout << "mode: " << dominant << endl;
    return dominant;
    
}

//get frequency of dominant number
int Cluster::frequency(){
    int dominant = findDominance();
    //cout << "dominant number is: " << dominant << endl;
    int count = 0;
    for(unsigned int i = 0; i < n.size(); i++){
        if(dominant == n[i]){
            count++;
        }
    }
    //cout << "frequency: " << count << endl;
    return count;
}

int Cluster::getImageVectorSize(){
    return listI.size();
}

double* Cluster::getClustHist(){
    return arrHist;
}

int* Cluster::getPixelArr(){
    return pixelArr;
}
