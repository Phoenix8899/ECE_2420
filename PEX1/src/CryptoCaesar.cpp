#include "CryptoCaesar.hpp"

#include <iostream>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


	Caesar::Caesar(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
               std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
	: Crypto(encryptCallback, decryptCallback)
	{
	}

	void Caesar::genKeys(){

		srand (time(NULL));
		m_key = rand() % 255 + 1;
	}

	bool Caesar::getKeys(uint8_t **pubKey, uint32_t &pubLen,
			     uint8_t **priKey, uint32_t &priLen){
 
		*pubKey = & m_key;
		pubLen = 1;
	}
	
	void Caesar::setKeys(const uint8_t *pubKey, uint32_t pubLen,
                       const uint8_t *priKey, uint32_t priLen){
	
			m_key = *pubKey;
			m_len = pubLen;
	}	
	
	void Caesar::destroyKeys(){
		//delete any pointers here 
	}

	bool Caesar::encrypt(const uint8_t *data, uint32_t len){
		//for(int i = 0; i < len-1; i++)
		//{
		//if data + key > 255
		//data += ((data+key)-255)
		//
		//else 
		//data += key
		//
			
		//copy data to modify that, your call back will pass back the coppied file 
		
		uint8_t *localData =  new uint8_t[len];

		if(m_key != 0)
		{
			for (int i = 0; i < len; i++)
			{
				if (data[i]-m_key < 255)
				{
					localData[i]= (data[i]-m_key) + 256;	//im trying to modify a con		
				}
				else 
				localData[i]= data[i]-m_key;
			}

			m_encryptCallback(localData, len);
			delete[] localData;

		return true;
		}
		return false;
 	
	}

	bool Caesar::decrypt(const uint8_t *data, uint32_t len){
		 // std::cout << "this function was called" << std::endl;
		 uint8_t *localData =  new uint8_t[len];
 
                 if(m_key != 0) 
		{
		//	std::cout << "key is not 0" << std::endl;
                          for (int i = 0; i < len; i++)
                          {
		//		std::cout <<  "this loop keeps going" << std::endl;
                                  if (data[i]+m_key > 255)
                                  {
		//			std::cout << "key is greater than 255" << std::endl;
                                          localData[i]= (data[i]+m_key) + 256;                      
                                  }
                                  else
			 	  {
                                  localData[i]= data[i]+m_key; 
		//			std::cout << "we are in the else block" << std::endl;
				  }
                          }
                
		m_decryptCallback(localData, len);
		delete[] localData;
		return true;
		}
		else 
		return false;
	}
