#ifndef __BASE__GRAPH__HPP__
#define __BASE__GRAPH__HPP__

namespace base{

template<typename edgeT = uint64_t, typename vertexT = uint32_t>
class Graph{
	public:
		typedef edgeT    edge_t;
		typedef vertexT  vertex_t;
		
		Graph(){}
		Graph(size_t vertex_sum):aList(vertex_sum){}
		
		bool addEdge(vertex_t sour, vertex_t dest);
		size_t getVertexSum(){ return aList.size(); }
		size_t getEdgeSum();

	private:
		std::vactor<AdjaList<vertex_t>> aList;

	
		
}

}

#endif // #ifndef __BASE__GRAPH__HPP__
