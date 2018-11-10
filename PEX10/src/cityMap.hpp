#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>


class cityMap
{
	public:
        struct edge {
        std::string name;
        uint32_t distance;
        };
	
	struct node {
        std::string name;
        std::vector<edge> m_neighbors;
	};

	
	std::vector<node> m_nodes;
	
	void psudoConstructor(std::string nodeName, std::string edgeName, uint32_t distance);   //just for thinking stuffs
		
     	
        uint32_t getMapDistance(std::string, std::string);
};

