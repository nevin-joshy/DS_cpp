#include <iostream>

class Matrix{
public:
    Matrix();//defaule constructor
    Matrix(const unsigned int row, const unsigned int col, const double fill);//
    //constructor
    ~Matrix();//destructor
    Matrix(const Matrix& other);//copy constuctor
    int num_rows() const{return m_rows;}
    int num_cols() const{return m_cols;}
    void multiply_by_coefficient(double co);
    void clear();
    void transpose();
    bool swap_row(unsigned int srow, unsigned int trow);
    bool add(const Matrix& other);
    bool subtract(const Matrix& other);
    bool get(unsigned int row, unsigned int col, double &val) const;
    bool set(unsigned int row, unsigned int col, double val);
    bool isEqual(const Matrix& other) const;//function that is used in == and != functions
    double* get_row(unsigned int rownum) const;
    double* get_col(unsigned int colnum) const;
    void resize(unsigned int newrow, unsigned int newcol, double fill);
    Matrix* quarter() const;
    Matrix& operator=(const Matrix& other);//assignment operator

private:
    double**data;//grid for matrix values
    unsigned int m_rows;
    unsigned int m_cols;
};
std::ostream& operator<< (std::ostream& out, const Matrix& m);
bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);


