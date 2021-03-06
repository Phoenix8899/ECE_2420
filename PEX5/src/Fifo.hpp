#ifndef FIFO_HPP
#define FIFO_HPP

#include <list>
#include <mutex>
#include <condition_variable>

/**
 * @class Fifo
 *
 * The purpose of this class is to create a templatized 
 * software fifo that has blocking read/pop functionality
 *
 * Arbitrary objects can be placed in the FIFO in a thread safe
 * manner.  They can also be removed in a thread safe way, and if
 * the fifo is empty, the pop will block until it has something to return
 *
 * The Fifo should function in a "by value" way.  I.E. when items are added,
 * they are copied into the fifo.  When they are popped, the item that is
 * popped is used to populate the passed in by ref object
 */
template<class T>
class Fifo
{
public:
  /**
   * @brief Add Item to fifo
   *
   * @param item Object to be copied into FIFO
   */
  void addItem(const T &item)
  {
	std::unique_lock<std::mutex> lck(m_mtx);
  	m_items.push_back(item);
	m_cv.notify_all();	
  }


  /**
   * @brief Pop item from fifo
   *
   * @param item Object to be populated with the value
   *   of the object being removed from the fifo
   */
  void popItem(T &item)
  {
	std::unique_lock<std::mutex> lck(m_mtx);
	m_cv.wait(lck, [this](){return m_items.size() > 0;}); //think of as error checking, so that we cant pop / trash
	item = m_items.front();
  	m_items.pop_front();
  }
private:
  /** @brief Used to track/contain FIFO contents */
  std::list<T> m_items;
  /** @brief Needed to protect list and for use by m_cv */
  std::mutex m_mtx;
  /** @brief Used to manage sleeping until FIFO not emtpy */
  std::condition_variable m_cv;  
};

#endif /* FIFO_HPP */
