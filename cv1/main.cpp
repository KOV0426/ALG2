#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>
#include<queue>
#include<stack>

using std::cout, std::vector;

long long int fibonacciRec(const int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return fibonacciRec(n - 2) + fibonacciRec(n - 1);
}

class Fibonacci{
private:
	vector<int> cache;

	long long int recWithCache(const int n) {
		if (n < cache.size()) {
			return cache.at(n);
		}
		long long int newVal = recWithCache(n - 2) + recWithCache(n - 1);
		cache.push_back(newVal);
		return newVal;
	}

public:
	Fibonacci() {
		cache.push_back(0);
		cache.push_back(1);
	}

	long long int compute(const int n) {
		return recWithCache(n);
	}
};

void printVec(const vector<int>& vec) {
	for (const auto& item : vec) {
		cout << item << " ";
	}
	cout << "\n";
}

int findModus(const vector<int>& vec) {
	int modus = 0;
	int freq = 0;
	int i = 0;
	int runLength;
	int runVal;

	while (i < vec.size()) {
		runLength = 1;
		runVal = vec.at(i);
		while (i + runLength < vec.size() && vec.at(i + runLength) == runVal) {
			runLength += 1;
		}
		i += runLength;
		if (freq < runLength) {
			modus = runVal;
			freq = runLength;
		}
	}
	return modus;
}

int modusByDict(const vector<int>& vec) {
	std::map<int, int> dict;
	for (const int item : vec) {
		dict[item] += 1;
	}
	int modus = 0;
	int modus_freq = 0;
	for (const auto& [number, freq] : dict) {
		if (freq > modus_freq) {
			modus = number;
			modus_freq = freq;
		}
	}
	return modus;
}



int main() {
	vector<int> data = { 1, 1, 1, 2, 3, 4, 5, 1, 2, 15, 15, 15, 15, 15 };

	int modus = modusByDict(data);
	cout << modus;
	cout << "\n";
	std::sort(data.begin(), data.end());

	int modus2 = findModus(data);

	cout << modus2;
	cout << "\nhello\n";
}