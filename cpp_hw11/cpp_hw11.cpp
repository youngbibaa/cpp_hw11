#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

    void freeMemory() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    ~Matrix() {
        freeMemory();
    }

    void fillFromInput() {
        cout << "Введите элементы матрицы:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

    void fillRandom(T minVal, T maxVal) {
        srand(time(nullptr));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = minVal + static_cast<T>(rand()) / (RAND_MAX / (maxVal - minVal));
            }
        }
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << setw(8) << data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    T maxElement() const {
        T maxVal = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maxVal = max(maxVal, data[i][j]);
            }
        }
        return maxVal;
    }

    T minElement() const {
        T minVal = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                minVal = min(minVal, data[i][j]);
            }
        }
        return minVal;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(T scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j] / scalar;
            }
        }
        return result;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            freeMemory();
            rows = other.rows;
            cols = other.cols;
            data = new T * [rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new T[cols];
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            freeMemory();
            rows = other.rows;
            cols = other.cols;
            data = other.data;
            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }
};

int main() {
    int rows = 2, cols = 2;
    Matrix<int> mat1(rows, cols);
    Matrix<int> mat2(rows, cols);

    mat1.fillFromInput();
    mat2.fillRandom(1, 10);

    cout << "Матрица 1:\n";
    mat1.display();
    cout << "Матрица 2:\n";
    mat2.display();

    Matrix<int> sum = mat1 + mat2;
    cout << "Сумма матриц:\n";
    sum.display();

    Matrix<int> diff = mat1 - mat2;
    cout << "Разность матриц:\n";
    diff.display();

    Matrix<int> product = mat1 * mat2;
    cout << "Произведение матриц:\n";
    product.display();

    int scalar = 2;
    Matrix<int> divided = mat1 / scalar;
    cout << "Матрица после деления на скаляр " << scalar << ":\n";
    divided.display();

    cout << "Максимальный элемент матрицы 1: " << mat1.maxElement() << "\n";
    cout << "Минимальный элемент матрицы 1: " << mat1.minElement() << "\n";

    return 0;
}
