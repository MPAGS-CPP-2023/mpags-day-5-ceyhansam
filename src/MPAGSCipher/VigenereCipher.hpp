#ifndef MPAGSCIPHER_VIGENERECIPHER_HPP
#define MPAGSCIPHER_VIGENERECIPHER_HPP

#include "CipherMode.hpp"
#include "CaesarCipher.hpp"
#include "Cipher.hpp"

#include <string>
#include <map>

/**
 * \file VigenereCipher.hpp
 * \brief Contains the declaration of the VigenereCipher class
 */

/**
 * \class VigenereCipher
 * \brief Encrypt or decrypt text using the Vigenere cipher with the given key
 */

class VigenereCipher: public Cipher{
    public:
        /**
         * \brief Create a new VigenereCipher with the given key
         * 
         * \param key the key to use in the cipher
        */
        explicit VigenereCipher(const std::string& key);

        /**
         * \brief Set the key to use for encryption/decryption
         * 
         * \param key the key to use in the cipher
        */
        void setKey(const std::string& key);

        /**
         * \brief Apply the cipher to the input text
         * 
         * \param inputText the text to encrypt or decrypt
         * \param cipherMode whether to encrypt or decrypt inputText
         * \return the result of applying the cipher to inputText
        */

        std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const override;

    private:
        /// The cipher key
        std::string key_{""}; 

        /// Lookup Table
        std::map<char, CaesarCipher> charLookup_;

};

#endif