#ifndef MYINT_H
#define MYINT_H

#include <assert.h>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

template<unsigned int BIT_SIZE>
class myuint
{
private:
    typedef int BACKEND_TYPE;


public:
    // Default constructor. Note smaller built in types are handled by constructors inside the specializations
    myuint()                            {initialize(0u);}
    myuint(unsigned long long value)    {initialize(value);}

    myuint(const std::string s)
    {
        fromString(s);
    }

    // Operations
    myuint operator+(const myuint& rhs)
    {
        myuint<BIT_SIZE> result(0u);
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            result.m_value[i] = m_value[i] + rhs.m_value[i];
        }
        
        result.normalize();

        return result;
    }

    myuint operator-(const myuint& rhs)
    {
        // "A computation involving unsigned operands can never overflow, because a result that cannot be
        // represented by the resulting unsigned integer type is reduced modulo the number that is one greater
        // than the largest value that can be represented by the resulting type. (ISO/IEC 9899:1999 (E) §6.2.5/9)"
        // Ref: http://ptgmedia.pearsoncmg.com/images/0321335724/samplechapter/seacord_ch05.pdf page 166
        
        // As you can see, (unsigned)0 - (unsigned)1 equals -1 modulo UINT_MAX+1, or in other words, UINT_MAX.
        // -X  ->  (UINT_MAX + 1 - X)
        
        myuint<BIT_SIZE> result(0u);
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            result.m_value[i] = m_value[i] - rhs.m_value[i];
        }
        
        result.normalize();

        return result;
    }

    myuint operator*(const myuint& rhs) const;
    myuint operator/(const myuint& rhs) const;
    myuint operator%(const myuint& rhs) const;

    friend std::ostream &operator<<(std::ostream &s, const myuint &instance)
    {
        bool first = true;
        for (int i = (int) instance.m_value.size() - 1; i >= 0; --i)
        {
            if (first)
            {
                s << instance.m_value[i];
                first = false;
            }
            else
            {
                s << std::setfill('0') << std::setw(instance.s_num_digits) << instance.m_value[i];
            }
        }
        return s;
    }

private:

    void initialize(unsigned long long value)
    {
        // Spread the input value across vector units.
        m_value.clear();
        do
        {
            m_value.push_back((BACKEND_TYPE) (value % s_base));
            value = value / s_base;
        } while (value > 0);
    }

    void normalize()
    {
        for (size_t i = 0; i < m_value.size(); ++i)
        {
            // Check if out of bounds, note our bounds are +/-999,999,999
            if ((m_value[i] >= s_base) || (m_value[i] <= -s_base))
            {
                div_t dt = div(m_value[i], s_base);
                m_value[i] = dt.rem;

                // Assert if value is out of bounds.
                assert(i + 1 < m_value.size());
                
                m_value[i + 1] += dt.quot;
            }

            // Remove potential negative numbers by wrapping from our MAX values (s_base).
            if (m_value[i] < 0)
            {
                m_value[i] = s_base + m_value[i];
                if (i + 1 < m_value.size())
                {
                    m_value[i + 1] -= 1;
                }
            }
        }
    }

    inline void fromString(const std::string& s)
    {
        m_value.clear();
        m_value.reserve(s.size() / s_num_digits + 1);
        int i = (int) s.size() - s_num_digits;
        for (; i >= 0; i -= s_num_digits)
        {
            m_value.push_back(atoi(s.substr(i, s_num_digits).c_str()));
        }
        if (i > -s_num_digits)
        {
            std::string ss = s.substr(0, i + s_num_digits);
            m_value.push_back(atoi(ss.c_str()));
        }
    }

private:
    static const int s_bitsize = BIT_SIZE;
    static const int s_vecUnitBitSize = 32;
    static const int s_base = 1000000000;
    static const int s_num_digits = 9;

    std::vector<BACKEND_TYPE> m_value;
};

#endif // MYINT_H