#include "Transformer.hpp"

class Edge : public Transformer
{
	public:
         Edge(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount);


        virtual std::shared_ptr<cv::Mat> transform(std::shared_ptr<const cv::Mat> pInFrame);


};

