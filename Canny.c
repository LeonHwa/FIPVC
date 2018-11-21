//
//  Canny.c
//  OCImageProcessing
//
//  Created by appl on 2018/11/12.
//  Copyright © 2018年 appl. All rights reserved.
//

#include "Canny.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>



///*
// *   四个角度对应编号
// *   0 1 2
// *   3 * 5
// *   6 7 8
// *   edgedirction
// */
//void getEdgeDirection(double *edgedirection,double *sample_direction,int width,int height){
//    double angle=0.0;
//    for(int i=0;i<width*height;i++){
//        angle=edgedirection[i];
//        if(angle<22.5||angle>=337.5)/// 垂直边缘
//            sample_direction[i]=5.0;
//        else if(angle<67.5&&angle>=22.5)/// +45边缘
//            sample_direction[i]=2.0;
//        else if(angle<112.5&&angle>=67.5)/// 水平边缘
//            sample_direction[i]=1.0;
//        else if(angle<157.5&&angle>=112.5)///  -45边缘
//            sample_direction[i]=0.0;
//        else if(angle<202.5&&angle>=157.5)
//            sample_direction[i]=3.0;
//        else if(angle<247.5&&angle>=202.5)
//            sample_direction[i]=6.0;
//        else if(angle<292.5&&angle>=247.5)
//            sample_direction[i]=7.0;
//        else if(angle<337.5&&angle>=292.5)
//            sample_direction[i]=8.0;
//        else if(angle==-1.0)
//            sample_direction[i]=-1.0;
//    }
//}
///*
// *   四个角度对应编号
// *   0 1 2
// *   3 * 5
// *   6 7 8
// *
// */
//// Non_MaxSuppression(edge_a, temp, edge_d, width, height);
////非最大抑制
//void Non_MaxSuppression(double *src,double *dst,double *dirction,int width,int height){
//    double *temp=(double*)malloc(sizeof(double)*width*height);
//    int dir;
//    int y;
//    int x;
//    double value_c;
//    Zero(temp, width, height);
//    for(int j=1;j<height-1;j++)
//        for(int i=1;i<width-1;i++){
//            if(dirction[j*width+i]!=-1.0){
//                dir=(int)dirction[j*width+i];
//                y=dir/3-1;
//                x=dir%3-1;
//                value_c=src[j*width+i];
//                if(value_c<=src[(j+y)*width+i+x]||value_c<src[(j-y)*width+i-x])
//                    temp[j*width+i]=0.0;
//                else
//                    temp[j*width+i]=value_c;
//            }
//        }
//    matrixCopy(temp, dst, width, height);
//    free(temp);
//}
//void EdgeTrack(double *src,int width,int height,Position *seed){
//    int x=seed->x;
//    int y=seed->y;
//    if(x>=0&&x<width&&y>=0&&y<height&&src[y*width+x]==1.0){
//        src[y*width+x]=2;
//        for(int j=-1;j<2;j++)
//            for(int i=-1;i<2;i++){
//                if(!(j==0&&i==0)){
//                    Position seed_next;
//                    seed_next.x=x+i;
//                    seed_next.y=y+j;
//                    EdgeTrack(src,width,height,&seed_next);
//                }
//            }
//    }
//}
//void NonZeroSetOne(double *src,double *dst,int width,int height){
//    for(int i=0;i<width*height;i++)
//        dst[i]=src[i]!=0.0?1.0:0.0;
//}
//void Canny(double *src,double *dst,int width,int height,int sobel_size,double threshold1,double threshold2){
//    double *temp=(double *)malloc(sizeof(double)*width*height);
//    double *edge_a=(double *)malloc(sizeof(double)*width*height);//边缘幅度
//    double *edge_d=(double *)malloc(sizeof(double)*width*height);//边缘方向
//    double *threshold_max=(double *)malloc(sizeof(double)*width*height);
//    double *threshold_min=(double *)malloc(sizeof(double)*width*height);
//    /*
//     *step1:gaussian smooth
//     */
//    double gaussianmask[25]={ 2, 4, 5, 4, 2,
//        4, 9,12, 9, 4,
//        5,12,15,12, 5,
//        4, 9,12, 9, 4,
//        2, 4, 5, 4, 2};
//    RealConvolution(src, temp, gaussianmask, width, height, 5, 5);
//    matrixMultreal(temp, temp, 1.0/159.0, width, height);
//    /*
//     *step2:sobel
//     */
//    if(sobel_size==3)
//        Scharr(temp, edge_a, edge_d, width, height);
//    else if(sobel_size==5||sobel_size==7)
//        Sobel(temp, edge_a, edge_d, width, height,sobel_size);
//    /*
//     *step3:Non_MaxSuppression
//     */
//    getEdgeDirection(edge_d, edge_d, width, height);
//    Non_MaxSuppression(edge_a, temp, edge_d, width, height);
//    /*
//     *step4:double threshold
//     */
//    Threshold(temp, threshold_max, width, height, threshold1, MORETHAN);
//    Threshold(temp, threshold_min, width, height, threshold2, MORETHAN);
//    NonZeroSetOne(threshold_max,threshold_max,width,height);
//    NonZeroSetOne(threshold_min,threshold_min,width,height);
//
//    for(int j=0;j<height;j++){
//        for(int i=0;i<width;i++){
//            if(threshold_max[j*width+i]==1.0&&threshold_min[j*width+i]!=2.0){
//                Position p;
//                p.x=i;
//                p.y=j;
//                EdgeTrack(threshold_min, width, height, &p);
//            }
//
//        }
//    }
//    /*
//     *step5:result
//     */
//    Zero(dst, width, height);
//    for(int i=0;i<width*height;i++)
//        if(threshold_min[i]==2.0)
//            dst[i]=255.0;
//    free(temp);
//    free(threshold_max);
//    free(threshold_min);
//    free(edge_d);
//    free(edge_a);
//
//}
