#ifndef SRC_OBJECT_MODEL_UTILITIES_HPP
#define SRC_OBJECT_MODEL_UTILITIES_HPP

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>
#include <istream>

#include <bitset>
#include <iostream>

namespace utilities {

using Byte = int8_t;

//################################ encode ################################
template <class T>
void encode(
    std::back_insert_iterator<std::vector<Byte>>& bufferInserter,
    T value
) 
{   
    Byte byte;
    for (int32_t i = 1; i < sizeof(T) + 1; ++i) {
        byte = value >> ((8 * sizeof(T)) - (8 * i));
        bufferInserter = byte;
    }
}

template <>
inline void encode<double>(
    std::back_insert_iterator<std::vector<Byte>>& bufferInserter,
    double value
)  
{
    int64_t val = *reinterpret_cast<int64_t*>(&value);
    encode<int64_t>(bufferInserter, val);
} 

template <>
inline void encode<float>(
    std::back_insert_iterator<std::vector<Byte>>& bufferInserter,
    float value
)  
{
    int64_t val = *reinterpret_cast<int64_t*>(&value);
    encode<int64_t>(bufferInserter, val);
} 

template <class T>
void encode(
    std::back_insert_iterator<std::vector<Byte>> bufferInserter,
    const std::vector<T>& value
) 
{   
    for (const auto& v : value) {
        encode<T>(bufferInserter, v);
    }
}

template <>
inline void encode<std::string>(
    std::back_insert_iterator<std::vector<Byte>>& bufferInserter,
    std::string string 
) 
{
    std::vector<char> charArr;
    std::copy(string.begin(), string.end(), std::back_inserter(charArr)); 
    encode<char>(bufferInserter, charArr);
}


//################################ decode ################################
template <class T>
inline void addByteTOEnd(T& val, int8_t byte) {
    Byte mask = 1;
    mask <<= (sizeof(Byte) * 8 - 1);
    T append = 1;
    for (size_t i = 0; i < sizeof(Byte) * 8; ++i, byte <<= 1) {
        val <<= 1;
        if (byte & mask) {
            val |= append;
        } else {
            val &= ~append;
        }
    }
} 

// decode val in file
template<class T>
void decode(std::vector<utilities::Byte>::iterator& it, T& value) {
    Byte byte;
    value = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        byte = *(it++); 
        addByteTOEnd(value, byte);
    }
}

// decode array in file
template<class T>
inline void decode(std::vector<utilities::Byte>::iterator& it, std::vector<T>& value, int32_t valueLength) {
    Byte byte;
    value.clear();
    for (size_t i = 0; i < valueLength; ++i) {
        byte = *(it++); 
        value.push_back(byte);
    }
}

// decode string in file
template<class T>
inline void decode(std::vector<utilities::Byte>::iterator& it, std::string& string, int32_t stringLength) {  
    string.clear();
    std::vector<char> charStr(stringLength);
    decode<char>(it, charStr, stringLength);
    std::copy(charStr.begin(), charStr.end(), std::back_inserter(string));
}

// decode value in byte array
template<class T>
inline void decode(std::vector<Byte>::const_iterator& it, T& value) {
    Byte byte;
    value = 0;
    for (int i = 0; i < sizeof(T); ++i) {
        byte = *(it++);
        addByteTOEnd(value, byte);
    }
}

} // namespace utilities


#endif // SRC_OBJECT_MODEL_UTILITIES_HPP