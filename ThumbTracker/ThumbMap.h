//
//  ThumbMap.h
//  
//
//  Created by meiroo on 15/10/27.
//
//

#ifndef ____ThumbMap__
#define ____ThumbMap__

#include "Thumbnail.h"

class ThumbMap{
public:
    ThumbMap();
    ~ThumbMap();
    
    void addKeyFrame(Thumbnail& t);
    
    Thumbnail* getKeyFrame(int i);
    
    int getSize();
    
    int findBestKeyFrame(Thumbnail& t, float& outScore);
    
private:
    std::vector<Thumbnail> Thumbnails;
    
};

#endif /* defined(____ThumbMap__) */
