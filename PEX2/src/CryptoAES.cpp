#include "CryptoAES.hpp"

    
AES(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
std::function<void(const uint8_t *data, uint32_t len)> decryptCallback);

void AES::genKeys()
{
	srand (time(NULL));
	for (int i = 0; int < 16; i++)
	{
	m_key[i] = rand() % 255 + 1;
	}

}
bool AES::getKeys(uint8_t **pubKey, uint32_t &pubLen,
		      uint8_t **priKey, uint32_t &priLen)
{
	for (int i = 0; i < 16; i++)
	{
	*priKey[i] = &m_key[i];
	}
	priLen = 16;
	return true;
}
void AES::setKeys(const uint8_t *pubKey, uint32_t pubLen,
		const uint8_t *priKey, uint32_t priLen)
{		
	for (int = 0; i < 16; i++)
	{
	m_key[i] = *priKey ;
	}
	m_key = priLen;
}
void AES::destroyKeys()
{

}
bool AES::encrypt(const uint8_t *data, uint32_t len)
{
	if (m_key != {})
	{
	uint8_t *localData =  new uint8_t[len];
	mcrypt_generic(m_key,localData,len);
	delete[] localData;
	return true;
	} 
	return false;
}
bool AES::decrypt(const uint8_t *data, uint32_t len)
{	if (m_key != {})
	{
	uint8_t *localData =  new uint8_t[len];
	mdecrypt_generic(m_key,localData,len); 
	delete[] localData;
	return true;
	} 
	return false;
}












