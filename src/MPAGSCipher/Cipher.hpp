#ifndef MPAGSCIPHER_CIPHER_HPP
#define MPAGSCIPHER_CIPHER_HPP

#include "CipherMode.hpp"
#include <string>
/**
 * \file Cipher.hpp
 * \brief Contains the declaration of the pABC Cipher class
 */

/**
 * \class Cipher
 * \brief Encrypt or decrypt text with a cipher 
 */
class Cipher {
    public:
        /**
         * \brief Default member functions
        */
        Cipher() = default;
        Cipher(const Cipher& rhs) = default;
        Cipher(Cipher&& rhs) = default;
        Cipher& operator=(const Cipher& rhs) = default;
        Cipher& operator=(Cipher&& rhs) = default;
        virtual ~Cipher() = default;

        /**
         * \brief Apply a cipher to the provided text
         * 
         * \param input Input text to be de/encrypted
         * \param mode Specifies whether to encrypt/decrypt
        */
        virtual std::string applyCipher(const std::string& input,
                                        const CipherMode mode) const = 0;
};

#endif