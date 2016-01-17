
#include<set>
#include"../headers/Clique.hpp"

void
CliqueEnumeration(std::set<uint32_t>, std::set<uint32_t>, std::set<uint32_t>);

void
CliqueEnumeration(std::set<uint32_t> &C, 
		          std::set<uint32_t> &Cand, 
				  std::set<uint32_t> &NCand,
				  Graph *g,
				  std::vector<Clique> &cliques){
	if(Cand.size() == 0 && NCand.size() == 0)
		cliques.push_back(C);
	else{
		for(std::set<uint32_t>::iterator iter = Cand.begin();
			iter != Cand.end();
			++iter){

			Cand.erase(*iter);
			C.insert(*iter);
			std::set<uint32_t> tmp_Cand;
			std::set<uint32_t> tmp_NCand;
			
			std::set_intersection(tmp_Cand, )

			CliqueEnumeration(C, tmp_Cand, tmp_NCand, g, cliques);
		}
	}

}
