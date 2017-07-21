#include <dataSet.h>

dataSet::dataSet(){
    counter = 0;
    size = 0;
    clusters.reserve(0);
    classNumbers.reserve(0);
}

dataSet::dataSet(const dataSet &dset){
    this->counter = dset.counter;
    this->size = dset.size;
}


dataSet::~dataSet(){
    for(unsigned int i = 0; i < listImages.size(); i++){
        delete listImages[i];
     }
     for(unsigned int i = 0; i < perceptrons.size(); i++){
        delete perceptrons[i];
        perceptrons[i] = NULL;
     }
}

bool dataSet::readFile(string fileName){
    string imageName = "";
    string errorInFile = "";
    ifstream ifstr(fileName); 
    
//     if(ifstr.fail()) {
//         cerr << "Error message : Unable to open file" << endl;
//         return false;
//     }
    
    while(ifstr >> imageName){
        if(ifstr.fail()){
            
            if(ifstr.eof()){
                break;
            }
            
            else{
                ifstr.clear();
                ifstr >> errorInFile;
                cerr << "Error: Found a non-string varaible: " << errorInFile << endl;
                return false;
            }
        }
        fileNames.push_back(imageName); //contains the pgm names
        if(!(checkFileName())){
            cerr << "Error: wrong pgm name" << endl;
            return false;
        }
        listImages.push_back(new Image()); //LOST HOW?
        listImages.at(counter)->Read(imageName); 
        counter++;
    }
    size = fileNames.size();
    if(fileNames.size() < 2){
        cerr << "Error: not enough files to compare" << endl;
        return false;
    }
    
    return true;
}

void dataSet::fillClassNumVec(){
    vector<int> class1;
    for(unsigned int i = 1; i < listImages.size(); i++){        
        class1.push_back(listImages[i]->getClassNumber());

    }
    sort(class1.begin(), class1.end());
    classNumbers.push_back(class1[0]);
    for(unsigned int i = 1; i < class1.size(); i++){
        if(class1[i-1] != class1[i]){
            classNumbers.push_back(class1[i]);
        }
    }
}

bool dataSet::checkClassNumVec(){
    if(classNumbers.size() < 2){
        return false;
    }
    else
        return true;
}

bool dataSet::checkFileName(){
    if(fileNames[counter].substr(0,5) != "class"){
        return false;
    }
    else
        return true;
}

int dataSet::getSize(){
    return size;
}

//declares clusters with one image inside 
void dataSet::createClusters(){
    for(int i = 0; i < size; i++){
        clusters.push_back(new Cluster()); //creates vector of clusters --> # of clusters = # of files
        clusters.at(i)->addImage(listImages.at(i)); 
    }
}

//func that takes in # of clusters wanted and merges until you get that #
void dataSet::clustering1(unsigned int k){
    double compare = 0;
    double max = 0;
    int similarCluster = 0;
    int originalCluster = 0;
     //keep clustering/merging until we get the right amount of clusters
    while(clusters.size() > k){
        for(unsigned int i = 0; i < clusters.size(); i++){
            for(unsigned int j = i; j < clusters.size(); j++){
                if(i != j){
                    compare = clusters[i]->compareHistogram(clusters[j], listImages[j]);
//                     cout << "clusters 1 :"; Perceptron* p = new Perceptron();
//                     clusters[i].printFileName();
//                     cout << "compare to "<< endl;
//                     cout << "clusters 2:";
//                     clusters[j].printFileName();                    
//                     cout << "COMPARE: " << compare << endl;
//                     cout << endl;
                    if(compare > max){
                        max = compare;
                        originalCluster = i;
                        similarCluster = j;
                    }
                }
            }
        }
//         cout << "og Cluster: ";
//         clusters[originalCluster].printFileName();
        clusters[originalCluster]->merge(clusters[similarCluster]);
        clusters[originalCluster]->createHistogram(listImages[similarCluster]);
        eraseCluster(similarCluster);
        max = 0;
    
    }
       
}

