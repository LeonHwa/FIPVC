//
//  Hough.c
//  FIPVC
//
//  Created by leon on 2018/11/23.
//  Copyright © 2018年 leon. All rights reserved.
//

#include "Hough.h"
#include "mathematic.h"

#define THETA_RANGE 180 // -90 <= theta <= 90
#define THETA_STEP 0.5 //控制theta 最小步长
#define RHO_RANGE(width, height) sqrt(width * width + height * height)



void DrawLine(Matrix *image, double theta, double pho){
    
     for (int i = 0; i < image->width; i++) {
         
     }
    
}


/**
theta在坐标系中的值域为
[-90 ,90 ]
ph0为[-D,D] (D为图像对角线长度)

 ----------->theta
 |
 |
 |
 |
 pho
 
 pho = x*cos(theta) + y * sin(theta)
 
 @param polar 坐标系
 @param x 系数，边缘点的横坐标
 @param y 系数，边缘点的纵坐标
 */
void PolarShift(Matrix *polar, int x, int y){
    double theta = 0;
    int pho = 0;
    int half_polar_height = polar->height/2;
    for (int j = 0; j < polar->height ; j++) {
        for (int i = 0; i < polar->width; i++) {
            theta = (-90 + i * THETA_STEP) * M_PI/180;
            pho =  (int)(x * cos(theta) + y * sin(theta)) + half_polar_height;
            polar->array[polar->width * pho + i]++;
        }
    }
}
Matrix * Hough(Matrix *src, Matrix *dst, int length){
    int width = src->width;
    int height = src->height;
    /// 显示上下半部分
    int rho_height = RHO_RANGE(width, height) * 2;
    Matrix *polar = matrixMake(THETA_RANGE/THETA_STEP, rho_height);
    for (int j = 0; j < height ; j++) {
        for (int i = 0; i < width; i++) {
            if(src->array[j * width + i] == 255)
              PolarShift(polar, i, j);
        }
    }
    
    for (int j = 0; j < polar->height ; j++) {
        for (int i = 0; i < polar->width; i++) {
            int index = j * polar->width + i;
            if(polar->array[index] >= length){
                double theta =  (-90 + i * THETA_STEP) * M_PI/180;
                DrawLine(dst, theta, j - rho_height/2);
            }
      
        }
    }
    
    
    for(int i=0;i<polar->width * polar->height;i++){
        polar->array[i] = (polar->array[i] != 0 ? 255 : 0);
    }
    return polar;
}
