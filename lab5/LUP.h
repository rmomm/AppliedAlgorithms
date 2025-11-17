#pragma once

#include "VectorMatrix.h"
#include <vector>

struct LUPResult {
    Matrix LU;
    std::vector<int> P; 
};

LUPResult LUP(const Matrix& A);
Vector LUPSolve(const LUPResult& lup, const Vector& b);
