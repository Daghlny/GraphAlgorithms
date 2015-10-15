
#ifdef __GRAPH__
#include "../base/Graph.hpp"
#include "../base/Adjacency.hpp"
#endif

#ifdef __GRAPH__WT__
#include"../baseWithoutTemplate/Graph.hpp"
#include"../baseWithoutTemplate/AdjaList.hpp"
#include"../baseWithoutTemplate/AdjaNode.hpp"
#endif

#include<iostream>
#include<fstream>
#include<deque>
#include<vector>

using namespace base;
typedef void (*visitFcn)(Graph::vertex_t);

void BFS(const Graph&, Graph::vertex_t , visitFcn);
void BFS(const Graph&);
void storeVertex(Graph::vertex_t v);
void printVertex(Graph::vertex_t v);

void
BFS(const Graph &g, Graph::vertex_t sour, visitFcn visit){
	typedef char flag_t;
	uint64_t index = 1;

	std::vector<flag_t> mark(g.vsize(), 0);
	std::deque<vertex_t> wait_q;

	wait_q.push_back(sour);

	while(wait_q.size() != 0){
		vertex_t cur = wait_q.front();
		wait_q.pop_front();

		if(mark[cur] == 0)
			visit(cur);
		mark[cur] = 1;
		AdjaList cur_list = g.getList(cur);
		AdjaList *node = cur_list.getHead();
		while(node != NULL){
			if(mark[node->vid] == 0){
				mark[node->vid] = 1;
				visit(node->vid);
				wait_q.push_back(node->vid);
			}
			node = node->next;

		}
	}
}

void
BFS(const Graph& g){
	BFS(g, 0, printVertex);
}

void
printVertex(Graph::vertex_t v){
	std::cout << v << std::endl;
}

void
storeVertex(Graph::vertex_t v){
	std::ofstream out_file;
	out_file.open("../graphData.txt", std::ofstream::out | std::ofstream::app);
	out_file << v << std::endl;
	out_file.close();
}


