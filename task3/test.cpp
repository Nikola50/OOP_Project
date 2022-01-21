
#include <sstream>

#include "myint.h"
#include "myint_specializations.h"

using namespace std;

template <typename TYPE>
void testCheckResult(TYPE value, string expectedValue)
{
    ostringstream testOut;
    testOut << value;
    testOut.str() == expectedValue ? (cout << "PASS") : (cout << "FAIL");
    cout << ":      " << testOut.str() << endl;
}

void test()
{
    // Test 8-bit, including result wrapping
    myuint<8> X8(3u), Y8(255u), Z8(0u);
    Z8 = Y8 + X8; testCheckResult(Z8, "2");
    Z8 = X8 - 4;  testCheckResult(Z8, "255");

    // Test 32-bit, including result wrapping
    myuint<32> X32(1u), Y32(3u), Z32(0u);
    Z32 = Y32 + X32; testCheckResult(Z32, "4");
    Z32 = Y32 - X32; testCheckResult(Z32, "2");
    Z32 = X32 - Y32; testCheckResult(Z32, "4294967294");

    // Test UL contructor
    myuint<64> X64(12ul); testCheckResult(X64, "12");

    // Test string initialization
    myuint<256> X256("998877665544332211"), Z256;
    testCheckResult(X256, "998877665544332211");
    Z256 = X256 + 1; testCheckResult(Z256, "998877665544332212");

    // Test 1024 bit int.
    myuint<1024> X1k(1u), Y1k(3u), Z1k(0u);
    Z1k = Y1k + X1k; testCheckResult(Z1k, "4");
    Z1k = Y1k - X1k; testCheckResult(Z1k, "2");
}

