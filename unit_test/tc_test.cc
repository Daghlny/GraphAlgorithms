#include<iostream>
#include"../basic/uGraph.hpp"
#include"../algorithms/algorithms_types.hpp"

size_t tc_for_ugraph(std::set<tri_t> *res, const uGraph* ug);

int
main(int argc, char **argv){
	uGraph* ug = new uGraph();
	ug->read_graph_data(argv[1]);
	
	std::set<tri_t>* res = new std::set<tri_t>();
	size_t tri_num = tc_for_ugraph(res, ug);

	std::cout << tri_num << std::endl;
	return 1;
}
