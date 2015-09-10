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
