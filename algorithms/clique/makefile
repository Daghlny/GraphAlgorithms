
#clean: ./clique_enum.out
#	rm ./clique_enum.out
#clique_enum.out: ./clique_enumeration.cc ./main.cc ../impl/uGraph.cc
#	g++ -std=c++11 -I ../basic/ ./clique_enumeration.cc ../impl/program_process.cc ./main.cc ../impl/uGraph.cc -o clique_enum.out
#

#clique_compute.out: ./clique_bfs.cc ../impl/uGraph.cc
#	g++ -Wall -std=c++11 -I ../basic/ ./clique_bfs.cc ../impl/uGraph.cc -o clique_compute.out
clique_bfs.out: ./clique_bfs.cc ../../src/uGraph.cc
	g++ -std=c++0x -ggdb -Wall -I ../../include/ ./clique_bfs.cc ../../src/uGraph.cc -o clique_bfs.out
#

#clique_bfs_without_flag.out: ./clique_bfs_without_flag.cc ../impl/uGraph.cc
#	g++ -std=c++11 -ggdb -Wall -I ../basic/ ./clique_bfs_without_flag.cc ../impl/uGraph.cc -o clique_bfs_without_flag.out

