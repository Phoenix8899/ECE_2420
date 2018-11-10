#include "cityMap.hpp"


	
	void cityMap::psudoConstructor(std::string nodeName, std::string edgeName, uint32_t distance)
	{
		//TODO make real constructor based on this but with a file;
		edge eTemp;
		node nTemp;
		
		nTemp.name = nodeName;
		eTemp.name = edgeName;
		eTemp.distance  = distance;				
		
	
		if (m_nodes.size() == 0)
		{
			m_nodes.push_back(nTemp);
		}
		else
		{
			for(int i = 0; i < m_nodes.size(); i++)
			{
				if(m_nodes[i].name == edgeName)
				{	
					edge otherTemp;
					otherTemp.name = nodeName;
					otherTemp.distance = distance;
					m_nodes[i].m_neighbors.push_back(otherTemp);
				}			
				if (m_nodes[i].name == nodeName)
				{
					m_nodes[i].m_neighbors.push_back(eTemp);
					return;	
				}
			}
		m_nodes.push_back(nTemp);
		}
	}
        uint32_t cityMap::getMapDistance(std::string dataName, std::string unvisited)
	{
		for (int i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes[i].name == dataName)
			{
				for (int j = 0; j < m_nodes[i].m_neighbors.size(); j++)
				{
					if (m_nodes[i].m_neighbors[j].name == unvisited)
						return m_nodes[i].m_neighbors[j].distance;
					//TODO ONCE AGAIN I NEED SOME ERROR CHECKING
				}
			}
		}	
	}

