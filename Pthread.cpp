#include "Pthread.h"

using namespace std;

unordered_map<string, int> pthread_map;
pthread_mutex_t mutex;
string text_pthread;
int pthreads_num;

void *count_words_pthread(void *arg) {
    auto *data = (ThreadInterval *) arg;
    unordered_map<string, int> local_map;
    for (size_t i = data->start; i < data->end; i++) {
    	string word;
        while (text_pthread[i] != ' ' && i < data->end) {
            word += text_pthread[i];
            i++;
        }
        if (local_map.find(word) == local_map.end())
            local_map[word] = 1;
        else
            local_map[word]++;
    }
    
    unordered_map<string, int>::iterator it;
    pthread_mutex_lock(&mutex);
    for (it=local_map.begin(); it!=local_map.end(); ++it) {
        if (pthread_map.find(it->first) == pthread_map.end()) 
            pthread_map[it->first] = it->second;
        else
            pthread_map[it->first] += it->second;
	}
    pthread_mutex_unlock(&mutex);
}

unordered_map<string, int> parallel_pthread() {
    pthread_map.clear();
    double start_time_1, end_time_1;
    start_time_1 = omp_get_wtime();
    vector<int> segments = divide_string_length(text_pthread, pthreads_num);
    end_time_1 = omp_get_wtime();
    vector<ThreadInterval> threadIntervals(pthreads_num);
    pthread_t threads[pthreads_num];
    for (int i = 0; i < pthreads_num; i++) {
	threadIntervals[i].start = segments[i] + 1;
	threadIntervals[i].end = segments[i + 1];
	pthread_create(&threads[i], nullptr, count_words_pthread, &threadIntervals[i]);
    }
    for (int i = 0; i < pthreads_num; i++) {
	pthread_join(threads[i], nullptr);
    }
    pthread_mutex_destroy(&mutex);
    return pthread_map;
}

unordered_map<string, int> pthread_count(int threads_n, string text) {
    assert(threads_n > 0);
    text_pthread = text;
    pthreads_num = threads_n;
    unordered_map<string, int> word_freq = parallel_pthread();
    return word_freq;
}