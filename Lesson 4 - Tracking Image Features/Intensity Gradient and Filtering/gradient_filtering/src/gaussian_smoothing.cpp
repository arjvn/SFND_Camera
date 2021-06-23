#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

// void ShowManyImages(string title, int nArgs, ...) {
// int size;
// int i;
// int m, n;
// int x, y;
//
// // w - Maximum number of images in a row
// // h - Maximum number of images in a column
// int w, h;
//
// // scale - How much we have to resize the image
// float scale;
// int max;
//
// // If the number of arguments is lesser than 0 or greater than 12
// // return without displaying
// if(nArgs <= 0) {
//     printf("Number of arguments too small....\n");
//     return;
// }
// else if(nArgs > 14) {
//     printf("Number of arguments too large, can only handle maximally 12 images at a time ...\n");
//     return;
// }
// // Determine the size of the image,
// // and the number of rows/cols
// // from number of arguments
// else if (nArgs == 1) {
//     w = h = 1;
//     size = 300;
// }
// else if (nArgs == 2) {
//     w = 2; h = 1;
//     size = 300;
// }
// else if (nArgs == 3 || nArgs == 4) {
//     w = 2; h = 2;
//     size = 300;
// }
// else if (nArgs == 5 || nArgs == 6) {
//     w = 3; h = 2;
//     size = 200;
// }
// else if (nArgs == 7 || nArgs == 8) {
//     w = 4; h = 2;
//     size = 200;
// }
// else {
//     w = 4; h = 3;
//     size = 150;
// }
//
// // Create a new 3 channel image
// cv::Mat DispImage = cv::Mat::zeros(cv::Size(100 + size*w, 60 + size*h), CV_8UC3);
//
// // Used to get the arguments passed
// va_list args;
// va_start(args, nArgs);
//
// // Loop for nArgs number of arguments
// for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {
//     // Get the Pointer to the IplImage
//     cv::Mat img = va_arg(args, cv::Mat);
//
//     // Check whether it is NULL or not
//     // If it is NULL, release the image, and return
//     if(img.empty()) {
//         printf("Invalid arguments");
//         return;
//     }
//
//     // Find the width and height of the image
//     x = img.cols;
//     y = img.rows;
//
//     // Find whether height or width is greater in order to resize the image
//     max = (x > y)? x: y;
//
//     // Find the scaling factor to resize the image
//     scale = (float) ( (float) max / size );
//
//     // Used to Align the images
//     if( i % w == 0 && m!= 20) {
//         m = 20;
//         n+= 20 + size;
//     }
//
//     // Set the image ROI to display the current image
//     // Resize the input image and copy the it to the Single Big Image
//     cv::Rect ROI(m, n, (int)( x/scale ), (int)( y/scale ));
//     cv::Mat temp; resize(img,temp, cv::Size(ROI.width, ROI.height));
//     temp.copyTo(DispImage(ROI));
// }
//
// // Create a new window, and show the Single Big Image
// cv::namedWindow( title, 1 );
// cv::imshow( title, DispImage);
// cv::waitKey();
//
// // End the number of arguments
// va_end(args);
// }

void gaussianSmoothing1()
{
    // load image from file
    cv::Mat img;
    img = cv::imread("../images/img1gray.png");

    // create filter kernel
    float filter_data[25] = {1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1};

    float gauss_data[25] = {1, 4, 7, 4, 1,
                            4, 16, 26, 16, 4,
                            7, 26, 41, 26, 7,
                            4, 16, 26, 16, 4,
                            1, 4, 7, 4, 1};
    cv::Mat kernel = cv::Mat(5, 5, CV_32F, gauss_data)/25;
    // the values of a kernel need to add up to 1 so that no energy is added
    // to or removed from the image after the operation.


    // apply filter
    cv::Mat result;
    cv::filter2D(img, result, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::Mat blur;
    cv::blur(img, blur, cv::Size(5, 5));
    cv::Mat GuassianBlur;
    cv::GaussianBlur(img, GuassianBlur, cv::Size(5, 5), 0);
    cv::Mat MedianFiltering; //for salt and pepper noise
    cv::medianBlur(img, MedianFiltering, 5);

    // show result
    // ShowManyImages("Gaussian Blurring", 1, img);

    string windowName0 = "Original Image";
    cv::namedWindow(windowName0, 1); // create window
    cv::imshow(windowName0, img);

    string windowName1 = "Blurring via averaging";
    cv::namedWindow(windowName1, 1); // create window
    cv::imshow(windowName1, blur);

    string windowName2 = "Gaussian Blurring";
    cv::namedWindow(windowName2, 1); // create window
    cv::imshow(windowName2, result);



    string windowName4 = "Salt and pepper function";
    cv::namedWindow(windowName4, 1); // create window
    cv::imshow(windowName4, MedianFiltering);

    cv::waitKey(0); // wait for keyboard input before continuing
}

int main()
{
    gaussianSmoothing1();
}
