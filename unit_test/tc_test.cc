#include<iostream>
#include<ctime>
#include"../basic/uGraph.hpp"
#include"../algorithms/algorithms_types.hpp"

size_t tc_for_ugraph(std::set<tri_t> *res, uGraph* ug);

int
main(int argc, char **argv){
	long beg_time = std::clock();
	uGraph* ug = new uGraph();
	ug->read_graph_data(argv[1]);
	long end_time = std::clock();
	std::cout << "the time of building graph: " << (end_time-beg_time)/CLOCKS_PER_SEC << std::endl;
	
	std::set<tri_t>* res = new std::set<tri_t>();
	beg_time = std::clock();
	size_t tri_num = tc_for_ugraph(res, ug);
	end_time = std::clock();

	std::cout << tri_num << std::endl;
	std::cout << "Running time: " << (end_time-beg_time)/CLOCKS_PER_SEC << std::endl;
	return 1;
}
