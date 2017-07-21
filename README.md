# ImageRecognition
- This was a semester long project in a Problem Solving with C++ class my Junior year at Colorado State University
- The goal of this project is to read in many depth images and cluster then based on their similarities
- For the class we used depth images of hand gestures 
- The code creates and trains perceptrons to make a base example of what a depth image of a gesture should look like and uses that to cluster the input images 
## Image.cpp
- Image.cpp reads in a file that holds any amount of depth images 
- This class does almost all of the parsing of the images and gather all the information for the rest of the classses
  - file size, file name and pixels
  - you will see lots of checking commented out due to optimization at the end of the project
## Histogram.cpp
- This Histogram class creates and normalizes a histogram object once the image is read in
- It will normalize the pixels and create a historgram object based on the frequency of pixels in 4 intervals
## Cluster.cpp
- The Cluster class is in charge of clustering depth images based on their similarities 
- Each Cluster object has their own histogram based on the Image objects that belong in the Cluster
## Perceptron.cpp
- This is where the Perceptron object is trained 
## dataSet.cpp
- This class contains a few different ways to Cluster the Images together 
