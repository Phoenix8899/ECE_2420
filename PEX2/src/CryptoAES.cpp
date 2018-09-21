#include "CryptoAES.hpp"
    
AES::AES(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
std::function<void(const uint8_t *data, uint32_t len)> decryptCallback) : Crypto(encryptCallback, decryptCallback)
{
	m_key = NULL;
	m_IV = NULL;
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
		uint8_t Zarray[BLOCK_SIZE];
		uint8_t pad = 0;
		size_t buff_size = m_bufferstring.str().size();
		pad = BLOCK_SIZE - buff_size; //make a pad to see how much i need to pad
		m_bufferstring.read((char*)Zarray, m_bufferstring.str().size()); //read in the last of the string
										 // to array
		for (int i = m_bufferstring.str().size(); i < pad; i++) //start loop at size end after pad loops
		{
			Zarray[i] = 0; //anything after size will be a 0
		}
		Zarray[BUFF_SIZE] = BLOCK_SIZE - pad;
		mcrypt_generic(td,Zarray, BLOCK_SIZE);
		m_encryptCallback(Zarray,BLOCK_SIZE);
		return true;
	}	
	m_bufferstring.write((char*)data,len);
	while (m_bufferstring.str().size() > BUFF_SIZE)
	{
		uint8_t larray[BLOCK_SIZE];
		m_bufferstring.read((char*)larray, BUFF_SIZE);
		larray[BUFF_SIZE] = BUFF_SIZE;
		mcrypt_generic(td, larray, BUFF_SIZE);
		m_encryptCallback(larray, BLOCK_SIZE);	
	}


	return true;
	
}
bool AES::decrypt(const uint8_t *data, uint32_t len)
{	

	if (m_key == nullptr || m_IV == NULL) { return false; }
	

        if (len == 0)
        {
                uint8_t Zarray[BLOCK_SIZE];
                uint8_t pad = 0;
                pad = BLOCK_SIZE - m_bufferstring.str().size(); //make a pad to see how much i need to pad
                m_bufferstring.read((char*)Zarray, m_bufferstring.str().size()); //read in the last of the string
										 // to array
                for (int i = m_bufferstring.str().size(); i < pad; i++) //start loop at size end after pad loops
                {
                        Zarray[i] = 0; //anything after size will be a 0
                }
                mdecrypt_generic(td,Zarray, BLOCK_SIZE);

                m_decryptCallback(Zarray,Zarray[BUFF_SIZE]);
		
                return true;
        }
        m_bufferstring.write((char*)data,len);
        while (m_bufferstring.str().size() > BLOCK_SIZE)
        {
                uint8_t larray[BLOCK_SIZE];
                m_bufferstring.read((char*)larray, BLOCK_SIZE);
                mdecrypt_generic(td, larray, BLOCK_SIZE);
                m_decryptCallback(larray,larray[BUFF_SIZE]);
        }


        return true;
	
}












