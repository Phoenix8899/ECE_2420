#include <iostream>

struct Test
{
  int m_mem1;
  int m_mem2;
};

void process(char *buffer, int len)
{
  //do stuff here
}

int main()
{
  Test t;
  process((char *)&t, sizeof(Test));
}
