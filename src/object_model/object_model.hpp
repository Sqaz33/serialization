#ifndef SRC_OBJECT_MODEL_HPP
#define SRC_OBJECT_MODEL_HPP

#include <algorithm>
#include <istream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "field_types.hpp"
#include "utilities.hpp"

namespace object_model {

enum class Wrapper : int8_t {
    PRIMITIVE = 1,
    ARRAY,
    STRING,
    OBJECT
};

class Root {
public:
    Root() = default;

    Root(std::string name, Wrapper wrapper);

public:
    inline std::string name() const noexcept {
        return m_name;
    }

    inline Wrapper wrapper() const noexcept {
        return static_cast<Wrapper>(m_wrapper);
    }
    
    virtual void pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const = 0;
    virtual void unpack(std::vector<utilities::Byte>::const_iterator& it) = 0;
    
protected:
    int8_t m_wrapper = 0;
    size_t nameLength = 0;
    std::string m_name;
};


class Field : public Root {
public:
    Field() = default;

    template <class T>
    Field(std::string name, const T& data) :
        Root(name, Wrapper::PRIMITIVE)
        , type(field_types::type_number_v<T>)
        , dataCount(sizeof(T))
    {   
        auto it = std::back_inserter(this->data);
        utilities::encode<T>(it, data);
    }

    template <class T>
    Field(std::string name, const std::vector<T>& data) :
        Root(name, Wrapper::ARRAY)
        , type(field_types::type_number_v<T>)
        , dataCount(sizeof(T) * data.size())
    {   
        auto it = std::back_inserter(this->data);
        utilities::encode<T>(it, data);
    }

    Field(std::string name, const std::string& data) :
        Root(name, Wrapper::STRING)
        , type(field_types::type_number_v<char>)
        , dataCount(sizeof(char) * data.size())
    {   
        auto it = std::back_inserter(this->data);
        utilities::encode<std::string>(it, data);
    }
    
public:
    template <class T>
    T getPrimitive() const {
        if (static_cast<Wrapper>(m_wrapper) != Wrapper::PRIMITIVE) {
            throw std::logic_error("Attempt to obtain a primitive.");
        }
        T value;
        auto constIt = data.cbegin();
        utilities::decode<T>(constIt, value);
        return value;
    }

    template <class T>
    std::vector<T> getArray() const {
        if (static_cast<Wrapper>(m_wrapper) != Wrapper::ARRAY) {
            throw std::logic_error("Attempt to obtain an array.");
        }
        std::vector<T> array;
        T value;
        for (auto it = data.cbegin(); it != data.cend(); ) {
            utilities::decode<T>(it, value);
            array.push_back(value);
        }
        return array;
    }

    std::string getString() const {
        if (static_cast<Wrapper>(m_wrapper) != Wrapper::STRING) {
            throw std::logic_error("Attempt to obtain an array.");
        }
        std::vector<char> charArr;
        char ch;
        for (auto it = data.cbegin(); it != data.cend(); ) {
            utilities::decode<char>(it, ch);
            charArr.push_back(ch);
        }

        std::string str;
        std::copy(charArr.begin(), charArr.end(), std::back_inserter(str));
        return str;
    }

    void pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const override;
    void unpack(std::vector<utilities::Byte>::const_iterator& it) override;

private:
    int8_t type = 0;
    size_t dataCount = 0;
    std::vector<utilities::Byte> data;
};


class Object : public Root {
public:
    Object() = default;

    Object(std::string name); 

public:
    std::shared_ptr<Field> getEntitieByName(std::string name);

    template <class T>
    void addEntitie(std::string name, T val) {
        entities.push_back(
            std::make_shared<Field>(name, val)
        );
        ++entitiesCount;
    }

    template <class T>
    void addEntitie(std::string name, const std::vector<T>& val) {
        entities.push_back(
            std::make_shared<Field>(name, val)
        );
        ++entitiesCount;
    }

    template <>
    void addEntitie(std::string name, const std::string& val) {
        entities.push_back(
            std::make_shared<Field>(name, val)
        );
        ++entitiesCount;
    }

    
    void pack(std::back_insert_iterator<std::vector<utilities::Byte>>& bufferInserter) const override;
    void unpack(std::vector<utilities::Byte>::const_iterator& it) override;

private:
    size_t entitiesCount = 0;
    std::vector<std::shared_ptr<Field>> entities;
};

} // namespace object_model

#endif // SRC_OBJECT_MODEL_HPP