#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
vector<vector<int>> readSimplicesFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> simplices;
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return simplices;
    }
    string line;
    while (getline(file, line)) {
        stringstream lineAsStream(line);
        int num;
        vector<int> simplex;
        while (lineAsStream >> num) {
            simplex.push_back(num);
        }
        if (!simplex.empty()) simplices.push_back(simplex);
    }
    file.close();
    return simplices;
}
vector<vector<int>> combinations(int n, int k) {
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
void findBoundary(const string& filename) {
    vector<vector<int>> inputSimplices = readSimplicesFromFile(filename);
    if (inputSimplices.empty()) {
        cerr << "No simplices found in file.\n";
        return;
    }
    vector<vector<int>> simplices;
    for (auto s : inputSimplices) {
        sort(s.begin(), s.end());
        simplices.push_back(s);
        int n = (int)s.size();
        for (int k = 1; k < n; ++k) {
            auto combs = combinations(n, k);
            for (auto &idxs : combs) {
                vector<int> subs;
                for (int i : idxs) {
                    subs.push_back(s[i]);
                }
                simplices.push_back(subs);
            }
        }
    }
    sort(simplices.begin(), simplices.end());
    simplices.erase(unique(simplices.begin(), simplices.end()), simplices.end());
    
    if (simplices.empty()) {
        cout << "No simplices provided.\n";
        return;
    }
    int maxDim = 0;
    for (const auto &s : simplices) {
        int dim = (int)s.size() - 1;
        maxDim = max(maxDim, dim);
    }
    vector<int> countByDim(maxDim + 1, 0);
    for (const auto &s : simplices) {
        int dim = (int)s.size() - 1;
        countByDim[dim]++;
    }
    vector<vector<int>> allFaces;
    for (const auto &s : simplices) {
        int n = (int)s.size();
        if (n <= 1) continue;
        auto combs = combinations(n, n - 1);
        for (auto &idxs : combs) {
            vector<int> face;
            for (int i : idxs) face.push_back(s[i]);
            allFaces.push_back(face);
        }
    }
    sort(allFaces.begin(), allFaces.end());
    vector<vector<int>> boundaryFaces;
    for (size_t i = 0; i < allFaces.size(); ) {
        size_t j = i + 1;
        while (j < allFaces.size() && allFaces[j] == allFaces[i]) j++;
        if (j - i == 1) boundaryFaces.push_back(allFaces[i]);
        i = j;
    }
    long long chi = 0;
    for (size_t d = 0; d < countByDim.size(); ++d) {
        if (d % 2 == 0) chi += countByDim[d];
        else chi -= countByDim[d];
    }
    vector<string> labels = {"Verticies", "Edges", "Triangles", "Tetrahedrons"};
    for (size_t d = 0; d < countByDim.size(); ++d) {
        string label;
        if (d < labels.size()) label = labels[d];
        else label = "Dim " + to_string(d);
        cout << label << ": " << countByDim[d] << '\n';
    }
    cout << "chi: " << chi << "\n\n";
    if (boundaryFaces.empty()) cout << "Boundary:\nis empty\n";
    else {
        for (const auto &f : boundaryFaces) {
            for (size_t i = 0; i < f.size(); ++i) {
                if (i) cout << ' ';
                cout << f[i];
            }
            cout << '\n';
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Not enough arguments\n";
        return 1;
    }
    findBoundary(argv[1]);
    return 0;
}