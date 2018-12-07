#include <iostream>
#include "RBTKeyVal.hpp"
#include <string>
int main ()
{
	RBTKeyVal<int , std::string> rbt;
	RBTKeyVal<int , std::string> RBTWO;
	
	rbt.insert(5,"five");
	rbt.insert(4,"four");
	rbt.insert(6,"six");
	rbt.insert(3,"three");
	rbt.insert(7,"seven");
	rbt.insert(2,"two");
	rbt.insert(8,"eight");
	rbt.insert(1,"one");
	rbt.insert(9,"nine");

	RBTWO = rbt; //does this work

	rbt.printTree();

	//std::cout << std::endl << std::endl << "Full iteration:" << std::endl;
 	//rbt.forEach([](const int &key, std::string &val){
    	//std::cout << "Key: " << key << std::endl;
    	//std::cout << "Val: " << val << std::endl;
  	//});
	//	
	//std::cout << std::endl << std::endl << "Deleted item \"three" << std::endl;
	//rbt.del(3);

	//std::cout << std::endl << std::endl << "After Del:" << std::endl;
        //rbt.forEach([](const int &key, std::string &val){
        //std::cout << "Key: " << key << std::endl;
        //std::cout << "Val: " << val << std::endl;
        //});

	//std::cout << std::endl << std::endl << "Deep Copy?" << std::endl;
	
	//std::cout << std::endl << std::endl << "RBTWO:" << std::endl;
        //RBTWO.forEach([](const int &key, std::string &val){
        //std::cout << "Key: " << key << std::endl;
        //std::cout << "Val: " << val << std::endl;
        //});


}
