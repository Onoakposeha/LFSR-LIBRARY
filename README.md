
# 🔐 LFSR – Linear Feedback Shift Register - Class Template

## 📘 Overview

`LFSR<N>` is a C++ class template that simulates a **Linear Feedback Shift Register** of size `N`. LFSRs are commonly used in cryptographic systems and pseudo-random number generation. This class supports encryption and decryption of binary strings using bitwise XOR operations.

---

## ⚙️ Usage

### 💼 Include the File
```cpp
#include "LFSR.cpp"
```

### 🏗️ Creating an LFSR Object
```cpp
LFSR<size> myLfsr(tap_vector);
```
- `size`: An integer constant greater than 1 representing the number of LFSR registers.
- `tap_vector`: A `std::bitset<size>` containing the tap (a.k.a. switch) vector configuration for the LFSR.

---

## 🚀 Initialization

Before using the object, initialize it with a binary key using:

```cpp
myLfsr.setkey(key);
```

- `key`: A `std::bitset<size>` representing the initial state of the LFSR.
- Returns: `true` on success; `false` if initialization fails.

---

## 🔒 Encryption

```cpp
std::bitset<8> ciphertext = myLfsr.encrypt(message);
```

- `message`: An 8-bit binary string (`std::bitset<8>`).
- Output: Encrypted 8-bit binary string.

---

## 🔓 Decryption

```cpp
std::bitset<8> plaintext = myLfsr.decrypt(ciphertext);
```

- `ciphertext`: An 8-bit encrypted binary string (`std::bitset<8>`).
- Output: Original 8-bit message.
- Note: XOR encryption ensures symmetric transformation, so the same logic decrypts the data.

---
### NOTE ⚠️:
    It is good practice to reset the LFSR before decryption and encryption, so that the decryption and encryption are correct.
---

## 🛠️ Other Functions

| Function Name         | Description                                          | Input                | Output                  | Example                             |
|----------------------|------------------------------------------------------|----------------------|--------------------------|-------------------------------------|
| `isActive()`         | Checks if the LFSR is initialized                    | None                 | `bool`                   | `myLfsr.isActive();`                |
| `reset()`            | Reinitializes LFSR with original key                 | None                 | None                     | `myLfsr.reset();`                   |
| `peekRegisters()`    | Returns current contents of the LFSR registers       | None                 | `std::bitset<size>`      | `auto r = myLfsr.peekRegisters();`  |
| `getKey()`           | Retrieves the original key used for initialization   | None                 | `std::bitset<size>`      | `auto k = myLfsr.getKey();`         |
| `getTap()`           | Returns the tap configuration                        | None                 | `std::bitset<size>`      | `auto t = myLfsr.getTap();`         |
| `getShiftCount()`    | Returns total number of shifts performed             | None                 | `unsigned long`          | `auto count = myLfsr.getShiftCount();` |

---

## 🧪 Example

```cpp
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

```
## Output
```
LFSR Active: true
Original Key: 01010101
Tap Config: 10011001
Message: 11001100
Encrypted: 01100110
Decrypted: 11001100
Current Registers: 00110101
Shift Count: 8
Registers after reset: 01010101
```

---

## 📄 License
This project is available for educational and cryptographic exploration. No warranties, implied or otherwise.
