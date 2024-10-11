#ifndef SRC_SERIALIZATION_HPP
#define SRC_SERIALIZATION_HPP

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>

#include "object_model/object_model.hpp"
#include "object_model/utilities.hpp"

namespace serialization {

class Serialization {
public:
    Serialization();   

    template <class T>
    void addField(std::string name, T val) {
        obj->addEntitie<T>(name, val);
    }

    template <class T>
    void addField(std::string name, const std::vector<T>& val) {
        obj->addEntitie<T>(name, val);
    }

    void addField(std::string name, const std::string& val) {
        obj->addEntitie(name, val);
    }

    void save(std::ostream& os);

    void clear();

private:
    void setupNewObj();

private:
    std::unique_ptr<object_model::Object> obj;
    size_t objCount = 0;
};

class Deserialization {

public:
    Deserialization();

    template <class T>
    void getField(std::string name, T& outVal) const {
        throwExceptionIfIsNotOjb();
        auto entitiePtr = obj->getEntitieByName(name);
        outVal = entitiePtr->getPrimitive<T>();
    }

    template <class T>
    void getField(std::string name, std::vector<T>& outVal) const {
        throwExceptionIfIsNotOjb();
        auto entitiePtr = obj->getEntitieByName(name);
        outVal = entitiePtr->getArray<T>();
    }
    
    template <>
    inline void getField(std::string name, std::string& outVal) const {
        throwExceptionIfIsNotOjb();
        auto entitiePtr = obj->getEntitieByName(name);
        outVal = entitiePtr->getString();
    }

    void load(std::istream& is);

    void clear();

private:
    void throwExceptionIfIsNotOjb() const {
        if (!obj) {
            throw std::logic_error("No serialization object.");
        }
    }

    void setupNewObj();

private:
    std::unique_ptr<object_model::Object> obj;
};

} // namespace serialization

#endif // SRC_SERIALIZATION_HPP