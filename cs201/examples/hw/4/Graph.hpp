#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;
                    vertices[i].distance = 65535; // Instead using INFINITY, you can use a large int number to initialize your graph
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		// your implementation goes here
		// priority queue
		Vertex u, buffer;
		int currIndex;
		Vertex * queue = new Vertex[_V];
		int * index = new int[_V];
		int head = 0;
		int tail = 0;

		// initialize list of vertices for bfs
		for (int i = 0; i < _V; i++) {
			// mark vertices as white
			vertices[i].visited = false;
			vertices[i].finish = 0;

			// set distance to infinity
			vertices[i].distance = 65535;

			// set predecessor to nil
			vertices[i].previous = -1;
		}

		// set argument node to gray, distance 0, predecessor nil
		vertices[s].visited = true;
		vertices[s].distance = 0;
		vertices[s].previous = -1;

		// add s to queue
		queue[tail] = vertices[s];
		index[tail] = s;
		tail++;

		// perform bfs with priority queue
		while (head != tail) {
			// dequeue from pri queue
			u = queue[head];
			currIndex = index[head];
			head++;
			auto it = vertices[currIndex].adj.begin();

			for (int i = 0; i < degree(currIndex); i++) {
				// check if white
				if (vertices[*it].visited == false && vertices[*it].finish == 0) {
					// do bfs operations
					vertices[*it].visited = true;
					vertices[*it].distance = vertices[currIndex].distance + 1;
					vertices[*it].previous = currIndex;
					// enqueue
					queue[tail] = vertices[*it];
					index[tail] = *it;
					tail++;
				}
				it++;
			}
			vertices[currIndex].finish = 1;
		}

		delete[] queue;
		return;
	}

	void dfs() {
		// your implementation goes here
		Vertex u;
		int * time = new int;
		*time = 0;
		for (int i = 0; i < _V; i++) {
			// mark vertices as white
			vertices[i].visited = false;
			vertices[i].finish = -1;
			
			// mark predecessor as nil
			vertices[i].previous = -1;
		}

		for (int i = 0; i < _V; i++) {
			u = vertices[i];
			if (u.visited == false && u.finish == -1) {
				u.finish = *time;
				dfs_visit(i, time);
			}
		}

		int order = 1;
		int count = 0;
		while (count < _V) {
			for (int i = 0; i < _V; i++) {
				if (vertices[i].distance == order) {
					std::cout << i << std::endl;
					count++;
				}
			}
			order++;
		}

		delete time;
		return;
	}

	void dfs_visit(int u, int * time) {
		// your implementation goes here
		// node setup
		*time = *time + 1;
		auto it = vertices[u].adj.begin();

		// mark starting time
		vertices[u].distance = *time;

		// color node gray
		vertices[u].visited = true;

		for (int i = 0; i < degree(u); i++) {
			if (vertices[*it].visited == false) {
				vertices[*it].previous = u;
				dfs_visit(*it, time);
			}
			it++;
		}

		(*time)++;
		vertices[u].finish = *time;

	}

	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
};

#endif
