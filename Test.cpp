#include <cstring>
#include <cctype>
#include "Serial.h"
#include "Pthread.h"
#include "OpenMP.h"
#include "Utils.h"

using namespace std;
double start_time, end_time;
unordered_map<string, int> freq;
string text;
int t_n;

void count_n_times_files(vector<string> files, int times, int threads_n) {
    for (string file : files) {
        text = readFileIntoString(file);
        t_n = threads_n;
        string path1, path2, path3;
    	fstream fs1, fs2, fs3;
    	path1 = file + "_serial";
        path2 = file + "_pthread";
        path3 = file + "_openmp";
    	fs1.open(path1, fstream::out | fstream::app);
        fs2.open(path2, fstream::out | fstream::app);
        fs3.open(path3, fstream::out | fstream::app);
        for (int i = 0; i < times; i++) {
            start_time = omp_get_wtime();
    	    freq = serial_count(text);
            end_time = omp_get_wtime();
            fs1 << end_time - start_time << "\n";
            start_time = omp_get_wtime();
    	    freq = pthread_count(t_n, text);
            end_time = omp_get_wtime();
            fs1 << end_time - start_time << "\n";
            start_time = omp_get_wtime();
    	    freq = openmp_count(t_n, text);
            end_time = omp_get_wtime();
            fs2 << end_time - start_time << "\n";
        }
        fs1.close();
        fs2.close();
        fs3.close();
    }
}

void count_n_times_threads(string file, int times, int max_threads) {
    text = readFileIntoString(file);
    fstream fs1, fs2;
    string path1, path2;
    for (int i = 0; i <= max_threads; i++) {
        if (i == 0) {
            t_n = 1;
        }
        else {
            t_n = i * 2;
        }
        path1 = to_string(t_n) + "_pthread";
        path2 = to_string(t_n) + "_openmp";
        fs1.open(path1, fstream::out | fstream::app);
        fs2.open(path2, fstream::out | fstream::app);
        for (int i = 0; i < times; i++) {
            start_time = omp_get_wtime();
    	    freq = pthread_count(t_n, text);
            end_time = omp_get_wtime();
            fs1 << end_time - start_time << "\n";
            start_time = omp_get_wtime();
    	    freq = openmp_count(t_n, text);
            end_time = omp_get_wtime();
            fs2 << end_time - start_time << "\n";

        }
        fs1.close();
        fs2.close();
    }
}

void mapEquals() {
    string text = readFileIntoString("text_pre_1000000");
    int t_n = 8;
    unordered_map<string, int> word_freq1 = serial_count(text);
    unordered_map<string, int> word_freq2 = pthread_count(t_n, text);
    unordered_map<string, int> word_freq3 = openmp_count(t_n, text);
    assert(word_freq1 == word_freq2);
    assert(word_freq1 == word_freq3);
}

void testSerial() {
    string text = readFileIntoString("text_test");
    freq = pthread_count(1, text);
    assert(freq.size() == 5);
    assert(freq.at("стул") == 2);
    assert(freq.at("стол") == 4);
    assert(freq.at("подушка") == 2);
    assert(freq.at("автомобиль") == 1);
    assert(freq.at("машина") == 3);
}

void perfomance_test(int times, int t_n, string file) {
    string text = readFileIntoString(file);
    for (int i = 0; i < times; i++) {
        cout << "========= " << i + 1<< " =========" << endl;
        start_time = omp_get_wtime();
    	freq = serial_count(text);
        end_time = omp_get_wtime();
        cout << "[serial] \\ " << end_time - start_time << endl;
        start_time = omp_get_wtime();
    	freq = pthread_count(t_n, text);
        end_time = omp_get_wtime();
        cout << "[pthread] \\ " << end_time - start_time << endl;
        start_time = omp_get_wtime();
    	freq = openmp_count(t_n, text);
        end_time = omp_get_wtime();
        cout << "[openmp] \\ " << end_time - start_time << endl;
    }
}

int main(int argc, char* argv[]){
    testSerial();
    mapEquals();
    perfomance_test(1, 8, "text_pre_1000000");
    return 0;
}