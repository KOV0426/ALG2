#include <iostream>
#include <vector>
#include<cmath>

using std::vector, std::cout;

using ScalarType = double;
//using Matrix = vector<vector<ScalarType>>;

class Matrix {
private:
	vector<vector<ScalarType>> data;

public:
	Matrix(){};
	Matrix(const vector<vector<ScalarType>>& input) : data(input) {};

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
				cout << item << " ";
			}
			cout << "\n";
		}
	}
};

vector<ScalarType> solveAxb(Matrix A, vector<ScalarType> b) {
	for (size_t i = 0; i < A.size(); i++) {
		size_t pivotIndex = i;
		ScalarType pivot = std::abs(A(i, i));

		for (size_t k = i + 1; k < A.size(); k++) {
			if (std::abs(A(k, i)) > pivot) {
				pivotIndex = k;
				pivot = A(k, i);
			}
		}

		if (pivotIndex != i) {
			std::swap(A.accessRow(i), A.accessRow(pivotIndex));
			std::swap(b[i], b[pivotIndex]);
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
		cout << item << " ";
	}
	cout << "\n";
}

int main() {
	vector<vector<ScalarType>> data = { {2, 1} ,{1, 2} };
	Matrix mat(data);
	vector<ScalarType> b = { 1, 1 };

	vector<ScalarType> x = solveAxb(mat, b);
	printVector(x);

	mat.print();
	return 0;
}