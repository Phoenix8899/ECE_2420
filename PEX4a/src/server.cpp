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

	mqd_t problems = mq_open(problemQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
        std::cout << "mqProblems ID: " << problems << std::endl;
	//iloop
	//mq_open answerque
	mqd_t answers = mq_open(answerQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);	
	std::cout << "mqAnswers ID: " << answers << std::endl;	

	while(1)
	{
	int retVal = mq_receive(toAnswer,prob, 8192, &prio);
	float toSend = 0;
	switch (Operation)	
	{
	case eADD : toSend = prob.m_op1 + prob.m_op2;
	case eSUB : toSend = prob.m_op1 - prob.m_op2;
	case eMUL : toSend = prob.m_op1 * prob.m_op2;
	case eDIV : toSend = prob.m_op1 / prob.m_op2;
	}    
	int sRetVal = mq_send(answers, (char*)&toSend, sizeof(Problem), 1); 
	//mq_send toCient 
	}
	
	int retVal = mq_close(problems);
	int aRetVal = mq_close(answers);
	//close mq

	}
