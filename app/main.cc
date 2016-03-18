#include"types.hpp"
#include"uGraph.hpp"

#include<set>
#include<algorithm>
#include<iostream>

void clique_write_file(adj_t *res);
void clique_output_screen(adj_t *res);
void clique_enum(uGraph *, adj_t, adj_t, adj_t, void(* )(adj_t*));

int
main(int argc, char **argv){

	if(argc <= 0){
		std::cout << "parameter error" << std::endl;
		return -1;
	}

	//uGraph *g = new uGraph(argv[1]);
	uGraph *g = new uGraph("./graph_data.txt");
	
	adj_t *cand = new adj_t();
	g->vtx_set(cand);

	adj_t c, ncand;
	clique_enum(g, c, *cand, ncand, clique_output_screen);

	return 1;
}
