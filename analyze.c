#include "analyze.h"
#include "algorithm.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//
// Private
//

//Warmupfunction that gets the processer running faster
static void warmup_process(){
    int uselessCounter = 0;
    for(int i = 0; i < WARMUP; i++){
        uselessCounter++;
    }
}
static void calculate_BigO_values(result_t *resultArray, int arraySize,double totalTime, double *big_O_notation, double *faster_O_notation,double *slower_O_notation,int i){

    if(resultArray[i].big_O_notation_t == O_one_t){
        *big_O_notation = totalTime / 1;
        *faster_O_notation = totalTime / log2(arraySize);
        *slower_O_notation = totalTime / arraySize;
        resultArray[i].slower_O_notation_t = O_n_t;
        resultArray[i].faster_O_notation_t = O_logn_t;
    }
    else if(resultArray[i].big_O_notation_t == O_n_t){
        *big_O_notation = totalTime / arraySize;
        *faster_O_notation = totalTime / log2(arraySize);
        *slower_O_notation = totalTime / (arraySize * log2(arraySize));    
        resultArray[i].slower_O_notation_t = O_nlogn_t;
        resultArray[i].faster_O_notation_t = O_logn_t;    
    }
    else if(resultArray[i].big_O_notation_t == O_n2_t){
        *big_O_notation = totalTime / pow(arraySize,2);
        *faster_O_notation = totalTime / (arraySize * log2(arraySize));
        *slower_O_notation = totalTime / pow(arraySize,3);    
        resultArray[i].slower_O_notation_t = O_n3_t;
        resultArray[i].faster_O_notation_t = O_nlogn_t;    
    }
    else if(resultArray[i].big_O_notation_t == O_logn_t){
        *big_O_notation = totalTime / log2(arraySize);
        *faster_O_notation = totalTime / 1;
        *slower_O_notation = totalTime / arraySize;    
        resultArray[i].slower_O_notation_t = O_n_t;
        resultArray[i].faster_O_notation_t = O_one_t;
    }
    else if(resultArray[i].big_O_notation_t == O_nlogn_t){
        *big_O_notation = totalTime / (arraySize * log2(arraySize));
        *faster_O_notation = totalTime / arraySize;
        *slower_O_notation = totalTime / pow(arraySize,2);    
        resultArray[i].slower_O_notation_t = O_n2_t;
        resultArray[i].faster_O_notation_t = O_n_t;
    }


}
//Fills the Array with integers depending on the current Case
static void fill_array(int *Array,algorithm_t algorithm,case_t Case,int arraySize){


    if(algorithm == quick_sort_t ){
        if(Case == worst_t){
            for(int i = 0; i < arraySize; i++){
                Array[i] = 5;
            }
        }
/*          else if(Case == best_t){
            for(int i = 1; i < arraySize + 1; i++){
                Array[i] = i;
            }
        } */ 
        else if(Case == average_t || Case == best_t){
            for(int i = 0; i < arraySize; i++){
                Array[i] = rand() % arraySize;
            }  
        }   
    }
    else if(Case == best_t){
        for(int i = 0; i < arraySize; i++){
            Array[i] = i;
        }   
    }
    else if(Case == worst_t){
        for(int i = 0; i < arraySize; i++){
            Array[i] = arraySize-i;
        }    
    }
    else if(Case == average_t){
        for(int i = 0; i < arraySize; i++){
            Array[i] = rand() % arraySize-1;
        }    
    }

}

//Chooses the element to search for in the array depending on what Case is chosen and returns that element
static int get_SearchElement(int *Array,int arraySize,algorithm_t algorithm, case_t Case){

    int element = 0;

    if(algorithm == linear_search_t){
        if(Case == best_t){
                element = 0;
        }
        else if(Case == worst_t){
            element = arraySize-1;
        }
        else if(Case == average_t){
            element = rand() % arraySize-1;
        }
        else{
            return -1;
        }
    }
    else if(algorithm == binary_search_t){
        if(Case == best_t){
            element = (arraySize - 1) / 2;
        }
        else if(Case == worst_t){
            element = 0;
        }
        else if(Case == average_t){
            element = rand() % arraySize-1;
        }
        else{
            return -1;
        }
    }
    return Array[element];
}

//Sets the pivotvalue to use for the quicksort function depending on the case to use
static void set_pivot_for_quicksort(int *Array,int arraySize, case_t Case){

    if(Case == worst_t){
        Array[0] = 0;
    }
    else if(Case == average_t || Case == best_t){
        Array[0] = rand() % arraySize;
    }
    /*else if(Case == best_t){
        Array[0] = rand() % arraySize + 1;
    } */
}

static double time_function_sort(void (*function)(), int *Array, int arraySize, algorithm_t algorithm, case_t Case,int itterations){
    struct timespec beginning,ending;
    double totalTime = 0;

    warmup_process();
    //Beginning timestamp

    for(int i = 0; i < itterations; i++){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&beginning);
        
        function(Array, arraySize);
        
        //Ending timestamp 
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ending);

        totalTime = totalTime + ((ending.tv_sec * BILLION + ending.tv_nsec) - (beginning.tv_sec * BILLION + beginning.tv_nsec));
        fill_array(Array,algorithm,Case,arraySize);
        if(algorithm == quick_sort_t)
            set_pivot_for_quicksort(Array,arraySize,Case);
    } 


   return totalTime / itterations;
}

