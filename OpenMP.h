#include "Utils.h"
#include <cassert>
#include <omp.h>

using namespace std;

void count_words_openmp(ThreadInterval data);

unordered_map<string, int> parallel_openmp();

unordered_map<string, int> openmp_count(int threads_n, string text);