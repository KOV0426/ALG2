#include<iostream>
#include<vector>

using std::vector;

double evaluatePolynomial(const vector<double>& coeff, double x) {
	double res = 0;
	double xPower = 1;
	for (int k = 0; k < coeff.size(); k++) {
		res += coeff[k] * xPower;
		xPower *= x;
	}

	return res;
}

double Horner(const vector<double>& coeff, double x) {
	double res = coeff.back();
	for (int k = coeff.size() - 2; k >= 0; k--) {
		res = res * x + coeff[k];
	}
	return res;
}

void test_polynomials() {
	vector<double> c = { 1, 1, 1 };
	std::cout << Horner(c, 1) << " " << evaluatePolynomial(c, 1) << "\n";
}

vector<vector<int>> combinations(int n, int k) { // n - pocet prvku, k - pocet prvku v kombinaci
	vector<vector<int>> res;
	if (k < 0 or k > n) {
		return res;
	}
	vector<int> currentComb;
	currentComb.reserve(k);
	for (int i = 0; i < k; i++) {
		currentComb.push_back(i);
	}
	
	while (true) {
		res.push_back(currentComb);

		int i = k - 1;
		while (i >= 0 and currentComb[i] == n - k + i) {
			i--;
		}
		if (i < 0) {
			break;
		}

		currentComb[i] += 1;
		for (size_t j = i + 1; j < currentComb.size(); j++) {
			currentComb[j] = currentComb[j - 1] + 1;
		}
	}
	return res;
}

void printVec(const vector<int>& data) {
	for (const int item : data) {
		std::cout << item << " ";
	}
	std::cout << "\n";
}

int main() {
	test_polynomials();

	auto res = combinations(6, 3);
	for (const auto& line : res) {
		printVec(line);
	}
	return 0;
}