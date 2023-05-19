#include "OpenMP.h"

using namespace std;

unordered_map<string, int> openmp_map;
string text_openmp;
int threads_num;

void count_words_openmp(ThreadInterval data) {
    std::unordered_map<std::string, int> local_map;
    for (size_t i = data.start; i < data.end; i++) {
        std::string word;
        while (text_openmp[i] != ' ' && i < data.end) {
            word += text_openmp[i];
            i++;
        }
        if (local_map.find(word) == local_map.end())
            local_map[word] = 1;
        else
            local_map[word]++;
    }
    std::unordered_map<std::string, int>::iterator it;
    #pragma omp critical
    {
        for (it = local_map.begin(); it != local_map.end(); ++it) {
            if (openmp_map.find(it->first) == openmp_map.end())
                openmp_map[it->first] = it->second;
            else
                openmp_map[it->first] += it->second;
        }
    }
}

unordered_map<string, int> parallel_openmp() {
    double start_time_1, end_time_1;
    vector<int> segments = divide_string_length(text_openmp, threads_num);
    vector<ThreadInterval> threadIntervals(threads_num);
    omp_set_dynamic(0);
    #pragma omp parallel num_threads(threads_num)
    {
        int tid = omp_get_thread_num();
        threadIntervals[tid].start = segments[tid] + 1;
        threadIntervals[tid].end = segments[tid + 1];
        count_words_openmp(threadIntervals[tid]);
    }
    
    end_time_1 = omp_get_wtime();
    return openmp_map;
}

unordered_map<string, int> openmp_count(int threads_n, string text) {
    assert(threads_n > 0);
    text_openmp = text;
    threads_num = threads_n;
    unordered_map<string, int> word_freq = parallel_openmp();
    return word_freq;
}