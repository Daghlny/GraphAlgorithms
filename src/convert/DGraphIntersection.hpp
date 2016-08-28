/*************************************************
/ Authors: 
/	Ritchie Lee
/
/ ***********************************************/

#ifndef __D__GROUP__INTERSECTION__
#define __D__GROUP__INTERSECTION__

#include<vector>
#include<map>
#include<cstdint>
#include<string>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<ctime>

#define LINE_MAX 100

// the class means a intersection of a banch of directed graphs
// @edges is a set stores all edges of intersection
class DGraphIntersection{
	public:
		typedef uint64_t edge_t;
		typedef uint32_t vertex_t;
		typedef uint8_t  flag_t;

		DGraphIntersection(): curr_flag(1), refreshed(1), graph_num(0){}

		DGraphIntersection(std::string filename): curr_flag(1), refreshed(1), graph_num(0){
			initDGraphIntersectionByFile(filename);
		}

		DGraphIntersection(std::vector<std::string> &filenames, std::string logname = ""): 
			curr_flag(1), refreshed(1), graph_num(0){
			
			if(filenames.size() < 1)
				return;
			initDGraphIntersectionByFile(filenames[0]);
			if(filenames.size() < 2)
				return;

			for(std::vector<std::string>::const_iterator iter = filenames.begin();
				iter != filenames.end();
				++iter){

				getNewIntersection(*iter, logname);
			}
		}

		inline bool changeEdgeFlag(edge_t);
		
		bool addEdge(vertex_t sour, vertex_t dest);
		void initDGraphIntersectionByFile(std::string filename);
		void printEdges();

		void getNewIntersection(std::string filename);
		void getNewIntersection(std::string filename, std::string logname);

		flag_t getEdgeFlag(edge_t e);

		void getIncrement(std::vector<edge_t>& inc, std::string graph_file);
		void writeIncrement(const std::vector<edge_t>& inc, std::string inc_file_name, uint32_t no);
		void writeGroupIncrement(std::vector<std::string> files, std::string inc_file_name);
		
		void writeIntersection(std::string its_file_name);
		std::pair<vertex_t, vertex_t> getVertexPair(const edge_t e);
	
	private:
		std::map<edge_t, flag_t> edges;
		int8_t curr_flag;
		flag_t refreshed;
		uint32_t graph_num;

		edge_t convert2Edge(vertex_t sour, vertex_t dest);
		void refreshEdges();
};

/*
 * check the edge @e whether alive in the current intersection;
 * if alive, change the flag of @e different with @curr_flag;
 * return true if alive, false not;
 */
bool
DGraphIntersection::changeEdgeFlag(edge_t e){
	refreshed = 0;
	std::map<edge_t, flag_t>::iterator iter = edges.find(e);
	if( iter != edges.end()){
		//(*iter).second = (-1)*curr_flag;
		(*iter).second = curr_flag == 1 ? 2 : 1;
		return true;
	}
	return false;
}

/*
 * refresh the set of edges, erase the edges with the different 
 * flag to @curr_flag;
 */
void
DGraphIntersection::refreshEdges(){

	std::map<edge_t, flag_t>::iterator curr = edges.begin();

	for(std::map<edge_t, flag_t>::iterator i = edges.begin();
		i != edges.end();
		++i){
		
		if(i->second == curr_flag){
			edges.erase(i);
		}
	}
	
	curr_flag = curr_flag == 1 ? 2 : 1;
	refreshed = 1;
}

/*
 * add a new edge to the edges' set
 * @sour and @dest are the pair of vertexs of the edge
 */
bool 
DGraphIntersection::addEdge(vertex_t sour, vertex_t dest){
	if(refreshed == 0)	
		return false;
	edge_t e = convert2Edge(sour, dest);
	std::pair<std::map<edge_t, flag_t>::iterator, bool> result = 
		edges.insert(std::map<edge_t, flag_t>::value_type(e, curr_flag));
	if(result.second == false){
		return false;
	}
	return true;
}

/*
 * return a edge_t equals to a pair of vertexs;
 */
DGraphIntersection::edge_t
DGraphIntersection::convert2Edge(vertex_t sour, vertex_t dest){
	edge_t e = sour;
	e = (e<<32) | dest;
	return e;
}

/*
 * will get a initial intersection of file @filename
 */
void 
DGraphIntersection::initDGraphIntersectionByFile(std::string filename){
	std::ifstream initFile;
	char buff[LINE_MAX];
	initFile.open(filename);

	while(!initFile.eof()){
		initFile.getline(buff, LINE_MAX);
		if(buff[0] == '#')
			continue;
		if(!isdigit(buff[0]))
			continue;
		std::string line(buff);
		std::string::size_type tab_pos = 
			line.find_first_of('	',0);
		vertex_t sour = atoi(line.substr(0, tab_pos).c_str());
		vertex_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());
		
		addEdge(sour, dest);

	}
}

void
DGraphIntersection::printEdges(){
	std::cout << "the size of edges is: " << edges.size() << std::endl;
	for(std::map<edge_t, flag_t>::iterator iter = edges.begin();
		iter != edges.end();
		++iter)
		printf("edge: %016lx flag: %d\n", iter->first, iter->second);
		//std::cout << "edge: " << iter->first << "  flag: " << iter->second << std::endl;
}

