#include "serialization.hpp"

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace serialization {

//########################## Serialization ##########################
Serialization::Serialization()  {
    setupNewObj();
}

void Serialization::setupNewObj() {
    obj = std::make_unique<object_model::Object>(               /*name:*/
                                                std::format("obj_{}", objCount++)
                                            );
}

void Serialization::save(std::ostream& os) {
    std::vector<utilities::Byte> bytes;
    auto it = std::back_inserter(bytes);
    obj->pack(it);
    
    std::ostream_iterator<utilities::Byte> osi(os);
    std::copy(bytes.begin(), bytes.end(), osi);
}

void Serialization::clear() {
    setupNewObj();
}


//########################## Deserialization ##########################
Deserialization::Deserialization() {    
    setupNewObj();
}

void Deserialization::setupNewObj() {
    obj = std::make_unique<object_model::Object>();
} 

void Deserialization::clear() {
    setupNewObj();
}

void Deserialization::load(std::istream& is) {
    clear();

    std::vector<utilities::Byte> bytes;
    std::istream_iterator<utilities::Byte> isBegin(is);
    std::istream_iterator<utilities::Byte> isEnd;
    std::copy(isBegin, isEnd, std::back_inserter(bytes));

    auto constIt = bytes.cbegin();  
    obj->unpack(constIt);
}

} // namespace serialization