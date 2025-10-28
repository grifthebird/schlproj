#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>
#include <vector>

#include "RBT.hpp"
#include "RBTNode.hpp"
#include "RBTPrint.hpp"

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
	typedef RBTNode<Key, Type>* iterator;
	iterator root;

	// Constructors
	// constant
	ST() {
		root = nullptr;
		nodeCount = 0;
	}; 

	// Destructor
	// linear in the size of the ST
	~ST(){
		deletepostorder(root);
	};

	// access or insert specifies element
	// inserts if the key is not present and returns a reference to
	// the value corresponding to that key
	// O(LogN), N size of ST
	Type& operator[](const Key& key) {
		iterator pos = RedBlackTree<Key, Type>::Search(key);
		if (pos == nullptr) {
			RedBlackTree<Key, Type>::Insert(key, 0);
			pos = RedBlackTree<Key, Type>::Search(key);
			nodeCount++;
		}
		return pos->value;
	}; 

	// insert a (key, value) pair, if the key already exists
	// set the new value to the existing key
	// O(LogN), N size of ST
	void insert(const Key& key, const Type& value) {
		iterator pos = RedBlackTree<Key, Type>::Search(key);
		if (pos == nullptr) {
			RedBlackTree<Key, Type>::Insert(key, value);
			nodeCount++;
		}
		else {
			pos->value = value;
		}
	};

	// remove element at the given position
	// amortized constant
	void remove(iterator position) {
		RedBlackTree<Key, Type>::Remove(position->key);
	};

    // remove element with keyvalue key and 
	// return number of elements removed (either 0 or 1)
	// O(logN), N size of ST
	std::size_t remove(const Key& key) {
		iterator pos = RedBlackTree<Key, Type>::Search(key);
		if (pos != nullptr) {
			remove(pos);
			nodeCount--;
			return 1;
		}
		else {
			return 0;
		}
	};  

	// removes all elements from the ST, after this size() returns 0
	// linear in the size of the ST
	void clear() {
		deletepostorder(root);
		RedBlackTree<Key, Type>::root = nullptr;
		nodeCount = 0;
	}; 

	// checks if ST has no elements; true is empty, false otherwise
	// constant
	bool empty() const {
		if (RedBlackTree<Key, Type>::root != nullptr && nodeCount != 0) {
			return false; 
		}
		else { return true; }
	}; 

	// returns number of elements in ST
	// constant
	std::size_t size() const {
		return nodeCount;
	}; 

	// returns number of elements that match keyvalue key
	// value returned is 0 or 1 since keys are unique
	// O(LogN), N size of ST
	std::size_t count(const Key& key) {
		iterator pos = RedBlackTree<Key, Type>::Search(key);
		if (pos == nullptr) { return 0; }
		else { return 1; }
	}; 

	// find an element with keyvalue key and return 
	// the iterator to the element found, nullptr if not found
	// O(LogN), N size of ST
	iterator find(const Key& key) {
		iterator pos = RedBlackTree<Key, Type>::Search(key);
		return pos;
	};

	// check if key exists in ST
	// O(LogN), N size of ST
	bool contains(const Key& key) {
		iterator pos = RedBlackTree<Key, Type>::Search(key);
		if (pos == nullptr) { return false; }
		else { return true; }
	};

	// return contents of ST as a vector of (key,value) pairs
	// O(N), N size of ST
	std::vector<std::pair<Key, Type> > toVector() {
		std::vector<std::pair<Key, Type> > output;
		postorderdec(RedBlackTree<Key, Type>::root, output);
		return output;
	};

	// print the symbol table as Red-Black Tree
	// O(N), N size of ST
	void displayTree() {
		std::cout << RBTPrint<Key,Type>::TreeToString(RedBlackTree<Key,Type>::root) << std::endl;
	};

	// print the symbol table in sorted order
	// O(N), N size of ST
	void display() {
		std::vector<std::pair<Key, Type> > input = toVector();
		std::sort(input.begin(), input.end(), comp);
		for (int i = 0; i < input.size(); i++) {
			std::cout << input.at(i).first << ": " << input.at(i).second << std::endl;
		}
	};

	// post-order traversal on ST to delete without memory leaks
	void deletepostorder(RBTNode<Key, Type>* rootnode) {
		if (rootnode != nullptr) {
			deletepostorder(rootnode->left);
			deletepostorder(rootnode->right);
			delete rootnode;
		}
	}

	void postorderdec(RBTNode<Key, Type>* rootnode, std::vector<std::pair<Key, Type> >& vec) {
		if (rootnode != nullptr) {
			postorderdec(rootnode->right, vec);
			std::pair<std::string, int> curr = {rootnode->key, rootnode->value};
			vec.push_back(curr);
			postorderdec(rootnode->left, vec);
		}
	}

	void print(RBTNode<Key, Type>* rootnode) {
		if (rootnode != nullptr) {
			print(rootnode->right);
			std::cout << rootnode->key << ": " << rootnode->value << std::endl;
			print(rootnode->left);
		}
	}

	bool static comp(std::pair<Key, Type> a, std::pair<Key, Type> b) {
		if (a.second == b.second) {
			return a.first < b.first;
		}
		return a.second > b.second;
	}

private:
	std::size_t nodeCount;

};

#endif

