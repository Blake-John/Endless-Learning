#include "../include/swap.h"

using namespace std;

void Swap::run ()
{
    int temp;
    temp = _a;
    _a = _b;
    _b = temp;
}

void Swap::printInfo ()
{
    cout << "_a = " << _a << endl;
    cout << "_b = " << _b << endl;
}