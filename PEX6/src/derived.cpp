#include "derived.hpp"

/*
 *
 * derived.cpp
 *
 */

	derived::derived()
	:Head()
	{
	}

	void derived::execute(std::function<void()> action)
	{
        std::unique_lock<std::mutex> lockLeft (m_left->m_mtx, std::defer_lock);
	std::unique_lock<std::mutex> lockRight (m_right->m_mtx, std::defer_lock);
        std::unique_lock<std::mutex> lockSelf (m_mtx, std::defer_lock);


	std::lock(lockLeft,lockRight,lockSelf); //john claims this doesnt need order

	//if (m_right.m_order == 0) //check syntax //m_left.order < right 
        //{
		//lock RIGHT then LEFT then SELF
        //}
	//else if (m_order == 0)
        //{
         	//lock SELF then RIGHT then LEFT
        //}
        //else 
        //{
        	//lock LEFT then SELF then RIGHT
        //}
		
		
	action();
	
	//DO I NEED A SLEEP IN HERE?
	
	//unique lock will unlock when out of scope...	

	//KEY:	regardless of pattern there is a deadlock w/o more complex solution
	//	remember the inclass cookies there was a list that must be followed.
	
	}