//compare y values
void dataSet::clustering2(unsigned int k){
    double compare = 0;
    double max = 0;
    int similarCluster = 0;
    int originalCluster = 0;
    while(clusters.size() > k){
        for(unsigned int i = 0; i < clusters.size(); i++){
            for(unsigned int j = i; j < clusters.size(); j++){
                if(i != j){
                    compare = clusters[i]->compareYValues(clusters[j], perceptrons, listImages[j]);
//                     cout << "clusters 1 :"; Perceptron* p = new Perceptron();
//                     clusters[i].printFileName();
//                     cout << "compare to "<< endl;
//                     cout << "clusters 2:";
//                     clusters[j].printFileName();                    
//                     cout << "COMPARE: " << compare << endl;
//                     cout << endl;
                    if(compare > max){
                        max = compare;
                        originalCluster = i;
                        similarCluster = j;
                    }
                }
            }
        }
        //         cout << "og Cluster: ";
//         clusters[originalCluster].printFileName();
        clusters[originalCluster]->merge(clusters[similarCluster]);
        clusters[originalCluster]->createHistogram(listImages[similarCluster]);
        eraseCluster(similarCluster);
       // cout << "3: ";
       // printClusters();
        max = 0;
    
    }
       
}

void dataSet::eraseCluster(int simIndex){
//     cout << "4: ";
//     printClusters();
//     cout << "swap this element with simIndex: ";
//     clusters[(clusters.size() - 1)].printFileName();
    clusters[simIndex] = clusters[(clusters.size() - 1)]; //swapping the last cluster to take the 
//     cout << "swapped element: ";
//     clusters[simIndex].printFileName();
    clusters.pop_back(); //shortens cluster 
    listImages[simIndex] = listImages[(listImages.size() - 1)];
    listImages.pop_back();
}

void dataSet::printOneCluster(){
    for(int i = 0; i < size; i++){
        cout << fileNames.at(i) << " ";
    }
    cout << endl;
}

void dataSet::printOnePerLine(){
    for(int i = 0; i < size; i++){
        cout << fileNames.at(i) << endl;
        cout << "1" << endl;
    }
}

void dataSet::printClusters(){
    for(unsigned int i = 0; i < clusters.size(); i++){
        clusters[i]->printFileName();
    }
    cout<< endl;
}

void dataSet::printQuality(){
    double dominantNum = 0;
    double totalClasses = 0;
    for(unsigned int i = 0; i < clusters.size(); i++){
        clusters[i]->getNumbers();
        dominantNum += clusters[i]->frequency();
        totalClasses += clusters[i]->getImageVectorSize();
        //dominantNum /= clusters[i].getImageVectorSize();
        //cout << "print quality dom; " << dominantNum << endl;
        
    }
    dominantNum /= totalClasses;
    cout << dominantNum << endl;
}

void dataSet::callDelete(){
    for(unsigned int i = 0; i < clusters.size(); i++){
        clusters[i]->deleteArrays();
    }
}

int dataSet::getClusterSize(){
    return clusters.size();
}

bool dataSet::checkPerceptron(int num){
    int count = 0;
    Perceptron* p = new Perceptron();
    
    for(unsigned int i = 0; i < listImages.size(); i++){
        count += p->checkClassNumber(listImages.at(i), num);
    }
    if(count == 0){
        delete p;
        return false;
    }
    else{
        delete p;
        return true;
    }
    
}

void dataSet::createPerceptronVec(){
    for(unsigned int i = 0; i < classNumbers.size(); i++){
        perceptrons.push_back(new Perceptron());
        for(int j = 0; j < 100; j++){
            perceptrons[i]->generalPerceptron(listImages, classNumbers[i]);
        }
//         perceptrons[i]->printWeightsAndBias();
//         cout << endl;
    }
}

void dataSet::setPerceptron(vector<Perceptron*> p){
    for(unsigned int i = 0; i < p.size(); i++){
        perceptrons.push_back(new Perceptron(*p[i]));
    }
}

int dataSet::getVecSize(){
    return perceptrons.size();
}

// void dataSet::createPerceptron(int num){
// 
//     Perceptron* p = new Perceptron();
//     
//     for(int i = 0; i < 100; i++){
//         for(unsigned int j = 0; j < listImages.size(); j++){
//             p->weight(listImages.at(j), num);
//         }
//     }
//     
//     p->printWeightsAndBias();
//     delete p;
// }