//Function that times the search algorithms and returns the avrage time it took
static double time_function_search(bool (*function)(), int *Array, int arraySize, algorithm_t algorithm, case_t Case,int itterations){
    struct timespec beginning,ending;
    double totalTime = 0;
    int searchElement = searchElement = get_SearchElement(Array, arraySize, algorithm, Case);
    warmup_process();
    //Beginning timestamp
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&beginning);

    for(int i = 0; i < itterations; i++){
        function(Array, arraySize, searchElement);
    }

    //Ending timestamp 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&ending);
    totalTime = ((ending.tv_sec * BILLION + ending.tv_nsec) - (beginning.tv_sec * BILLION + beginning.tv_nsec)) / itterations;

   return totalTime;
}


bool isSorted(int *Array, int lenght){
    for(int i = 0; i < lenght-1;i++){
        if(Array[i] > Array[i+1]){
            return false;
        }
    }
    return true;
}

static void saveInformation(algorithm_t algorithm, case_t Case, int arraySize, int totalTime, result_t *resultArray,int i){
 double big_O_notation_value,faster_O_notation_value,slower_O_notation_value;
    calculate_BigO_values(resultArray,arraySize,totalTime,&big_O_notation_value,&faster_O_notation_value,&slower_O_notation_value, i);
    
    resultArray[i].time = totalTime;
    resultArray[i].size = arraySize;
    resultArray[i].big_O_notation_value = big_O_notation_value;
    resultArray[i].faster_O_notation_value = faster_O_notation_value;
    resultArray[i].slower_O_notation_value = slower_O_notation_value;

}


//
// Public
//

//This function is called by the ui and starts the correct algorithms timingfunctions
void benchmark(const algorithm_t algorithm, const case_t Case, result_t *resultArray, int RESULT_ROWS){
    double totalTime = 0;
    int arraySize = 0;
    srand(clock());

    for(int i = 0; i < RESULT_ROWS; i++){
        arraySize = SIZE_START * pow(2,i);
        int *Array = calloc(arraySize, sizeof(int));

        if(algorithm == linear_search_t || algorithm == binary_search_t){
            fill_array(Array,algorithm,best_t,arraySize);
        }
        else if(algorithm == insertion_sort_t || algorithm == quick_sort_t || algorithm == bubble_sort_t){
            fill_array(Array,algorithm,Case,arraySize);
        }

        if(algorithm == bubble_sort_t){
            totalTime = time_function_sort(&bubble_sort, Array, arraySize, algorithm, Case, BUBBLEITTERATIONS);
         if(Case == best_t)
                resultArray[i].big_O_notation_t = O_n_t;
            else if(Case == worst_t)
                resultArray[i].big_O_notation_t = O_n2_t;
            else if(Case == average_t)
                resultArray[i].big_O_notation_t = O_n2_t;
        }

        else if(algorithm == insertion_sort_t){
            totalTime = time_function_sort(&insertion_sort, Array, arraySize, algorithm, Case, INSERTIONITTERATIONS);
            if(Case == best_t)
                resultArray[i].big_O_notation_t = O_n_t;
            else if(Case == worst_t)
                resultArray[i].big_O_notation_t = O_n2_t;
            else if(Case == average_t)
                resultArray[i].big_O_notation_t = O_n2_t;
        }

        else if(algorithm == quick_sort_t){
            set_pivot_for_quicksort(Array,arraySize,Case);
            totalTime = time_function_sort(&quick_sort, Array, arraySize, algorithm, Case, QUICKITTERATIONS);
             if(Case == best_t)
                resultArray[i].big_O_notation_t = O_nlogn_t;
            else if(Case == worst_t)
                resultArray[i].big_O_notation_t = O_n2_t;
            else if(Case == average_t)
                resultArray[i].big_O_notation_t = O_nlogn_t;   
        }
        
        else if(algorithm == linear_search_t){
            totalTime = time_function_search(&linear_search, Array, arraySize, algorithm, Case, SEARCHITTERATIONS);
            if(Case == best_t)
                resultArray[i].big_O_notation_t = O_one_t;
            else if(Case == worst_t)
                resultArray[i].big_O_notation_t = O_n_t;
            else if(Case == average_t)
                resultArray[i].big_O_notation_t = O_n_t;
        }
        else if(algorithm == binary_search_t){
            if(!isSorted(Array,arraySize)){
                insertion_sort(Array,arraySize);
            }
            totalTime = time_function_search(&binary_search, Array, arraySize, algorithm, Case, SEARCHITTERATIONS);
            if(Case == best_t)
                resultArray[i].big_O_notation_t = O_one_t;
            else if(Case == worst_t)
                resultArray[i].big_O_notation_t = O_logn_t;
            else if(Case == average_t)
                resultArray[i].big_O_notation_t = O_logn_t;
        }
    free(Array);
    saveInformation(algorithm,Case,arraySize,totalTime,resultArray,i);

    }
}
