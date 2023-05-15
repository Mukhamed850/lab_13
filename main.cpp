#include <iostream>
#include <fstream>

template <typename T>
class Matrix {
private:
    int row, column;
    T** values;
public:
    Matrix() : row(0), column(0), values(nullptr) {}
    Matrix(int rows_t, int cols_t, T** data2) {
        row = rows_t;
        column = cols_t;
        values = new T*[row];
        for (int i = 0; i < row; ++i) {
            values[i] = new T[column];
            for (int j = 0; j < column; ++j) {
                values[i][j] = data2[i][j];
            }
        }
    }
    Matrix(const Matrix& other)  {
        row = other.row;
        column = other.column;
        values = new T*[row];
        for (int i = 0; i < row; ++i) {
            values[i] = new T[column];
            for (int j = 0; j < column; ++j) {
                values[i][j] = other.values[i][j];
            }
        }
    }
    ~Matrix() {
        if (row > 0){
            for (int i = 0; i < row; ++i) {
                delete[] values[i];
            }
            delete[] values;
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (&other == this) {
            return *this;
        }
        if (row > 0){
            for (int i = 0; i < row; ++i) {
                delete[] values[i];
            }
            delete[] values;
        }
        delete[] values;
        row = other.row;
        column = other.column;
        values = new T*[row];
        for (int i = 0; i < row; ++i) {
            values[i] = new T[column];
            for (int j = 0; j < column; ++j) {
                values[i][j] = other.values[i][j];
            }
        }
        return *this;
    }
    T* operator[](int row) {
        return values[row];
    }
    Matrix operator*(const Matrix& other) const {
        if (column != other.row) {
            std::cout << "Matrices have incompatible dimensions" << std::endl;
        }
        T** temp_ar;
        temp_ar = new T*[row];
        for (int i = 0; i < row; ++i){
            temp_ar[i] = new T[other.column];
            for (int j = 0; j < other.column; ++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(row, other.column, temp_ar);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < other.column; ++j) {
                T sum = T();
                for (int k = 0; k < column; ++k) {
                    sum += values[i][k] * other.values[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
        for (int i = 0; i < 2;++i) { delete[] temp_ar[i]; }
        delete[] temp_ar;
    }
    Matrix operator+(const Matrix& other) const {
        if (column != other.column || row != other.column) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        T** temp_ar;
        temp_ar = new T*[row];
        for (int i = 0; i < row; ++i){
            temp_ar[i] = new T[column];
            for (int j = 0; j < column; ++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(row, column, temp_ar);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j){
                result[i][j] = values[i][j] + other.Getdata()[i][j];
            }
        }
        return result;
        for (int i = 0; i < 2;++i) { delete[] temp_ar[i]; }
        delete[] temp_ar;
    }
    Matrix operator-(const Matrix& other) const {
        if (column != other.column || row != other.column) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        T** temp_ar;
        temp_ar = new T*[row];
        for (int i = 0; i < row; ++i){
            temp_ar[i] = new T[column];
            for (int j = 0; j < column; ++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(row, column, temp_ar);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j){
                result[i][j] = values[i][j] - other.Getdata()[i][j];
            }
        }
        return result;
        for (int i = 0; i < 2;++i){delete[] temp_ar[i];}
        delete[] temp_ar;
    }
    Matrix operator*(T scalar) const {
        T** temp_ar;
        temp_ar = new T*[row];
        for (int i = 0; i < row; ++i){
            temp_ar[i] = new T[column];
            for (int j = 0; j < column; ++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(row, column, temp_ar);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                result[i][j] = values[i][j] * scalar;
            }
        }
        return result;
        for (int i = 0; i < 2;++i){delete[] temp_ar[i];}
        delete[] temp_ar;
    }

    friend Matrix operator*(const T& scalar, const Matrix& matrix) {return matrix * scalar;}
    int Getrows() const{
        return row;
    }
    int Getcols() const{
        return column;
    }
    T** Getdata() const{return values;}
    void writeToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << row << " " << column << std::endl;
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    file << values[i][j] << " ";
                }
                file << std::endl;
            }
            file.close();
        } else {
            throw std::runtime_error("Failed to open file");
        }
    }
    static Matrix ZeroCr(int rows,int cols){
        int r = rows;
        int c = cols;
        T** temp_ar_l;
        temp_ar_l = new T*[r];
        for (int i = 0; i < r;++i){
            temp_ar_l[i] = new T[c];
            for (int j = 0; j < c;++j){
                temp_ar_l[i][j] = 0;
            }
        }
        Matrix result_l(r, c,temp_ar_l);
        return result_l;
        for (int i = 0; i < 2;++i){delete[] temp_ar_l[i];}
        delete[] temp_ar_l;
    }
    static Matrix UnitCr(int rows,int cols){
        int r = rows;
        int c = cols;
        T** temp_ar_l;
        temp_ar_l = new T*[r];
        for (int i = 0; i < r;++i){
            temp_ar_l[i] = new T[c];
            for (int j = 0; j < c;++j){
                if (i==j) {temp_ar_l[i][j] = 1;}
                else {temp_ar_l[i][j] = 0;}
            }
        }
        Matrix result_l(r, c,temp_ar_l);
        return result_l;
        for (int i = 0; i < 2;++i){delete[] temp_ar_l[i];}
        delete[] temp_ar_l;
    }
    bool operator==(const Matrix& other) {
        int c = 0;
        if ((row != other.row) || (column != other.column) ){ c+=1;}
        else {
            for (int i = 0; i < row; ++i ) {
                for (int j = 0; j < column; ++j){
                    if (values[i][j] != other.values[i][j]){
                        c+=1;
                    }
                }
            }
        }
        if (c==0) {return true;}
        return false;
    }
    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            int newRows, newCols;
            file >> newRows >> newCols;
            Matrix<T> newMatrix(newRows, newCols);
            file >> newMatrix;
            *this = newMatrix;
            file.close();
        } else {
            throw std::runtime_error("Failed to open file");
        }
    }
    friend std::ostream& operator<<(std::ostream &os,const Matrix& matr){
        for (int i = 0; i < matr.Getrows();++i){
            for (int j = 0; j < matr.Getcols();++j){
                os << matr.Getdata()[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};
int main() {

    int **data2;
    int **data3;

    int k = 2;
    int l = 4;
    data2 = new int*[2];
    for (int i = 0; i < 2; ++i){
        data2[i] = new int[2];
        for (int j = 0; j < 2; ++j){
            data2[i][j] = k;
            k++;
        }
    }
    data3 = new int*[2];
    for (int i = 0; i < 2; ++i){
        data3[i] = new int[2];
        for (int j = 0; j < 2; ++j){
            data3[i][j] = l;
            l++;
        }
    }


    Matrix<int> matr1(2, 2, data2);
    Matrix<int> matr2(2, 2, data3);
    std::cout << "matr1 = " << "\n" << matr1 << std::endl;// '<<' demonstration
    std::cout << "matr2 = " << "\n" << matr2 << std::endl;// '<<' demonstration
    Matrix<int> e = matr1;
    std::cout <<"e = " << "\n" <<  e << std::endl;    // ' = ' demonstration
    std::cout << "matr1 == matr2 (0 - no, 1 - yes) -> " << (matr1 == matr2) << std::endl;
    std::cout << "matr1 == e (0 - no, 1 - yes) -> " << (matr1 == e) << std::endl; // '==' demonstration
    std::cout << "matr2*matr1 = " << "\n" << matr2 * matr1 << std::endl;// '*' demonstration
    std::cout << "matr2+matr1 = " << "\n" << matr2 + matr1 << std::endl;// '+' demonstration
    std::cout << "matr2-matr1 = " << "\n" << matr2 - matr1 << std::endl; // '-' demonstration
    std::cout << "matr2 * 5 =  " << "\n" << matr2 * 5 << std::endl;   // '* scalar' demonstration
    std::cout <<"Zero 3x3 matrix = \n" <<  Matrix<int>::ZeroCr(3,3) << std::endl; // ' zero matrix ' demonstration
    std::cout <<"The unit 3x3 matrix = \n" <<  Matrix<int>::UnitCr(3,3) << std::endl; // ' unit matrix ' demonstration
}