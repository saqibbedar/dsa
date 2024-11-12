#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <string> // for file handling

// Data Model class
class DataModel{

public:

    // Schema
    int task;
    std::string algorithm_name;
    int array_size;
    std::string array_type;
    double average_time_taken;

    DataModel(int t = 0, const std::string &algo_name = "", int arr_size = 0, const std::string arr_type = "", double avg_time = 0.0) : task(t), algorithm_name(algo_name), array_size(arr_size), array_type(arr_type), average_time_taken(avg_time) {}
};

// Algorithm holder class
class Algorithm{
public:
    void correct_selection_sort(int *, int);
    void wrong_selection_sort(int *, int);
    void bubble_sort(int *, int);
    void insertion_sort(int *, int);
};

void Algorithm::correct_selection_sort(int *arr, int size){
    // Best: O(n^2)
    // Worst: O(n^2)

    for (int i = 0; i < size - 1; ++i) {
        int smallest_element_index = i; // In selection sort we assume our first element is small
        for (int j = i + 1; j < size; ++j) { // starting from i+1? bcz we will compare small_element_index with next elements
            if(arr[smallest_element_index] > arr[j]) { // Incase if it not small
                smallest_element_index = j; // assign the small element index
            }
        }
        if(smallest_element_index != i){
            std::swap(arr[i], arr[smallest_element_index]);
        }
    }

}

void Algorithm::wrong_selection_sort(int *arr, int size){
    // Best: O(n^2)
    // Worst: O(n^2)

    for (int i = 0; i < size - 1; ++i) {
        int smallest_element_index = i; // In selection sort we assume our first element is small
        for (int j = i + 1; j < size; ++j) { // starting from i+1? bcz we will compare small_element_index with next elements
            if(arr[smallest_element_index] > arr[j]) { // Incase if it not small
                std::swap(arr[smallest_element_index], arr[j]); // swap the values 
            }
        }
    }

}

void Algorithm::bubble_sort(int *arr, int size){
    // Best: O(n)
    // Worst: O(n^2)

    bool isSwapped = true;

    for (int i = 0; i < size - 1; ++i) {

        isSwapped = false;

        for (int j = 0; j < size - i - 1 ; ++j) {
            if(arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }

        if(!isSwapped) break;

    }

}

void Algorithm::insertion_sort(int *arr, int size){
    // Best: O(n)
    // Worst: O(n^2)

    for (int i = 1; i < size; i++) {  // Start from the second element
        int current_element = arr[i];
        int j = i - 1;  // Start comparing with the previous element
        // Shift elements of arr[0..i-1] that are greater than current_element
        while (j >= 0 && arr[j] > current_element) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current_element;  // Place current_element in the correct position
    }
}

// Utility functions class
class Utility {
public:
    void generate_random_array(int *, int);
    void generate_ascending_order_array(int *, int);
    void generate_descending_order_array(int *, int);
    void copy_array(int *, int *, int size);
    void display(const char *, int *, int);
    void generate_csv_file(const DataModel *, int);
};

void Utility::generate_random_array(int *arr, int size) {
    srand(time(0));
    for (int i = 0; i < size; ++i){
        arr[i] = rand() % 100;
    }
}

void Utility::generate_ascending_order_array(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
}

void Utility::generate_descending_order_array(int *arr, int size) {
    for (int i = size, j=0; i > 0; --i, ++j) {
        arr[j] = i;
    }
}

void Utility::copy_array(int *des, int *src, int size){
    for (int i = 0; i < size; ++i){
        des[i] = src[i];
    }
}

void Utility::display(const char* array_name, int *arr, int size) {
    // Best: O(n)
    // Worst: O(n)
    std::cout  << array_name << ": [";
    for (int i = 0; i < size; ++i) {
        if(i == size -1) {
            std::cout << arr[i] << "]" << std::endl;
        } else {
            std::cout << arr[i] << ", ";
        }
    }
}

void Utility::generate_csv_file(const DataModel *data, int size) {
    std::ofstream f("data.csv");
    if(!f.is_open()){
        throw("Error: <file> Unable to open file");
    } else {

        f << "Task No, Algorithm, Array Size, Array Type (random/sorted-asc/sorted-desc), Average Time Taken" << std::endl;
        // write to csv
        for (int i = 0; i < size; ++i) {
            f << data[i].task << "," << data[i].algorithm_name << "," << data[i].array_size << "," << data[i].array_type << "," << data[i].average_time_taken << std::endl;
        }

        f.close();
    }
}

// Time Calculator
class CalculateTime{
    Algorithm algorithm;

public:
    double calculate_css_time(int *, int); // calculate correct selection sort time
    double calculate_wss_time(int *, int); // calculate wrong selection sort time
    double calculate_bs_time(int *, int); // calculate bubble sort time
    double calculate_is_time(int *, int); // calculate insertion sort time
};

double CalculateTime::calculate_css_time(int *arr, int size){ // calculate correct selection sort time
    const auto start{std::chrono::steady_clock::now()};
    algorithm.correct_selection_sort(arr, size); // sort array
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    return elapsed_seconds.count();
}

double CalculateTime::calculate_wss_time(int *arr, int size){ // calculate wrong selection sort time
    const auto start{std::chrono::steady_clock::now()};
    algorithm.wrong_selection_sort(arr, size); // sort array
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    return elapsed_seconds.count();
}

double CalculateTime::calculate_bs_time(int *arr, int size){ // calculate bubble sort time
    const auto start{std::chrono::steady_clock::now()};
    algorithm.bubble_sort(arr, size); // sort array
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    return elapsed_seconds.count();
} 

double CalculateTime::calculate_is_time(int *arr, int size){ // calculate insertion sort time
    const auto start{std::chrono::steady_clock::now()};
    algorithm.insertion_sort(arr, size); // sort array
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    return elapsed_seconds.count();
}
