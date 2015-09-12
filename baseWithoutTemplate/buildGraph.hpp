#ifndef __BASE__NT__BUILDGRAPH__HPP__
#define __BASE__NT__BUILDGRAPH__HPP__

#include<fstream>
#include"Graph.hpp"

#define LINE_MAX 100

namespace base{

class buildGraph{
	public:
		static void byFile(Graph& g, std::string file_name);
}

}

void
base::buildGraph::byFile(Graph& g, std::string file_name){
	std::ifstream in_file;
	in_file.open(file_name);
	char buf[LINE_MAX];

	while(!in_file.eof()){
		in_file.getline(buf, LINE_MAX);
		if(buff[0] == '#') continue;
		if(!isdigit(buff[0])) break;

		std::string line_str(buf);
		std::string::size_type tab_pos = line.find_first_of('	',0);
		vertex_id_t sour = atoi(line.substr(0, tab_pos).c_str());
		vertex_id_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());
		g.addEdge(sour, dest);
	}
}
#endif
