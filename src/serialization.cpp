#include "serialization.hpp"

#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <memory>
#include <iostream>
#include <format>

namespace serialization {

Serialization::Serialization(std::ostream& out) :
    out(out)
{
    obj = std::make_unique<object_model::Object>(std::format("obj_{}", objCount++));
}

void Serialization::save() {
    std::vector<utilities::Byte> bytes;
    auto it = std::back_inserter(bytes);
    obj->pack(it);
    
    std::ostream_iterator<utilities::Byte> osi(out);
    std::copy(bytes.begin(), bytes.end(), osi);

    obj = std::make_unique<object_model::Object>(std::format("obj_{}", objCount++));
}

} // namespace serialization