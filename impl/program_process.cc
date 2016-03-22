
#include<string>
#include<map>
#include<utility>
#include<iostream>


typedef std::map<std::string, std::string> pars_t;
pars_t *all_pars;

// return -1 if the parameters don't match
// 
int
deal_parameters(size_t argc, char **argv){
	
	all_pars = new pars_t();

	for(size_t cnt = 1; cnt != argc; ++cnt){
		if(argv[cnt][0] == '-'){
			if(cnt == argc-1 || argv[cnt+1][0] == '-'){
				all_pars->insert(std::make_pair(std::string(argv[cnt]+1), "true"));
			} else {
				all_pars->insert(std::make_pair(std::string(argv[cnt]+1), std::string(argv[cnt+1])));
				cnt++;
			}
		}
	}
	
	return 1;
}

std::string
get_option_string(std::string name){
	
	if(all_pars->count(name) != 0)
		return (all_pars->find(name)->second);
	return "";
}

int
get_option_int(std::string name){
	
	if(all_pars->count(name) != 0)
		return atoi((all_pars->find(name)->second).c_str());
	return -1;
}