/*
 * refresh the intersection of a new graph by file @filename
 */
void 
DGraphIntersection::getNewIntersection(std::string filename){
	getNewIntersection(filename, "");
}

/*
 * refresh the intersection of a new graph by file @filename and 
 * write the error log in the file @logname;
 */
void 
DGraphIntersection::getNewIntersection(std::string filename, std::string logname){

	std::ifstream newFile;
	std::ofstream logFile;

	char buff[LINE_MAX];
	newFile.open(filename);
	if(logname != ""){
		logFile.open(logname);
		std::time_t now_time = std::time(NULL);
		logFile << now_time << std::endl;
	}
		

	while(!newFile.eof()){
		newFile.getline(buff, LINE_MAX);
		if(buff[0] == '#')
			continue;
		if(!isdigit(buff[0]))
			continue;
		std::string line(buff);
		std::string::size_type tab_pos = 
			line.find_first_of('	',0);
		vertex_t sour = atoi(line.substr(0, tab_pos).c_str());
		vertex_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());

		edge_t e = convert2Edge(sour, dest);
		bool result = changeEdgeFlag(e);
		if(result == false && logname == ""){
			std::cout << "ERROR: the edge with (" << 
			sour << "," << dest << ")" << std::endl;
			continue;
		}
		if(result == false && logname != ""){
			logFile << "ERROR: the edge with (" << 
			sour << "," << dest << ")" << std::endl;
			continue;
		}

	}
	
	if(logname != "")
		logFile << "***********************************" << std::endl;
	refreshEdges();
	graph_num++;
}

DGraphIntersection::flag_t
DGraphIntersection::getEdgeFlag(edge_t e){
	std::map<edge_t, flag_t>::const_iterator iter = edges.find(e);
	if(iter == edges.end())
		return -1;
	return iter->second;
}

void 
DGraphIntersection::writeIncrement(const std::vector<edge_t>& inc, std::string inc_name, uint32_t graph_num){
	std::ofstream inc_file;
	inc_file.open(inc_name, std::ofstream::out | std::ofstream::app);
	inc_file << "#" << graph_num << std::endl;
	for(int i = 0; i != inc.size(); ++i){
		std::pair<vertex_t, vertex_t> tmp = getVertexPair(inc[i]);
		inc_file << tmp.first << '\t' << tmp.second << std::endl;
	}
	inc_file.close();
}

std::pair<DGraphIntersection::vertex_t, DGraphIntersection::vertex_t>
DGraphIntersection::getVertexPair(const edge_t e){
	vertex_t sour = (e>>32) & (0xFFFFFFFF);
	vertex_t dest = e & 0xFFFFFFFF;
	std::pair<vertex_t, vertex_t> tmp = std::make_pair(sour, dest);
	return tmp;
}

/*
 * refresh the increment with a new graph by the file@graph_file_name;
 * the parameter @inc will get all edges in the increment;
 */
void 
DGraphIntersection::getIncrement(std::vector<edge_t>& inc, std::string graph_file_name){

	std::ifstream graph_file;
	char buff[LINE_MAX];
	graph_file.open(graph_file_name);

	while(!graph_file.eof()){
		graph_file.getline(buff, LINE_MAX);

		if(buff[0] == '#')
			continue;
		if(!isdigit(buff[0]))
			continue;

		std::string line(buff);
		std::string::size_type tab_pos = line.find_first_of('	',0);
		vertex_t sour = atoi(line.substr(0, tab_pos).c_str());
		vertex_t dest = atoi(line.substr(tab_pos, line.size()-tab_pos).c_str());

		edge_t e = convert2Edge(sour, dest);
		
		//printf("%016lx\n", e);
		std::map<edge_t, flag_t>::iterator iter = edges.find(e);
		if(iter != edges.end())
			continue;

		inc.push_back(e);

	}
}

/*
 * write the increments with each graph, the file @inc_file_name will store the increments
 */
void 
DGraphIntersection::writeGroupIncrement(std::vector<std::string> files, std::string inc_file_name){

	uint32_t graph_no = 0;
	//std::ofstream inc_file;
	//inc_file.open(inc_file_name, std::ofstream::out | std::ofstream::trunc);
	//inc_file.close();

	for(int i = 0; i != files.size(); ++i){
		std::cout << "writing the " << i+1 << " file, " << files.size() - i-1 << "left." << std::endl;
		std::vector<edge_t> inc;
		getIncrement(inc, files[i]);
		writeIncrement(inc, inc_file_name, graph_no);
		graph_no++;
	}
}

// const method
void 
DGraphIntersection::writeIntersection(std::string its_file_name) {
	std::ofstream its_file;
	its_file.open(its_file_name, std::ofstream::out | std::ofstream::app);
	
	its_file << "# the intersection content " << std::endl;
	for(std::map<edge_t, flag_t>::const_iterator iter  = edges.begin(); 
		iter != edges.end(); 
		++iter){

		std::pair<vertex_t, vertex_t> tmp = getVertexPair(iter->first);
		its_file << tmp.first << '\t' << tmp.second << std::endl;
	}
}


#endif
