#include "sorting.h" 
#include <string>
#include "iostream"
#include <ctime>
#include <cstdlib>
using namespace std;

/*
 * Title: Sorting and Algorithm Efficiency
 * Author: Alperen Can 
 * ID: 21601740
 * Section: 1
 * Assignment: 1
 * Description: Implementations of sorting algorithms.
 */

const int MAX_SIZE = 100000;

void insertionSort(int *arr, const int size, int &compCount, int &moveCount){
   compCount = 0;
   moveCount = 0;
   for(int j = 1; j < size; j++){
      int key = arr[j];
      moveCount++;
      int i = j - 1;
      while(i >= 0 && arr[i] > key){
         arr[i + 1] = arr[i];
         i--;
         compCount++;
         moveCount++;
      }
      if(i >= 0)
         compCount++;
      arr[i + 1] = key;
      moveCount++;
   }
}

void swap(int *arr, int index1, int index2){
    int element1 = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = element1;
}

void bubbleSort(int *arr, const int size, int &compCount, int &moveCount){
   bool sorted = false;
   compCount = 0;
   moveCount = 0;
   for (int pass = 1; pass < size && !sorted; pass++) {  
      sorted = true; 
      for (int index = 0; index < size - pass; index++) {
         int nextIndex = index + 1;
         if (arr[index] > arr[nextIndex]) {  
            swap(arr, index, nextIndex);
            moveCount += 3;
            sorted = false; 
         }
         compCount++;
      }
   }
}

void merge(int *arr, int &compCount, int &moveCount, int first, int mid, int last) {
	int *tempArray = new int[last - first + 1]; 	   // temporary array
	int first1 = first; 	                  // beginning of first subarray
   int last1 = mid; 		                  // end of first subarray
   int first2 = mid + 1;	               // beginning of second subarray
   int last2 = last;		                  // end of second subarray
   int index = 0;                         // next available location in tempArray

   for ( ; (first1 <= last1) && (first2 <= last2); index++) {
      if (arr[first1] < arr[first2]) {  
         tempArray[index] = arr[first1];
         first1++;
      }
      else {  
          tempArray[index] = arr[first2];
          first2++;
      }
      compCount++;
      moveCount++;
   }
   // finish off the first subarray, if necessary
   for (; first1 <= last1; first1++, index++){
      tempArray[index] = arr[first1];
      moveCount++;
   }

   // finish off the second subarray, if necessary
   for (; first2 <= last2; first2++, index++){
      tempArray[index] = arr[first2];
      moveCount++;
   }

   // copy the result back into the original array
   for (index = 0; index <= last - first; index++){
      arr[index + first] = tempArray[index];
      moveCount++;
   }
   delete[] tempArray;
} 

void mergeSortHelper(int *arr, int &compCount, int &moveCount, int first, int last){
    if (first < last) {
      int mid = (int) ((first + last) / 2); 	// index of midpoint
      mergeSortHelper(arr, compCount, moveCount, first, mid);
      mergeSortHelper(arr, compCount, moveCount, mid + 1, last);
      // merge the two halves
      merge(arr, compCount, moveCount, first, mid, last);
   }
}

void mergeSort(int *arr, const int size, int &compCount, int &moveCount){
   compCount = 0;
   moveCount = 0;
   mergeSortHelper(arr, compCount, moveCount, 0, size - 1);
}

void partition(int *arr, int &compCount, int &moveCount, int first, int last, int &pivotIndex) {
   int pivot = arr[first];          // copy pivot
   moveCount++;
   int lastS1 = first;              // index of last item in S1
   int firstUnknown = first + 1;    // index of first item in unknown
   
	// move one item at a time until unknown region is empty
   for (  ; firstUnknown <= last; firstUnknown++) {
      // move item from unknown to proper region
      compCount++;
      if (arr[firstUnknown] < pivot) {  	// belongs to S1
		  lastS1++;
    	  swap(arr, firstUnknown, lastS1);
        moveCount += 3;
      }	// else belongs to S2
   }

   // place pivot in proper position and mark its location
   if(first != lastS1){
      swap(arr, first, lastS1);
      moveCount += 3;
   }
   pivotIndex = lastS1;
}

void quickSortHelper(int *arr, int &compCount, int &moveCount, int first, int last){
   int pivotIndex = first;
   if (first < last) {

      // create the partition: S1, pivot, S2
      partition(arr, compCount, moveCount, first, last, pivotIndex);

      // sort regions S1 and S2
      quickSortHelper(arr, compCount, moveCount, first, pivotIndex - 1);
      quickSortHelper(arr, compCount, moveCount, pivotIndex + 1, last);
   }
}

void quickSort(int *arr, const int size, int &compCount, int &moveCount){
   compCount = 0;
   moveCount = 0;
   quickSortHelper(arr, compCount, moveCount, 0, size - 1);
}

void displayArray(const int *arr, const int size){
   string arrString = "[";
   for(int i = 0; i < size - 1; i++){
      arrString += to_string(arr[i]);
      arrString += ",";
   }
   if(size > 0){
      arrString += to_string(arr[size - 1]);
      arrString += "]\n";
   }
   cout << arrString;
}

void initializeArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size){
   arr1 = new int[size];
   arr2 = new int[size];
   arr3 = new int[size];
   arr4 = new int[size];
}

void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size){
   srand((unsigned) time(0));
   initializeArrays(arr1, arr2, arr3, arr4, size);
   for(int i = 0; i < size; i++){
      int randomNumber = rand();
      arr1[i] = randomNumber;
      arr2[i] = randomNumber;
      arr3[i] = randomNumber;
      arr4[i] = randomNumber;
   }
}

void pertubArray(int *arr, const int size){
   int pertubCount = size / 20;
   srand((unsigned) time(0));
   for(int i = 0; i < pertubCount; i++){
      int randomIndex1 =  rand() % size;
      int randomIndex2 =  rand() % size;
      swap(arr, randomIndex1, randomIndex2);
   }
}

void createAnAlmostSortedArray(int *arr, const int size){
   for(int i = 0; i < size; i++){
      arr[i] = i;
   }
   pertubArray(arr, size);
}

void createAnAlmostUnsortedArray(int *arr, const int size){
   int n = size;
   for(int i = 0; i < size; i++){
      n--;
      arr[i] = n;
   }
   pertubArray(arr, size);
}

void copyFirstArrayToOthers(int *arr1, int *arr2, int *arr3, int *arr4, const int size){
   for(int i = 0; i < size; i++){
      arr2[i] = arr1[i]; 
      arr3[i] = arr1[i]; 
      arr4[i] = arr1[i]; 
   }
}

void createAlmostSortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size){
   initializeArrays(arr1, arr2, arr3, arr4, size);
   createAnAlmostSortedArray(arr1, size);
   copyFirstArrayToOthers(arr1, arr2, arr3, arr4, size);
}

void createAlmostUnsortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size){
   initializeArrays(arr1, arr2, arr3, arr4, size);
   createAnAlmostUnsortedArray(arr1, size);
   copyFirstArrayToOthers(arr1, arr2, arr3, arr4, size);
}