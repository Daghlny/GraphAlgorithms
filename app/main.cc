#include"types.hpp"
#include"uGraph.hpp"

#include<set>
#include<algorithm>
#include<iostream>
#include<cstdlib>


// the functions below are in clique_enumeration.cc
void clique_write_file(adj_t *res);
void clique_output_screen(adj_t *res);
void clique_enum(uGraph *, adj_t, adj_t, adj_t, void(* )(adj_t*), size_t);


typedef std::map<std::string, std::string> paras_t;



int
main(int argc, char **argv){

	if(argc <= 0){
		std::cout << "parameters are wrong" << std::endl;
		std::cout << "for help typing --help" << std::endl;
		return -1;
	}

	size_t lower_bound = 2;
	if(argc == 3){
		lower_bound = atoi(argv[1]);
	}
	uGraph *g = NULL;
	if(argc == 2)
		g = new uGraph(argv[1]);
	else
		g = new uGraph(argv[2]);
	//uGraph *g = new uGraph("./graph_data.txt");
	
	adj_t *cand = new adj_t();
	g->vtx_set(cand);

	adj_t c, ncand;
	clique_enum(g, c, *cand, ncand, clique_output_screen, lower_bound);

	return 1;
}

/*
paras_t*
trans_paras(int argc, char **argv){

	paras_t *p = new paras_t();

	if(argc % 2 != 0)
	size_t pos = 0;
	while(pos <= argc-1){
		std::string key(argv[pos]);
		std::string value(argv[pos+1]);
		
		p->insert(std::make_pair(key, value));
		pos += 2;
	}

	return p;
	
}
*/

