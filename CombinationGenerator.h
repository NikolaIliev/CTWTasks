#pragma once
#define COMBINATION_GENERATOR_H
#include <vector>
#include <iostream>
using namespace std;

class CombinationGenerator {
    vector<int> elements;
    void _generate(vector<vector<int>>&, vector<int>, int, size_t&);
public:
    CombinationGenerator(vector<int> elements) { this->elements = elements; };
    vector<vector<int>> generate(size_t);
    virtual bool areCompatible(int, int);
};
