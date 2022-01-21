
#include <ostream>

#include "myint.h"
#include "myint_specializations.h"
#include "test.h"

using namespace std;

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
