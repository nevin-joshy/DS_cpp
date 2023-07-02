#include "Matrix.h"
#include <iomanip>
#include <iostream>


Matrix::Matrix(){//default constructor, makes empty matrix
    m_rows = 0;
    m_cols = 0;
    data = NULL;
}

//initializer
Matrix::Matrix(const unsigned int row, const unsigned int col, const double fill){
    m_rows= row;
    m_cols = col;
    if(m_rows==0 || m_cols==0){//creates empty array of either dimension is 0
        m_rows=0;
        m_cols=0;
        data = NULL;
    
    }else{
        data = new double*[m_rows];//data points to array of pointers

        for (unsigned int i=0; i<m_rows;i++){
            data[i] = new double[m_cols];//pointer array points to a double array
        }

        for (int i = 0; i<m_rows;i++){
            for(int j = 0; j<m_cols; j++){
                data[i][j]=fill;//fills data with value fill
            }
        }
    }

}

Matrix::Matrix(const Matrix& other){//copy constructor
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    if(m_rows==0 || m_cols==0) data=NULL;//creates empty matrix is either dimesion 0
    else{
        data = new double*[m_rows];//data points to array of pointers

        for (int i=0; i<m_rows;i++){
            data[i] = new double[m_cols];//pointer array points to a double array
        }

        for (int i = 0; i<m_rows;i++){
            for(int j = 0; j<m_cols; j++){
                data[i][j]=other.data[i][j];//copys values from other matrix into
                //current matrix
            }
        }
    }
}

Matrix::~Matrix(){//destructor
    this->clear();//clears data pointer using clear function
}

bool Matrix::add(const Matrix& other){
    if(m_rows!=other.m_rows||m_cols!=other.m_cols){
        return false;//checks whether dimensions are the same
    }
    for (int i = 0; i<m_rows;i++){
        for(int j = 0; j<m_cols; j++){
            data[i][j]+=other.data[i][j];//adds values from other matrix into current
        }
    }
    return true;
}

bool Matrix::subtract(const Matrix& other){
    if(m_rows!=other.m_rows||m_cols!=other.m_cols){
        return false;//checks whether dimensions are the same
    }
    for (int i = 0; i<m_rows;i++){
        for(int j = 0; j<m_cols; j++){
            data[i][j]-=other.data[i][j];//subtracts values from other matrix into
            //current matrix
        }
    }
    return true;
}

void Matrix::multiply_by_coefficient(double co){
    for (int i = 0; i<m_rows;i++){
        for(int j = 0; j<m_cols; j++){
            data[i][j]*=co;//multiplies each value in data by coefficient
        }
    }
}

void Matrix::clear(){

    if(data!=NULL){
        for (unsigned int i=0; i<m_rows; i++){
            delete [] data[i];//deletes each double array first
        }
        delete [] data;// after deleting each doublr array, data is deleted
        data = NULL;
    }
    m_rows = 0;
    m_cols = 0;
}

bool Matrix::get(unsigned int row, unsigned int col, double & val) const{

    if(row<m_rows && col<m_cols){//checks whether given dimensions are in bounds
        val = data[row][col];//accesses value at specified row and column, assigns it
        //to val
        return true;
    }
    return false;
}

bool Matrix::set(unsigned int row, unsigned int col, double val){
    if(row<m_rows && col<m_cols){//checks whether given dimensions are in bounds
        data[row][col]=val;//accesses value at specified row and column, 
        //and gives it the value val
        return true;
    }
    return false;
}

bool Matrix::swap_row(unsigned int srow, unsigned int trow){
    if(srow>=m_rows||trow>=m_cols||srow<0||trow<0){//checks whether given rows are in 
    //bounds
        return false;
    }
    double* temp = data[srow];//temp saves content of initial row
    double* temp2 = data[trow];//temp2 saves content on new row
    data[srow]=temp2;//old row changes to temp2, which is new row
    data[trow]=temp;//new row changes to temp, which is old row
    temp = NULL;//both temps set to null
    temp2 = NULL;
    return true;
}

bool Matrix::isEqual(const Matrix& other) const{//function used to compare matrixes in ==
//and != functions
    if (m_rows==other.m_rows&&m_cols==other.m_cols){//checks that dimensions are same
        for(int i = 0; i<m_rows; i++){
            for(int j = 0;j<m_cols;j++){
                if(data[i][j]!=other.data[i][j]){//iterates trough each value and checks
                //returns false if the values are different
                    return false;
                }
            }
        }
    }else{
        return false;
    }
    return true;
}

double* Matrix::get_row(unsigned int rownum) const{
    double* row;
    if(rownum<0||rownum>=m_rows){//chekcs if given row is out of bounds
        row = NULL;
        return row;
    }
    row = new double[m_cols];
    for(int i = 0; i<m_cols; i++){
        row[i] = data[rownum][i];//assigns each value in row to the
        //corresponding value in the matrix
    }
    return row;
}

double* Matrix::get_col(unsigned int colnum) const{
    double* col;
    if(colnum<0||colnum>=m_cols){//chekcs if given row is out of bounds
        col = NULL;
        return col;
    }
    col = new double[m_rows];
    for(int i = 0; i<m_rows;i++){
        col[i] = data[i][colnum];//assigns each value in col to the corresponding
        //value in the matrix
    }
    return col;
}

