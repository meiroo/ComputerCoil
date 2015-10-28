//
//  Thumbnail.cpp
//  
//
//  Created by meiroo on 15/10/27.
//
//

#include "Thumbnail.h"

const cv::Size Thumbnail::size = cv::Size(40,30 );

Thumbnail::Thumbnail(){
}

Thumbnail::Thumbnail(const cv::Mat& img){
    cv::resize(img, thumbImg, Thumbnail::size);
    cv::cvtColor(thumbImg, thumbImg, cv::COLOR_BGR2GRAY);
    
    thumbImg.convertTo(normImg, CV_32F);
    
    cv::Scalar mean1, stddev1;
    cv::meanStdDev(normImg, mean1, stddev1);
    for(int i = 0; i<normImg.rows;i++)
        for(int j = 0; j<normImg.cols;j++){
            normImg.at<float>(i,j) -= mean1[0];
        }
    cv::blur(normImg, normImg, cv::Size(3,3));
}
Thumbnail::~Thumbnail(){
    
}