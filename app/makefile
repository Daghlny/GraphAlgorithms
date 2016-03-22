
#clean: ./clique_enum.out
#	rm ./clique_enum.out
clique_enum.out: ./clique_enumeration.cc ./main.cc ../impl/uGraph.cc
	g++ -std=c++11 -I ../basic/ ./clique_enumeration.cc ../impl/program_process.cc ./main.cc ../impl/uGraph.cc -o clique_enum.out
