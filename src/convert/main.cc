#include<string>
#include<iostream>
#include<vector>
#include"DGraphIntersection.hpp"

int
main( int argc, const char** argv){
	std::vector<std::string> files;
	
	for(int i = 1; i != argc-1; ++i){
		std::string tmp(*(argv+i));
		std::cout << "reading the " << i << " file(" << tmp << ")..." << std::endl;
		files.push_back(tmp);
	}
	
	std::string inc_file_name(*(argv+argc-1));
	DGraphIntersection dgi(files);

	std::cout << "begin writing the intersection" << std::endl;
	dgi.writeIntersection(inc_file_name);

	dgi.writeGroupIncrement(files, inc_file_name);
	std::cout << "all works have been done." << std::endl;

	return 1;
}
