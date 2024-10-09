#include "object_model.hpp"

#include <string>
#include <cstdint>

#include "utilities.hpp"

namespace object_model {


//########################## Root ##########################
Root::Root(std::string name, Wrapper wrapper) : 
    m_name(name) 
    , m_wrapper(static_cast<int8_t>(wrapper))
    , nameLength(name.length())
{}

void Root::pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const {
    using namespace utilities;
    encode<int8_t>(bufferInserter, m_wrapper);
    encode<int32_t>(bufferInserter, nameLength);
    encode(bufferInserter, m_name);
}


//########################## Field ##########################
void Field::pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const {
    using namespace utilities;
    Root::pack(bufferInserter);
    encode<int8_t>(bufferInserter, type);
    encode<int32_t>(bufferInserter, dataCount);
    encode<utilities::Byte>(bufferInserter, data);
}


//########################## Object ##########################
Object::Object(std::string name) :
    Root(name, Wrapper::OBJECT)
{}

void Object::pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const {
    Root::pack(bufferInserter);
    utilities::encode<int32_t>(bufferInserter, entitiesCount);
    for (auto p : entities) {
        p->pack(bufferInserter);
    }
}


} // namespace object_model