#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void gradientSobel()
{
    // TODO: Based on the image gradients in both x and y, compute an image
    // which contains the gradient magnitude according to the equation at the
    // beginning of this section for every pixel position. Also, apply different
    // levels of Gaussian blurring before applying the Sobel operator and compare the results.

    // load image from file
    cv::Mat img;
    img = cv::imread("../images/img1.png");

    // convert image to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // create filter kernel
    float sobel_x[9] = {-1, 0, +1,
                        -2, 0, +2,
                        -1, 0, +1};

    float sobel_y[9] = {-1, -2, -1,
                        0, 0, 0,
                        +1, +2, +1};

    float gauss_data[25] = {1, 4, 7, 4, 1,
                            4, 16, 26, 16, 4,
                            7, 26, 41, 26, 7,
                            4, 16, 26, 16, 4,
                            1, 4, 7, 4, 1};

    cv::Mat kernel_x = cv::Mat(3, 3, CV_32F, sobel_x);
    cv::Mat kernel_y = cv::Mat(3, 3, CV_32F, sobel_y);
    cv::Mat gauss_kernel = cv::Mat(5, 5, CV_32F, gauss_data)/273;

    // apply filter
    cv::Mat result_x, result_y, result_gauss, result_x_gauss, result_y_gauss;;
    cv::GaussianBlur(imgGray, result_gauss, cv::Size(5, 5), 3);
    // cv::filter2D(imgGray, result_gauss, -1, gauss_kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(result_gauss, result_x_gauss, -1, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(result_gauss, result_y_gauss, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    cv::filter2D(imgGray, result_x, -1, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(imgGray, result_y, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    cv::Mat Sobel_filter = imgGray.clone();
    cv::Mat Sobel_filter_gauss = imgGray.clone();
    for (int r = 0; r < Sobel_filter.rows; r++) {
      for (int c = 0; c < Sobel_filter.cols; c++) {
        Sobel_filter.at<unsigned char>(r, c) = sqrt(pow(result_x.at<unsigned char>(r,c), 2) + pow(result_y.at<unsigned char>(r, c), 2));
        Sobel_filter_gauss.at<unsigned char>(r, c) = sqrt(pow(result_x_gauss.at<unsigned char>(r,c), 2) + pow(result_y_gauss.at<unsigned char>(r, c), 2));
      }
    }

    // show result
    string windowName1 = "Sobel operator (x-direction)";
    cv::namedWindow( windowName1, 1 ); // create window
    cv::imshow(windowName1, result_x);

    string windowName2 = "Sobel operator (y-direction)";
    cv::namedWindow( windowName2, 1 ); // create window
    cv::imshow(windowName2, result_y);

    string windowName3 = "Sobel filter";
    cv::namedWindow( windowName3, 1 ); // create window
    cv::imshow(windowName3, Sobel_filter);

    string windowName4 = "Sobel filter + gauss";
    cv::namedWindow( windowName4, 1 ); // create window
    cv::imshow(windowName4, Sobel_filter_gauss);

    cv::waitKey(0); // wait for keyboard input before continuing
}

int main()
{
    gradientSobel();
}
