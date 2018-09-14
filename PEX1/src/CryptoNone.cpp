#include "CryptoNone.hpp"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

	None::None(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
               std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
        : Crypto(encryptCallback, decryptCallback)
        {
        }


	bool None::encrypt(const uint8_t *data, uint32_t len)
	{
		m_encryptCallback(data,len);
		return true;
	}
        bool None::decrypt(const uint8_t *data, uint32_t len)
	{
		m_decryptCallback(data,len);
		return true;
	}
	
	void None::genKeys()
	{
	
	}
	
	bool None::getKeys(uint8_t **pubKey, uint32_t &pubLen,
                             uint8_t **priKey, uint32_t &priLen)
	{
			pubKey = pubKey;
			pubLen = pubLen;
			return true;
	}

	void None::setKeys(const uint8_t *pubKey, uint32_t pubLen,
                       const uint8_t *priKey, uint32_t priLen)
	{
			
	}

        void None::destroyKeys()
	{
	}

