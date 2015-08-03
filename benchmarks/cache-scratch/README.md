cache-scratch is a benchmark that exercises a heap's cache locality.
An allocator that allows multiple threads to re-use the same small object (possibly all in one cache-line) will scale poorly.
