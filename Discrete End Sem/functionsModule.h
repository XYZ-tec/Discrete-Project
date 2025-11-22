#pragma once
#ifndef FUNCTIONSMODULE_H
#define FUNCTIONSMODULE_H
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

class FunctionsModule
{
public:
    // Function represented as map from domain to codomain
    using Function = map<string, string>;

    // Check if mapping is a valid function (each input has exactly one output)
    static bool isValidFunction(const Function& func, const set<string>& domain);

    // Check if function is injective (one-to-one)
    static bool isInjective(const Function& func);

    // Check if function is surjective (onto)
    static bool isSurjective(const Function& func, const set<string>& codomain);

    // Check if function is bijective (one-to-one and onto)
    static bool isBijective(const Function& func, const set<string>& codomain);

    // Compose two functions: (g ∘ f)(x) = g(f(x))
    static Function composeFunctions(const Function& f, const Function& g);

    // Get inverse function (only works for bijective functions)
    static Function inverseFunction(const Function& func);

    // Get image/range of function
    static set<string> getImage(const Function& func);

    // Get domain of function
    static set<string> getDomain(const Function& func);

    // Get preimage of an element (all inputs that map to given output)
    static set<string> getPreimage(const Function& func, const string& element);

    // Display function
    static void displayFunction(const Function& func, const string& functionName = "Function");

    // Display function properties
    static void displayProperties(const Function& func, const set<string>& codomain, const string& functionName = "Function");

    // Check if function is identity function
    static bool isIdentityFunction(const Function& func, const set<string>& domain);

    // Create identity function
    static Function createIdentityFunction(const set<string>& domain);

    // Check if function is constant
    static bool isConstantFunction(const Function& func);

    // Apply function to an element
    static string applyFunction(const Function& func, const string& input);

    // Demonstrate function operations
    static void demonstrateFunctions();
};

#endif#pragma once
