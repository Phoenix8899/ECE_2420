#pragma once

#include <string>
#include "cityMap.hpp"

class table
{
	public:
   	 struct sData {
                std::string city;
                uint32_t distance;
                std::string previous;
        };


        table(cityMap map, std::string start, std::string finish);

	std::string m_start;
	std::string m_finish;	
	cityMap m_cityMap;
        std::vector<sData> m_data;
        std::vector<std::string> m_unvisited; //this needs a spot or the function does or something

	bool doable();
	void printPath(std::string start, std::string finish);
	void doAlgorithm();
        void addItem (sData data);
	bool isNeighbor(std::string data,std::string unvisited); 
	uint32_t getTableDistance(std::string data);
	void setTableDistance(std::string unvisited, uint32_t distance);
	void setTablePrevious(std::string data, std::string unvisited);

};


