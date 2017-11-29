//
//  fontSpacerGame.cpp
//  Autokern
//
//  Created by Malith Ranathunga on 11/15/17.
//  Copyright © 2017 NMR. All rights reserved.
//

#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const int alphabetSize = 11;  //should be greater than 2. otherwise fails intializeBaseDistanceArr()
int maxWidthArr[alphabetSize];
int baseDistanceArr[alphabetSize];
int kernValueArr[alphabetSize]={0};

cv::Mat glyphMatArr[alphabetSize];

int rewardfunction(cv::Mat state ){
    int reward=0;
    
    return reward;
}

void printGlyph(cv::Mat glyph){
    
    for (int i =0 ; i<glyph.rows; i++) {
        for (int j = 0; j < glyph.cols; j++)
            if((int)glyph.at<uchar>(i,j) ==255)
                cout << "." << " ";
            else
                cout << (int)glyph.at<uchar>(i,j) << " ";
        cout << endl ;
    }
}

void printStats(){
    cout << "\nbaseDistanceArr  maxWidthArr KernValue\n";
    for(int i=0; i<alphabetSize; i++){
        cout << baseDistanceArr[i] << "\t\t\t\t\t" << maxWidthArr[i] << "\t\t" <<kernValueArr[i]<< endl;
    }
    
}

void intializeBaseDistanceArr(){
    baseDistanceArr[0] = 0;
    //baseDistanceArr[1] = baseDistanceArr[0] + maxWidthArr[0];
    for(int i=1; i<alphabetSize; i++){
        baseDistanceArr[i] = baseDistanceArr[i-1] + maxWidthArr[i-1];
    }
}

cv::Mat state(cv::Mat currentState, int action, int glyphID){
    cv::Mat nextState;
    
    return nextState;
}


cv::Mat gernerateState(){
    cv::Mat currentState = glyphMatArr[0];
    cv::Mat gapMat;
    cv::Mat leftPart,rightPart,commanPart,prevState,temp;
    //kernValueArr[0] = -10;
    //kernValueArr[1] = -10;
    for(int i=1;i<alphabetSize;i++){
        if(kernValueArr[i-1]==0){
            //cout << glyphMatArr[i].type()<<endl;
            cv::hconcat(currentState, glyphMatArr[i], currentState);
        }
        else if(kernValueArr[i-1] >0){
            gapMat = cv::Mat::zeros(currentState.rows, kernValueArr[i-1],CV_8U);
            cv::hconcat(currentState, gapMat, currentState);
            cv::hconcat(currentState, glyphMatArr[i], currentState);
            
            
        }
        else if(kernValueArr[i-1] <0){
            //cv::hconcat(currentState, glyphMatArr[i], currentState);
            leftPart = currentState.colRange((currentState.cols-1)-(kernValueArr[i-1]*-1) , (currentState.cols-1));
            rightPart = glyphMatArr[i].colRange(0, (kernValueArr[i-1]*-1));
            addWeighted( leftPart, 1, rightPart, 1, 0.0, commanPart);
            //printGlyph(commanPart);
            
            leftPart = currentState.colRange(0, (currentState.cols-1)-(kernValueArr[i-1]*-1));
            rightPart = glyphMatArr[i].colRange((kernValueArr[i-1]*-1),glyphMatArr[i].cols-1);
            cv::hconcat(leftPart, commanPart, currentState);
            cv::hconcat(currentState, rightPart, currentState);
        }
    }

    return currentState;
}

