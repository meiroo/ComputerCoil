//
//  ThumbMap.cpp
//  
//
//  Created by meiroo on 15/10/27.
//
//

#include "ThumbMap.h"

ThumbMap::ThumbMap(){}

ThumbMap::~ThumbMap(){}


void ThumbMap::addKeyFrame(Thumbnail &t){
    
    Thumbnails.push_back(t);
}

Thumbnail* ThumbMap::getKeyFrame(int i){
    
    if(i >= 0 && i < Thumbnails.size())
        return &Thumbnails[i];
    
    return NULL;
}

int ThumbMap::getSize(){
    return Thumbnails.size();
}

int ThumbMap::findBestKeyFrame(Thumbnail &t, float& outScore){
    unsigned int bestScore = 9e6;
    int bestIndex = -1;
    for(int i = 0; i < Thumbnails.size(); i++){
        //get the difference and compare it to bestScore
        unsigned int score = cv::norm(Thumbnails[i].normImg, t.normImg, cv::NORM_L2SQR);
        if(score < bestScore){
            bestScore = score;
            bestIndex = i;
        }
    }
    
    if(bestIndex != -1){
        outScore = bestScore;
        return bestIndex;
    }
    
    return -1;
    
}


