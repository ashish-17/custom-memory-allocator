#ifndef __SYNCHRO_ATOMIC_H__
#define __SYNCHRO_ATOMIC_H__

#include <stdatomic.h>

static inline unsigned int compare_and_swap64(volatile unsigned long long *address, 
						unsigned long long old_value, unsigned long long new_value)
{
	return atomic_compare_exchange_strong(address, &old_value, new_value);
}

static inline unsigned long compare_and_swap_ptr(volatile void *address, void* old_ptr, void* new_ptr)
{
	return compare_and_swap64((volatile unsigned long long *)address, (unsigned long long)old_ptr, (unsigned long long)new_ptr); 
}

#endif

