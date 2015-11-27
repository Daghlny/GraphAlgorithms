#ifndef __HEADERS__TYPES__HPP__
#define __HEADERS__TYPES__HPP__

#include<cstdint>

typedef uint64_t usize_t; 
typedef uint64_t edge_id_t;
typedef uint32_t vertex_id_t;

class u_Graph;
class adjaList;

struct a_node{
	vertex_id_t nid;
	struct a_node *next;
	struct a_node *pre;
};

#endif

