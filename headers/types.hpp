#ifndef __HEADERS__TYPES__HPP__
#define __HEADERS__TYPES__HPP__

#include<cstdint>
#include<set>

typedef uint32_t vtx_t;
typedef uint64_t edg_t;

typedef std::set<vtx_t> ajcl_t;

typedef uint64_t usize_t; 

class u_Graph;
class adjaList;

struct a_node{
	vertex_id_t nid;
	struct a_node *next;
	struct a_node *pre;
};

#endif

