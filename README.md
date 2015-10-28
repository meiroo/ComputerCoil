# ComputerCoil
### Sample and Experiments for Augmented Reality by meiroo@outlook.com
####Open source License : MIT


see articles at : http://zhuanlan.zhihu.com/computercoil


### ThumbTracker Project

##### P1 : Inter-frame rotation estimation 

The rotation estimation algorithm (esm tracking of thumbnail images) is rewritened with OpenCV (less than 80 lines). 

##### P2 : Relocalisation

When traking failed, find the best matched KeyFrame from map (based on the opencv norm method, very simple).

-------------------------

中文分界线

-------------------------
### ThumbTracker Project
#### P1  PTAM跟踪过程中的旋转预测

旋转预测基于ESM跟踪算法。本部分将算法使用OpenCV重写。并且进行了简化（不到80行）。可用于跟踪过程中的旋转预测等。

##### P2 : 重定位到关键帧

当跟踪失败后，查找最匹配的关键帧。（基于opencv的norm比较，非常简单。）
