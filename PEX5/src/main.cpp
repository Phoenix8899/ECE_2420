#include <iostream>

#include <stdint.h>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Transformer.hpp"
#include "Color.hpp"
#include "BlacknWhite.hpp"
#include "Edge.hpp"
#include "Fifo.hpp"

using namespace cv;	
std::mutex mtx;

void DisColor(std::shared_ptr<cv::Mat> frame)
{
	mtx.lock();
	cv::imshow("Color", *frame);
	cv::waitKey(25);
	mtx.unlock();
}

void DisBnW(std::shared_ptr<cv::Mat> frame)
{       
        mtx.lock();
        cv::imshow("Black n White", *frame);
        cv::waitKey(25);
        mtx.unlock();
}

void DisEdge(std::shared_ptr<cv::Mat> frame)
{       
        mtx.lock();
        cv::imshow("Edge", *frame);
        cv::waitKey(25);
        mtx.unlock();
}


int main (int argc, char* argv[])
{
//	std::string file = argv[1];
	int tempLen = atoi(argv[2]);
	uint32_t len = tempLen;
	
	//std::shared_ptr<cv::Mat> frame; //this breaks a lot of thingss
	std::shared_ptr<cv::Mat> frame(new Mat()); //im just making crap up here, but i think it works

	
	Fifo<std::shared_ptr<cv::Mat>> F1;
	Fifo<std::shared_ptr<cv::Mat>> F2;
	Fifo<std::shared_ptr<cv::Mat>> F3;	
		
	Color TColor(F1,F2,DisColor,len);
	BlacknWhite TBnW(F2,F3,DisBnW,len);
	Edge TEdge(F3,DisEdge,len);

	VideoCapture cap(argv[1]);
	for (int i = 0;i < len; i++)
	{
		std::shared_ptr<cv::Mat> frame(new Mat()); 
		std::shared_ptr<cv::Mat> passFrame(new Mat()); 
		cap  >> *frame;
                frame->copyTo(*passFrame);
		F1.addItem(passFrame);
//                F1.addItem(frame);

	}
	
	TColor.wait();
	TBnW.wait();
	TEdge.wait();
	
	cap.release();
	destroyAllWindows();
	
}
