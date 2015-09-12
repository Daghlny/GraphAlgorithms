#ifndef __BASE__NT__GRAPH__HPP__
#define __BASE__NT__GRAPH__HPP__

#include<vector>
#include<utility>
#include"AdjaList.hpp"

namespace base{

class Graph{
	public:
		typedef uint32_t vertex_t;
		typedef uint64_t edge_t;

		Graph(): aList(0), vertex_sum(0){}
		Graph(size_t vertex_num): aList(vertex_num), vertex_sum(vertex_num){}
		Graph(const Graph& obj): aList(obj.aList), vertex_sum(obj.aList.size()){}

		bool addEdge(vertex_t sour, vertex_t dest);
		bool addEdge(edge_t e);
		bool findEdge(vertex_t sour, vertex_t dest);
		bool findEdge(edge_t e);
		bool deleteEdge(vertex_t sour, vertex_t dest);
		bool deleteEdge(edge_t e);

		const AdjaList& getList(vertex_t sour);
		size_t vsize(){return vertex_sum;}

	private:
		std::vector<AdjaList> aList; size_t vertex_sum; 
		edge_t convert2edge(vertex_t sour, vertex_t dest);
		std::pair<vertex_t, vertex_t> convert2vertexs(edge_t e);
		

}

}








#endif
