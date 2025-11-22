#include <iostream>
#include "RelationsModule.h"
using namespace std;

int main()
{
    cout << "=============================================\n";
    cout << "        RELATIONS MODULE - TEST RUN\n";
    cout << "=============================================\n";

    RelationsModule module;

    // Run all built-in demonstrations
    module.demonstrateRelations();

    cout << "\n=============================================\n";
    cout << "        END OF TESTING\n";
    cout << "=============================================\n";

    return 0;
}
