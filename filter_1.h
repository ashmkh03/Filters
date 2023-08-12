#pragma once
#include "imageToMat.h"

void makeGray(cv::Mat& image);
void makeGray(Image& img);

void blurImage(cv::Mat& image);
void blurImage(Image& img);

void date_and_time(Image& img );
void date_and_time(cv::Mat& mat);

void five_filters(Image& img);
void five_filters(cv::Mat& mat);

void Grain(Image& img);
void Grain(cv::Mat& mat);
