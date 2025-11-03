#include "LUP.h"
#include <stdexcept>
#include <cmath>

using namespace std;

LUPResult LUP(const Matrix& A) {
    int n = A.size();
    Matrix LU = A;
    vector<int> P(n);
    for (int i = 0; i < n; i++) P[i] = i;

    for (int k = 0; k < n; k++) {
        double maxVal = 0.0;
        int pivot = k;
        for (int i = k; i < n; i++) {
            if (abs(LU.at(i, k)) > maxVal) {
                maxVal = abs(LU.at(i, k));
                pivot = i;
            }
        }

        if (maxVal == 0)
            throw runtime_error("Матриця вироджена!");

        swap(P[k], P[pivot]);
        for (int j = 0; j < n; j++)
            swap(LU.at(k, j), LU.at(pivot, j));

        for (int i = k + 1; i < n; i++) {
            LU.at(i, k) /= LU.at(k, k);
            for (int j = k + 1; j < n; j++)
                LU.at(i, j) -= LU.at(i, k) * LU.at(k, j);
        }
    }

    return { LU, P };
}

Vector LUPSolve(const LUPResult& lup, const Vector& b) {
    int n = lup.LU.size();
    Vector x(n), y(n);

    Vector bp(n);
    for (int i = 0; i < n; i++)
        bp.at(i) = b.at(lup.P[i]);

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += lup.LU.at(i, j) * y.at(j);
        y.at(i) = bp.at(i) - sum;
    }

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += lup.LU.at(i, j) * x.at(j);
        x.at(i) = (y.at(i) - sum) / lup.LU.at(i, i);
    }


    return x;
}