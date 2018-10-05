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

	mqd_t toAnswer = mq_open(problemQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
        std::cout << "Queue ID: " << toAnswer << std::endl;
	//iloop
	//mq_open answerque
	//
	while(1)
	{
	int retVal = mq_receive(toAnswer,buffer, 8192, &prio);
	}
	// pro.ob1 switch prob->ob2    
	
	//mq_send toCient 
	
	//close mq

	}
