#!/bin/bash

if [[ $# -ne 1 ]] ; then
 echo "Usage: testall <NameOfClass>"
 exit 1
fi

#make include files
echo "#include \"../$1.hpp\"" > include.hpp
echo "$1<std::string, $1<std::string, int> > outer;"                                   > instantiate.hpp
echo "$1<std::string, int> inner;"                                                    >> instantiate.hpp
echo "std::shared_ptr<KeyVal<std::string, int> > pKeyVal(new $1<std::string, int>); " >> instantiate.hpp
echo "$1<int, std::string> numeric;" >> instantiate.hpp

mkdir -p bin

#compile and execute first test (interface conformance)
g++ -g -std=c++11 test1.cpp -o bin/test1 2>/dev/null
if [[ $? -ne 0 ]] ; then
  echo "Failed interface verbatim test during compilation"
else
  bin/test1 | grep one1three4 > /dev/null && echo "Passed interface verbatim test" || echo "Failed interface verbatim test"
fi

#compile and execute second test (stack creation)
g++ -g -std=c++11 test2.cpp -o bin/test2 2>/dev/null
if [[ $? -ne 0 ]] ; then
  echo "Failed stack constuction compilation test"
else
  bin/test2 | grep success > /dev/null && echo "Passed stack construction test" || echo "Failed stack construction test"
fi

#compile and execute third test (copy construct and assign)
g++ -g -std=c++11 test3.cpp -o bin/test3 2>/dev/null
if [[ $? -ne 0 ]] ; then
  echo "Failed copy/assign compilation test"
else
  bin/test3 | grep success > /dev/null && echo "Passed cp ctor and assign test" || echo "Failed cp ctor and assign test"
fi

#compile and execute fourth test (deep copy)
g++ -g -std=c++11 test4.cpp -o bin/test4 
if [[ $? -ne 0 ]] ; then
  echo "Failed deep copy compilation test"
else
  bin/test4 | grep outer1two2outer2one1 > /dev/null && echo "Passed deep copy test" || echo "Failed deep copy test"
fi

#compile and execute fifth test (modify after get)
g++ -g -std=c++11 test5.cpp -o bin/test5 
if [[ $? -ne 0 ]] ; then
  echo "Failed get/modify compilation test"
else
  bin/test5 | grep 3 > /dev/null && echo "Passed get/modify test" || echo "Failed get/modify test"
fi

#compile and execute sixth test (modify in foreach)
#doesn't check ordering
g++ -g -std=c++11 test6.cpp -o bin/test6 
if [[ $? -ne 0 ]] ; then
  echo "Failed modify in foreach compilation test"
else
  bin/test6 | grep 2 > /dev/null
  if [[ $? -eq 0 ]] ; then
    bin/test6 | grep 3 > /dev/null
    if [[ $? -eq 0 ]] ; then
      bin/test6 | grep 4 > /dev/null
      if [[ $? -eq 0 ]] ; then
        echo "Passed foreach modify test"
      else
        echo "Failed foreach modify test"
      fi
    else
      echo "Failed foreach modify test"
    fi
  else
    echo "Failed foreach modify test"
  fi
fi

#compile and execute seventh test (iterate in order)
g++ -g -std=c++11 test7.cpp -o bin/test7 
if [[ $? -ne 0 ]] ; then
  echo "Failed in order iteration compilation test"
else
  bin/test7 | grep 132 > /dev/null && echo "Passed in order iteration test" || echo "Failed in order itration test"
fi

#compile and execute h test (insert at head)
#doesn't check ordering
g++ -g -std=c++11 test8.cpp -o bin/test8 
if [[ $? -ne 0 ]] ; then
  echo "Failed insert at head compilation test"
else
  bin/test8 | grep 1 > /dev/null
  if [[ $? -eq 0 ]] ; then
    bin/test8 | grep 2 > /dev/null
    if [[ $? -eq 0 ]] ; then
      bin/test8 | grep 3 > /dev/null
      if [[ $? -eq 0 ]] ; then
        echo "Passed insert at head test"
      else
        echo "Failed insert at head test"
      fi
    else
      echo "Failed insert at head test"
    fi
  else
    echo "Failed insert at head test"
  fi
fi

#compile and execute ninth test (get/del non-key)
g++ -g -std=c++11 test9.cpp -o bin/test9 
if [[ $? -ne 0 ]] ; then
  echo "Failed non existing key compilation test"
else
  bin/test9 | grep success > /dev/null && echo "Passed non-key test" || echo "Failed non-key test"
fi

#compile and execute tenth test (tree insert)
g++ -g -std=c++11 test10.cpp -o bin/test10
if [[ $? -ne 0 ]] ; then
  echo "Failed tree insert compilation test"
else
  bin/test10 | grep "onetwothreefourfivesixseven" > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed tree insert test"
  else
    echo "Failed tree insert test"
  fi
fi

#compile and execute tenth test (tree delete)
g++ -g -std=c++11 test11.cpp -o bin/test11
if [[ $? -ne 0 ]] ; then
  echo "Failed tree delete compilation test"
else
  bin/test11 | grep "del1:twothreefourfivesixseven" > /dev/null
  if [[ $? -eq 0 ]] ; then
    bin/test11 | grep "del2:onethreefourfivesixseven" > /dev/null
    if [[ $? -eq 0 ]] ; then
      bin/test11 | grep "del3:onetwofourfivesixseven" > /dev/null
      if [[ $? -eq 0 ]] ; then
        bin/test11 | grep "del4:onetwothreefivesixseven" > /dev/null
        if [[ $? -eq 0 ]] ; then
          bin/test11 | grep "del5:onetwothreefoursixseven" > /dev/null
          if [[ $? -eq 0 ]] ; then
            bin/test11 | grep "del6:onetwothreefourfiveseven" > /dev/null
            if [[ $? -eq 0 ]] ; then
              bin/test11 | grep "del7:onetwothreefourfivesix" > /dev/null
              if [[ $? -eq 0 ]] ; then
                echo "Passed tree delete test"
              else
                echo "Failed tree delete test"
              fi
            else
              echo "Failed tree delete test"
            fi
          else
            echo "Failed tree delete test"
          fi
        else
          echo "Failed tree delete test"
        fi
      else
        echo "Failed tree delete test"
      fi
    else
      echo "Failed tree delete test"
    fi
  else
    echo "Failed tree delete test"
  fi
fi

#mem leak test
#test1 should be a sufficient test for mem leaks
valgrind bin/test1 2>&1 | grep "no leaks are possible" > /dev/null && echo "Passed leak test" || echo "Failed leak test"
