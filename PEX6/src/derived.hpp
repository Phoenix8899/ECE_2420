#include "Head.hpp"

#include <mutex>

/*
 *
 * derived.hpp
 *
 */

	
class derived : public Head
{
	public:	
	derived();

	void execute(std::function<void()> action);


	std::mutex m_mtx;
	derived* m_left; //Head->left.m_mtx 
	derived* m_right;	
	int m_order;
};
