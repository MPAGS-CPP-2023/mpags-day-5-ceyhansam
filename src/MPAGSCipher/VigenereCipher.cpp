#include "VigenereCipher.hpp"
#include "Alphabet.hpp"

#include <algorithm>
#include <string>

VigenereCipher::VigenereCipher(const std::string& key) {
    this->setKey(key);
}

void VigenereCipher::setKey(const std::string& key) {
    key_ = key;

    // Make sure the key is upper case
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                   ::toupper);

    // Remove non-alphabet characters
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),
                              [](char c) { return !std::isalpha(c); }),
               std::end(key_));
    
    // Check if key is empty and replace with a default key if so
    if (key_.empty()) {key_ = "DEFAULT";}

    // Loop over each char in the key, create and insert a pair of the char and CaeserCipher using the char position as the key into the map
    // std::for_each(key.begin(), key.end(), 
    //                                     [&](char x) {
    //                                     for (std::size_t i{0}; i < Alphabet::size; i++){
    //                                         if (x == Alphabet::alphabet[i]) {
    //                                             CaesarCipher charCipher{i};
    //                                             charLookup_[x] = charCipher;
    //                                         }}});
    // WORKED SOLUTION
    for (const char letter : key_) {
        if (charLookup_.find(letter) != charLookup_.end()) {
            continue;
        }
        const std::size_t index{Alphabet::alphabet.find(letter)};
        charLookup_.emplace(std::piecewise_construct, std::make_tuple(letter), std::make_tuple(index));
    } 
    // WORKED SOLUTION

}

std::string VigenereCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const {
    std::string outputText{inputText};
    // For each letter in input:
        // Find the corresponding letter in the key

        // repeating/truncating the key as required

        // Find the caesar cipher from the lookup

        // Run the (de)encryption

        //Add the result to the output

    //WORKED SOLUTION
    const std::size_t inputSize{inputText.size()};
    const std::size_t keySize{key_.size()};

    for (std::size_t i{0}; i < inputSize; i++) {
        const char keyChar{key_[i % keySize]};

        const CaesarCipher& cipher{charLookup_.at(keyChar)};

        const std::string oldChar{inputText[i]};
        outputText+=cipher.applyCipher(oldChar, cipherMode);
    }
    //WORKED SOLUTION
    
    return outputText;
}