#include <iostream>
#include "filter.h"

using namespace cv;
using namespace std;

void blurImage(cv::Mat& image)
{
    cv::GaussianBlur(image, image, cv::Size(11, 11), 0);
}
void blurImage(Image& img)
{
    cv::Mat image=ImageToMat(img);
    cv::GaussianBlur(image, image, cv::Size(11, 11), 0);
    img=MatToImage(image);
}

void makeGray(cv::Mat& image){
    cv::cvtColor(image, image, 6);
}

void makeGray(Image& img){
    cv::Mat image=ImageToMat(img);
    cv::cvtColor(image, image, 6);
    img=MatToImage(image);
}

void date_and_time(Image& img ){
    cv::Mat mat=ImageToMat(img);
    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }
    time_t now = time(0);
    struct tm tstruct;
    char text[80];
    tstruct = *localtime(&now);
    strftime(text, sizeof(text), "%d.%m.%Y %X", &tstruct);
    string date_time = text;
    Scalar brightness = mean(mat);
    int font = FONT_HERSHEY_SIMPLEX; //tareri dzev
    double font_scale = 0.9; //tarachap
    Scalar font_color;
    if (brightness[0] < 127) {
        font_color = Scalar(255, 255, 255);
    } else {
        font_color = Scalar(0, 0, 0);
    }
    int font_thickness = 2;
    Size text_size = getTextSize(date_time, font, font_scale, font_thickness, nullptr);
    Point text_pos(mat.cols - text_size.width - 10, mat.rows - text_size.height - 10);
    putText(mat, date_time, text_pos, font, font_scale, font_color, font_thickness);
    img=MatToImage(mat);
} 

void date_and_time(cv::Mat& mat ){
    
    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }
    time_t now = time(0);
    struct tm tstruct;
    char text[80];
    tstruct = *localtime(&now);
    strftime(text, sizeof(text), "%d.%m.%Y %X", &tstruct);
    string date_time = text;
    Scalar brightness = mean(mat);
    int font = FONT_HERSHEY_SIMPLEX; //tareri dzev
    double font_scale =0.9; //tarachap
    Scalar font_color;
    if (brightness[0] < 127) {
        font_color = Scalar(255, 255, 255);
    } else {
        font_color = Scalar(0, 0, 0);
    }
    int font_thickness = 2;
    Size text_size = getTextSize(date_time, font, font_scale, font_thickness, nullptr);
    Point text_pos(mat.cols - text_size.width - 10, mat.rows - text_size.height - 10);
    putText(mat, date_time, text_pos, font, font_scale, font_color, font_thickness);
   
} 

void applyFilter(Mat& image, Scalar color)
{
    Mat filter(image.size(), image.type(), color);
    addWeighted(image, 0.5, filter, 0.5, 0, image);
}
void five_filters(Image& img) {
    cv::Mat mat = ImageToMat(img);
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    int width = mat.cols / 5;
    vector<Scalar> filter_colors = {
        Scalar(255, 0, 0),   // blue filter
        Scalar(0, 255, 0),   // green filter
        Scalar(0, 0, 255),   // red filter
        Scalar(0, 255, 255), // yellow filter
        Scalar(255, 0, 255)  // purple filter
    };
    Mat combined(mat.rows, mat.cols, mat.type(), Scalar(0, 0, 0));
    for (int i = 0; i < 5; i++) {
        vector<Point> pts(4);
        pts[0] = Point(i * width, 0);
        pts[1] = Point((i + 1) * width, 0);
        pts[2] = Point((i + 1) * width, mat.rows);
        pts[3] = Point(i * width, mat.rows);
        Mat mask(mat.size(), CV_8UC1, Scalar(0));
        fillConvexPoly(mask, pts, Scalar(255));
        Mat roi(mat.size(), mat.type(), filter_colors[i]);
        mat.copyTo(roi, mask);
        applyFilter(roi, filter_colors[i]);
        roi.copyTo(combined, mask);
    }
    img = MatToImage(combined);
}
void five_filters(cv::Mat& mat) {
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    int width = mat.cols / 5;
    vector<Scalar> filter_colors = {
        Scalar(255, 0, 0),   // blue filter
        Scalar(0, 255, 0),   // green filter
        Scalar(0, 0, 255),   // red filter
        Scalar(0, 255, 255), // yellow filter
        Scalar(255, 0, 255)  // purple filter
    };
    Mat combined(mat.rows, mat.cols, mat.type(), Scalar(0, 0, 0));
    for (int i = 0; i < 5; i++) {
        vector<Point> pts(4);
        pts[0] = Point(i * width, 0);
        pts[1] = Point((i + 1) * width, 0);
        pts[2] = Point((i + 1) * width, mat.rows);
        pts[3] = Point(i * width, mat.rows);
        Mat mask(mat.size(), CV_8UC1, Scalar(0));
        fillConvexPoly(mask, pts, Scalar(255));
        Mat roi(mat.size(), mat.type(), filter_colors[i]);
        mat.copyTo(roi, mask);
        applyFilter(roi, filter_colors[i]);
        roi.copyTo(combined, mask);
    }
      mat=combined;
}

void Grain(cv::Mat& mat){
    if (mat.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noise = cv::Mat::zeros(mat.size(), mat.type());
    randn(noise, cv::Scalar::all(0), cv::Scalar::all(30)); // mean=0, SD=50
    mat+=noise;
}

void Grain(Image& img){
    cv::Mat mat = ImageToMat(img);
    if (mat.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noise = cv::Mat::zeros(mat.size(), mat.type());
    randn(noise, cv::Scalar::all(0), cv::Scalar::all(30)); // mean=0, SD=50
    mat+=noise;
    img = MatToImage(mat);

}

