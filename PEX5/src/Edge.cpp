#include "Edge.hpp"

using namespace cv; //i hate this but it helps when useing the examples

        Edge::Edge(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
        :Transformer(inFifo, displayFunc, frameCount)
        {
        }

        std::shared_ptr<cv::Mat> Edge::transform(std::shared_ptr<const cv::Mat> pInFrame)
        {	
		Mat edge;
		std::shared_ptr<cv::Mat> pOutFrame (new cv::Mat());
		Canny(*pInFrame, edge, 50, 150, 3);
		edge.convertTo(*pOutFrame, CV_8U);
		
                return pOutFrame;
        }

