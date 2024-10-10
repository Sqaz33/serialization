#ifndef SRC_OBJECT_MODEL_FIELD_TYPES_HPP
#define SRC_OBJECT_MODEL_FIELD_TYPES_HPP

#include <cstdint>

namespace field_types {

enum class Type : int8_t {
    I8 = 1,
    I16,
    I32,
    I64,

    U8,
    U16,
    U32,
    U64,

    FLOAT,
    DOUBLE,

    BOOL
};

constexpr int8_t typeNumber(int8_t) {
    return static_cast<int8_t>(Type::I8);
}

constexpr int8_t typeNumber(int16_t) {
    return static_cast<int8_t>(Type::I16);
}

constexpr int8_t typeNumber(int32_t) {
    return static_cast<int8_t>(Type::I32);
}

constexpr int8_t typeNumber(int64_t) {
    return static_cast<int8_t>(Type::I64);
}


constexpr int8_t typeNumber(uint8_t) {
    return static_cast<int8_t>(Type::U8);
}

constexpr int8_t typeNumber(uint16_t) {
    return static_cast<int8_t>(Type::U16);
}
constexpr int8_t typeNumber(uint32_t) {
    return static_cast<int8_t>(Type::U32);
}

constexpr int8_t typeNumber(uint64_t) {
    return static_cast<int8_t>(Type::U64);
}


constexpr int8_t typeNumber(float) {
    return static_cast<int8_t>(Type::FLOAT);
}

constexpr int8_t typeNumber(double) {
    return static_cast<int8_t>(Type::DOUBLE);
}


constexpr int8_t typeNumber(bool) {
    return static_cast<int8_t>(Type::BOOL);
}

template <typename Type>
struct type_number {
    static constexpr int8_t value = typeNumber(Type());
};

template <typename Type>
static constexpr int8_t type_number_v = type_number<Type>::value;


} // namespace field_types

#endif // SRC_OBJECT_MODEL_FIELD_TYPES_HPP



