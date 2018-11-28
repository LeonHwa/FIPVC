//
//  Histogram.c
//  FIPVC
//
//  Created by leon on 2018/11/27.
//  Copyright © 2018年 leon. All rights reserved.
//

#include "Histogram.h"
#define GREY_LEVEL 256

void CaculateSum(Matrix *mat, double sum[]){
    int v = 0;
    for (int  j = 0; j < mat->height; j++) {
        for (int i = 0; i < mat->width; i++) {
            v = mat->array[j * mat->width + i];
            sum[v]++;
        }
    }
}

void HistogramEqualization(Matrix *src, Matrix *dst){
    int width =  src->width;
    int height = src->height;
    double count_grey[GREY_LEVEL] = {};
    CaculateSum(src, count_grey);
    double accumulate[GREY_LEVEL] = {};
    double coefficient = (GREY_LEVEL - 1)/(width * height * 1.0);
    int sum = 0;
    for (int i = 0; i < GREY_LEVEL; i++) {
        sum += count_grey[i];
        accumulate[i] = sum;
    }
    int v = 0;
    for (int  j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            v = src->array[j * width + i];
            dst->array[j * width + i] = coefficient * accumulate[v];
        }
    }
}
