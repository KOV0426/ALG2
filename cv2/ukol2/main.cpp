#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Z2 {
private:
    int value;

public:
    Z2(int v = 0) : value((v % 2 + 2) % 2) {}

    Z2 operator+(const Z2& other) const { return Z2(value + other.value); }
    Z2 operator-(const Z2& other) const { return Z2(value - other.value); }
    Z2 operator*(const Z2& other) const { return Z2(value * other.value); }
    Z2 operator/(const Z2& other) const {
        if (other.value == 0) {
            throw runtime_error("Division by zero in Z2.");
        }
        return Z2(value);
    }

    Z2& operator+=(const Z2& other) { value = (value + other.value) % 2; return *this; }
    Z2& operator-=(const Z2& other) { value = (value - other.value + 2) % 2; return *this; }
    Z2& operator*=(const Z2& other) { value = (value * other.value) % 2; return *this; }

    bool operator==(const Z2& other) const { return value == other.value; }
    bool operator!=(const Z2& other) const { return value != other.value; }
    bool operator>(const Z2& other) const { return value > other.value; }

    int getValue() const {
        return value;
    }
};

using ScalarType = Z2;

class Matrix {
private:
    size_t rows;
    size_t cols;
    vector<vector<ScalarType>> data;

public:
    Matrix() : rows(0), cols(0) {};
    Matrix(const vector<vector<ScalarType>>& input) : data(input) {
        if (!input.empty()) {
            rows = input.size();
            cols = input[0].size();
        }
        else {
            rows = 0;
            cols = 0;
        }
    };

    Matrix(size_t n, const ScalarType& initial_value)
        : rows(n), cols(n), data(n, vector<ScalarType>(n, initial_value)) {
    }

    ScalarType operator()(size_t i, size_t j) const {
        return data.at(i).at(j);
    }

    ScalarType& operator()(size_t i, size_t j) {
        return data[i][j];
    }

    vector<ScalarType>& accessRow(size_t i) {
        return data[i];
    }

    size_t size() const {
        return data.size();
    }

    void print() const {
        for (const auto& row : data) {
            for (const auto& item : row) {
                cout << item.getValue() << " ";
            }
            cout << "\n";
        }
    }
};

Matrix build_A(int n) {
    int size = n * n;
    Matrix A(size, Z2(0));

    vector<pair<int, int>> directions = {
        { 0,  0},
        {-1,  0},
        { 1,  0},
        { 0, -1},
        { 0,  1}
    };

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            int button_index = x + n * y;

            for (const auto& dir : directions) {
                int dx = dir.first;
                int dy = dir.second;

                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    int affected_index = nx + n * ny;
                    A(affected_index, button_index) = Z2(1);
                }
            }
        }
    }
    return A;
}

vector<ScalarType> solveAxb(Matrix A, vector<ScalarType> b) {
    for (size_t i = 0; i < A.size(); i++) {
        size_t pivotIndex = i;
        ScalarType pivot = A(i, i);

        for (size_t k = i + 1; k < A.size(); k++) {
            if (A(k, i) > pivot) {
                pivotIndex = k;
                pivot = A(k, i);
                break;
            }
        }

        if (pivotIndex != i) {
            swap(A.accessRow(i), A.accessRow(pivotIndex));
            swap(b[i], b[pivotIndex]);
        }

        for (size_t j = i + 1; j < A.size(); j++) {
            ScalarType temp = A(j, i) / A(i, i);
            for (size_t k = i; k < A.size(); k++) {
                A(j, k) = A(j, k) - temp * A(i, k);
            }
            b[j] = b[j] - temp * b[i];
        }
    }

    for (int i = A.size() - 1; i >= 0; i--) {
        ScalarType suma = 0;
        for (size_t j = i + 1; j < A.size(); j++) {
            suma -= A(i, j) * b[j];
        }
        b[i] = (b[i] + suma) / A(i, i);
    }

    return b;
}

void printVector(const vector<ScalarType>& vec) {
    for (const auto item : vec) {
        cout << item.getValue() << " ";
    }
    cout << "\n";
}

int main(int argc, char* argv[1]) {
    const int n = stoi(argv[1]);
    if (argc != n * n + 2) {
        cerr << "Invalid number of arguments\n";
        return -1;
    }
    
    vector<ScalarType> rhs;
    for (int i = 0; i < n * n; i++) {
        rhs.push_back(stoi(argv[i + 2]));
    }
    
	Matrix A = build_A(n);

	rhs = solveAxb(A, vector<ScalarType>(rhs.begin(), rhs.end()));
    printVector(rhs);
    
    return 0;
}