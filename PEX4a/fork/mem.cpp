#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>           
#include <iostream>           
#include <semaphore.h>           
#include <map>
#include <functional>

int main()
{
  int head = 0;

  //create the shared memory
  int fd = shm_open("/problems", O_RDWR | O_CREAT, 0666);
  ftruncate(fd, 1000);
  void *addr = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  int *val = (int *)addr;

  int pid = fork();
  if(0 == pid)
  {
    while(1)
    {
      *val = *val + 1;
      sleep(1);
    }
  }
  else
  {
    while(1)
    {
      std::cout << "Val: " << *val << std::endl;
      sleep(1);
    }
  }
}
