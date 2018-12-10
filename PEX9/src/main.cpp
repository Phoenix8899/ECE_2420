#include <iostream>
#include "RBTKeyVal.hpp"
#include <string>
int main ()
{
	RBTKeyVal<int , std::string> rbt;
	RBTKeyVal<int , std::string> RBTWO;
	
	std::cout << "insert 1" << std::endl;
	rbt.insert(1,"one");
	rbt.printTree();
	
	std::cout << "insert 2" << std::endl;
	rbt.insert(2,"two");
	rbt.printTree();
	
	std::cout << "insert 3" << std::endl;
	rbt.insert(3,"three");
	rbt.printTree();
	
	std::cout << "insert 4" << std::endl;
	rbt.insert(4,"four");
	rbt.printTree();
	
	std::cout << "insert 5" << std::endl;
	rbt.insert(5,"fiven");
	rbt.printTree();
	
	std::cout << "insert 6" << std::endl;
	rbt.insert(6,"six");
	rbt.printTree();
	
	std::cout << "insert 7" << std::endl;
	rbt.insert(7,"seven");
	rbt.printTree();
	
	std::cout << "insert 8" << std::endl;
	rbt.insert(8,"eight");
	rbt.printTree();
	
	std::cout << "insert 9" << std::endl;
	rbt.insert(9,"nine");
	rbt.printTree();

	RBTWO = rbt; //does this work


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
