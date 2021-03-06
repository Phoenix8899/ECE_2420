#include "Crypto.hpp"
#include "CryptoNone.hpp"
#include "CryptoCaesar.hpp"

/**
 * @brief Constructor
 *
 * This function creates/initializes this oject.
 * The callbacks are used by the underlying
 * algorithm to pass back processed data to the using logic.
 *
 * NOTE: There is no correlation between the amount of data passed into the algorithm
 * and the amount returned from it.  Likewise, there is no required correlation between
 * the number of times data is passed into the algorithm and the number of times callbacks
 * are called.
 *
 * @param encryptCallback Callback function for returning encrypted data
 * @param decryptCallback Callback function for returning decrypted data
 */
Crypto::Crypto(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
               std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: m_encryptCallback(encryptCallback), 
  m_decryptCallback(decryptCallback)
{
	
}

/**
 * @brief Create a Crypto object using the correct transform
 *
 * @param encryptCallback Callback function for returning encrypted data
 * @param decryptCallback Callback function for returning decrypted data
 * @param algorithm Enum indicationg which transform should be used
 * @return shared_ptr to newly constructed heap object
 */
std::shared_ptr<Crypto> Crypto::cryptoFactory(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
                                              std::function<void(const uint8_t *data, uint32_t len)> decryptCallback,
                                              Algorithm algorithm)
{		
		switch(algorithm)
		{
		case Algorithm::eNONE : return std::shared_ptr<Crypto>(new None(encryptCallback,decryptCallback));
		case Algorithm::eCAESAR : return std::shared_ptr<Crypto>(new Caesar(encryptCallback,decryptCallback));
		}
	
		//
		//callback follows down from main untill it gets the data from caesar.
		//
				


		



		//\\//\\//\\//\\//
		//
		// 
		//seek much much more understanding on this subject
		//
		//\\//\\//\\//\\//
}
