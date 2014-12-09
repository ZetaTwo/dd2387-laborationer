> Vad finns det för designfel i Matrix.h? Vad borde man kunna göra som man inte kan göra?

- There is no scalar division operator
- `Matrix::transpose()` modifies the matrix instead of returning a modified
  copy. It's not `const`, which means it's forbidden to compute the transpose
  of a `const Matrix`. Better solution:
  - `Matrix& Matrix::transpose()`
  - `Matrix Matrix::transposition() const`
- The output operator `std::ostream& operator<<(std::ostream&, Matrix&)` takes
  a mutable `Matrix` reference instead of a `const` reference. This means that
  `const Matrix m; std::cout << m;` is forbidden. `operator<<` should declare
  its `Matrix&` parameter as `const Matrix&`.
- `Matrix` does not declare `operator==` or `operator!=`


> ha gissningar på vad som är galet i de olika matrisimplementationerna du testat

 1. Subtraction is weird. It seems to randomly zero out a lot of elements in
 the result.
 2. Multiplication fails. It seems like it computes the result correctly but
 then adds 1 to the bottom-left element.
 3. Assignment operator(s) fails. It seems to set itself to twice the argument.
 4. Output operator modifies the matrx, seems like it zeroes the whole matrix.
 5. Constructors always build a 3x3 matrix.
 6. Transposition fails. Looks like the first column is zeroed.
 7. Addition with zero matrix is interpreted as elementwise multiplication
 instead.
 8. Addition with zero matrix from the left is interpreted as elementwise
 multiplication instead.
 9. Addition with zero matrix sets bottom-right element equal to that of the
 second term. Subtraction seemingly sets bottom-right element and that to the
 left of it to zero.
