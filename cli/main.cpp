#include <iostream>
#include "dummy.hpp"

int main() {

    std::cout  << "Enter a text to encrypt" << std::endl;

    std::string input, enc;
    std::cin >> input;

    enc = dummy_cipher(input);

    std::cout << "Encrypted text: " << std::endl;
    std::cout << enc << std::endl;

}
