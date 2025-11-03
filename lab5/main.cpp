#include "VectorMatrix.h"
#include "LUP.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Vector\n";
    Vector v1({ 3, 5, 8 });
    Vector v2({ 1, -5, 9 });

    cout << "v1 = "; v1.print();
    cout << "v2 = "; v2.print();

    cout << "v1 + v2 = "; (v1.add(v2)).print();
    cout << "v1 - v2 = "; (v1.sub(v2)).print();
    cout << "v1 * 3 = "; (v1.mulScalar(3.0)).print();
    cout << "v1 . v2 = " << v1.dot(v2) << endl;


    cout << "\n Matrices \n";
    Matrix A({
        {3, 5, 2},
        {5, -1, 0},
        {1, 3, 9}
        });
    Matrix B({
        {0, 2, 7},
        {4, 3, 5},
        {1, -2, -1}
        });

    cout << "A =\n"; A.print();
    cout << "B =\n"; B.print();

    cout << "A + B =\n"; A.add(B).print();
    cout << "A - B =\n"; A.sub(B).print();
    cout << "A * B =\n"; A.mulMatrix(B).print();
    cout << "A * v1 =\n"; A.mulVector(v1).print();
    cout << "B * v2 =\n"; B.mulVector(v2).print();

    cout << "\n LUP: 6x6 system\n";
    Matrix M(6);
    Vector b(6);

    double values[6][6] = {
      {2, -1, 3, 5, 7, -1},
      {-1, 3, -1, 8, 3, 0},
      {0, -2, 1, 3, 4, 9},
      {1, 5, 2, 2, -3, 0},
      {8, 1, 3, 8, 1, 5},
      {1, 2, 4, 6, 8, 0}
    };
    double b_values[6] = { 1, 3, 2, 5, 1, 7 };

    for (int i = 0; i < 6; i++) {
        b.at(i) = b_values[i];
        for (int j = 0; j < 6; j++)
            M.at(i, j) = values[i][j];
    }

    cout << "Matrix M:\n"; M.print();
    cout << "Vector b: "; b.print();

    LUPResult lup = LUP(M);
    Vector x = LUPSolve(lup, b);
    cout << "Solution x: ";
    x.printDecimal();

    return 0;

}