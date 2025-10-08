#include <iostream>
#include <vector>

using std::vector;

class myHeap {
private:
	vector<int> data;

	vector<size_t> children(const size_t index) {
		return { 2 * index + 1, 2 + 2 * index };
	}
	
	size_t parentIndex(const size_t index) {
		return (index - 1) / 2;
	}

	void heapify(const size_t index) {
		vector<size_t> c = children(index);
		size_t largest = index;

		for (const auto child : c) {
			if (not (child < data.size())) { break; }
			if (data[child] > data[largest]) {
				largest = child;
			}
		}
		if (largest != index) {
			std::swap(data[index], data[largest]);
			heapify(largest);
		}
	}

	void makeHeap() {
		for (int i = data.size() / 2; i >= 0; i--) {
			heapify(i);
		}
	}

public:
	myHeap() {};

	myHeap(vector<int> input) {
		data = input;
		makeHeap();
	}

	void insert(const int key) {
		data.push_back(key);
		if (data.size() == 1) {
			return;
		}
		size_t currentIndex = data.size() - 1;
		size_t parent = parentIndex(currentIndex);

		while (currentIndex != 0 and data[currentIndex] > data[parent]) {
			std::swap(data[currentIndex], data[parent]);
			currentIndex = parent;
			parent = parentIndex(currentIndex);
		}
	}

	int getMax() {
		if (data.empty()) {
			throw std::out_of_range("Getting items from empty heap");
		}

		int maximum = data[0];

		int last = data.back();
		data[0] = last;
		data.pop_back();

		if (data.size() > 1) {
			heapify(0);
		}

		return maximum;
	}

	void print() const {
		for (const auto item : data) {
			std::cout << item << " ";
		}
		std::cout << "\n";
	}

	bool empty() const {
		return data.empty();
	}

	static vector<int> heapSort(vector<int>& data) {
		myHeap heap(data);
		vector<int> res;

		while (not heap.empty()) {
			res.push_back(heap.getMax());
		}

		return res;
	}

};

int main() {
	int k = 10;
	vector<int> data = { -100, -200, 1, 2, 3, 4, 5, 6, 7, 8 };

	myHeap heap(data);
	heap.print();

	heap.insert(22);
	heap.print();
	heap.getMax();
	heap.print();

	auto sorted = myHeap::heapSort(data);

	for (const auto item : sorted) {
		std::cout << item << " ";
	}
	std::cout << "\n";

	return 0;
}