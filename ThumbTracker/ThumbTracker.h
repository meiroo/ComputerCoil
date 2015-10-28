//
//  Tracker
//
//  Created by meiroo on 15/10/26.
//
//

#ifndef __Thumb__Tracker__
#define __Thumb__Tracker__

#include "Thumbnail.h"

class ThumbTracker{
public:
    
    ThumbTracker();
    ~ThumbTracker();
    
    void setTemplateThumb(const Thumbnail& t);
    void setCompareThumb(const Thumbnail& c);

    // outPose : the pose transform matrix calculated.
	// outFinalScore : the pixel difference score.
	// return : current template Image. only for view.
    cv::Mat IteratePose(cv::Mat& outPose, float& outFinalScore);
    
private:
    
    Thumbnail templThumb;
    Thumbnail compThumb;

};

#endif /* defined(__Thumb__Tracker__) */
