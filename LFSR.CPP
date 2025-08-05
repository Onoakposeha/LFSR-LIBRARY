#include <bitset>
#include <stdexcept>

template <size_t N>//size of LFSR, i.e. number of registers
class LFSR
{
    std::bitset<N> tap;       // switch variable or multiplier vector
    std::bitset<N> keystring; // key string of length equal to size of LFSR
    std::bitset<N> registers; // content of registers
    bool initialised = false;
    unsigned long shiftCount = 0;

    bool nextKey()
    { // next-key function
        if (!initialised)
        {
            throw std::runtime_error("LFSR not initialized. Set the Key first");
        }
        bool feedback = 0;
        bool nextkey = registers[N - 1];

        // compute feedback
        for (int i = 0; i < N; i++)
        {
            feedback = (registers[i] & tap[i]) ^ feedback;
        }
        // shift registers
        for (int i = N - 1; i >= 1; i--)
        {
            registers[i] = registers[i - 1];
        }
        // update r0
        registers[0] = feedback;
        //update count
        shiftCount++;
        return nextkey;
    }

public:
    LFSR(std::bitset<N> tap_)
    {
        tap = tap_;
    }

    // initialise
    bool setkey(std::bitset<N> keystring_)
    {
        keystring = keystring_;
        registers = keystring_;
        initialised = true;
        shiftCount=0;
        return initialised;
    }

    bool isActive()
    {
        return initialised;
    }

    std::bitset<8> encrypt(std::bitset<8> message)
    { // encryption function. takes message in 8-bits per chunk
        if (!initialised)
        {
            throw std::runtime_error("LFSR not initialized. Set the Key first");
        }
        std::bitset<8> Y; // ciphertext
        for (int i = 0; i < 8; i++)
        {
            Y[i] = message[i] ^ nextKey();
        }
        return Y;
    }


    std::bitset<8> decrypt(std::bitset<8> message) // decryption function. takes message in 8-bits per chunk
    {
        if (!initialised)
        {
            throw std::runtime_error("LFSR not initialized. Set the Key first");
        }
        std::bitset<8> X; // plaintext
        for (int i = 0; i < 8; i++)
        {
            X[i] = message[i] ^ nextKey();
        }
        return X;
    }

    void reset()
    {
        setkey(keystring);
        shiftCount=0;
    }

    std::bitset<N> peekRegisters() const
    {
        return registers;
    }
    std::bitset<N> getKey() const
    {
        return keystring;
    }
    std::bitset<N> getTap() const
    {
        return tap;
    }

    unsigned long getShiftCount() const {
    return shiftCount;
}
};
