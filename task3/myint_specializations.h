#ifndef MYINT_SPECIALIZATIONS_H
#define MYINT_SPECIALIZATIONS_H

#include "myint.h"

// Type traits translating bit-size to built in types.
template<unsigned int BIT_SIZE> struct myuint_traits {};
template<> struct myuint_traits<8>  {typedef unsigned char      int_type;};
template<> struct myuint_traits<16> {typedef unsigned short     int_type;};
template<> struct myuint_traits<32> {typedef unsigned int       int_type;};
template<> struct myuint_traits<64> {typedef unsigned long long int_type;};

// Base class for all specializations.
template<unsigned int BIT_SIZE>
class BuiltInIntBase
{
protected:
    typedef typename myuint_traits<BIT_SIZE>::int_type IntType;

public:
    BuiltInIntBase() : m_value(0u) {}
    BuiltInIntBase(IntType value) : m_value(value) {}

    BuiltInIntBase(const std::string s)
    {
        m_value = static_cast<IntType>(atoll(s.c_str()));
    }

protected:
    IntType m_value;
};

// Specializations for each of the built-in int types: 8, 16, 32, 64 bits.

template<>
class myuint<8> : BuiltInIntBase<8>
{
public:
   myuint() : BuiltInIntBase() {};
   myuint(IntType value) : BuiltInIntBase(value) {};
   myuint(const std::string s) : BuiltInIntBase(s) {};
   
   IntType operator+(const myuint& rhs)   {return m_value + rhs.m_value;}
   IntType operator-(const myuint& rhs)   {return m_value - rhs.m_value;}
   IntType operator*(const myuint& rhs)   {return m_value * rhs.m_value;}
   IntType operator/(const myuint& rhs)   {return m_value / rhs.m_value;}
   IntType operator%(const myuint& rhs)   {return m_value % rhs.m_value;}
   
   // Cast to 'unsigned short' for output, as 'unsigned char' is printed out as ASCII
   friend std::ostream &operator<<(std::ostream &s, const myuint &instance) {s << static_cast<unsigned short>(instance.m_value); return s;}
};

template<>
class myuint<16> : BuiltInIntBase<16>
{
public:
   myuint() : BuiltInIntBase() {};
   myuint(IntType value) : BuiltInIntBase(value) {};
   myuint(const std::string s) : BuiltInIntBase(s) {};
   
   IntType operator+(const myuint& rhs)   {return m_value + rhs.m_value;}
   IntType operator-(const myuint& rhs)   {return m_value - rhs.m_value;}
   IntType operator*(const myuint& rhs)   {return m_value * rhs.m_value;}
   IntType operator/(const myuint& rhs)   {return m_value / rhs.m_value;}
   IntType operator%(const myuint& rhs)   {return m_value % rhs.m_value;}
   
   friend std::ostream &operator<<(std::ostream &s, const myuint &instance) {s << instance.m_value; return s;}
};

template<>
class myuint<32> : BuiltInIntBase<32>
{
public:
   myuint() : BuiltInIntBase() {};
   myuint(IntType value) : BuiltInIntBase(value) {};
   myuint(const std::string s) : BuiltInIntBase(s) {};
   
   IntType operator+(const myuint& rhs)   {return m_value + rhs.m_value;}
   IntType operator-(const myuint& rhs)   {return m_value - rhs.m_value;}
   IntType operator*(const myuint& rhs)   {return m_value * rhs.m_value;}
   IntType operator/(const myuint& rhs)   {return m_value / rhs.m_value;}
   IntType operator%(const myuint& rhs)   {return m_value % rhs.m_value;}
   
   friend std::ostream &operator<<(std::ostream &s, const myuint &instance) {s << instance.m_value; return s;}
};

template<>
class myuint<64> : BuiltInIntBase<64>
{
public:
   myuint() : BuiltInIntBase() {};
   myuint(IntType value) : BuiltInIntBase(value) {};
   myuint(const std::string s) : BuiltInIntBase(s) {};
   
   IntType operator+(const myuint& rhs)   {return m_value + rhs.m_value;}
   IntType operator-(const myuint& rhs)   {return m_value - rhs.m_value;}
   IntType operator*(const myuint& rhs)   {return m_value * rhs.m_value;}
   IntType operator/(const myuint& rhs)   {return m_value / rhs.m_value;}
   IntType operator%(const myuint& rhs)   {return m_value % rhs.m_value;}
   
   friend std::ostream &operator<<(std::ostream &s, const myuint &instance) {s << instance.m_value; return s;}
};

#endif // MYINT_SPECIALIZATIONS_H