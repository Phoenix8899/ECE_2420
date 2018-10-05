#include "MathObj.hpp"

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>           
#include <iostream>           
#include <semaphore.h>           
#include <map>
#include <functional>
#include <mqueue.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  //process command line arguments here because you
  //most likely want to do a number of iterations of a size.
  //Using command line parameters can help you choose how many 
  //times to iterate through a particular loop
 
  //Here is where you should open the IPC primites.  This will either
  //be the message queues or the shared memory and semaphores.
  //Include some amount of error checking on the IPC open.  Remember
  //that this program doesn't create the primitives, that should happen
  //on the server side

  //Fork the process so we have two processes running.  The child will create
  //problems and send them to the service.  The parent will wait for responses
  //and then wait for the child to die after collecting and evaluating all responses
  int pid = fork();
  if(pid == 0)
  {
    //Perhaps this becomes two nested loops.  The outer loop executes as directed by a 
    //a command line argument, but the inner executes ARRAY_SIZE times
    for(int i = 0; i < loopVar; i++)
    {
      //Create a problem to send to the server.  Note that if your "random" problems
      //are created in a predicatable way, it may help you know that the answer is correct
      //when received by the parent process
    }
  }
  else
  {
    //Perhaps this becomes two nested loops.  The outer loop executes as directed by a 
    //a command line argument, but the inner executes ARRAY_SIZE times
    for(int i = 0; i < loopVar; i++)
    {
      //Retrieve an answer from the server.  Check that it is the correct answer if desired
    }

    //This call will force the parent process to wait for the child to die.  It may ensure
    //that all problems are processed.  Also ensure a clean teardown, (i.e. no zombie/orphaned 
    //processes)
    int status;
    waitpid(pid, &status, 0);
  }
}
