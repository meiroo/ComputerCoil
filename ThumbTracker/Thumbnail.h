//
//  Thumbnail.h
//  
//
//  Created by meiroo on 15/10/27.
//
//

#ifndef ____Thumbnail__
#define ____Thumbnail__

#include <stdio.h>
#include <opencv2/opencv.hpp>

class Thumbnail{
public:
    
    Thumbnail();
    Thumbnail(const cv::Mat& image);
    ~Thumbnail();
    
    cv::Mat thumbImg; //thumbnail image
    cv::Mat normImg;  //thumbnail image after normalized
    
    const static cv::Size size;
};

#endif /* defined(____Thumbnail__) */
