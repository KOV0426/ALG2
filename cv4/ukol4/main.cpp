#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::vector;

class myHeap {
private:
	vector<int> data;
	size_t n;

	vector<size_t> children(const size_t index) {
		vector<size_t> children_index;
		for(size_t i = 1; i <= n; ++i){
		    children_index.push_back(n * index + i);
		}
		return children_index;
	}
	
	size_t parentIndex(const size_t index) {
		return (index - 1) / n;
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
		for (int i = data.size() / n; i >= 0; i--) {
			heapify(i);
		}
	}

public:
	myHeap() {};

	myHeap(vector<int> input, size_t n) {
		data = input;
		this->n = n;
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
};

std::vector<int> readIntegersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> numbersVec;

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return numbersVec;
    }

    std::string line;


    if (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        int num;
        while (lineAsStream >> num) {
            numbersVec.push_back(num);
        }
    }

    file.close();
    return numbersVec;
}

int main(int argc, char* argv[]) {
    if( argc != 3 ){
        std::cerr << "Not enough arguments\n";
        return 1;
    }
    
	size_t n = std::stoul(argv[1]);
	std::string filename = argv[2];
	
	vector<int> data = readIntegersFromFile(filename);

	myHeap heap(data, n);
	heap.print();
	
	heap.getMax();
	heap.print();

	heap.insert(42);
	heap.print();
	
	heap.insert(-5);
	heap.print();
	
	heap.getMax();
	heap.print();

	return 0;
}