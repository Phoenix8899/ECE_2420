#include <iostream>
#include "include.hpp"

int main() {
#include "instantiate.hpp"
	numeric.insert(4, "four");
	
	numeric.insert(2, "two");
	numeric.insert(6, "six");

	numeric.insert(1, "one");
	numeric.insert(3, "three");

	numeric.insert(5, "five");
	numeric.insert(7, "seven");

	for (int i = 1; i < 8; ++i) {
		auto deli = numeric;
		deli.del(i);
		std::cout << "del" << i << ":";
		deli.forEach([](const int &key, std::string &val) {
			std::cout << val;
		});
		std::cout << std::endl;
	}
}
