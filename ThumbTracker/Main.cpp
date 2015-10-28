#include <opencv2/opencv.hpp>
#include "ThumbTracker.h"
#include "ThumbMap.h"


#include <sys/time.h>

int main(){
    
   
   
    cv::VideoCapture cap(0);
    ThumbTracker tracker;
    ThumbMap map;
    
    std::vector<cv::Point2f> screen;
    screen.push_back(cv::Point2f(0, 0));
    screen.push_back(cv::Point2f(0, 480));
    screen.push_back(cv::Point2f(640, 480));
    screen.push_back(cv::Point2f(640, 0));
    
    cv::Mat templateImg ;//set first captured image as template image
    cap >> templateImg;
    Thumbnail templateThumb(templateImg);
    tracker.setTemplateThumb(templateThumb);
    
    // add it to map
    map.addKeyFrame(templateThumb);
    int currentKeyFrameIndex = 0;
    
    

    while (true)
    {
        
        
        
        cv::Mat img;
        cap >> img; //get image from camera
        
        
        float finalScore;
        
        struct timeval tv;
        gettimeofday(&tv,NULL);
        unsigned long s0 = 1000000 * tv.tv_sec + tv.tv_usec;
        
        //make thumbnail for current image
        Thumbnail compThumb(img);
        tracker.setCompareThumb(compThumb);
        
        cv::Mat pose;
        //tracking : find the transform between current image and template image
        cv::Mat currentKeyFrameImg = tracker.IteratePose(pose,finalScore);
        
        cv::Scalar color = cv::Scalar(255, 255, 255); //white
        
        
        if(finalScore > 2.0e6){//tracking failed (the diffrence between current and template image is too large)

            //see if there is some other Keyframe better
            int best = map.findBestKeyFrame(compThumb, finalScore);
            
            
            if(best != -1 && finalScore < 2.0e6){ //finally find it. the use it as tracking template
                tracker.setTemplateThumb(*map.getKeyFrame(best));
                currentKeyFrameIndex = best;
            }else{ //nothing find
                
            }
        }else{  //tracking is OK, draw some information

            //draw pose
            std::vector<cv::Point2f> trans;
            cv::transform(screen, trans, pose);
            for (size_t i = 0; i < screen.size(); ++i) {
                cv::Point2f& r1 = trans[i % 4];
                cv::Point2f& r2 = trans[(i + 1) % 4];
                cv::line(img, r1 , r2 , color, 3, CV_AA);
            }
            
            //draw thumbnail image
            cv::cvtColor(currentKeyFrameImg, currentKeyFrameImg, cv::COLOR_GRAY2BGR);
            cv::resize(currentKeyFrameImg, currentKeyFrameImg, cv::Size(120,90 ));            
            cv::Rect roi = cv::Rect(10, 10, currentKeyFrameImg.cols, currentKeyFrameImg.rows);
            cv::addWeighted( img(roi), 0.0, currentKeyFrameImg, 1.0, 0.0, img(roi));
            
            //draw current template index
            std::stringstream stream;
            stream<<"KF: "<<currentKeyFrameIndex;
            cv::putText(img, stream.str(),cv::Point(50,50), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,255,255),2);
        }
        
        gettimeofday(&tv,NULL);
        unsigned long s1 = 1000000 * tv.tv_sec + tv.tv_usec;
        std::cout << "one round cost time: " << s1 - s0 << " micro" << std::endl;
        std::cout << "score: " << finalScore << " micro" << std::endl;
        
        imshow ("Image", img);

        int k = cv::waitKey(1);
        if (k == 13){
            //Press Enter to add one keyframe
            map.addKeyFrame(compThumb);
            tracker.setTemplateThumb(compThumb);
            currentKeyFrameIndex = map.getSize()-1;
        }else if(k == 32){
            break; // Press Space to exit
        }
        
    }

}