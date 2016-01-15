#ifndef __GA__ALGORITHMS__TYPES__HPP__
#define __GA__ALGORITHMS__TYPES__HPP__

#include<cstdint>
#include"../basic/types.hpp"

struct tri_t{
	
	tri_t(vid_t f, vid_t s, vid_t t){
		vid_arr[0] = f;
		vid_arr[1] = s;
		vid_arr[2] = t;
	}	
	
	friend bool operator<(const tri_t& lhs, const tri_t& rhs);
	friend bool operator==(const tri_t& lhs, const tri_t& rhs);

	// Problem: why should there be two versions of operator[]
	// otherwise will call errors
	const vid_t& operator[](const size_t index) const {
		return vid_arr[index]; 
	}

	vid_t& operator[](const size_t index) {
		return vid_arr[index]; 
	}

	bool if_exist(vid_t v) const{
		for(int i = 0; i != 3; ++i)
			if(vid_arr[i] == v) 
				return true;
		return false;
	}

	private:
		vid_t vid_arr[3];
};

inline bool 
operator<(const tri_t& lhs, const tri_t& rhs){
	if(lhs[0] < rhs[0])
		return true;
	else if(lhs[0] > rhs[0])
		return false;
	if(lhs[1] < rhs[1])
		return true;
	else if(lhs[1] > rhs[1])
		return false;
	if(lhs[2] < rhs[2])
		return true;
	else if(lhs[2] > rhs[2])
		return false;
}

inline bool
operator==(const tri_t& lhs, const tri_t& rhs){
	for(int i = 0; i != 3; ++i){
		if(lhs.if_exist(rhs[i]))
			continue;
		else
			return false;
	}	
	return true;
}
#endif

