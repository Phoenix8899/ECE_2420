#include "MathObj.hpp"

#include <unistd.h>
#include <iostream>

#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>
#include <string.h>		


/*
 *	forked client
 */





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
	Answer* answ = (Answer*) buffer;
	unsigned int prio = 1;
	int its = atoi(argv[1]);

	int pid = fork(); //this is were i start the fork


	if (0 == pid)
	{
		for (int i = 0; i < its; i++)
		{
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
			int retVal = mq_send(problemQueue,(char *)&add, sizeof(Problem), 1);
			}
		}
	}
	else
	{
		for (int i = 0; i < its; i++)
        	{
        		for (int i = 0; i < ARRAY_SIZE; i++)
        		{
        		int retVal = mq_receive(answerQueue, buffer, 8192, &prio);
			std::cout << "forked client: " << answ->m_answer << std::endl;
        		}
        	}
	}

	

//   int retVal = mq_receive(answerQueue, buffer, 8192, &prio);




	return 0;
	}
	



