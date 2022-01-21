#include "myint.h"
#include "myint_specializations.h"

using namespace std;

/*
TODO:
- bash files in java and the other C++ task
- BUG myuint<16> X16(-1u);  cout << X16 << endl;
     std::cout << "    " << value << "    ";
- CONSTRUCTORS:
        - Both initialize() and fromString(): don't check limits and store massive values, AND don't handle negative numbers;
                FIX NEGATIVE NUMBERS IN INITIALIZE
                // For 64-bit and higher, check if value not out of bounds.
                int numVecUnits = s_bitsize / s_vecUnitBitSize;
                if ((m_value.size() > 1) && (m_value.size() > numVecUnits))
                {
                    throw overflow_error("Value is out of bounds!");
                }
- *, /, %
    - Why my_div
- Better testing
*/


void test()
{
    // Test 8-bit
    myuint<8> X8(3u), Y8(255u), Z8(0u);
    Z8 = Y8 + X8; 
    cout << Z8 << endl;

    // Test UL contructor
    myuint<64> My64(12ul);
    cout << My64 << endl;

    // Test initialization with -1
    myuint<16> X16(-1u);  cout << X16 << endl;
    myuint<256> X256(-1u); cout << X256 << endl;

    // Test 32-bit operations, including result wrapping
    myuint<32> X(1u), Y(3u), Z(0u);
    Z = Y + X; cout << Z << endl;
    Z = Y - X; cout << Z << endl;
    Z = X - Y; cout << Z << endl;

    // Test string initialization
    myuint<32> MyIntStr(string("998877665544332211"));
    cout << MyIntStr << endl;;

    // Test 1024 bit int.
    myuint<1024> X1k(1u), Y1k(3u), Z1k(0u);
    Z1k = Y1k + X1k; 
    cout << Z1k << endl;
}

int main()
{
    try
    {
        test();
    }
    catch (const exception& e)
    {
        cerr << "Caught: " << e.what() << " Exception type: " << typeid(e).name() << endl;
    }

    return 0;
}
