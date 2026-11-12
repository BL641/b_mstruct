
#ifndef __BPAIR__H
#define __BPAIR__H

#define bpair(T, N)\
typedef struct {\
	T* first;\
	N* second;\
} bp_##T##_##N##;\

#endif // !__BPAIR__H

