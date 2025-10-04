#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
// AVL Tree

struct Node {
	Node* left;
	Node* right;
	int key;
	int height;

	Node(int value) : left(nullptr), right(nullptr), key(value), height(0) {}
};

class BinaryTree {
private:
	Node* root;

	int height(Node* node) {
		if (node == nullptr) return -1;
		return node->height;
	}
	
	void updateHeight(Node* node) {
		if (node == nullptr) return;
		node->height = 1 + std::max(height(node->left), height(node->right));
	}

	int balanceFactor(Node* node) {
		if (node == nullptr) return 0;
		return height(node->left) - height(node->right);
	}

	Node* rotateRight(Node* r) {
		Node* c = r->left;
		Node* t2 = c->right;
		
		c->right = r;
		r->left = t2;

		updateHeight(r);
		updateHeight(c);
		return c;
	}

	Node* rotateLeft(Node* r) {
		Node* c = r->right;
		Node* t2 = c->left;

		c->left = r;
		r->right = t2;

		updateHeight(r);
		updateHeight(c);
		return c;
	}

	Node* balance(Node* node) {
		updateHeight(node);
		int bf = balanceFactor(node);
		if (bf > 1) {
			if (balanceFactor(node->left) < 0) {
				node->left = rotateLeft(node->left);
			}
			return rotateRight(node);
		}
		if (bf < -1) {
			if (balanceFactor(node->right) > 0) {
				node->right = rotateRight(node->right);
			}
			return rotateLeft(node);
		}
		return node;
	}

	void clear(Node* node) {
		if (node == nullptr) return;
		clear(node->left);
		clear(node->right);
		delete node;
	}

	Node* insert(Node* node, const int key) {
		if (node == nullptr) {
			return new Node(key);
		}
		if (key < node->key) {
			node->left = insert(node->left, key);
		}
		else if (key > node->key) {
			node->right = insert(node->right, key);
		}
		else {
			return node;
		}
		return balance(node);
	}

	Node* findMinKeyNode(Node* node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	Node* erase(Node* node, const int key) {
		if (node == nullptr) {
			return node;
		}
		if (key < node->key) {
			node->left = erase(node->left, key);
		}
		else if (key > node->key) {
			node->right = erase(node->right, key);
		}
		else {
			if (node->left == nullptr or node->right == nullptr) {
				Node* temp = node->left ? node->left : node->right;
				delete node;
				return temp;
			}
			Node* successor = findMinKeyNode(node->right);
			node->key = successor->key;
			node->right = erase(node->right, successor->key);
		}
		return balance(node);
	}

	bool containsKey(Node* node, const int key) const {
		if (node == nullptr) {
			return false;
		}
		if (key < node->key) {
			return containsKey(node->left, key);
		}
		else if (key > node->key) {
			return containsKey(node->right, key);
		}
		else {
			return true;
		}
	}

	void inOrderPrint(const Node* node) const {
		if (node == nullptr) return;
		inOrderPrint(node->left);
		std::cout << node->key << " ";
		inOrderPrint(node->right);
	}
	
	void preOrderPrint(const Node* node) const {
		if (node == nullptr) return;
		std::cout << node->key << " ";
		preOrderPrint(node->left);
		preOrderPrint(node->right);
	}
	
	void postOrderPrint(const Node* node) const {
		if (node == nullptr) return;
		postOrderPrint(node->left);
		postOrderPrint(node->right);
		std::cout << node->key << " ";
	}

public:
	BinaryTree() : root(nullptr) {}
	~BinaryTree() {
		clear(root);
	}

	void insert(const int key) {
		root = insert(root, key);
	}

	bool containsKey(const int key) const {
		return containsKey(root, key);
	}

	void erase(const int key) {
		root = erase(root, key);
	}

	void inOrderPrint() const {
		inOrderPrint(root);
		std::cout << "\n";
	}
	
	void preOrderPrint() const {
		preOrderPrint(root);
		std::cout << "\n";
	}
	
	void postOrderPrint() const {
		postOrderPrint(root);
		std::cout << "\n";
	}

	void printByLevels() const {
		if (root == nullptr) {
			std::cout << "Tree is empty\n";
		}
		std::queue<Node*> Q;
		Q.push(root);

		while (not Q.empty()) {
			size_t count = Q.size();
			bool foundNewNodes = false;

			for (size_t i = 0; i < count; i++) {
				Node* currentNode = Q.front();
				Q.pop();

				if (currentNode == nullptr) {
					std::cout << "# ";
				}
				else {
					std::cout << currentNode->key << " ";
				}
				if (currentNode != nullptr) {
					Q.push(currentNode->left);
					Q.push(currentNode->right);
					if (currentNode->left or currentNode->right) {
						foundNewNodes = true;
					}
				}
			}
			std::cout << "\n";
			if (not foundNewNodes) {
				break;
			}
		}
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
    
    std::string file1 = argv[1];
    std::string file2 = argv[2];
	std::vector<int> addVec = readIntegersFromFile(file1);
	std::vector<int> deleteVec = readIntegersFromFile(file2);
	
	BinaryTree tree;
	
	for (const int item : addVec) {
		tree.insert(item);
	}
	
	for (const int item : deleteVec) {
		tree.erase(item);
	}
	
	tree.postOrderPrint();
	tree.preOrderPrint();
	tree.inOrderPrint();
	
	return 0;
}