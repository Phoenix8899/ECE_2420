#include "MathObj.hpp"

#include <unistd.h>
#include <iostream>

#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>
#include <string.h>

	int main(){

	char buffer[10000];
	Problem* prob = (Problem*) buffer;	
	unsigned int prio = 1;

	mqd_t problemQueue = mq_open(problemQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
        //std::cout << "problemQueue ID: " << problemQueue << std::endl;
	//iloop
	//mq_open answerque
	mqd_t answerQueue = mq_open(answerQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);	
	//std::cout << "mqAnswerQueue ID: " << answerQueue << std::endl;	
	float toSend = 0;
	while(1)
	{
	int retVal = mq_receive(problemQueue,buffer, 8192, &prio);
	switch(prob->m_opcode)	
	{
	case Operation::eADD : toSend = prob->m_op1 + prob->m_op2;
	case Operation::eSUB : toSend = prob->m_op1 - prob->m_op2;
	case Operation::eMUL : toSend = prob->m_op1 * prob->m_op2;
	case Operation::eDIV : toSend = prob->m_op1 / prob->m_op2;
	}   
	int sRetVal = mq_send(answerQueue, (char*)&toSend, sizeof(Answer), 1); 
	//mq_send toCient 
	}
	
	int retVal = mq_close(problemQueue);
	int aRetVal = mq_close(answerQueue);
	//close mq

	}
