
#include"algorithms_types.hpp"
#include<iostream>
#include<algorithm>

int
main(void){
	tri_t* t1 = new tri_t(1, 3, 7);
	tri_t* t2 = new tri_t(3, 7, 1);

	for(int i = 0; i != 3; ++i)
		std::cout << (*t1)[i] << '\t' << (*t2)[i] << std::endl;

	uint32_t arr[5] = {2, 3, 9, 1, 5};
	std::sort(arr, arr+5);
	for(int i = 0; i != 5; ++i)
		std::cout << arr[i] << '\t';
	std::cout << std::endl;
	
	return 1;
}
