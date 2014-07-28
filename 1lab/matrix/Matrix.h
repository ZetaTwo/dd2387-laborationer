#pragma once

#include <iostream>
#include <stdexcept>
#include "../vector/kth_cprog_vektor.cpp"

class Matrix
{
 public:
    typedef unsigned int index;

    class matrix_row : private Vector< int >
    {
    public:
        matrix_row(std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator [];
    private:
        friend std::istream& operator>>( std::istream&, Matrix& );
    };

    Matrix();
    Matrix(const Matrix& other);
    explicit Matrix(std::size_t size);
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(std::string serialized);
    ~Matrix();

    Matrix& operator= ( const Matrix& );
    bool operator== (const Matrix&) const;
    bool operator!= (const Matrix&) const;
    Matrix operator+ ( const Matrix& ) const;
    Matrix operator* ( const Matrix& ) const;
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator-( ) const;


    Matrix transpose( ) const;

    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;

    std::size_t rows() const;
    std::size_t cols() const;

 protected:
 private:
    Vector< matrix_row >        m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;

    void add_row( );            // Non mandatory help function
    friend std::istream& operator>> ( std::istream&, Matrix& );
};

std::istream& operator>> ( std::istream& stream, Matrix& matrix);
std::ostream& operator<< (std::ostream& stream, Matrix& matrix);
Matrix operator* ( int factor, const Matrix& matrix);