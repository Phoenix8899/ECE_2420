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

	int main(int argc, char *argv[]){
	
		sem_t* problemNotFull;
        	sem_t* problemNotEmpty;
        	sem_t* answerNotFull;
		sem_t* answerNotEmpty;

	        problemNotFull = sem_open(problemNotFullSem.c_str(), O_RDWR);
	        problemNotEmpty = sem_open(problemNotEmptySem.c_str(), O_RDWR);
	        answerNotFull = sem_open(answerNotFullSem.c_str(), O_RDWR);
	        answerNotEmpty = sem_open(answerNotEmptySem.c_str(), O_RDWR);                        
		
		int probshm = shm_open(problemMem.c_str(), O_RDWR,0666);//CHECK MONDAY THAT I OPENED CORECTLY
	        int answshm = shm_open(answerMem.c_str(), O_RDWR, 0666);
		
		void *probaddr = mmap(NULL, sizeof(Problem) * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, probshm, 0);
		void *answaddr = mmap(NULL, sizeof(Answer) * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, answshm, 0);

		Problem* prob = (Problem *)probaddr;
	        Answer* answ = (Answer *)answaddr;

		//std::cout << "it crashes after this?" << std::endl;
			
	int its = atoi(argv[1]);

	for (int i = 0; i < its; i++)
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
		{

		//std::cout << "does it make it to sem wait?" << std::endl;

		sem_wait(problemNotFull);

		//std::cout << "does it make it past the sem wait?" << std:: endl;		

		prob[i].m_opcode = eADD;
		prob[i].m_op1 = 1;
		prob[i].m_op2 = 1;			
		
		sem_post(problemNotEmpty);
		
		sem_wait(answerNotEmpty);
		std::cout << answ[i].m_answer;	
		//not really sure how to consume...

		//sem_post(answerNotFull);      // i think there is a reason to post here maybe?

		}
	}
	


	return 0;
	}
	



