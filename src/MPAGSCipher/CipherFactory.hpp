#ifndef MPAGSCIPHER_CIPHERFACTORY_HPP
#define MPAGSCIPHER_CIPHERFACTORY_HPP

#include "Cipher.hpp"
#include "CipherType.hpp"
#include <memory>


namespace CipherFactory {
    std::unique_ptr<Cipher> makeCipher(const CipherType type, const std::string key);
}

#endif