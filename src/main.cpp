
#include <iostream>
#include <format>
#include <fstream>
#include <istream>
#include <memory>
#include <vector>

#include "objec_model/object_model.hpp"
#include "objec_model/utilities.hpp"


// #include "boost/archive/text_oarchive.hpp" 
// #include "boost/archive/text_iarchive.hpp" 


// struct P {
// public:
//     P() = default;
//     P(int x, int y) :
//         m_x(x)
//         , m_y(y)
//     {}

//     int x() const {return m_x;}
//     int y() const {return m_y;}
    
// private:
//     int m_x = 0, m_y = 0;

//     friend boost::serialization::access;

//     template <class Archive>
//     void serialize(Archive& ar, const unsigned int version) {
//         ar & m_x;
//         ar & m_y;
//     }
// };

// std::ostream& operator<<(std::ostream& out, const P& p) {
//     return out << std::format("x: {}, y: {}", p.x(), p.y());
// }

// class asdf {

// };


// int main(int argc, char** argv) {
//     auto name = "p1point.txt";
//     {
//         P p1(10, 5);
//         std::ofstream ofs(name);
//         boost::archive::text_oarchive oa(ofs);
//         oa << p1;
//     }


//     {
//         P p2;
//         std::ifstream ifs(name);
//         boost::archive::text_iarchive ia(ifs);
//         ia >> p2;
//         std::cout << p2 << '\n';
//     }

//     (void) argc;
//     (void) argv;
//     return 0;
// }

// struct S {
// public:
//     S() : v({1, 2, 3, 4}) {}

//     void serialize(std::ofstream& ofs) {
//         ...::serialization s(ofs);
//         s.addEntitie("x", x);
//         s.addEntitie("v", v);
//         s.save();
//     }

//     static S desirialize(std::ifstream& ifs) {
//         ...::deserialization ds(ifs);
//         ds.getEntitie("x", x);
//         ds.getEntitie("v", v);
//     }

// private:
//     int x = 0;
//     std::vector<int> v;
// };

// struct S {

// int x = 1;


// };

// void f(std::istream& is) {
//     while (is) {
//         int8_t byte;
//         is >> byte;
//         std::cout << byte << ' ';
//     }

// }

int main(int argc, char** argv) {
    using namespace object_model;
    using namespace utilities;

    // std::ifstream ifs("D:\\serialization\\test.txt");
    // f(ifs);
    {    
        int d = 1;
        Field f("d", d);
        
        std::vector<Byte> bytes;
        auto it = std::back_inserter(bytes);
        f.pack(it);

        std::ofstream file("hi.abc");

        for (auto c : bytes) {
            file << c;
        }
        file.close();
    }

    {
        Field f;
        std::ifstream file("hi.abc");
        f.unpack(file);
        file.close();
    }


    (void) argc;
    (void) argv;
    return 0;
}

