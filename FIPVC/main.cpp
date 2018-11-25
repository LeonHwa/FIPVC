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

int main(int argc, const char * argv[]) {
    

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
    Matrix *houghMat  = Hough(m_src, m_dst, 0);
    IplImage *image =cvCreateImage(cvSize(houghMat->width, houghMat->height), 8, 1);
    for (int j=0;j<houghMat->height; j++) {
        for(int i=0;i<houghMat->width;i++){
            cvSetReal2D(image, j, i,houghMat->array[j * houghMat->width+i]);
        }
    }
    cvNamedWindow("houghMat", 1);
    cvShowImage("houghMat", image);
    cvWaitKey(0);
    
    //Fig1010(a)(five-dots).tif
//    char *path = Path("nana.png");
//    IplImage *src =cvLoadImage(path, 0);
//    int height =  src->height;
//    int width = src->width;
//    Matrix * m_src = matrixMake(width, height);
//    Matrix * m_dst = matrixMake(width, height);
//    for (int j=0;j<height; j++) {
//        for(int i=0;i<width;i++){
//            m_src->array[j*width+i]=cvGetReal2D(src,j,i);
//        }
//    }
//
//    doSomething(m_src,m_dst);
//
//    IplImage *dst =cvCreateImage(cvSize(width, height), src->depth, 1);
//    for (int j=0;j<height; j++) {
//        for(int i=0;i<width;i++){
//            cvSetReal2D(dst, j, i,m_dst->array[j*width+i]);
//        }
//    }
//    cvNamedWindow("src", 1);
//    cvShowImage("src", src);
//
//    cvNamedWindow("dst", 1);
//    cvShowImage("dst", dst);
//
//
//    IplImage *cv_dst =  cvCreateImage(CvSize(width,height), src->depth, 1);
//    cvCanny(src, cv_dst, low_threshold, hight_threshold);
//
//    cvNamedWindow("opencv_dst", 1);
//    cvShowImage("opencv_dst", cv_dst);
    cvWaitKey(0);
    
//    matrixFree(m_src);
//    matrixFree(m_dst);
    return 0;
}


void doSomething(Matrix *src, Matrix *dst){
//    Matrix *gauss = matrixMake(5, 5);
//    double arr[25] = { 2, 4, 5, 4, 2,
//        4, 9,12, 9, 4,
//        5,12,15,12, 5,
//        4, 9,12, 9, 4,
//        2, 4, 5, 4, 2};
//    Matrix *filter = matrixMake(3, 3);
//    double arr[25] = { -1, -1, -1, 2, 2,
//        2, -1,-1, -1};
//    matrixSet(filter, arr);
//    matrixConvolution(src, dst, filter);
//    matrixMultreal(dst, dst, 1.0/159.0);
//    matrixFree(filter);
    IplImage *src_image =cvLoadImage(Path("nana.png"), 0);
    Canny(src, dst, 3, low_threshold, hight_threshold);
    Matrix *houghMat  = Hough(dst, NULL, 0);
    IplImage *image =cvCreateImage(cvSize(houghMat->width, houghMat->height), src_image->depth, 1);
    for (int j=0;j<houghMat->height; j++) {
        for(int i=0;i<houghMat->width;i++){
            cvSetReal2D(image, j, i,houghMat->array[j * houghMat->width+i]);
        }
    }
    cvNamedWindow("houghMat", 1);
    cvShowImage("houghMat", image);
    cvWaitKey(0);
}



