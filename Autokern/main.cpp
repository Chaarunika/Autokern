//
//  main.cpp
//  Autokern
//
//  Created by malith on 10/7/17.
//  Copyright © 2017 NMR. All rights reserved.
//
/*
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

cv::Mat imgOriginal;        // input image

Mat shift(Mat state, int id, bool direction);
int rewardFunction(Mat currentState, int id, bool direction);
Mat translateImg(Mat &img, int offsetx, int offsety);

int main(int argc, char** argv)
{
    
    const int size = 3;
    cv::Mat glyphArray[size];
    std::string name;
    
    for (int i = 1; i <= size; i++) {
        name = "/Users/malithranathunga/Desktop/Research/Code/Autokern/Autokern/" + to_string(i) + ".png";
        glyphArray[i - 1] = cv::imread(name, 0);          // open image
        threshold(glyphArray[i - 1], glyphArray[i - 1], 150, 255, CV_THRESH_BINARY_INV); // invert colors
        
        for (int k = 0; k < glyphArray[i - 1].rows; k++) { //assigning id's to each letter
            for (int j = 0; j < glyphArray[i - 1].cols; j++) {
                if ((int)glyphArray[i - 1].at<uchar>(k, j) >= 255) {
                    glyphArray[i - 1].at<uchar>(k, j) = (100-i); //problem with increasing alphabet
                }
            }
        }
        
        if (i > 1) {
            cv::hconcat(imgOriginal, glyphArray[i - 1], imgOriginal);
        }
        else {
            imgOriginal = glyphArray[i - 1];
        }

        
    }
    
    
    //cv::namedWindow("imgCanny", CV_WINDOW_AUTOSIZE);
    //cv::imshow("xx", imgOriginal);
    //waitKey(2000);
    int v1, v2, rewardValue;
    Mat temp;
    temp = imgOriginal.clone();
    for (long double t = 0; t < 1000000000000; t++) {
        v1 = rand() % size + (99-(size-1)); //temporary
        v2 = rand() % 2;
        rewardValue = rewardFunction(temp, v1, 1);
        temp = shift(temp, v1, 1);
        
        std::cout << rewardValue << "\n";
        
        
    }
    return 0;
    
}


int rewardFunction(Mat currentState, int id, bool direction) {
    Mat nextState;
    int rewardValue=0;
    nextState = shift(currentState, id, direction);
    
    int nextPixelCount=0;
    int curPixelCount=0;
    
    for (int i = 0; i < currentState.rows; i++) { //assigning id's to each letter
        for (int j = 0; j < currentState.cols; j++) {
            if ((int)imgOriginal.at<uchar>(i, j) > 0) {
                curPixelCount++;
            }
            if ((int)nextState.at<uchar>(i, j) > 0) {
                nextPixelCount++;
            }
        }
    }
    
    if (curPixelCount != nextPixelCount) {
        rewardValue = -10*(curPixelCount- nextPixelCount);
    }
    return rewardValue;
}


Mat shift(Mat state, int id, bool direction) { // 1-right ,0-left
    cv::Mat imgTemp1;
    cv::Mat imgTemp2;
    cv::Mat output;
    
    imgTemp1 = state.clone();
    imgTemp2 = state.clone();
    
    for (int k = 0; k < state.rows; k++) {
        for (int j = 0; j < state.cols; j++) {
            
            Scalar intensity = state.at<uchar>(k, j);
            int intensityValue = (int)intensity.val[0];
            
            if (intensityValue == id) {
                imgTemp1.at<uchar>(k, j) = 0;
            }
            
            if (intensityValue != id) {
                imgTemp2.at<uchar>(k, j) = 0;
            }
        }
        
    }
    
    if (direction) {
        translateImg(imgTemp2, +1, 0);
    }
    else {
        translateImg(imgTemp2, -1, 0);
    }
    
    addWeighted(imgTemp1, 1, imgTemp2, 1, 0,output);
    state = output.clone();
    
    //threshold(output, output, 1, 255, CV_THRESH_BINARY_INV);
    cv::imshow("xxxx", state);
    waitKey(1);
    
    return state;
}

Mat translateImg(Mat &img, int offsetx, int offsety) {
    Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img, img, trans_mat, img.size(), cv::INTER_CUBIC,cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0, 0));
    return trans_mat;
}
*/
