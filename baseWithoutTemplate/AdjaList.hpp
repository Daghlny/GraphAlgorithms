#ifndef __BASE__NT__ADJALIST__HPP__
#define __BASE__NT__ADJALIST__HPP__

#include"Graph.hpp"

namespace base{

class AdjaList{
	public:

		AdjaList(): head(NULL), tail(NULL), vid(-1), node_sum(0){}
		AdjaList(const AdjaList& obj):
			head(obj.head), tail(obj.tail),
			vid(obj.vid), node_sum(obj.node_sum){}

		void addEdge(Graph::vertex_t dest);
		bool findNode(Graph::vertex_t dest);
		bool deleteNode(Graph::vertex_t dest);

	private:
		AdjaNode *head;
		AdjaNode *tail;
		Graph::vertex_t vid;
		size_t   node_sum;
};

}






















#endif
