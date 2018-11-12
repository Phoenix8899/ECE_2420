#include "table.hpp"


	table::table(cityMap map,std::string start, std::string finish)
	:m_cityMap(map),
	 m_start(start),
	 m_finish(finish)
	{	


		for (int i = 0; i < m_cityMap.m_nodes.size(); i++)
		{
			sData dTemp;
			dTemp.city = m_cityMap.m_nodes[i].name;

			if (m_cityMap.m_nodes[i].name == m_start)
				dTemp.distance = 0;
			else
			dTemp.distance = 9999;
		
			dTemp.previous = "Unavailable";
		
			m_data.push_back(dTemp);

			m_unvisited.push_back(m_cityMap.m_nodes[i].name);
		}	
		
	}
	

      	void table::addItem (sData data)
	{
 		m_data.push_back(data);
	}

        bool table::isNeighbor(std::string data,std::string unvisited)	//TODO could the this pointer help in this instance
	{
		for (int i = 0; i < m_cityMap.m_nodes.size(); ++i)
		{
			if(m_cityMap.m_nodes[i].name == data)
			{
				for (int j = 0; j < m_cityMap.m_nodes[i].m_neighbors.size(); ++j) //ugghhhh nested vectors
				{
					if (m_cityMap.m_nodes[i].m_neighbors[j].name == unvisited)
						return true;
				}
			}
		}
		return false;
	}

        uint32_t table::getTableDistance(std::string data)
	{
		for (int i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].city == data)
				return m_data[i].distance;
		}
		//TODO ALL OF THESE WILL NEED ELSE CASES FOR FAILURE TO FIND. OR A CATCH ALL BEFORE THESE GET CALLED;
	}

	void table::setTableDistance(std::string unvisited, uint32_t distance)
	{
		for (int i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].city == unvisited)
				m_data[i].distance = distance; 
		}
	}
        void table::setTablePrevious(std::string data, std::string unvisited)
	{
		for (int i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].city == unvisited)
				m_data[i].previous = data; 
		}
	}
	void table::printPath(std::string start, std::string finish)
	{
		int index;	
	
		if(start == finish) 
			std::cout << "start_" << start << std::endl;
		else 
		{
			for (int i = 0; i < m_data.size(); ++i)
			{
				if (m_data[i].city == finish) //find the desination on the table 
				{
					printPath(start,m_data[i].previous); //follow table backwords
					index = i;
				}
			}
		if (finish == m_finish)
			{
			std::cout << "Destination_" << finish << std::endl;
			std::cout << "Total Distance: " << m_data[index].distance << std::endl;
			}
		else
		std::cout << "intermediate_" << finish << std::endl;
		}

	}
	
	




		
	void table::doAlgorithm ()
	{


		uint32_t minUnvis;
		int unvisIndex;
		int dataIndex;
		uint32_t distance;
		
		//std::cout << "algorithm start" << std::endl;
        	while (m_unvisited.size() > 0) //while unvisited not empty
        	{
			
                	minUnvis = 9999;       //var to find minimum unvisited
	                unvisIndex = 0;  //var to index location in list
			dataIndex = 0;
	                for (int i = 0; i < m_unvisited.size(); ++i) //compariston to find minUnvis & index
	                {
				for(int j = 0; j < m_data.size(); j++)
				{
					if (m_data[j].city == m_unvisited[i])
					{
				
	                        		if (m_data[j].distance <= minUnvis)
        	                		{
						
                	                		minUnvis = m_data[j].distance;
	                        	        	unvisIndex = i;
							dataIndex = j;
		                        	}
					}
				}
        	        }
		
                	m_unvisited.erase(m_unvisited.begin() + unvisIndex); //remove minUnvis from list (object not int)

	                distance = 0; //burner comparitor 
        	        for (int i = 0; i < m_unvisited.size(); ++i) //loop for each unvisited neighbor
                	{
	                        if (isNeighbor(m_data[dataIndex].city,m_unvisited[i]))
        	                {
				
	                                uint32_t mddTemp = m_cityMap.getMapDistance(m_data[dataIndex].city, m_unvisited[i]);
        	                        distance = m_data[dataIndex].distance + mddTemp; //set temp distance to added 
					

					uint32_t gtdTemp = getTableDistance(m_unvisited[i]);
		

                        	        if (distance < gtdTemp) //check if temp distance is less than 
	                                {
					
        	                        	setTableDistance(m_unvisited[i],distance);   
                	                	setTablePrevious(m_data[dataIndex].city,m_unvisited[i]);                  

                        	        }
	                        }
			}
                
		//restart while loop 
               	
		}
		printPath(m_start, m_finish);
	}







