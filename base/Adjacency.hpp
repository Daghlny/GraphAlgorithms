#ifndef __BASE__GRAPH__HPP__
#define __BASE__GRAPH__HPP__

namespace base{

/*one adjaNode stands a node in a linkedlist used in adjacency list*/
template<typename vertexT>
class adjaNode{
	public:
		typedef vertexT vertex_t;
		friend class AdjaList;

		adjaNode(): vertexID(-1), next(NULL){}
		adjaNode(vertex_t id):vertexID(id), next(NULL){}
		~adjaNode(){
			
		}

		adjaNode &getNext();
		void addNext(vertex_t id);

		vertex_t vertexID;
	private:
		adjaNode *next;
}


/* the class helps the Graph class build adjacency list;*/
template<typename vertexT>
class AdjaList{
	public:
		typedef vertexT vertex_t;

		AdjaList(vertex_t id): val(id), head(NULL){}
		
		void addEdge(vertex_t id);
		void *findEdge(vertex_t id);
		void deleteEdge(vertex_t id);

		void getListSize(){return num;}

	private:
		adjaNode *head;
		adjaNode *tail;
		vertex_t val;
		size_t   num;
}


}





#endif

