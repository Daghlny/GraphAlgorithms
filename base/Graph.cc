#include"Graph.hpp"

bool template<typename edgeT = uint64_t,typename  vertexT = uint32_t>
base::Graph::addEdge(vertex_t sour, vertex_t dest){
	if(sour > getVertexSum()-1 || sour > getVertexSum()-1)
		return false;
	AdjaList curr_list = aList[sour];
	if(curr_list.findVertex(dest) != NULL)
		return false;
	curr_list.addEdge(dest);
	return true;
}

size_t template<typename edgeT = uint64_t,typename  vertexT = uint32_t>
base::Graph::getEdgeSum(){
	size_t sum = 0;
	for(int i = 0; i != aList.size(); ++i){
		sum += aList[i].getListSize();
	}
	return sum;
}

template<typename edgeT = uint64_t, typename vertexT = uint32_t>
bool base::Graph::getAdjaList(vertex_t vid){
	return aList[vid];
}

template<typename edgeT = uint64_t, typename vertexT = uint32_t>
bool base::Graph::deleteEdge(vertex_t sour, vertex_t dest){
	if(sour >= getVertexSum() || dest >= getVertexSum())
		return false;
	AdjaList cur_list = edges[sour];
	return cur_list.deleteEdge(dest);
}

template<typename edgeT = uint64_t, typename vertexT = uint32_t>
bool base::Graph::deleteEdge(edge_t e){
	size_t e_size = sizeof(edgeT);
	size_t v_size = sizeof(vertexT);
	if(e_size != 2*v_size)
		return false;
	
	vertex_t sour = e << v_size;
	vertex_t dest = e & (0xffffffffffffffff >> (64-v_size));
	return deleteEdge(sour, dest);
}