void Matrix::transpose(){
    int tmpr = m_rows;//saves number of rows
    int tmpc = m_cols;//saves number of columns
    if(data!=NULL){
        double** newdata = new double*[m_cols];//creates new data object with
        //opposite dimensions
        for (unsigned int i=0; i<m_cols;i++){
            newdata[i] = new double[m_rows];
        }
        for(int i = 0; i<m_rows; i++){
            for(int j = 0; j<m_cols; j++){
                newdata[j][i] = data[i][j];//assigns opposite values to new data
                //object(instead of row,col, assigns col,row)
            }
        }
        clear();//clears current data to avoid leak
        data = newdata;//sets current data, now null, equal to the new data object
    }
    m_rows = tmpc;//sets the rows equal to the saved columns
    m_cols = tmpr;//sets columns equal to saved rows
}

void Matrix::resize(unsigned int newrow, unsigned int newcol, double fill){
    
    if(newrow == 0 || newcol ==0){//checks if either dimension is 0 and ends function
        clear();
        return;
    }
    double** sizedata = new double*[newrow];//creates new double** object with specified
    //rows and columns
    for (unsigned int i=0; i<newrow;i++){
        sizedata[i] = new double[newcol];
    }

    for(int i = 0; i<newrow; i++){
        for(int j = 0; j<newcol; j++){
            if(i<m_rows && j<m_cols){
                sizedata[i][j] = data[i][j];//sets each value that is in bounds in the
                //new double** object to the current data values
            }
            else{
                sizedata[i][j] = fill;//all values out of bounds are set to the fill
                //value
            }
        }
    }
    clear();//clears the current data to avoid leaks
    data = sizedata;//sets current data equal to the new double**object
    m_rows = newrow;//refreshes column and row data
    m_cols = newcol;
}

Matrix* Matrix::quarter() const{
    Matrix* matrixlist = new Matrix[4];//new matrix pointer array for quarters to be 
    //stored in
    unsigned int numrows;//initlaizes the numer and rows and columns the
    // quarters will have
    unsigned int numcols;
    unsigned int coldif =0;//sets a differential value default to zero,
    //which is used to make sure that when assigning values to quarters, index does 
    //not go out of bounds in cases where the numer of rows or columns is odd
    unsigned int rowdif = 0;
    if(m_rows%2!=0){
        numrows = (m_rows/2) + 1;//checks if odd and, takes the larger value
        rowdif = 1;// differential set to 1 
    }else{
        numrows = m_rows/2;
    }

    if(m_cols%2!=0){
        numcols = (m_cols/2) + 1;//checks if odd and, takes the larger value
        coldif = 1;//differential set to 1
    }else{
        numcols = m_cols/2;
    }

    Matrix ul(numrows,numcols,0);//initalizes 4 matrixes of the same size with numrows
    //and numcols
    Matrix ur(numrows,numcols,0);
    Matrix bl(numrows,numcols,0);
    Matrix br(numrows,numcols,0);

    for(int i = 0; i<numrows; i++){
        for(int j = 0; j<numcols; j++){//loops through indexes within upper left corner
            ul.set(i,j,data[i][j]);//takes values and simply copies because indexes are
            //of top left corner
            ur.set(i,j,data[i][j+numcols-coldif]);//adds the number of coluns to the 
            //column index, and subtracts the differential to access values to the right
            bl.set(i,j,data[i+numrows-rowdif][j]);//adds number of rows to row index and
            //subracts differential so that values below can be accessed
            br.set(i,j,data[i+numrows-rowdif][j+numcols-coldif]);//annds number of rows 
            //and columns to the respective index, so values to the right and below can
            // be accessed
        }
    }
    
    matrixlist[0] = ul;//assigns each matrix to a spot, in order, in matrix pointer list.
    matrixlist[1] = ur;
    matrixlist[2] = bl;
    matrixlist[3] = br;

    return matrixlist;
}

std::ostream& operator<< (std::ostream& out, const Matrix& m){
    out<<"\n"<<m.num_rows()<<" x "<<m.num_cols()<<" matrix:\n";
    out<<"[";//accesses sze of matrix
    
    for(unsigned int i = 0; i<m.num_rows();i++){
        for(unsigned int j = 0; j<m.num_cols(); j++){
            double val;
            m.get(i,j,val);//iterates through each value and assigns it to va//to print
            out<<" "<<val;
        }
        if(i!=m.num_rows()-1){
            out<<"\n ";
        }
    }
    out<<" ]"<<"\n";
    return out;
}

bool operator==(const Matrix& a, const Matrix& b){
    return a.isEqual(b);//calls isequal function
}

bool operator!=(const Matrix& a, const Matrix& b){
    return (!a.isEqual(b));//calss isequal function
}

Matrix& Matrix::operator=(const Matrix& other){
    if(*this!=other){//checks whether both are same object
        clear();
    }else{
        return *this;
    }
    if(other.m_rows==0 || other.m_cols==0) data=NULL;//empties array if eith dim is 0
    else{
        m_rows = other.m_rows;//copies rows and cols
        m_cols = other.m_cols;
        data = new double*[m_rows];

        for (int i=0; i<m_rows;i++){
            data[i] = new double[m_cols];
        }

        for (int i = 0; i<m_rows;i++){
            for(int j = 0; j<m_cols; j++){
                data[i][j]=other.data[i][j];//iterates through and copies other matrix
            }
        }
    }
    return *this;
}