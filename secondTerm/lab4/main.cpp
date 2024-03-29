#include <iostream>

template<typename T, int N, int M>
class Matrix {
private:
    T _content[N][M];
public:
    Matrix()=default;

    void set(const Matrix<T, N, M>& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                _content[i][j] = other._content[i][j];
            }
        }
    }

    Matrix(const Matrix<T, N, M>& other) {
        this->set(other);
    }

    Matrix& operator=(const Matrix<T, N, M>& other) {
        this->set(other);
        return *this;
    }

    Matrix& operator+=(const Matrix<T, N, M>& other) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->_content[i][j] += other._content[i][j];
            }
        }
        return *this;
    }

    friend Matrix operator+(const Matrix<T, N, M>& matrix1, const Matrix<T, N, M>& matrix2) {
        Matrix<T, N, M> result = matrix1;
        result += matrix2;
        return result;
    }

    T& at(int i, int j) {
        return this->_content[i][j];
    }


    template<typename TT, int NN, int MM>
    friend Matrix<T, N, MM> operator*(const Matrix<T, N, M>& matrix1, Matrix<TT, NN, MM>& matrix2) {
        if (M == NN) {
            Matrix<T, N, MM> result;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < MM; ++j) {
                    result.at(i, j) = 0;
                    for (int k = 0; k < M; ++k) {
                        result.at(i, j) += matrix1._content[i][k] * matrix2.at(k, j);
                    }
                }
            }
            return result;
        } else {
            std::cout << "Error size of multiplied matrix\n";
        }
    }

    Matrix<T, N, M>& operator*=(const Matrix<T, M, M>& other) {
        Matrix<T, N, M> tmp = *this;
        *this = tmp * other;
        return *this;
    }

    Matrix& operator++() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->_content[i][j]++;
            }
        }
        return *this;
    }

    Matrix operator++(int) {
        Matrix<T, N, M> temp = *this;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ++this->_content[i][j];
            }
        }
        return temp;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& matrix) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0 ; j < M; ++j) {
                std::cout << matrix._content[i][j] << " ";
            }
            std::cout << "\n";
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0 ; j < M; ++j) {
                std::cin >> matrix._content[i][j];
            }
        }
        return in;
    }



    T determinant() {
        if (N == M) {
            if (N == 1) {
                return this->_content[0][0];
            }
            if constexpr (N > 1) {
                T result = 0;
                Matrix<T, N - 1, M - 1> minor;
                for (int i = 0; i < N; ++i) {
                    for (int j = 1; j < N; ++j) {
                        for (int k = 0; k < M; ++k) {
                            if (k < i) {
                                minor.at(j - 1, k) = this->_content[j][k];
                            }
                            if (k > i) {
                                minor.at(j - 1, k - 1) = this->_content[j][k];
                            }
                        }
                    }
                    result += this->_content[0][i] * minor.determinant();
                    return result;
                }
            }
        } else {
            std::cout << "Matrix is not square\n";
        }
    }

};



int main()
{
    Matrix<int, 3, 3> sample1;
    std::cin >> sample1;
    //Matrix<int, 3, 2> sample2;
    //std::cin >> sample2;
    //Matrix<int, 3, 2> sample3;
    //sample3 = (sample1 + sample1) * sample2;
    //std::cout << sample3;
    std::cout << sample1.determinant();
    return 0;
}
