#include "CryptoAES.hpp"
    
AES::AES(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
std::function<void(const uint8_t *data, uint32_t len)> decryptCallback) : Crypto(encryptCallback, decryptCallback)
{
	m_key = NULL;
	m_IV = NULL;
	m_counter = 0;
	td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
}


AES::~AES()
{
	mcrypt_generic_deinit(td);
	mcrypt_module_close(td);
}
	
void AES::genKeys()
{
	srand (time(NULL));
	m_key = new uint8_t[BLOCK_SIZE];
	m_IV = new uint8_t[BLOCK_SIZE];
	for (int i = 0; i  < BLOCK_SIZE; i++)
	{
	m_key[i] = rand() % 255 + 1;
	}
	//m_IV = calloc(1,BLOCK_SIZE);
        for (int i = 0; i  < BLOCK_SIZE; i++)
        {
        m_IV[i] = rand() % 255 + 1;
        }
	
	m_counter = 0;
	mcrypt_generic_init(td, m_key, BLOCK_SIZE, m_IV);
	

}

bool AES::getKeys(uint8_t **pubKey, uint32_t &pubLen,
		      uint8_t **priKey, uint32_t &priLen)
{
	if (m_key == NULL)
	{
	return false;
	}
	(*priKey) = new uint8_t[2 * BLOCK_SIZE];
	std::memcpy((*priKey) ,m_key, BLOCK_SIZE);
	std::memcpy((*priKey) + BLOCK_SIZE, m_IV, BLOCK_SIZE);
		//
		//no need to delete beuase the user is responsible
		//
	return true;
}
void AES::setKeys(const uint8_t *pubKey, uint32_t pubLen,
		const uint8_t *priKey, uint32_t priLen)
{	
        m_key = new uint8_t[BLOCK_SIZE];
        m_IV = new uint8_t[BLOCK_SIZE];

        std::memcpy(m_key, (priKey) + 0,          BLOCK_SIZE);
        std::memcpy(m_IV,  (priKey) + BLOCK_SIZE, BLOCK_SIZE);

 	m_counter = 0;
	mcrypt_generic_init(td, m_key, BLOCK_SIZE, m_IV);
}
void AES::destroyKeys()
{
	delete m_key;
	delete m_IV;
}
bool AES::encrypt(const uint8_t *data, uint32_t len)
{
	if (m_key == nullptr || m_IV == NULL ) { return false; }
	if (len == 0)
	{
		if (m_counter > 0) {
			uint8_t Zarray[BLOCK_SIZE];
			m_bufferstring.read((char*)Zarray, m_counter); //read in the last of the string
											 // to array
			Zarray[BUFF_SIZE] = m_counter;
			mcrypt_generic(td,Zarray, BLOCK_SIZE);
			m_encryptCallback(Zarray,BLOCK_SIZE);
		}
		mcrypt_generic_init(td, m_key, BLOCK_SIZE, m_IV);
		m_counter = 0;
		return true;
	}	
	m_bufferstring.write((char*)data,len);
	m_counter+= len; //write
	while (m_counter  >= BUFF_SIZE) //.size doesnt work cause we dont lose size
	{
		uint8_t larray[BLOCK_SIZE];
		m_bufferstring.read((char*)larray, BUFF_SIZE);
		m_counter-=BUFF_SIZE; //read
		larray[BUFF_SIZE] = BUFF_SIZE;
		mcrypt_generic(td, larray, BLOCK_SIZE);
		m_encryptCallback(larray, BLOCK_SIZE);
	}
	return true;
	
}
bool AES::decrypt(const uint8_t *data, uint32_t len)
{	

	if (m_key == nullptr || m_IV == NULL) { return false; }

/*        if (len == 0)
        {
                uint8_t Zarray[BLOCK_SIZE];
                m_bufferstring.read((char*)Zarray, m_counter); //read in the last of the string
                mdecrypt_generic(td,Zarray, BLOCK_SIZE);
                m_decryptCallback(Zarray,Zarray[BUFF_SIZE]);
		m_counter = 0;
		mcrypt_generic_init(td, m_key, BLOCK_SIZE, m_IV);

                return true;
        }*/
	if (len == 0) { 
		if (m_counter > 0) {
			return false; 
		}
		return true;
	}

        m_bufferstring.write((char*)data,len);
	m_counter+=len;//write
        while (m_counter >= BLOCK_SIZE)
        {
                uint8_t larray[BLOCK_SIZE];
                m_bufferstring.read((char*)larray, BLOCK_SIZE);
		m_counter-= BLOCK_SIZE;//read
                mdecrypt_generic(td, larray, BLOCK_SIZE);
                m_decryptCallback(larray,larray[BUFF_SIZE]);
        }

        return true;
	
}

