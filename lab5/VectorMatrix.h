#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>

using namespace std;

class Vector {
private:
	vector<double> data;
public:
	Vector(int n = 0) : data(n, 0.0) {}

    Vector(const vector<double>& values) : data(values) {}

	int size() const { return data.size(); }

	double& at(int i) {
		if (i < 0 || i >= size()) throw out_of_range("Vector index out of range");
		return data[i];
	}

	double at(int i) const {
		if (i < 0 || i >= size()) throw out_of_range("Vector index out of range");
		return data[i];
	}

    void printDecimal(int precision = 4) const {
        for (double x : data)
            cout << setw(10) << fixed << setprecision(precision) << x << " ";
        cout << "\n";
    }

    Vector add(const Vector& other) const {
        if (size() != other.size()) throw invalid_argument("Vector sizes do not match");
        Vector result(size());
        for (int i = 0; i < size(); i++)
            result.at(i) = data[i] + other.at(i);
        return result;
    }

    Vector sub(const Vector& other) const {
        if (size() != other.size()) throw invalid_argument("Vector sizes do not match");
        Vector result(size());
        for (int i = 0; i < size(); i++)
            result.at(i) = data[i] - other.at(i);
        return result;
    }

    Vector mulScalar(double k) const {
        Vector result(size());
        for (int i = 0; i < size(); i++)
            result.at(i) = data[i] * k;
        return result;
    }

    double dot(const Vector& other) const {
        if (size() != other.size()) throw invalid_argument("Vector sizes do not match");
        double sum = 0.0;
        for (int i = 0; i < size(); i++)
            sum += data[i] * other.at(i);
        return sum;
    }

    void input() {
        for (int i = 0; i < size(); i++) cin >> data[i];
    }

    void print() const {
        for (double x : data)
            cout << setw(5) << static_cast<int>(x) << " ";
        cout << "\n";
    }

};

class Matrix {
private:
    int n;
    vector<double> a; 
public:
    Matrix(int size = 0) : n(size), a(size* size, 0.0) {}

    Matrix(const vector<vector<double>>& values) {
        n = values.size();
        a.resize(n * n, 0.0); 
        for (int i = 0; i < n; i++) {
            if (values[i].size() != n)
                throw invalid_argument("Matrix must be square");
            for (int j = 0; j < n; j++)
                at(i, j) = values[i][j]; 
        }
    }

    int size() const { return n; }

    double& at(int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= n)
            throw out_of_range("Matrix index out of range");
        return a[i * n + j];
    }

    double at(int i, int j) const {
        if (i < 0 || j < 0 || i >= n || j >= n)
            throw out_of_range("Matrix index out of range");
        return a[i * n + j];
    }


    Matrix add(const Matrix& other) const {
        if (n != other.n) throw invalid_argument("Matrix sizes do not match");
        Matrix res(n);
        for (int i = 0; i < n * n; i++) res.a[i] = a[i] + other.a[i];
        return res;
    }

    Matrix sub(const Matrix& other) const {
        if (n != other.n) throw invalid_argument("Matrix sizes do not match");
        Matrix res(n);
        for (int i = 0; i < n * n; i++) res.a[i] = a[i] - other.a[i];
        return res;
    }

    Matrix mulScalar(double k) const {
        Matrix res(n);
        for (int i = 0; i < n * n; i++) res.a[i] = a[i] * k;
        return res;
    }

    Vector mulVector(const Vector& v) const {
        if (n != v.size()) throw invalid_argument("Matrix and vector size mismatch");
        Vector res(n);
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++)
                sum += at(i, j) * v.at(j);
            res.at(i) = sum;
        }
        return res;
    }

    Matrix mulMatrix(const Matrix& other) const {
        if (n != other.n) throw invalid_argument("Matrix sizes do not match");
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res.at(i, j) += at(i, k) * other.at(k, j);
        return res;
    }


    void input() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> at(i, j);
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << setw(5) << static_cast<int>(at(i, j)) << " ";
            cout << "\n";
        }
    }
};