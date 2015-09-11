#ifndef __BASE__NT__ADJANODE__HPP__
#define __BASE__NT__ADJANODE__HPP__

#include"AdjaList.h"

namespace base{

class AdjaNode{
	public:
		AdjaNode():vid(-1), next(NULL){}
		AdjaNode(Graph::vertex_t vvid): vid(vvid), next(NULL){}
		friend class AdjaList;
	private:
		Graph::vertex_t vid;
		AdjaNode *next;
};

}




#endif