void action(int glyphId, bool direction){
    if(glyphId > 0 && glyphId<alphabetSize){
        if(direction){ //true -right
            kernValueArr[glyphId-1] += 1;
            baseDistanceArr[glyphId] += 1;
        }
        else if(abs(kernValueArr[glyphId-1] )+2 < glyphMatArr[glyphId].cols ){
            kernValueArr[glyphId-1] -= 1;
            baseDistanceArr[glyphId] -= 1;

        }
    }
}
/*
void moveLeft(int glypId){
    cv::Mat leftPart,rightPart,commanPart,prevState,temp;
    
    if(baseDistanceArr[0] + maxWidthArr[0] > baseDistanceArr[1] ){
        
    }
    else if(baseDistanceArr[0] + maxWidthArr[0] < baseDistanceArr[1] ){
        
    }
    else{
        leftPart = glyphMatArr[0].colRange(glyphMatArr[0].cols-20-1, glyphMatArr[0].cols-1);
        rightPart = glyphMatArr[1].colRange(0, 20);
        addWeighted( leftPart, 1, rightPart, 1, 0.0, commanPart);
        printGlyph(commanPart);
        prevState = stateMat;
        
        leftPart = prevState.colRange(0, baseDistanceArr[0] + maxWidthArr[0] - 20-2);
        rightPart = prevState.colRange(baseDistanceArr[1]+20-1 , prevState.cols-1);
        //printGlyph(rightPart);
        cv::hconcat(leftPart, commanPart, temp);
        cv::hconcat(temp, rightPart, temp);
        printGlyph(temp);
    }

    
}

*/
class Glyph
{
private:
    static int glyphId;
    int id;
    int maxWidth;
    cv::Mat glyph;

public:
    Glyph()
    {
        
        cout << "glyphId is: " << glyphId << "\n";
        id = glyphId;
        glyphId++;
    }
    
    void setGlyphMat(cv::Mat glyphInput){
        //glyph.colRange(int startcol, int endcol);
        //printGlyph (glyphInput);
        int startcol = 0;
        int endcol = glyphInput.cols ;
        for (int i = 0; i < glyphInput.cols; i++) {
            int count = 0;
            for (int j = 0; j < glyphInput.rows; j++) {
                count += (int)glyphInput.at<uchar>(j,i);
            }
            if (count != 0){
                startcol = i ;
                break;
            }
            
        }
        for (int i = glyphInput.cols -1 ; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < glyphInput.rows; j++) {
                count += (int)glyphInput.at<uchar>(j,i);
                if(count != 0)
                    break;
            }
            if (count != 0){
                endcol = i + 1;
                break;
            }
            
        }
        
        maxWidth = endcol - startcol +1;
        maxWidthArr[id] = maxWidth;
        
        cout << startcol << " " << endcol << " " << maxWidth;
        glyph = glyphInput.colRange(startcol, endcol);
        glyphMatArr[id] = glyph;
    }
    
    cv::Mat getGlyphMat(){
        return glyph;
    }
};

int Glyph::glyphId = 0;

int main(int argc, char** argv)
{
    std::string glyphPath;
    Glyph glyphObject[alphabetSize];
    cv::Mat glyph;
    
    for (int i = 0; i < alphabetSize; i++) {
        glyphPath = "/Users/malithranathunga/Desktop/Research/Code/Autokern/Autokern/" + to_string(i) + ".png";
        cout<< glyphPath << "\n";
        glyph = cv::imread(glyphPath,CV_LOAD_IMAGE_GRAYSCALE);

        threshold(glyph, glyph, 127, 255, CV_THRESH_BINARY_INV); // invert colors
        if(!glyph.data){
            cout<<"Could not open or find the image : " << glyphPath << std::endl ;
            return -1;
        }
        glyphObject[i].setGlyphMat(glyph);          // open image
        glyph = glyphObject[i].getGlyphMat();

        //cv::imshow("xx", glyph);
        //waitKey(5);
        
    }
    intializeBaseDistanceArr();
    printStats();
    //printGlyph(gernerateState());
    //moveLeft(1);
    
    int glyphId;
    bool direction;
    
    for (long double t = 0; t < 1000000000; t++) {
        glyphId = rand() % alphabetSize;
        direction = rand() % 2;
        action(glyphId,direction);
        cv::imshow("xx", gernerateState());
        waitKey(1);
        //printStats();
        printStats();

    }
    printStats();
    return 0;
}
