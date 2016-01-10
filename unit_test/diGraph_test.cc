#include"../basic/diGraph.hpp"
#include<iostream>
#include<cstdio>

int main(int argc, char **argv){
	if(argc <= 1) return -1;
	printf("%s", argv[1]);
	diGraph dg(argv[1]);
	
	vid_t id = 0;
	std::cout << dg.vtx_sum() << std::endl;
	do{
		std::cin >> id;
		if(id == -1) break;
		std::cout << dg.adj_size(id) << std::endl;
	}while(true);
	return 1;
}
