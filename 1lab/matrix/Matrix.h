#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "../vector/kth_cprog_vektor.cpp"

class Matrix
{
 public:
    typedef size_t index;

    //typedef std::vector<int> vector_base;
    typedef Vector<int> vector_base;
    class matrix_row : private vector_base
    {
    public:
      matrix_row(std::size_t size = 0) : vector_base(size) {}
      using vector_base::operator [];
      using vector_base::iterator;
      using vector_base::const_iterator;
      using vector_base::begin;
      using vector_base::end;
    private:
      friend std::istream& operator>>(std::istream& stream, Matrix& matrix);
      friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix);
    };

    Matrix();
    Matrix(const Matrix& other);
    explicit Matrix(index size);
    Matrix(index rows, index cols);
    Matrix(std::string serialized);
    ~Matrix();

    Matrix& operator= (const Matrix& other);
    bool operator== (const Matrix& other) const;
    bool operator!= (const Matrix& other) const;
    Matrix operator+ (const Matrix& other) const;
    Matrix operator* (const Matrix& other) const;
    Matrix operator* (int factor) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator-() const;


    Matrix transpose() const;

    matrix_row& operator[](index i);
    const matrix_row& operator[](index i) const;

    std::size_t rows() const;
    std::size_t cols() const;

 protected:
 private:
    std::size_t                 m_rows;
    std::size_t                 m_cols;
    Vector<matrix_row>        m_vectors;
    
    void from_string(std::stringstream data);
    friend std::istream& operator>> (std::istream& stream, Matrix& matrix);
    friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix);
};

std::istream& operator>> ( std::istream& stream, Matrix& matrix);
std::ostream& operator<< (std::ostream& stream, const Matrix& matrix);
Matrix operator* ( int factor, const Matrix& matrix);