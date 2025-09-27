#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

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

void binarySearchFile(string datafile, string targetsfile) {
	vector<int> data = readIntsFromFile(datafile);
	sort(data.begin(), data.end());
	vector<int> targets = readIntsFromFile(targetsfile);
    for (const auto& target : targets) {
		if (target < data.front() || target > data.back()) {
			cout << target << ": F\n";
			continue;
		}
        else {
			size_t left = 0;
			size_t right = data.size() - 1;
			bool found = false;
			while (left <= right) {
				size_t mid = left + (right - left) / 2;
				if (data[mid] == target) {
					cout << target << ": T\n";
                    found = true;
					break;
				}
				else if (data[mid] < target) {
					left = mid + 1;
				}
				else {
					right = mid - 1;
				}
			}
            if (!found) {
                cout << target << ": F\n";
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Not enough arguments\n";
        return 1;
    }

    string data_file = argv[1];
    string numbers_file = argv[2];

    binarySearchFile(data_file, numbers_file);

    return 0;
}