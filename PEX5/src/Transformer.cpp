#include "Transformer.hpp"


	Tramsformer::Transformer(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              Fifo<std::shared_ptr<cv::Mat> > &outFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
	:m_inFifo(inFifo),
	 m_outFifo(outFifo),
	 m_displayFunc(displayFunc)
	{		
		m_last == false;
		m_pProcessThread.reset (new std::thread (&Transformer::process,this,frameCount));
	}

	Transformer::Transformer(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
	:m_inFifo(inFifo),
	 m_displayFunk(displayFunc)
	{	
		m_last == true;
		std::thread t(&Transformer::process,m_pProcessThread,frameCount);
	}

	void Transformer::wait()
	{
		m_pProcessThread->join();
	}

	void Transformer::process(uint32_t frameCount)
	{
		std::shared_ptr<cv::Mat> pFrame;
		m_inFifo.popItem(pFrame);
		transform(pFrame); 
		m_displayFunc(pFrame);
		if (!m_last)
			m_outFifo.addItem(pFrame);
	}
	

	//TODO 
	//
	//new class for each tranform? 
	// just constructor 
	// just transform
	//
