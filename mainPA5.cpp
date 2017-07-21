#include <Histogram.h>
#include <Image.h>
#include <Cluster.h>
#include <dataSet.h>

int main(int argc, char* argv[])
{
    if(argc != 4){
        cerr << "Not enough arguments" << endl;
        return -1;
        }
        
    char* secondArg = argv[3];
    int K = atoi(secondArg); //number of clusters
    dataSet dSet;
    dataSet dSet2;
    
    if(K <= 0){
        cerr << "Error: Incompatable number of clusters" << endl;
        return -1;
    }

    if(!(dSet.readFile(argv[1]))){
        return -1;
    }
    dSet.fillClassNumVec(); 
    if(!(dSet.checkClassNumVec())){
        cerr << "Error: not enough classes" << endl;
        return -1;
    }
    dSet.createPerceptronVec();
    if(dSet.checkPerceptron() < 2){
        cerr << "Error: not enough classes in traning text file" << endl;
        return -1;
    }
    
    if(!(dSet2.readFile(argv[2]))){
        return -1;
    }
    dSet2.setPerceptron(dSet.perceptrons);
    int numFiles = dSet2.getSize();
    
    if(K > numFiles){
        cerr << "Error: invalid number of clusters" << endl;
        return -1;
    }
//     else if(K == numFiles){
//         dSet2.printOnePerLine();
//     }
    if(numFiles < 2){
        cerr << "Error: not enough files to cluster" << endl;
        return -1;
    }
    else{
        dSet2.createClusters();
        while(K < dSet2.getClusterSize()){
            dSet2.clustering2(unsigned (K));
        }
        dSet2.printClusters();
    }
    
    return 1;
    
}
