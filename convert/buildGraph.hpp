#ifndef __BUILDGRAPH__H__
#define __BUILDGRAPH__H__

#include"Graph.hpp"
#include"AdjaList.hpp"
#include<fstream>
#include<locale>

#define LINE_MAX 100

class buildGraph{
	public:
		Graph* buildGraphByFile(std::string fileName, uint64_t vertex_num);
};

/*
 * Create a Graph Class by read the file with @filename
 * @vertex_num is the number of vertexs of the Graph
 * supply the @vertex_num will help to build vector with less overhead
 * return the pointer points the Graph
 */
Graph*
buildGraph::buildGraphByFile(std::string filename, uint64_t vertex_num){
	Graph *g = new Graph(vertex_num);
	std::ifstream graphFile;
	char buff[LINE_MAX];
	graphFile.open(filename);
	//if(!graphFile.is_open())
	//	return NULL;
	while(!graphFile.eof()){
		graphFile.getline(buff, LINE_MAX);
		if(buff[0] == '#')
			continue;
		if(!isdigit(buff[0]))
			break;
		std::string line(buff);
		std::string::size_type tab_pos = line.find_first_of('	',0);
		vertex_id_t sour = atoi(line.substr(0, tab_pos).c_str());
		vertex_id_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());
		g->addEdge(sour, dest);
	}

	return g;
}

#endif

















