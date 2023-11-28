#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Cipher.hpp"
#include "CipherMode.hpp"
#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"

bool testCipher(const Cipher& cipher, const CipherMode mode, const std::string& inputText, const std::string& outputText) {
    if (cipher.applyCipher(inputText, mode) == outputText) {
        return true;
    } else {
        return false;
    }
}

TEST_CASE("CaesarCipher encryption", "[caesar]")
{
    CaesarCipher cc{10};
    REQUIRE(testCipher(cc, CipherMode::Encrypt, "HELLOWORLD", "ROVVYGYBVN") == true);
}

TEST_CASE("CaesarCipher decryption", "[caesar]")
{
    CaesarCipher cc{10};
    REQUIRE(testCipher(cc, CipherMode::Decrypt, "ROVVYGYBVN", "HELLOWORLD") == true);
}

TEST_CASE("Playfair Cipher encryption", "[playfair]") {
  PlayfairCipher cc{"hello"};
  REQUIRE(testCipher(cc, CipherMode::Encrypt, "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA") == 1);
}

TEST_CASE("Playfair Cipher decrpytion", "[playfair]") {
  PlayfairCipher cc{"hello"};
  REQUIRE(testCipher(cc, CipherMode::Decrypt, "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING") == 1);
}

TEST_CASE("Vigenere encryption", "[vigenere]")
{
    VigenereCipher cc{"key"};
    REQUIRE(testCipher(cc, CipherMode::Encrypt, "HELLOWORLD", "RIJVSUYVN") == true);
}

TEST_CASE("Vigenere encryption", "[vigenere]")
{
    VigenereCipher cc{"key"};
    REQUIRE(testCipher(cc, CipherMode::Decrypt, "RIJVSUYVN", "HELLOWORLD") == true);
}