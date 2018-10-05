#include "MathObj.hpp"

#include <unistd.h>
#include <iostream>

#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>
#include <string.h>		


	int main(int argc, char *argv[]){
	
	mqd_t problemQueue = mq_open(problemQueueName.c_str(), O_RDWR, 0666, NULL);
	//std::cout << "Queue ID: " << problemQueue << std::endl;
	
	mqd_t answerQueue = mq_open(answerQueueName.c_str(), O_RDWR, 0666, NULL);
	//std::cout << "answerQueue ID: " << answerQueue << std::endl;

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
	char buffer[10000];
	Problem* prob = (Problem*) buffer;
	unsigned int prio = 1;

	for (int i = 0; i < *argv[0]; i++)
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
		int retVal = mq_send(problemQueue,(char *)&add, sizeof(Problem), 1);
		retVal = mq_receive(answerQueue, buffer, 8192, &prio);
		//std::cout << "client: " << buffer << std::endl;
		}
	}
	


	return 0;
	}
	


