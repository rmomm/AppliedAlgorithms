#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    int n;

public:
    vector<int> R, List, Next, Size, InternalNames, ExternalNames;

    UnionFind(int n) : n(n) {
        R.resize(n);
        Next.resize(n, 0);
        List.resize(n);
        Size.resize(n, 1);
        InternalNames.resize(n);
        ExternalNames.resize(n);

        for (int i = 0; i < n; ++i) {
            R[i] = i;
            List[i] = i;
            Next[i] = 0;
            InternalNames[i] = i;
            ExternalNames[i] = i;
        }

    }

    int Find(int x) {
        return R[x];
    }

    void Unite(int x, int y) {
        int A = Find(x);
        int B = Find(y);

        if (A == B) return;

        if (Size[A] < Size[B])
            swap(A, B);

        int i = List[B];
        while (i != 0) {
            R[i] = A;
            i = Next[i];
        }

        int last = List[A];
        while (Next[last] != 0)
            last = Next[last];
        Next[last] = List[B];

        Size[A] += Size[B];

        List[B] = 0;
        Size[B] = 0;
    }
};
