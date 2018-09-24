#pragma once 

#include <functional>
#include <memory>
#include "Crypto.hpp"
#include <mcrypt.h>
#include <sstream>
#include <cstring>

constexpr uint8_t const BLOCK_SIZE = 16;
constexpr uint8_t const BUFF_SIZE = 15;


class AES : public Crypto {
protected:
	MCRYPT td;	
	uint8_t*  m_key;
	uint8_t* m_IV;
	uint8_t* m_buffer;
	int buffer_len;
	uint8_t m_counter;
	std::stringstream m_bufferstring;
	
public:

AES(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
	std::function<void(const uint8_t *data, uint32_t len)> decryptCallback);

void genKeys();
bool getKeys(uint8_t **pubKey, uint32_t &pubLen,
		      uint8_t **priKey, uint32_t &priLen);
void setKeys(const uint8_t *pubKey, uint32_t pubLen,
		const uint8_t *priKey, uint32_t priLen);
void destroyKeys();
bool encrypt(const uint8_t *data, uint32_t len);
bool decrypt(const uint8_t *data, uint32_t len);

~AES();
};
