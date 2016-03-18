
#include"types.hpp"
#include"uGraph.hpp"

#include<set>
#include<algorithm>
#include<fstream>
#include<iostream>

#ifndef clique_file_path
#define clique_file_path "~/all_cliques.txt"
#endif


adj_t get_insct(adj_t *old, adj_t *ngbs);
void print_adj(char *str, adj_t a);

void
clique_enum(
			uGraph *g,
			adj_t c, 
		    adj_t cand, 
			adj_t ncand,
			void (*output_func)(adj_t *)){

	

	if(cand.size() == 0 && ncand.size() == 0){
		output_func(&c);
		return;
	}
	else
		while(!cand.empty()){
			/*
			std::cout << "******" << std::endl;
			print_adj("C:", c);
			print_adj("Cand:", cand);
			print_adj("NCand:", ncand);
			std::cout << "******" << std::endl;
			*/
			
			adj_t::iterator v = cand.begin();

			vid_t tmp = *v;
			cand.erase(v);
			adj_t ngbs = g->get_adj(tmp);
			c.insert(tmp);

			clique_enum(g, 
						c, 
						get_insct(&cand, &ngbs), 
						get_insct(&ncand, &ngbs), 
						output_func);

			//keep the origin set @c
			c.erase(c.find(tmp)); 
			ncand.insert(tmp);
		}
	// endif
		
}

adj_t
get_insct(adj_t *old, adj_t *ngbs){
	
	adj_t res;
	std::insert_iterator<adj_t> iter(res, res.begin());
	std::set_intersection(old->begin(),  old->end(), 
						  ngbs->begin(), ngbs->end(), 
						  iter);

	return res;
}

void
clique_write_file(adj_t *res){

	std::ofstream file;
	file.open(clique_file_path);
	
	for(adj_t::iterator iter = res->begin();
		iter != res->end();
		++iter)
		file << *iter << ", ";
	file << std::endl;

	file.close();
}

void
clique_output_screen(adj_t *res){
	
	std::cout << "clique: ";
	for(adj_t::iterator iter = res->begin();
		iter != res->end();
		++iter)
		std::cout << *iter << ", ";
	std::cout << std::endl;
}

// this section is used for debugging
void
print_adj(char *str, adj_t a){

	std::cout << str << ' ';
	for(adj_t::const_iterator iter = a.begin();
		iter != a.end();
		++iter)
		std::cout << *iter << ' ';
	std::cout << std::endl;

}

// end section
//
#ifndef __USER__DEFINED__MAIN
#define __USER__DEFINED__MAIN

/*
int
main(int argc, char **argv){
	
	if(argc == 1)
}
*/

#endif

