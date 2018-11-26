//
//  main.cpp
//  FIPVC
//
//  Created by leon on 2018/11/21.
//  Copyright © 2018年 leon. All rights reserved.
//
#include <opencv2/opencv.hpp>
#include <string.h>


#ifdef __cplusplus
extern "C"{
#endif
    
    
#include "Matrix.h"
#include "mathematic.h"
#include "Canny.h"
#include "Hough.h"
#ifdef __cplusplus
}
#endif



#define low_threshold 50
#define threshold_ratio 3
#define hight_threshold   low_threshold * threshold_ratio
using namespace std;

char *Path(const char * fileName){
    
    const char *basePath  = "/Users/leon/Documents/GitHub/FIPVC/FIPVC/";
    const size_t len = strlen(basePath)+strlen(fileName);
    char *path =  new char[len +1];
    strcpy(path, basePath);
    strcat(path, fileName);
    return path;
}
void doSomething(Matrix *src, Matrix *dst);


void houghLineTest(){
    int height =  101;
    int width = 101;
    Matrix * m_src =  matrixMake(width, height);
    Matrix * m_dst =  matrixMake(width, height);
    for (int j=0;j<height; j++) {
        for(int i=0;i<width;i++){
            int index = j * width + i;
            if(index == 0 ||
               (j == 0 && i == width - 1) ||
               (j == height - 1 && i == width - 1) ||
               (j == height - 1 && i == 0) ||
               (j == height/2 && i == width/2 ))
                m_src->array[index] = 255;
        }
    }
    Matrix *houghMat  = Hough(m_src, m_dst, 3);
    IplImage *image =cvCreateImage(cvSize(houghMat->width, houghMat->height), 8, 1);
    for (int j=0;j<houghMat->height; j++) {
        for(int i=0;i<houghMat->width;i++){
            cvSetReal2D(image, j, i,houghMat->array[j * houghMat->width+i]);
        }
    }
    cvNamedWindow("houghMat", 1);
    cvShowImage("houghMat", image);
    cvWaitKey(0);
}


void sbsb(){
    
    IplImage *srcRGB = cvLoadImage(Path("22.jpeg"));
    IplImage *src = cvCreateImage(cvSize(srcRGB->width,srcRGB->height),IPL_DEPTH_8U,1);
    
    cvCvtColor(srcRGB,src,CV_RGB2GRAY);
    IplImage *dst = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,src->nChannels);
    IplImage *color_dst = cvCloneImage(srcRGB);cvSetZero(color_dst);
    CvMemStorage *storage = cvCreateMemStorage();
    CvSeq *lines = 0;
    
    
    cvCanny(src,dst,40,90);
    cvCvtColor(dst,color_dst,CV_GRAY2RGB);
    
    
    
    
    
#if 1
    lines = cvHoughLines2(dst
                          ,storage
                          ,CV_HOUGH_STANDARD
                          ,1
                          ,CV_PI/180
                          ,150
                          ,0
                          ,0);
    for(int i = 0;i<MIN(lines->total,100);i++){
        float *line = (float*)cvGetSeqElem(lines,i);
        float rho = line[0];
        float threta = line[1];
        CvPoint pt1, pt2; // 这个地方的计算公式，在文章下面介绍。
        double a = cos(threta),b = sin(threta);
        double x0 = a*rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        cvLine(color_dst,pt1,pt2,CV_RGB(255,0,0),1,8);
    }
#else
    lines = cvHoughLines2(dst,
                          storage,
                          CV_HOUGH_PROBABILISTIC,
                          1,
                          CV_PI/180,
                          100,
                          50,
                          10);
    for(int i = 0;i<lines->total; ++i){
        CvPoint *line = (CvPoint*)cvGetSeqElem(lines,i);
        cvLine(color_dst,line[0],line[1],CV_RGB(255,0,0),1,8);
    }
#endif
    
    
    cvShowImage("source",src);
    cvShowImage("Hough",color_dst);
    cvShowImage("dst",dst);
    cvWaitKey(0);
    

}
int main(int argc, const char * argv[]) {
 
//    houghLineTest();
    
    char *path = Path("22.jpeg");
    IplImage *src =cvLoadImage(path, 0);
    int height =  src->height;
    int width = src->width;
    Matrix * m_src = matrixMake(width, height);
    Matrix * m_dst = matrixMake(width, height);
    for (int j=0;j<height; j++) {
        for(int i=0;i<width;i++){
            m_src->array[j*width+i]=cvGetReal2D(src,j,i);
        }
    }

    doSomething(m_src,m_dst);


    Matrix * Hough_dst = matrixMake(width, height);

    m_dst  =  Hough(m_dst, Hough_dst, height * 0.8);

    IplImage *dst =cvCreateImage(cvSize(m_dst->width, m_dst->height), src->depth, 1);
    for (int j=0;j<m_dst->height; j++) {
        for(int i=0;i<m_dst->width;i++){
            cvSetReal2D(dst, j, i,m_dst->array[j*m_dst->width+i]);
        }
    }
    cvNamedWindow("src", 1);
    cvShowImage("src", src);

    cvNamedWindow("dst", 1);
    cvShowImage("dst", dst);


    IplImage *cv_dst =  cvCreateImage(CvSize(width,height), src->depth, 1);
    cvCanny(src, cv_dst, low_threshold, hight_threshold);

    cvNamedWindow("opencv_dst", 1);
    cvShowImage("opencv_dst", cv_dst);
    cvWaitKey(0);

    matrixFree(m_src);
    matrixFree(m_dst);
    return 0;
}


void doSomething(Matrix *src, Matrix *dst){
  
    Canny(src, dst, 3, low_threshold, hight_threshold);
   
}



