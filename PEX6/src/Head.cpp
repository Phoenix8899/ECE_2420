#include "Head.hpp"
#include "derived.hpp"

/*
 *
 * Head.cpp
 *
 */
	Head::Head()
	{
	}

	std::vector<std::shared_ptr<Head> > Head::makePlatter(int numHeads)//Head::?
	{
	//this calls head numHeads times 
	
	std::vector<std::shared_ptr<derived> >  VofH; //local vector 	
	
	for (int i = 0; i < numHeads; i++)
	{
		std::shared_ptr<derived> head(new derived());
		head->m_order = i; 
		VofH.push_back(head);
	}

	for (int i = 0; i < numHeads; i++)
	{
		VofH[i]->m_left = VofH[(i-1+numHeads) % numHeads].get();
		VofH[i]->m_right = VofH[(i+1)%numHeads].get();
	}
		
	return std::vector<std::shared_ptr<Head>> (VofH.begin(), VofH.end());
	
	}
	//   give it access to the left and right mutex
	//   -- either through the neighbor object
	//   -- direct access to the neighbor's mutex
	
	//	after making all heads, assign awareness?

