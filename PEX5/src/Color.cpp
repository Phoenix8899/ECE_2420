#include "Color.hpp"
	
using namespace cv; //i hate this but it helps when useing the examples

	Color::Color(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              Fifo<std::shared_ptr<cv::Mat> > &outFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
        : Transformer(inFifo, outFifo, displayFunc, frameCount)

        {
        }

	std::shared_ptr<cv::Mat> Color::transform(std::shared_ptr<const cv::Mat> pInFrame)
	{
		std::shared_ptr<cv::Mat> pOutFrame (new cv::Mat());
		pInFrame->copyTo(*pOutFrame);
		return pOutFrame;
	}
	
