#include <iostream>
using namespace std;

int randSeed = 232623;

int rand() {
    randSeed = randSeed * 1103515245 + 12345;
    return (randSeed / 65536) % 32768;
}

bool checkSkip(int n)
{
    int num = 23*100+100;
    if(n < num)
    {
        return true;
    }
    return false;
}