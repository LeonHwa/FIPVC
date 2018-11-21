//
//  main.cpp
//  FIPVC
//
//  Created by appl on 2018/11/21.
//  Copyright © 2018年 leon. All rights reserved.
//

#ifdef __cplusplus
extern "C"{
#endif
    
#include "Matrix.h"
#include "mathematic.h"
    
    
#ifdef __cplusplus
}
#endif



#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>



using namespace std;

char *Path(const char * fileName){
    const char *basePath  = "/Users/appl/Documents/GitHub/FIPVC/FIPVC/";
    const size_t len = strlen(basePath)+strlen(fileName);
    char *path =  new char[len +1];
    strcpy(path, basePath);
    strcat(path, fileName);
    return path;
}
void doSomething(Matrix *src, Matrix *dst);

int main(int argc, const char * argv[]) {
    
    IplImage *src =cvLoadImage(Path("Lena.png"), 0);
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
    
    IplImage *dst =cvCreateImage(cvSize(width, height), src->depth, 1);
    for (int j=0;j<height; j++) {
        for(int i=0;i<width;i++){
            cvSetReal2D(dst, j, i,m_dst->array[j*width+i]);
        }
    }
    cvNamedWindow("src", 1);
    cvShowImage("src", src);
    
    cvNamedWindow("dst", 1);
    cvShowImage("dst", dst);
    cvWaitKey(0);
    
    return 0;
}


void doSomething(Matrix *src, Matrix *dst){
    Matrix *gauss = matrixMake(5, 5);
    double arr[25] = { 2, 4, 5, 4, 2,
        4, 9,12, 9, 4,
        5,12,15,12, 5,
        4, 9,12, 9, 4,
        2, 4, 5, 4, 2};
    matrixSet(gauss, arr);
    matrixConvolution(src, dst, gauss);
    matrixMultreal(dst, dst, 1.0/159.0);
}



