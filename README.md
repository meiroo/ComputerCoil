# ComputerCoil
### Sample and Experiments for Augmented Reality by meiroo@outlook.com
####Open source License : MIT


see articles at : http://zhuanlan.zhihu.com/computercoil

The code can be compiled at any platform with OpenCV 3.0.0. 

### ThumbTracker Project

##### P1 : PTAM Inter-frame rotation estimation 

The rotation estimation algorithm (esm tracking of thumbnail images) is rewritened with OpenCV (less than 80 lines).  The pose estimation cost less than 0.3 ms (Desktop CPU i5).

Code：https://github.com/meiroo/ComputerCoil/blob/master/ThumbTracker/ThumbTracker.cpp

##### P2 : Relocalisation

When traking failed, find the best matched KeyFrame from map (based on the opencv norm method, very simple and fast).

Code：https://github.com/meiroo/ComputerCoil/blob/master/ThumbTracker/ThumbMap.cpp

-------------------------

中文分界线

-------------------------

这里存放了个人一些关于AR的测试代码，主要包含对一些久远的开源库的调研以及重写。针对每个知识点有相关的文章。可以在 http://zhuanlan.zhihu.com/computercoil 查看。

代码仅依赖于OpenCV 3.0.0，可以在任意平台运行。

### ThumbTracker Project



#####P1 : PTAM跟踪过程中的旋转预测

旋转预测基于ESM跟踪算法。本部分将算法使用OpenCV重写。并且进行了简化（不到80行）。可用于跟踪过程中的旋转预测等。Pose预测矩阵的计算一般小于0.3毫秒（桌面平台i5）

Code：https://github.com/meiroo/ComputerCoil/blob/master/ThumbTracker/ThumbTracker.cpp
#####P2 : 重定位到关键帧

当跟踪失败后，查找最匹配的关键帧。（基于opencv的norm比较，非常简单和快。）

Code：https://github.com/meiroo/ComputerCoil/blob/master/ThumbTracker/ThumbMap.cpp
