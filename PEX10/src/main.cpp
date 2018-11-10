#include <iostream>
#include "cityMap.hpp"
#include "table.hpp"
#include <fstream>

int main()
{

	cityMap mainMap;

        std::ifstream mapfile;
	mapfile.open ("map.txt");
		
	std::string start;
	std::string finish;
	std::string line;	

	mapfile >> start;
	mapfile >> finish;
	
	while (mapfile.good())
	{
		std::string node;
		std::string neighbor;
		uint32_t distance;
		
		mapfile >> node;
		mapfile >> neighbor;
		mapfile >> distance;
	
		mainMap.psudoConstructor(node,neighbor,distance);
	}

	table mainTable(mainMap,start,finish);
	
	mainTable.doAlgorithm();

		


	
	return 0;	
}


