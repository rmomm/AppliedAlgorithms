#pragma once

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

enum class DataType { RANDOM, SORTED, REVERSED, ALMSORTED, FEWUN };

vector<int> generateData(size_t size, DataType type) {
    vector<int> data(size);
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(0, 100000);

    switch (type) {
    case DataType::RANDOM:
        for (auto& x : data) x = dist(gen);
        break;
    case DataType::SORTED:
        for (size_t i = 0; i < size; ++i) data[i] = i;
        break;
    case DataType::REVERSED:
        for (size_t i = 0; i < size; ++i) data[i] = size - i;
        break;
    case DataType::ALMSORTED:
        for (size_t i = 0; i < size; ++i) data[i] = i;
        for (size_t i = 0; i < size / 20; ++i) std::swap(data[dist(gen) % size], data[dist(gen) % size]);
        break;
    case DataType::FEWUN:
        for (auto& x : data) x = dist(gen) % 5;
        break;
    }
    return data;
}