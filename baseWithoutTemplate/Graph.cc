
#include<vector>
#include<utility>
#include"AdjaList.hpp"

bool
base::Graph::addEdge(vertex_t sour, vertex_t dest){
	if(sour >= vertex_sum || dest >= vertex_sum)
		return false;
	aList[sour].addEdge(dest);
	return true;
}

bool
base::Graph::addEdge(edge_t e){
	std::pair<vertex_t, vertex_t> rst = convert2vertexs(e);
	return addEdge(rst.first, rst.second);
}

bool
base::Graph::findEdge(vertex_t sour, vertex_t dest){
	if(sour >= vertex_sum || dest >= vertex_sum)
		return false;
	return aList[sour].findNode(dest);
}

bool
base::Graph::findEdge(edge_t e){
	std::pair<vertex_t, vertex_t> rst = convert2vertexs(e);
	return findEdge(rst.first, rst.second);
}

bool
base::Graph::deleteEdge(vertex_t sour, vertex_t dest){
	if(sour >= vertex_sum || dest >= vertex_sum)
		return false;
	return aList[sour].deleteNode(dest);
}

bool
base::Graph::deleteEdge(edge_t e){
	std::pair<vertex_t, vertex_t> rst = convert2vertexs(e);
	return deleteEdge(rst.first, rst.second);
}


std::pair<vertex_t, vertex_t>
base::Graph::convert2vertexs(edge_t e){
	return std::make_pair((e>>32) & 0xffffffff, e & 0xffffffff);
}

edge_t
base::Graph::convert2edge(vertex_t sour, vertex_t dest){
	edge_t rst = sour;
	rst = (rst << 32) | dest;
	return rst;
}

const AdjaList&
base::Graph::getList(vertex_t sour){
	return aList[sour];
}


















