#include "Transformer.hpp"

class BlacknWhite : public Transformer
{
	public:
         BlacknWhite(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              Fifo<std::shared_ptr<cv::Mat> > &outFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount);


        virtual std::shared_ptr<cv::Mat> transform(std::shared_ptr<const cv::Mat> pInFrame);


};

