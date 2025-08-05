#include "LFSR.cpp"
#include <bitset>
#include <iostream>

int main() {
    std::bitset<8> tap("10011001");
    std::bitset<8> key("01010101");
    std::bitset<8> message("11001100");

    LFSR<8> lfsr(tap);
    if (!lfsr.setkey(key)) {
        std::cerr << "Failed to initialize LFSR.\n";
        return 1;
    }

    std::cout << "LFSR Active: " <<std::boolalpha<< lfsr.isActive() << "\n";
    std::cout << "Original Key: " << lfsr.getKey() << "\n";
    std::cout << "Tap Config: " << lfsr.getTap() << "\n";
    std::cout << "Message: " << message << "\n";

    lfsr.reset();
    std::bitset<8> encrypted = lfsr.encrypt(message);
    lfsr.reset();
    std::bitset<8> decrypted = lfsr.decrypt(encrypted);

    std::cout << "Encrypted: " << encrypted << "\n";
    std::cout << "Decrypted: " << decrypted << "\n";
    std::cout << "Current Registers: " << lfsr.peekRegisters() << "\n";
    std::cout << "Shift Count: " << lfsr.getShiftCount() << "\n";

    lfsr.reset(); // Reset LFSR to original key
    std::cout << "Registers after reset: " << lfsr.peekRegisters() << "\n";

    return 0;
}
