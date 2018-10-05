#include "MathObj.hpp"

#include <unistd.h>
#include <iostream>

#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>
#include <string.h>		

	void makeMath(char *message, int len, mqd_t queue)
	{
	int retVal = mq_send(queue, message, len, 1);	
	}

	int main(){
	
	mqd_t toAnswer = mq_open(//change this , O_RDWR, 0666, NULL);
	//dont creat here becuase its better in server side.
	std::cout << "Queue ID: " << toAnswer << std::endl;
	
	//mq_open fromA answer

	//cast things to char...
	//
	////redo this \/ change to time iteratatis (check assignmnet description)
	//
	//time thingy todo use argv to run a loop enough times. 
	Problem add;
		add.m_opcode = eADD;
		add.m_op1 = 1;
		add.m_op2 = 1;
	Problem sub;
		add.m_opcode = eSUB;
                add.m_op1 = 2;
                add.m_op2 = 1;
	Problem mul;
		add.m_opcode = eMUL;
                add.m_op1 = 2;
                add.m_op2 = 2;
	Problem div;
		add.m_opcode = eDIV;
                add.m_op1 = 4;
                add.m_op2 = 2;

	makeMath((char *)&add, int sizeof(Problem), &toAnswer);
	makeMath((char *)&sub, int sizeof(Problem), &toAnswer);
	makeMath((char *)&mul, int sizeof(Problem), &toAnswer);
	makeMath((char *)&div, int sizeof(Problem), &toAnswer);

	


	return 0;
	}
	



