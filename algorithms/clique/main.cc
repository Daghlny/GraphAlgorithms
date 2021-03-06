
#include"types.hpp"
#include"uGraph.hpp"

#include<set>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include <ctime>

// the functions below are in clique_enumeration.cc
void clique_write_file(adj_t *res);
void clique_output_screen(adj_t *res);
void clique_enum(uGraph *, adj_t, adj_t, adj_t, void(* )(adj_t*), size_t);


// functions below is in program_process.cc file
int          deal_parameters(size_t , char **);
std::string  get_option_string(std::string);
int          get_option_int(std::string);

typedef std::map<std::string, std::string> paras_t;

void
output_help_msg(){
	std::cout << std::endl;
	std::cout << "This program is used to compute all maximal cliques in a undirected graph." << std::endl;
	std::cout << "Author: Ritchie Lee" << std::endl;
	std::cout << "The preprocess parameters are below: " << std::endl;
	std::cout << "-L         the size's lower bound of cliques" << std::endl;
	std::cout << "-input     the file path of graph data file"  << std::endl;
	std::cout << "-output    the file to store all results computed by the program" << std::endl;
	std::cout << std::endl;
}

// this main function is for clique_enumeration
int
main(int argc, char **argv){

	deal_parameters((size_t) argc, argv);

	if(get_option_string("-help") != ""){
		output_help_msg();
		return 1;
	}

	std::string istr(get_option_string("input"));
    std::cout << istr << std::endl;
	if(istr == ""){
		std::cout << "no available input data file" << std::endl;
		return -1;
	}

	int low_bound = get_option_int("L");
	if(low_bound == -1){
		std::cout << "*** *** *** ***" << std::endl;
		std::cout << "the lower bound of the clique is 3 default" << std::endl;
		std::cout << "*** *** *** ***" << std::endl;
		low_bound = 3;
	}

	uGraph *g = NULL;

    clock_t all_begin = clock();
    clock_t io_begin  = clock();
	g = new uGraph(istr.c_str());
    clock_t io_end    = clock();

    std::cout << "read graph data finished." << std::endl;
    std::cout << (double)((io_begin-io_end)/CLOCKS_PER_SEC);
    std::cout << " seconds used" << std::endl;
	
	adj_t *cand = new adj_t();
	g->vtx_set(cand);

	adj_t c, ncand;
    
	clique_enum(g, c, *cand, ncand, clique_output_screen, low_bound);
    clock_t all_end = clock();
    std::cout << "all computing is finished." << std::endl;
    std::cout << (double)((all_begin-all_end)/CLOCKS_PER_SEC);
    std::cout << " seconds used" << std::endl;
    std::cout << std::endl;

	return 1;
}


