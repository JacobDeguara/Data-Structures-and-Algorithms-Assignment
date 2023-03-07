#include <iostream>
#include "Log.cpp"

int main()
{
    Log log = Log("test.txt");

    log.Write("This is the first test on how this works");
    log.Write("This is the first test on how this works");
    log.Write("This is the first test on how this works");

    return 0;
}