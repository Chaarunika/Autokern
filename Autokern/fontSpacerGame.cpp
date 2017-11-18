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

void printGlyph(cv::Mat glyph){
    
    for (int i =0 ; i<glyph.rows; i++) {
        for (int j = 0; j < glyph.cols; j++)
            cout << (int)glyph.at<uchar>(i,j) << " ";
        cout << endl ;
    }
}

cv::Mat state(cv::Mat currentState, int action, int glyphID){
    cv::Mat nextState;
    
    return nextState;
}


class Glyph
{
private:
    static int glyphId;
    int maxWidth;
    cv::Mat glyph;

public:
    Glyph()
    {
        
        cout << "glyphId is: " << glyphId << "\n";
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
                startcol = i - 1;
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
        //cout << startcol << " " << endcol ;
        glyph = glyphInput.colRange(startcol, endcol);
    }
    
    cv::Mat getGlyphMat(){
        return glyph;
    }
};

int Glyph::glyphId = 0;

int main(int argc, char** argv)
{
    int alphabetSize = 3;
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

        cv::imshow("xx", glyph);
        waitKey(5000);
        
    }
    
    
    
    return 0;
}
