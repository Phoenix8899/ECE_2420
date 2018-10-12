#include "MathObj.hpp"

#include <unistd.h>
#include <iostream>

#include <sys/mman.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>
#include <string.h>

#include <semaphore.h>
#include <map>
#include <functional>

	int main(){
	
	//need to double check the naming with pex4a just to make sure im doing it right.

	sem_t* problemNotFull;
	sem_t* problemNotEmpty;
	sem_t* answerNotFull;
	sem_t* answerNotEmpty;
	//CHECK MONDAY THAT I USED CORRECT NAMING / INITIAL COUNT.
	problemNotFull = sem_open(problemNotFullSem.c_str(),O_CREAT | O_RDWR, 0666, ARRAY_SIZE); //need to fill it up....
	problemNotEmpty = sem_open(problemNotEmptySem.c_str(),O_CREAT | O_RDWR, 0666, 0); //made some maths
	answerNotFull = sem_open(answerNotFullSem.c_str(),O_CREAT | O_RDWR, 0666, ARRAY_SIZE); //NOT SURE YET WHAT THIS IS FOR.
	answerNotEmpty = sem_open(answerNotEmptySem.c_str(),O_CREAT | O_RDWR, 0666, 0); //made some maths
	

	//create semaphores remember to keep same name between client and server, thats how you open the same one on both sides.
	//
	//look into shared memory to keep track of the same stuffs and things n junk.
	
	//probably better to make and open all things serverside 
	
	int probshm = shm_open(problemMem.c_str(), O_RDWR | O_CREAT, 0666);
        int answshm = shm_open(answerMem.c_str(), O_RDWR | O_CREAT, 0666);
	
	ftruncate(probshm, sizeof(Problem) * 1024);
	ftruncate(answshm, sizeof(Answer) * 1024);
	
	void *probaddr = mmap(NULL, sizeof(Problem) * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, probshm, 0);
	void *answaddr = mmap(NULL, sizeof(Answer) * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, answshm, 0);

	Problem* prob = (Problem *)probaddr;
	Answer* answ = (Answer *)answaddr;
		
	//int fd = shm_open (man shm_overview)
	//ftrunkate, probably size of problem * 1024, to have a buffer, 
	//mmap makes it an array of bytes, cast it to an array of objects 
	//
	//void *ptr = malloc(sizeof(problem) *10) dont use this, use shared memory 
	//problem *pproblem = (problem *)ptr; //basicly its just to show us that a pointer of bytes
					      // can be cast to a problem 
	//for....
	//pProblem[i].m_member = 7; //used just like an array after cast
	
	int count = 0;
	float toSend = 0;
	while(1)
	{
		sem_wait(problemNotEmpty); //client should post for problems not empty, saying that i can do maths here.

		switch(prob->m_opcode)	
		{
			case Operation::eADD : toSend = prob->m_op1 + prob->m_op2;
			case Operation::eSUB : toSend = prob->m_op1 - prob->m_op2;
			case Operation::eMUL : toSend = prob->m_op1 * prob->m_op2;
			case Operation::eDIV : toSend = prob->m_op1 / prob->m_op2;
		}//switch   
		
		answ[count].m_answer = toSend;
		count++;		
		sem_post(answerNotEmpty);//post saying that there are now answers to be consumed. 

	}//while
	
	}//program
