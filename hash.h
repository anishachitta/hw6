#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash
{
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261, 261934300};
    MyStringHash(bool debug = true)
    {
        if (false == debug)
        {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {
        HASH_INDEX_T w[5] = {0, 0, 0, 0, 0};
        int len = k.length();
        int idx = 4;

        for (int i = len - 1; i >= 0; i -= 6)
        {
            for (int j = std::max(0, i - 5); j <= i; ++j)
            {
                w[idx] += letterDigitToNumber(k[j]) * pow(36, i - j);
            }
            --idx;
        }

        HASH_INDEX_T hash = 0;
        for (int i = 0; i < 5; ++i)
        {
            hash += rValues[i] * w[i];
        }

        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if (letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A';
        }
        else if (letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        return 0; // default case, should not happen
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for (int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
