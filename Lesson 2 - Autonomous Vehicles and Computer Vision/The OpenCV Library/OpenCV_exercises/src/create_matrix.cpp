#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


using namespace std;

void createMatrix1()
{
    // create matrix
    int nrows = 480, ncols = 640;
    cv::Mat m1_8u;
    cv::Mat m3_8u;
    //CV_8UC1 => a color depth of 8 bit as unsigned char and a single channel
    m1_8u.create(nrows, ncols, CV_8UC1); // two-channel matrix with 8bit unsigned elements
    m1_8u.setTo(cv::Scalar(255));        // white

    m3_8u.create(nrows, ncols, CV_8UC3); // two-channel matrix with 8bit unsigned elements
    m3_8u.setTo(cv::Scalar(255));

    // STUDENT TASK :
    // Create a variable of type cv::Mat* named m3_8u which has three channels with a
    // depth of 8bit per channel. Then, set the first channel to 255 and display the result.
    

    // show result
    string windowName = "First steps in OpenCV (m1_8u)";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, m3_8u);
    cv::waitKey(0); // wait for keyboard input before continuing

    // STUDENT TASK :
    // Display the results from the STUDENT TASK above

}


int main()
{
    createMatrix1();
    return 0;
}
