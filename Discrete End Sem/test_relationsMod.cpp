#include <iostream>
#include "FunctionsModule.h"
using namespace std;

int main()
{
    cout << "=============================================\n";
    cout << "        RELATIONS MODULE - TEST RUN\n";
    cout << "=============================================\n";

    FunctionsModule module;

    // Run all built-in demonstrations
    module.demonstrateFunctions();

    cout << "\n=============================================\n";
    cout << "        END OF TESTING\n";
    cout << "=============================================\n";

    return 0;
}
