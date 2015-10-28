//
//  Tracker
//
//  Created by meiroo on 15/10/26.
//
//

#include "ThumbTracker.h"
#include <random>


ThumbTracker::ThumbTracker(){
}


ThumbTracker::~ThumbTracker(){


}

void ThumbTracker::setTemplateThumb(const Thumbnail& t)
{
    templThumb = t;
}

void ThumbTracker::setCompareThumb(const Thumbnail& c)
{
    compThumb = c;
}


cv::Mat ThumbTracker::IteratePose(cv::Mat& outPose, float& outFinalScore)
{
    
    //initialize pose to be calculated.
    cv::Mat Pose;
    if(outPose.empty())
        Pose = cv::Mat::eye(2, 3, CV_32F);
    else
        Pose = outPose.clone();
    
    cv::Mat warpImage;
    
    
    // 2 iterations. can be added for accuracy.
    for(int i = 0; i< 3; i++){
        outFinalScore = 0.0;
        
        cv::Mat transform = Pose;
        
        //inverse warp. 
        //make the warpImage accroding to the template image
        cv::warpAffine(compThumb.normImg, warpImage, transform, compThumb.normImg.size(),cv::WARP_INVERSE_MAP|cv::INTER_LINEAR);
        

        cv::Vec3f v3Accum(0, 0, 0);
        cv::Vec6f v6Triangle(0, 0, 0, 0, 0, 0);
        
        for( int j = 1; j< warpImage.rows -1; j++)
            for(int k = 1; k <warpImage.cols -1; k++){
            
                //gradient for template and warpImage
                float l,r,u,d,here;
                l = templThumb.normImg.at<float>(j,k-1);
                r = templThumb.normImg.at<float>(j,k+1);
                u = templThumb.normImg.at<float>(j-1,k);
                d = templThumb.normImg.at<float>(j+1,k);
                here = templThumb.normImg.at<float>(j,k);
                
                cv::Point2f templGrad;
                templGrad.x = (r - l)/2;
                templGrad.y = (d - u)/2;
                
                float cl,cr,cu,cd,chere;
                cl = warpImage.at<float>(j,k-1);
                cr = warpImage.at<float>(j,k+1);
                cu = warpImage.at<float>(j-1,k);
                cd = warpImage.at<float>(j+1,k);
                chere = warpImage.at<float>(j,k);
                
                cv::Point2f warpGrad; 
                warpGrad.x = (cr - cl)/2;
                warpGrad.y = (cd - cu)/2;
                
                
                //make parameters for the ESM-model  JT J ∆p = JT e,
                cv::Point2f v2SumGrad = 0.5 * (templGrad  + warpGrad); //JxESM = 0.5[J(δ) +J(0)]. 
                cv::Vec3f v3Jac(v2SumGrad.x, v2SumGrad.y, -(j) * v2SumGrad.x + (k) * v2SumGrad.y);
                
                double dDiff = here - chere;
                outFinalScore += dDiff * dDiff;
                
                v3Accum += dDiff * v3Jac; //JT e
                
                //JT J
                v6Triangle[0] += v3Jac[0] * v3Jac[0];
                v6Triangle[1] += v3Jac[1] * v3Jac[0];
                v6Triangle[2] += v3Jac[1] * v3Jac[1];
                v6Triangle[3] += v3Jac[2] * v3Jac[0];
                v6Triangle[4] += v3Jac[2] * v3Jac[1];
                v6Triangle[5] += v3Jac[2] * v3Jac[2];
            }
        
        cv::Mat m3 = cv::Mat::zeros(3, 3, CV_32F); //JT J
        int v = 0;
        for(int j=0; j<3; j++)
            for(int i=0; i<=j; i++)
                m3.at<float>(j,i) = m3.at<float>(i,j) = v6Triangle[v++];
        
        
        //solve the model and get ∆p.
        cv::Mat update;
        cv::solve(m3, v3Accum, update);
        
        //calculate updateMat from ∆p
        cv::Mat updateMat = cv::Mat::zeros(3, 3, CV_32F);
        updateMat.at<float>(0,0) = updateMat.at<float>(1,1) = cos(update.at<float>(2,0));
        updateMat.at<float>(1,0) = sin(update.at<float>(2,0));
        updateMat.at<float>(0,1) = -updateMat.at<float>(1,0);
        updateMat.at<float>(2,2) = 1;
        updateMat.at<float>(0,2) = update.at<float>(0,0);
        updateMat.at<float>(1,2) = update.at<float>(1,0);

        //apply to Pose
        Pose = Pose * updateMat;
        
    }
    
    outPose = Pose;
    
    cv::Mat outImage; //only for show current template image.
    templThumb.normImg.convertTo(outImage, CV_8U);
    return outImage;
}
