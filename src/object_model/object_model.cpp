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

void Root::unpack(std::vector<utilities::Byte>::iterator& it) {
    using namespace utilities;
    decode<int8_t>(it, m_wrapper);
    decode<int32_t>(it, nameLength);
    decode<std::string>(it, m_name, nameLength);
}

//########################## Field ##########################
void Field::pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const {
    using namespace utilities;
    Root::pack(bufferInserter);
    encode<int8_t>(bufferInserter, type);
    encode<int32_t>(bufferInserter, dataCount);
    encode<utilities::Byte>(bufferInserter, data);
}

void Field::unpack(std::vector<utilities::Byte>::iterator& it) {
    using namespace utilities;
    Root::unpack(it);
    decode<int8_t>(it, type);
    decode<int32_t>(it, dataCount);
    decode<Byte>(it, data, dataCount);
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

void Object::unpack(std::vector<utilities::Byte>::iterator& it) {
    Root::unpack(it);
    utilities::decode<int32_t>(it, entitiesCount);

    std::shared_ptr<Field> p;
    for (int32_t i = 0; i < entitiesCount; ++i) {
        p = std::make_shared<Field>();
        p->unpack(it);
        entities.push_back(p);
    }
}


} // namespace object_model