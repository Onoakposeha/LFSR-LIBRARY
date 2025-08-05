#include <iostream>
#include <vector>
#include <bitset>
#include "LFSR.cpp" // Replace with the actual file name where your class is declared

int main()
{
    constexpr size_t N = 8;
    std::bitset<N> tapMask("10110101");                                                         // Choose arbitrary tap pattern
    std::bitset<N> key("11001010");                                                             // Sample key
    std::string message = "Lauren Ipson is meeting a British character named Clive in London."; // Sample plaintext

    // CONVERT STRIN TO BINARY
    std::vector<std::bitset<8>> charBits;
    for (char c : message)
    {
        charBits.push_back(std::bitset<8>(c));
    }

    // Create LFSR instance
    LFSR<N> lfsr(tapMask);

    // Check initialization status
    std::cout << "Initialized? " << std::boolalpha << lfsr.isActive() << "\n";

    // Set the key
    lfsr.setkey(key);
    std::cout << "Initialized after setkey? " << lfsr.isActive() << "\n";

    // Check tap and keystring
    std::cout << "Tap:        " << lfsr.getTap() << "\n";
    std::cout << "Keystring:  " << lfsr.getKey() << "\n";

    // Peek at the registers
    std::cout << "Registers (before shift): " << lfsr.peekRegisters() << "\n";

    for (size_t i = 0; i < charBits.size(); ++i)
    {
        std::bitset<8> encryptedChar = lfsr.encrypt(charBits[i]);
        std::cout << "Original: " << charBits[i]
                  << " (" << static_cast<char>(charBits[i].to_ulong()) << ")"
                  << " -> Encrypted: " << encryptedChar
                  << " (" << static_cast<char>(encryptedChar.to_ulong()) << ")\n";

       std::cout<<"LFSR shift count"<<lfsr.getShiftCount()<<"\n";   
       std::cout<<"LFSR register content"<<lfsr.peekRegisters()<<"\n";         
    }


        return 0;
}