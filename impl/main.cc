#include<iostream>

int deal_parameters(size_t, char**);
std::string get_option_string(std::string);
int get_option_int(std::string);

int
main(int argc, char **argv){

	if(!deal_parameters((size_t)argc, argv)){
		std::cout << "wrong" << std::endl;
		return 1;
	}

	std::string str;
	while(str != "NULL"){
		std::cin >> str;
		std::cout << get_option_string(str) << std::endl;
	}

	return 1;
}
