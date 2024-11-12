#include "Assignment.h"

int main()
{

    // Predefined size for all arrays, to check complexity change the size here only
    const int SIZE = 1000; // Array A size

    DataModel *data = new DataModel[16]; // Data Schema
    CalculateTime t; // for time calculation functions
    Utility utils; // for Utility functions

    // Required Arrays
    int A[SIZE]; // Array A: random elements
    int B[SIZE]; // Array B: elements in ascending order
    int C[SIZE]; // Array C: elements in descending order
    int temp_array[SIZE]; // to not loose original array values
    double time; // to hold calculation time



    //Task 1. Measure how much time each of the three algorithms takes to sort the random array (A).

    std::cout << "\n\tArray A: Random Array Execution Time \n" << std::endl; // screen message

    utils.generate_random_array(A, SIZE); // generate a random array

    // 1. Calculate the time for Array A using correct selection sort
    utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
    time = t.calculate_css_time(temp_array, SIZE);
    std::cout <<"1. Correct Selection Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time
    
    // write data to DataModel array
    data[0].task = 1;
    data[0].algorithm_name = "Correct Selection Sort";
    data[0].array_size = SIZE;
    data[0].array_type = "random";
    data[0].average_time_taken = time;

    // 2. Calculate the time for Array A using wrong selection sort
    utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
    time = t.calculate_wss_time(temp_array, SIZE);
    std::cout <<"2. Wrong Selection Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time

    // write data to DataModel array
    data[1].task = 1;
    data[1].algorithm_name = "Wrong Selection Sort";
    data[1].array_size = SIZE;
    data[1].array_type = "random";
    data[1].average_time_taken = time;

    // 3. Calculate the time for Array A using bubble sort
    utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
    time = t.calculate_bs_time(temp_array, SIZE);
    std::cout <<"3. Bubble Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time
    
    // write data to DataModel array
    data[2].task = 1;
    data[2].algorithm_name = "Bubble Sort";
    data[2].array_size = SIZE;
    data[2].array_type = "random";
    data[2].average_time_taken = time;
    
    // 4. Calculate the time for Array A using insertion sort
    utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
    time = t.calculate_is_time(temp_array, SIZE);
    std::cout <<"4. Insertion Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time

    // write data to DataModel array
    data[3].task = 1;
    data[3].algorithm_name = "Insertion Sort";
    data[3].array_size = SIZE;
    data[3].array_type = "random";
    data[3].average_time_taken = time;

    

    // Task 2. Measure how much time each of the three algorithms takes to sort an already sorted (ascending) array (B)

    std::cout << "\n\tArray B: Ascending Order Array Execution Time \n" << std::endl; // screen message
    
    utils.generate_ascending_order_array(B, SIZE); // ascending order array

    // 1. Calculate the time for Array B using correct selection sort
    utils.copy_array(temp_array, B, SIZE); // copy array B to temp_array
    time = t.calculate_css_time(temp_array, SIZE);
    std::cout <<"1. Correct Selection Sort took "<< time << " time to sort Ascending Order Array B" << std::endl; // print execution time
    
    // write data to DataModel array
    data[4].task = 2;
    data[4].algorithm_name = "Correct Selection Sort";
    data[4].array_size = SIZE;
    data[4].array_type = "sorted-asc";
    data[4].average_time_taken = time;

    // 2. Calculate the time for Array B using wrong selection sort
    utils.copy_array(temp_array, B, SIZE); // copy array B to temp_array
    time = t.calculate_wss_time(temp_array, SIZE);
    std::cout <<"2. Wrong Selection Sort took "<< time << " time to sort Ascending Order Array B" << std::endl; // print execution time

    // write data to DataModel array
    data[5].task = 2;
    data[5].algorithm_name = "Wrong Selection Sort";
    data[5].array_size = SIZE;
    data[5].array_type = "sorted-asc";
    data[5].average_time_taken = time;

    // 3. Calculate the time for Array B using bubble sort
    utils.copy_array(temp_array, B, SIZE); // copy array B to temp_array
    time = t.calculate_bs_time(temp_array, SIZE);
    std::cout <<"3. Bubble Sort took "<< time << " time to sort Ascending Order Array B" << std::endl; // print execution time

    // write data to DataModel array
    data[6].task = 2;
    data[6].algorithm_name = "Bubble Sort";
    data[6].array_size = SIZE;
    data[6].array_type = "sorted-asc";
    data[6].average_time_taken = time;

    // 4. Calculate the time for Array B using Insertion selection sort
    utils.copy_array(temp_array, B, SIZE); // copy array B to temp_array
    time = t.calculate_is_time(temp_array, SIZE);
    std::cout <<"4. Insertion Sort took "<< time << " time to sort Ascending Order Array B" << std::endl; // print execution time

    // write data to DataModel array
    data[7].task = 2;
    data[7].algorithm_name = "Insertion Sort";
    data[7].array_size = SIZE;
    data[7].array_type = "sorted-asc";
    data[7].average_time_taken = time;



    // Task 3. Measure how much time each of the three algorithms takes to sort an already sorted (descending) array (C)

    std::cout << "\n\tArray C: Descending Order Array Execution Time \n" << std::endl; // screen message
    
    utils.generate_descending_order_array(C, SIZE); // descending order array

    // 1. Calculate the time for Array C using correct selection sort
    utils.copy_array(temp_array, C, SIZE); // copy array C to temp_array
    time = t.calculate_css_time(temp_array, SIZE);
    std::cout <<"1. Correct Selection Sort took "<< time << " time to sort Descending Order Array C" << std::endl; // print execution time
    
    // write data to DataModel array
    data[8].task = 3;
    data[8].algorithm_name = "Correct Selection Sort";
    data[8].array_size = SIZE;
    data[8].array_type = "sorted-desc";
    data[8].average_time_taken = time;
    
    // 2. Calculate the time for Array C using wrong selection sort
    utils.copy_array(temp_array, C, SIZE); // copy array C to temp_array
    time = t.calculate_wss_time(temp_array, SIZE);
    std::cout <<"2. Wrong Selection Sort took "<< time << " time to sort Descending Order Array C" << std::endl; // print execution time

    // write data to DataModel array
    data[9].task = 3;
    data[9].algorithm_name = "Wrong Selection Sort";
    data[9].array_size = SIZE;
    data[9].array_type = "sorted-desc";
    data[9].average_time_taken = time;

    // 3. Calculate the time for Array C using bubble sort
    utils.copy_array(temp_array, C, SIZE); // copy array C to temp_array
    time = t.calculate_bs_time(temp_array, SIZE);
    std::cout <<"2. Bubble Sort took "<< time << " time to sort Descending Order Array C" << std::endl; // print execution time

    // write data to DataModel array
    data[10].task = 3;
    data[10].algorithm_name = "Bubble Sort";
    data[10].array_size = SIZE;
    data[10].array_type = "sorted-desc";
    data[10].average_time_taken = time;

    // 4. Calculate the time for Array C using Insertion selection sort
    utils.copy_array(temp_array, C, SIZE); // copy array C to temp_array
    time = t.calculate_is_time(temp_array, SIZE);
    std::cout <<"3. Insertion Sort took "<< time << " time to sort Descending Order Array C" << std::endl; // print execution time

    // write data to DataModel array
    data[11].task = 3;
    data[11].algorithm_name = "Insertion Sort";
    data[11].array_size = SIZE;
    data[11].array_type = "sorted-desc";
    data[11].average_time_taken = time;



    // Task 4. Instead of getting results for a single run, repeat the experiments 10 times (each time with different numbers in the arrays) and take the average time of 10 runs

    double css_avg_time = 0.0;
    double wss_avg_time = 0.0;
    double bs_avg_time = 0.0;
    double is_avg_time = 0.0;

    for (int i = 0; i < 10; ++i){

        utils.generate_random_array(A, SIZE); // each time generate a random number array

        // 1. Calculate the time for Array A using correct selection sort
        utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
        css_avg_time += time; // Average
        // std::cout <<"1. Correct Selection Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time

        // 2. Calculate the time for Array A using wrong selection sort
        utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
        time = t.calculate_wss_time(temp_array, SIZE);
        wss_avg_time += time; // Average
        // std::cout <<"2. Wrong Selection Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time

        // 3. Calculate the time for Array A using bubble sort
        utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
        time = t.calculate_bs_time(temp_array, SIZE);
        bs_avg_time += time; // Average
        // std::cout <<"3. Bubble Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time
        
        // 4. Calculate the time for Array A using insertion sort
        utils.copy_array(temp_array, A, SIZE); // copy array A to temp_array
        time = t.calculate_is_time(temp_array, SIZE);
        is_avg_time += time; // Average
        // std::cout <<"4. Insertion Sort took "<< time << " time to sort  Random Array A" << std::endl; // print execution time
    }
    
    std::cout << "\n\tAverage time of 10 runs \n" << std::endl; // screen message

    double correct_selection_sort_average = css_avg_time / 10;
    // write data to DataModel array
    data[12].task = 4;
    data[12].algorithm_name = "Correct Selection Sort";
    data[12].array_size = SIZE;
    data[12].array_type = "random";
    data[12].average_time_taken = correct_selection_sort_average;

    double wrong_selection_sort_average = wss_avg_time / 10;
    // write data to DataModel array
    data[13].task = 4;
    data[13].algorithm_name = "Wrong Selection Sort";
    data[13].array_size = SIZE;
    data[13].array_type = "random";
    data[13].average_time_taken = wrong_selection_sort_average;

    double bubble_sort_average = bs_avg_time / 10;
    // write data to DataModel array
    data[14].task = 4;
    data[14].algorithm_name = "Bubble Sort";
    data[14].array_size = SIZE;
    data[14].array_type = "random";
    data[14].average_time_taken = bubble_sort_average;

    double insertion_sort_average = is_avg_time / 10;
    // write data to DataModel array
    data[15].task = 4;
    data[15].algorithm_name = "Insertion Sort";
    data[15].array_size = SIZE;
    data[15].array_type = "random";
    data[15].average_time_taken = insertion_sort_average;
    
    std::cout << "Average time for Correct Selection Sort: " << correct_selection_sort_average << std::endl;
    std::cout << "Average time for Wrong Selection Sort: " << wrong_selection_sort_average << std::endl;
    std::cout << "Average time for Bubble Sort: " << bubble_sort_average << std::endl;
    std::cout << "Average time for Insertion Sort: " << insertion_sort_average << std::endl;


    // generate a csv file data
    utils.generate_csv_file(data, 16);

    return 0;
}
