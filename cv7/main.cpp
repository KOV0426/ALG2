#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using std::vector, std::string;

vector<int> distributionCountingSort(const vector<int>& data) {
	if (data.size() < 2) {
		return data;
	}
	int u, l;
	u = data[0];
	l = data[0];
	for (const int item : data) {
		u = std::max(item, u);
		l = std::min(item, l);
	}

	int length = u - l + 1;
	vector<int> counts(length, 0);

	for (const int item : data) {
		counts[item - l] += 1;
	}

	for (size_t i = 1; i < counts.size(); i++) {
		counts[i] += counts.at(i - 1);
	}

	vector<int> output(data.size());
	for (int i = data.size() - 1; i >= 0; i--) {
		int index = data.at(i) - l;
		output[counts[index] - 1] = data.at(i);
		counts[index] -= 1;
	}

	return output;
}

void test() {
	vector<int> data = { 1, 1, 1, 2, 2, 2, 4, 4, 4, 4, 3, 3, 3, 11, 11, 10, 10, 10 };
	auto dataCopy = data;
	std::sort(dataCopy.begin(), dataCopy.end());
	data = distributionCountingSort(data);
	for (size_t i = 0; i < data.size(); i++) {
		std::cout << data.at(i) << " ";
		if (data.at(i) != dataCopy.at(i)) {
			std::cout << "je to zle\n";
			return;
		}
	}
	std::cout << ":)\n";
	return;
}

int horspoolSearch(const string& text, const string& pattern) {
	int m = pattern.size();
	int i = m - 1;
	
	const int TABLESIZE = 255;
	std::unordered_map<char, int> shifts;
	for (unsigned char c = 0; c < TABLESIZE; c++) {
		shifts[c] = m;
	}

	for (int i = 0; i < m - 1; i++) {
		shifts[pattern[i]] = m - 1 - i;
	}

	while (i < text.size()) {
		int k = 0;
		while (k <= m - 1 && pattern[m - 1 - k] == text[i - k]) {
			k++;
		}
		if (k == m) {
			return i - m + 1;
		}
		else {
			i += shifts[text[i]];
		}
	}
	return -1;
}

void test2() {
	string test = "Pec nam spadla";
	string pattern = "nam";
	int position = horspoolSearch(test, pattern);
	std::cout << position << "\n";
	std::cout << test.size() << "\n";
	return;
}

int main() {
	//test();
	test2();
	return 0;
}