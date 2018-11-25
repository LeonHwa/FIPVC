//
//  mathematic.c
//  FIPVC
//
//  Created by leon on 2018/11/21.
//  Copyright © 2018年 leon. All rights reserved.
//

#include "mathematic.h"

void Zero(double *src,int width,int height){
    for (int i = 0; i < width * height; i++) {
        src[i] = 0;
    }
}





void matrixConvolution(Matrix *src, Matrix *dst, Matrix *mask){
    if(src->width != dst->width && src->height != dst->height){
        printf("size is not match !");
        exit(0);
    }
    if(dst == NULL){
        printf("dst can not be NULL\n");
        exit(0);
    }
    int height = src->height;
    int width = src-> width;
    int m_width= mask->height;
    int m_height= mask->height;
    int mask_center_x = m_width/2;
    int mask_center_y = m_height/2;
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            double value=0.0;
            for(int n=0;n<m_height;n++)
                for(int m=0;m<m_width;m++){
                    int x = i+m-mask_center_x;
                    int y = j+n-mask_center_y;
                    if(x <width&&y<height&&
                       x>=0&&y>=0){
                        value += src->array[y*width + x] * mask->array[n*m_width+m];
                    }
                }
            dst->array[j*width+i]=value;
        }
}

void matrixMultreal(Matrix *src, Matrix *dst,double k){
    for(int i=0;i<src->width * src->height;i++)
        dst->array[i] = src->array[i]*k;
}


void matrixToBinary(Matrix *src, Matrix *dst){
    for(int i=0;i<src->width * src->height;i++){
        dst->array[i] = (src->array[i] != 0 ? 1 : 0);
    }
}


