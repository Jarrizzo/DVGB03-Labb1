#include "algorithm.h"

void bubble_sort(int* array, int lenght){
	for(int i = 0; i < lenght; i++){
		bool switchedCheck = false;
		for(int j = 0; j < lenght-i-1; j++){
			if(array[j] > array[j+1]){
				switchedCheck = true;
				int tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}
		if(!switchedCheck){
			return ;
		}
	}
}
void insertion_sort(int *array, int lenght){

	for(int i = 0; i < lenght; i++){
		int current = array[i];
		int j = i - 1;
		
		while(j >= 0 && array[j] > current){
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = current;
	}
}
static void swapFunction(int* const first, int* const second){
	int tmp = *first;
	*first = *second;
	*second = tmp;
}
static int partition(int array [],int start, int end ){

	int pivot = array[end]; 
	int i = start - 1;

	for(int j = start; j <= end -1; j++){
		if(array[j] < pivot){
			i++;
			int tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}
	swapFunction(&array[i+1],&array[end]);

	return (i+1);	
}
static void actualQuicksort(int array[],int start,int end){

	if(start < end){
		int pivot = partition(array,start,end);

		actualQuicksort(array, start, pivot - 1);
		actualQuicksort(array,pivot + 1,end);
	}


}
void quick_sort(int *array, int length){
	actualQuicksort(array,0,length-1);
}
bool linear_search(const int *array, int length, int value){
	for(int i = 0; i < length; i++){
		if(array[i] == value){
			return true;
		}
	}
		return false;
}
bool binary_search(const int* array, int length, int value){
	//pre: Sorted list
	int high = length-1;
	int low = 0;

	while(low <= high){
		int mid = (low + high) / 2;

		if(array[mid] > value){
			high = mid - 1;
		}
		else if(array[mid] < value){
			low = mid + 1;
		}
		else{
			return true;
		}
	}
	return false;
}
