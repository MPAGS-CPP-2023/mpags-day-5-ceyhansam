#include "CaesarCipher.hpp"
#include "CipherMode.hpp"
#include "CipherType.hpp"
#include "PlayfairCipher.hpp"
#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"
#include "VigenereCipher.hpp"
#include "CipherFactory.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//TODO: ADD TO THIS TO TAKE MULTIPLE CIPHERS, MOST OF THE CODE IS PRESENT BUT STILL NEED TO ADD THE OPTIONS
//EXAMPLE CMD LINE: ./mpags-cipher --multi-cipher 3 -c caesar -k 10 -c playfair -k hello ...

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    ProgramSettings settings{false, false, "", "", {}, {}, CipherMode::Encrypt};

    // Process command line arguments
    const bool cmdLineStatus{processCommandLine(cmdLineArgs, settings)};

    // Any failure in the argument processing means we can't continue
    // Use a non-zero return value to indicate failure
    if (!cmdLineStatus) {
        return 1;
    }

    // Handle help, if requested
    if (settings.helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>] [-c <cipher>] [-k <key>] [--encrypt/--decrypt]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help         Print this help message and exit\n\n"
            << "  --version         Print version information\n\n"
            << "  -i FILE           Read text to be processed from FILE\n"
            << "                    Stdin will be used if not supplied\n\n"
            << "  -o FILE           Write processed text to FILE\n"
            << "                    Stdout will be used if not supplied\n\n"
            << "                    Stdout will be used if not supplied\n\n"
            << "  --multi-cipher N  Perform encryption/decryption using N ciphers\n\n"
            << "  -c CIPHER         Specify the cipher to be used to perform the encryption/decryption\n"
            << "                    CIPHER can be caesar, playfair or vigenere - caesar is the default\n\n"
            << "  -k KEY            Specify the cipher KEY\n"
            << "                    A null key, i.e. no encryption, is used if not supplied\n\n"
            << "  --encrypt         Will use the cipher to encrypt the input text (default behaviour)\n\n"
            << "  --decrypt         Will use the cipher to decrypt the input text\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (settings.versionRequested) {
        std::cout << "0.4.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    if (!settings.inputFile.empty()) {
        // Open the file and check that we can read from it
        std::ifstream inputStream{settings.inputFile};
        if (!inputStream.good()) {
            std::cerr << "[error] failed to create istream on file '"
                      << settings.inputFile << "'" << std::endl;
            return 1;
        }

        // Loop over each character from the file
        while (inputStream >> inputChar) {
            inputText += transformChar(inputChar);
        }

    } else {
        // Loop over each character from user input
        // (until Return then CTRL-D (EOF) pressed)
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    std::string outputText;


    std::vector<std::unique_ptr<Cipher>> cipherVec{};
    cipherVec.reserve(settings.cipherType.size());

    for (size_t iCipher = 0; iCipher < settings.cipherType.size(); iCipher++) {
        //std::cout << "iCipher = " << iCipher << std::endl;
        auto cipher = CipherFactory::makeCipher(settings.cipherType[iCipher], settings.cipherKey[iCipher]);
        if (!cipher) {
            std::cerr << "[error] problem constructing cipher" << std::endl;
            return 1;
        }
        cipherVec.push_back(std::move(cipher));
    }

    switch (settings.cipherMode)
    {
        case(CipherMode::Encrypt):
            for (auto&& cipher : cipherVec) {
                outputText =  cipher->applyCipher(inputText, settings.cipherMode);
                inputText = outputText;
            }
            break;
        
        case(CipherMode::Decrypt):
            std::reverse(cipherVec.begin(), cipherVec.end());
            for (auto&& revCipher : cipherVec) {
                outputText = revCipher->applyCipher(inputText, settings.cipherMode);
                inputText = outputText;
            }
            break;
    }

    // Output the encrypted/decrypted text to stdout/file
    if (!settings.outputFile.empty()) {
        // Open the file and check that we can write to it
        std::ofstream outputStream{settings.outputFile};
        if (!outputStream.good()) {
            std::cerr << "[error] failed to create ostream on file '"
                      << settings.outputFile << "'" << std::endl;
            return 1;
        }

        // Print the encrypted/decrypted text to the file
        outputStream << outputText << std::endl;

    } else {
        // Print the encrypted/decrypted text to the screen
        std::cout << outputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
