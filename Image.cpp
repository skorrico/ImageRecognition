#include <Image.h>


Image::Image(){
    size = 0;
    counter = 0;
    pixelValues = NULL;
    fileName2 = "";
    classNum = 0;
}

Image::Image(const Image &image){
    //cout << "image cc" << endl;
    this->size = image.size;
    this->counter = image.counter;
    if(image.pixelValues == NULL){
        this->pixelValues = NULL;
    }
    else{
        this->pixelValues = new int[size];
        for(int i = 0; i < size; i++){
            this->pixelValues[i] = image.pixelValues[i];
        }
    }    
    //this->pixelValues = image.pixelValues;
    this->fileName2 = image.fileName2;
    this->classNum = image.classNum;
}

Image& Image::operator=(const Image &image){
    delete[] pixelValues;
    size = image.size;
    counter = image.counter;
    if(image.pixelValues == NULL){
        pixelValues = NULL;
    }
    else{
        pixelValues = new int[size];
        for(int i = 0; i < size; i++){
            pixelValues[i] = image.pixelValues[i];
        }
    }    
    //this->pixelValues = image.pixelValues;
    fileName2 = image.fileName2;
    classNum = image.classNum;
return *this;
}

Image::~Image(){
        //cout << "free "<<pixelValues << endl;
     delete[] pixelValues;
     pixelValues = NULL;
}

bool Image::Read(string fileName){
    
    int width = 0;
    int height = 0;
    int maxPixel = 0;
    int number = 0;
    string errorInFile = "";
    fileName2 = fileName;
    
    ifstream ifstr(fileName);
    
    if(ifstr.fail()) {
        cerr << "Error message : Unable to open file" << endl;
        return false;
    }
    
    classNum = setClassNumber();

    
//     if(ifstr.get() != 'P'){
//         cerr << "Error" << endl;
//         return false;
//     }
//     if(ifstr.get() != '2'){
//         cerr << "Error" << endl;
//         return false;
//     }
    string x;
    ifstr >> x;
		
    ifstr >> width; //reading in width
           /* if(width != 128){
                    cerr << "Error: wrong width" << endl;
                    return false;
            } */       
    ifstr >> height; //reading in height
            /*if(height != 128){
                    cerr << "Error: wrong height" << endl;
                    return false;
            }*/ 
		
    ifstr >> maxPixel;
//             if(maxPixel != 255){
//                     cerr << "Error: max pixel" << endl;
//                     return false;
//             }
    size = width * height; //get size of picture
    pixelValues = new int[size];
    //cout << "allocating "<<pixelValues << endl;
    
    while(true){
        
        ifstr >> number; //reading into my int 
        
        if(ifstr.fail()){
            
            if(ifstr.eof()){
                break;
            }
            
//             else{
//                 ifstr.clear();
//                 ifstr >> errorInFile;
//                 cerr << "Error: Found a non-integer variable: " << errorInFile << endl;
//                 return false;
//             }
        }
        
//         if(number < 0 || number > 255){
//             largeNumber = number;
//             cerr << "Error: Number " <<  largeNumber << " is out of bounds." << endl;
//             return false;
//         }
        pixelValues[counter] = number;
        counter++; 
        
    }
//     if(!(checkSize(counter, size))){
//         cerr << "Error: number of pixels does not equal size" << endl;
//         return false;
//     }
//     if(!(Empty(counter))){
//         cerr << "Error" << endl;
//         return false;
//     }
    imageHistogram();
    return true;
}

string Image::getFileName(){
    return fileName2;
}

int Image::setClassNumber(){
    int under = 0;
    int number = 0;
    under = fileName2.find("_");
    under = under - 5;
    string s = fileName2.substr(5,under);
    number = atoi(s.c_str());
    return number;
}

void Image::imageHistogram(){
    hist1.createHistogram(pixelValues, size);
    hist1.Normalize(size);
}

bool Image::checkSize(int counter, int size){
    if(size != counter){
        return false;
    }
    else
        return true;
}

bool Image::Empty(int counter){
    if(counter == 0){
        cerr << "Error: Empty File no pixels" << endl;
        return false;
    }
    else
        return true;
}


int* Image::getPixels(){
    return pixelValues;
}

int Image::getPixelsAt(int i){
    return pixelValues[i];
}

const Histogram& Image::getHist(){
    return hist1;
}


int Image::getSize(){
    return size;
}

int Image::getClassNumber(){
    return classNum;
}

//comparing pixels
void Image::squareSumTo(Image& Image2){
    
    int sqaureSum = 0;
    int* secondPixelValues = new int[size];
    secondPixelValues = Image2.getPixels();
	
    for(int i = 0; i < size; i++){
            secondPixelValues[i] = pow(pixelValues[i] - secondPixelValues[i], 2);
    }
	
    for(int i = 0; i < size; i++){
            sqaureSum += secondPixelValues[i];
    }
    cout << sqaureSum << endl;
}

//PA4 method that compares two histograms at a time --> now should work for image.cpp COMPARING HISTS
double Image::histogramCompare(string file1, string file2){
    
    Image image1; 
    Image image2; 
    
    if(!(image1.Read(file1))){
        return -1.0;
    }
    
    if(!(image2.Read(file2))){
        return -1.0;
    }
    
    Histogram hist2 = image2.getHist();
    int size2 = image2.getSize();
        
    hist1.Normalize(size);
    hist2.Normalize(size2);
    
    double ans = hist1.compareTo(hist2);
    return ans;
    
}

