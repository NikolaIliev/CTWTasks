#include <iostream>
#include <vector>
#include <math.h>
#include "CombinationGenerator.h"
using namespace std;

void CombinationGenerator::_generate(vector<vector<int>>& subsets, vector<int> current, int start, size_t& k) {
    // The new element must be compatible with all elements in the current subset
    for (int element : current) {
        if (!areCompatible(elements[start], element))
            return;
    }

    current.push_back(elements[start]);

    if (current.size() == k) {
        subsets.push_back(current);
        return;
    }

    for (int i = start + 1; i < elements.size(); i++) {
        _generate(subsets, current, i, k);
    }
}

vector<vector<int>> CombinationGenerator::generate(size_t k) {
    if (k <= 0 || k > elements.size()) return vector<vector<int>>();

    vector<vector<int>> subsets;

    for (int i = 0; i <= elements.size() - k; i++) {
        _generate(subsets, vector<int>(), i, k);
    }

    return subsets;
}

bool CombinationGenerator::areCompatible(int a, int b) {
    return a % 2 == b % 2;
}