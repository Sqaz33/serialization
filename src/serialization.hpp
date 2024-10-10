#ifndef SRC_SERIALIZATION_HPP
#define SRC_SERIALIZATION_HPP

#include <fstream>
#include <string>
#include <memory>
#include <istream>
#include <iterator>
#include <iostream>

#include "object_model/object_model.hpp"
#include "object_model/utilities.hpp"

namespace serialization {

class Serialization {
public:
    Serialization(std::ostream& out);   

    template <class T>
    void addField(std::string name, T val) {
        obj->addEntitie(name, val);
    }

    template <class T>
    void addField(std::string name, const std::vector<T>& val) {
        obj->addEntitie(name, val);
    }

    void save();

private:
    std::ostream& out;
    std::unique_ptr<object_model::Object> obj;
    size_t objCount = 0;
};

class Deserialization {

};

} // namespace serialization

#endif // SRC_SERIALIZATION_HPP