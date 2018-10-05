#include <unistd.h>
#include <iostream>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>
#include <string.h>


int main()
{

#if 0
  std::cout << "Before fork" << std::endl;
  int pid = fork();
#endif



  int var = 10;
#if 0
  if(0 == pid)
  {
    var++;
    std::cout << "I am the child" << std::endl;
    std::cout << "Var: " << var << std::endl;
  }
  else
  {
    var--;
    std::cout << "I am the parent" << std::endl;
    std::cout << "Var: " << var << std::endl;
  }
#endif

#if 1
  std::string input = "This is a test"; 
  char buffer[10000];

  mqd_t queue = mq_open("/test", O_CREAT | O_RDWR, 0666, NULL);
  std::cout << "Queue ID: " << queue << std::endl;
  mq_attr attr;
  mq_getattr(queue, &attr);
  std::cout << "Message size: " << attr.mq_msgsize << std::endl;
  int pid = fork();

  if(0 == pid)
  {
    int retVal = mq_send(queue, input.c_str(), input.size(), 1);
    std::cout << "sendVal: " << retVal << std::endl; 
    std::cout << "wrote message" << std::endl;
  }
  else
  {
    sleep(5);
    unsigned int prio = 1;
    int retVal = mq_receive(queue, buffer, 8191, &prio);
    std::cout << "recvVal: " << retVal << std::endl; 
    std::cout << "Got message of length: " << prio << std::endl;
    std::cout << "Msg content: " << buffer << std::endl;
    std::cout << "Error: " << strerror(errno) << std::endl;
  }
  sleep(60);

#endif
}
