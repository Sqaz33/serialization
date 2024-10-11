#include <bitset>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <vector>

#include "object_model/object_model.hpp"
#include "object_model/utilities.hpp"
#include "serialization.hpp"

int main(int argc, char** argv) {
    using namespace object_model;
    using namespace utilities;
    using namespace serialization;
    
    {   
        serialization::Serialization ser;

        int i = 5;
        ser.addField("i", i);

        std::vector v = {1, 2, 3, 4};
        ser.addField("v", v);

        std::string s = "str";
        ser.addField("s", s);

        std::ofstream ofs("ser.abc");
        ser.save(ofs);
    }

    {   
        serialization::Deserialization dser;
        std::ifstream ifs("ser.abc");
        dser.load(ifs);

        std::string s;
        dser.getField("s", s);

        std::vector<int> v;
        dser.getField("v", v);

        int i = 0;
        dser.getField("i", i);
    }

    (void) argc;
    (void) argv;
    return 0;
}

