#include <iostream>
#include <string>
#include <cstdint> // For size_t
#include <stdexcept> // For out_of_range
#include <algorithm> // for transform

// Improved Caesar cipher implementation
std::string encrypt_decrypt_caesar(const std::string& input, int shift, bool encrypt) {
    const size_t len = input.length();
    std::string result(len);

    // Carry out the encryption/decryption process.
    // We'll iterate through the input string and convert characters manually.
    // For each character, we will use arithmetic operations with wrap-around to handle the Caesar shift and bounces on 'a' and 'z' lowercase and 'A' and 'Z' uppercase characters.
    for (size_t i = 0; i < len; ++i) {
        char ch = input[i];

        if (std::isalpha(ch)) {
            bool isUpper = std::isupper(ch);
            ch = std::tolower(ch); // Convert to lowercase for calculation
            ch = (ch - 'a' + shift) % 26 + 'a';
            if (isUpper)
                ch = std::toupper(ch);
        }
        result[i] = ch;
    }

    return result;
}

int main() {
    std::cout << "Caesar Cipher Application\n";
    std::cout << "=========================\n";

    std::string input;
    std::cout << "Enter the text to encrypt/decrypt: ";
    std::getline(std::cin, input);

    int shift;
    std::cout << "Enter the shift value (0-25): ";
    while (!(std::cin >> shift) || shift < 0 || shift > 25) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid shift value. Please enter an integer between 0 and 25: ";
    }

    bool encrypt;
    char choice;
    do {
        std::cout << "\nChoose mode:\n(e)ncrypt\n(d)ecrypt\n(x)exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 'e':
            encrypt = true;
            break;
        case 'd':
            encrypt = false;
            break;
        case 'x':
            std::cout << "Goodbye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 'e' && choice != 'd' && choice != 'x');

    std::string ciphertext = encrypt_decrypt_caesar(input, shift, encrypt);
    std::cout << "\n";
    std::cout << "Original Text: " << input << std::endl;
    std::cout << "Shifted Value: " << shift << std::endl;
    std::cout << "Mode: " << (encrypt ? "Encryption" : "Decryption") << std::endl;
    std::cout << "Result:     " << ciphertext << std::endl;

    return 0;
}
