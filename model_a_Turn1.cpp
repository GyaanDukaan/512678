#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

class CaesarCipher {
public:
    CaesarCipher(int shift) : shift(shift % 26) {
        if (shift < 0) {
            throw std::invalid_argument("Shift must be non-negative.");
        }
    }

    std::string encrypt(const std::string& plaintext) const {
        return processText(plaintext, shift);
    }

    std::string decrypt(const std::string& ciphertext) const {
        return processText(ciphertext, 26 - shift);
    }

private:
    int shift;

    std::string processText(const std::string& text, int shiftAmount) const {
        std::string result;
        result.reserve(text.size());  // Reserve space to prevent multiple allocations

        for (char c : text) {
            if (std::isalpha(c)) {  // Check if the character is alphabetic
                char offset = std::isupper(c) ? 'A' : 'a';  // Determine uppercase or lowercase
                char encryptedChar = static_cast<char>((c - offset + shiftAmount) % 26 + offset);
                result.push_back(encryptedChar);
            }
            else {
                result.push_back(c);  // Non-alphabetic characters remain unchanged
            }
        }
        return result;
    }
};

int main() {
    try {
        int shift;
        std::cout << "Enter the shift amount (0-25): ";
        std::cin >> shift;

        CaesarCipher cipher(shift);

        std::string input;
        std::cout << "Enter the text to encrypt: ";
        std::cin.ignore(); // Ignore leftover newline from previous input
        std::getline(std::cin, input);

        std::string encrypted = cipher.encrypt(input);
        std::cout << "Encrypted text: " << encrypted << std::endl;

        std::string decrypted = cipher.decrypt(encrypted);
        std::cout << "Decrypted text: " << decrypted << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
