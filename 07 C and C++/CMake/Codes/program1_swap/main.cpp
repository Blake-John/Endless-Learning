#include "../include/swap.h"
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
    Swap myswap ((int*)10, (int*)20);
    myswap.printInfo ();
    myswap.run ();
    myswap.printInfo ();

    return 0;
}