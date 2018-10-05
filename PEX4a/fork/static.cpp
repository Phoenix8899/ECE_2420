#include <iostream>
#include <unistd.h>

int count = 0;

int main()
{
  while(1)
  {
    std::cout << "Count at address: " << &count << " " << count++ << std::endl;
    sleep(1);
  }
}
