#include <iostream>
#include "BSTKeyVal.hpp"
#include <string>
int main ()
{
	BSTKeyVal<int , std::string> bst;

	bst.insert(5,"five");
	bst.insert(4,"four");
	bst.insert(6,"six");
	bst.insert(3,"three");
	bst.insert(7,"seven");
	bst.insert(2,"two");
	bst.insert(8,"eight");
	bst.insert(1,"one");
	bst.insert(9,"nine");

	std::cout << std::endl << std::endl << "Full iteration:" << std::endl;
 	bst.forEach([](const int &key, std::string &val){
    	std::cout << "Key: " << key << std::endl;
    	std::cout << "Val: " << val << std::endl;
  	});
		
	std::cout << std::endl << std::endl << "Deleted item \"three" << std::endl;
	bst.del(3);

	std::cout << std::endl << std::endl << "After Del:" << std::endl;
        bst.forEach([](const int &key, std::string &val){
        std::cout << "Key: " << key << std::endl;
        std::cout << "Val: " << val << std::endl;
        });



}
