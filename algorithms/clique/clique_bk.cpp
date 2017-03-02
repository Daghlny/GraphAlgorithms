
#include "types.hpp"
#include "uGraph.hpp"

#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <map>
#include <string>

#ifndef __clique_file_path
#define __clique_file_path "~/all_cliques.txt"
#endif

uint64_t max_clique_size;
uint64_t clique_num;

// functions below is in program_process.cc file
int          deal_parameters(size_t , char **);
std::string  get_option_string(std::string);
int          get_option_int(std::string);

// functions below is in this file
vlist get_insct(vlist *old, vlist *ngbs);
void  print_adj(char *str, vlist a);


// this function uses Born-Kerbosch algorithm
// The set @c represents the current clique, @cand is the candidates vertices
// which can expend @c. @ncand has these vertices that have been finished.
// @output_func is a function pointer that stores the results
// @low_bound means cliques' size at least bigger than it.

void
clique_enum( uGraph *g, vlist c, vlist cand, vlist ncand, void (*output_func)(vlist *), size_t low_bound){

	if(cand.size() == 0 && ncand.size() == 0)
    {
		if(c.size() >= low_bound)
        {
            clique_num++;
            max_clique_size = std::max(max_clique_size, c.size());
			output_func(&c);
        }
		return;
	}
	else
		while(!cand.empty()){
			/*
			 * this section used iterator v with for-loop
			 * but erase() will let v invalid in for-loop's condition
			*/
			
			vlist::iterator v = cand.begin();

			vid_t tmp = *v;
			cand.erase(v);
			vlist ngbs = g->get_adj(tmp);
			c.insert(tmp);

			clique_enum(g, c, 
						get_insct(&cand, &ngbs), 
						get_insct(&ncand, &ngbs), 
						output_func, low_bound);

			//keep the origin set @c
			c.erase(c.find(tmp)); 
			ncand.insert(tmp);
		}
	// endif
		
}



// compute two vertex sets' intersetion
vlist
get_insct(vlist *old, vlist *ngbs){
	
	vlist res;
	std::insert_iterator<vlist> iter(res, res.begin());
	std::set_intersection(old->begin(),  old->end(), 
						  ngbs->begin(), ngbs->end(), 
						  iter);

	return res;
}


// there are two example functions as @output_func in clique_enum()

std::ofstream file;
void
clique_write_file(vlist *res){

	
	for(vlist::iterator iter = res->begin();
		iter != res->end();
		++iter)
		file << *iter << " ";
	file << std::endl;

}

void
clique_output_screen(vlist *res){
	
	std::cout << "clique: ";
	for(vlist::iterator iter = res->begin();
		iter != res->end();
		++iter)
		std::cout << *iter << ", ";
	std::cout << std::endl;
}
// end examples


// this section is used for debugging
void
print_adj(char *str, vlist a){

	std::cout << str << ' ';
	for(vlist::const_iterator iter = a.begin();
		iter != a.end();
		++iter)
		std::cout << *iter << ' ';
	std::cout << std::endl;

}

// end section
#ifndef __USER__DEFINED__MAIN
#define __USER__DEFINED__MAIN

int
main(int argc, char **argv) {

    if( argc < 2 || argc > 3 ){
        std::cout << "Parameters wrong" << std::endl;
        std::cout << "First parameter is input graph data file,"; 
        std::cout << "Second is output path" << std::endl;
        return -1;
    }

    uGraph *g = new uGraph(argv[1]);

    std::string t_file_path(argv[1]);
    t_file_path += ".clique.data";
    if( argc == 2 )
        file.open(t_file_path.c_str());
    else
        file.open(argv[2]);

    max_clique_size = 0;
    clique_num      = 0;

    vlist cand;
    g->vertex_set(cand);
    vlist c, ncand;

    clique_enum(g, c, cand, ncand, clique_write_file, 1);

    file.close();

    std::cout << "Total cliques' number: " << clique_num << std::endl;
    std::cout << "Maximum clique's size: " << max_clique_size << std::endl;
    
    return 0;
}

#endif

