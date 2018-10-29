#include "BlacknWhite.hpp"

using namespace cv; //i hate this but it helps when useing the examples

        BlacknWhite::BlacknWhite(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              Fifo<std::shared_ptr<cv::Mat> > &outFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
        :Transformer(inFifo, outFifo, displayFunc, frameCount)
        {
        }

        std::shared_ptr<cv::Mat> BlacknWhite::transform(std::shared_ptr<const cv::Mat> pInFrame)
        {	
		//Mat image = *pInFrame;
		//Mat gray;
//		cvtColor(image, gray, CV_BGR2GRAY);
		
		std::shared_ptr<cv::Mat> pOutFrame (new cv::Mat());
//		*pOutFrame = gray;	
		cvtColor(*pInFrame, *pOutFrame, CV_BGR2GRAY);
                return pOutFrame;
        }

