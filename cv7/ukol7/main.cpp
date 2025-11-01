#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

using std::vector, std::string, std::ifstream, std::stringstream, std::cerr, std::endl;

vector<int> distributionCountingSort(const vector<int>& data, int place) {
	if (data.size() < 2) {
		return data;
	}
	
	const int length = 10;
	vector<int> counts(length,0);
	
	for(const int item : data){
	    int digit = (item/place) % 10;
	    counts[digit] += 1;
	}
	
	for(size_t i = 1; i < counts.size(); i++){
	    counts[i] += counts.at(i - 1);
	}
	
	vector<int> output(data.size());
	
	for(int i = data.size() - 1; i >= 0; i--){
	    int digitIndex = (data.at(i) / place) % 10;
	    output[counts[digitIndex] - 1] = data.at(i);
	    counts[digitIndex] -= 1;
	}
	
	return output;
}

void print(vector<int>& data){
    for (size_t i = 0; i < data.size(); i++) {
		std::cout << data.at(i) << " ";
    }
    std::cout << "\n";
}

void radixSort(vector<int>& data){
    int max = data[0];
    for (int num : data){
        if (num > max){
            max = num;
        }
    }
    
    for(int place = 1; max/place > 0; place *= 10){
        data = distributionCountingSort(data, place);
    }
    
    print(data);
}

vector<int> readIntsFromFile(const string& filename) {
    ifstream file(filename);
    vector<int> numbersVec;
    
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return numbersVec;
    }

    string line;

    if (getline(file, line)) {
        stringstream lineAsStream(line);
        int num;
        while (lineAsStream >> num) {
            numbersVec.push_back(num);
        }
    }

    file.close();
    return numbersVec;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Not enough arguments\n";
        return 1;
    }
    
    auto data = readIntsFromFile(argv[1]);
	radixSort(data);
	return 0;
}