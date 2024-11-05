#ifndef MATRIX_H
#define MATRIX_H

#include "iostream"
using namespace std;

typedef long double precision_type;

class Matrix {
protected:
    unsigned int m; //lines
    unsigned int n; //columns
    precision_type** matr;
    void init() {
        matr = new precision_type * [m];
        //cout << "	Initialized Matrix_addr=" << this << "	matr=" << matr << endl;
        for (int i = 0; i < m; i++)//i - illustrates line
            matr[i] = new precision_type[n];
    }
public:
    //constructors
    Matrix(unsigned int a) {
        m = n = a;
        init();
    }
    Matrix(unsigned int a, unsigned int b) {
        m = a;
        n = b;
        init();
    }
    Matrix(unsigned int a, unsigned int b, precision_type** arr) {
        m = a;
        n = b;
        init();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                matr[i][j] = arr[i][j];
    }
    //copy
    Matrix(const Matrix&);
    //	Matrix(Matrix&&);

    //destructor
    ~Matrix() {
        //cout << "	Deleted Matrix_addr=" << this << "	matr=" << matr << endl;
        for (int i = 0; i < m; i++) {
            //cout << "deleted " << i << "-line" << endl;
            delete[] matr[i];
        }
        delete[] matr;
    }

    //operators
    Matrix& operator=(const Matrix&);
    precision_type* operator[](int);
    Matrix operator+(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix operator*(const precision_type&);
    Matrix operator*(const Matrix&);
    Matrix& operator*=(const Matrix&);
    //
    //det - square-only
    //invert

    //func
    unsigned int lines() const {
        return m;
    }
    unsigned int columns() const {
        return n;
    }
    precision_type elem(unsigned int i, unsigned int j) const {
        return matr[i][j];
    }
    Matrix transpose();
    precision_type det();
    Matrix inverse();
    void show();
};

int matrix_test();

#endif // MATRIX_H
