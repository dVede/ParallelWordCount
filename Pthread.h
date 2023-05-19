#include "Utils.h"
#include <cassert>
#include <pthread.h>
#include <omp.h>

void *count_words_pthread(void *arg);

unordered_map<string, int> parallel_pthread();

unordered_map<string, int> pthread_count(int threads_n, string text);