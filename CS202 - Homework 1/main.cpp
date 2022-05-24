#include "sorting.h"
#include "iostream"
#include <stdio.h>
#include <chrono>
using namespace std;

/*
 * Title: Sorting and Algorithm Efficiency
 * Author: Alperen Can
 * ID: 21601740
 * Section: 1
 * Assignment: 1
 * Description: This program compares sorting algorithms by move and comparison counts.
 */

void displayCompMoveCountsAndArray(int *arr, const int size, int compCount, int moveCount){
  printf("Comparison Count: %d\n", compCount);
  printf("Move Count: %d\n", moveCount);
  displayArray(arr, size);
}

void print(int *compCount, int *moveCount, int *elapsedTime, int count, int interval){
  printf("Array Size\tElapsed time\t\tcompCount\t\tmoveCount\n");
  for(int i = 0; i < count; i++){
    printf("%d\t\t", interval * (i + 1));
    printf("%d ms\t\t", elapsedTime[i]);
    printf("%d\t\t", compCount[i]);
    printf("%d\n", moveCount[i]);
  }
}

void printResults(int *compCount, int *moveCount, int *elapsedTime, int count, int interval){
    printf("-----------------------------------------------------\n");
    printf("Analysis of Insertion Sort\n");
    print(compCount, moveCount, elapsedTime, count, interval);
    printf("-----------------------------------------------------\n");
    printf("Analysis of Bubble Sort\n");
    print(&compCount[count], &moveCount[count], &elapsedTime[count], count, interval);
    printf("-----------------------------------------------------\n");
    printf("Analysis of Merge Sort\n");
    print(&compCount[count * 2], &moveCount[count * 2], &elapsedTime[count * 2], count, interval);
    printf("-----------------------------------------------------\n");
    printf("Analysis of Quick Sort\n");
    print(&compCount[count * 3], &moveCount[count * 3], &elapsedTime[count * 3], count, interval);
}

void createArray(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size, const int scenario){
  switch(scenario){
    case 0:
      createRandomArrays(arr1, arr2, arr3, arr4, size);
      break;
    case 1:
      createAlmostSortedArrays(arr1, arr2, arr3, arr4, size);
      break;
    case 2:
      createAlmostUnsortedArrays(arr1, arr2, arr3, arr4, size);
      break;

  }
}

void printScenario(const int scenario){
  switch(scenario){
    case 0:
      printf("Analysis of Random Array Scenario\n");
      break;
    case 1:
      printf("Analysis of Almost Sorted Array Scenario\n");
      break;
    case 2:
      printf("Analysis of Almost Unsorted Array Scenario\n");
      break;
  }
}

void performanceAnalysis(){
  static const int RESULT_COUNT = 8;
  static const int INTERVAL = 5000;
  static const int SCENARIO_COUNT = 3;
  int compCountResults[RESULT_COUNT * 4];
  int moveCountResults[RESULT_COUNT * 4];
  int elapsedTimeResults[RESULT_COUNT * 4];
  int *arr1, *arr2, *arr3, *arr4;

  for(int scenario = 0; scenario < SCENARIO_COUNT; scenario++){
    printf("\n--------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------\n");
    printScenario(scenario);
    for(int i = 0; i < RESULT_COUNT; i++){
      int size = (i + 1) * INTERVAL;
      createArray(arr1, arr2, arr3, arr4, size, scenario);
      chrono::steady_clock::time_point start = chrono::steady_clock::now();
      insertionSort(arr1, size, compCountResults[i], moveCountResults[i]);
      chrono::steady_clock::time_point end = chrono::steady_clock::now();
      int elapsedTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
      elapsedTimeResults[i] = elapsedTime;

      start = chrono::steady_clock::now();
      bubbleSort(arr2, size, compCountResults[i + RESULT_COUNT], moveCountResults[i + RESULT_COUNT]);
      end = chrono::steady_clock::now();
      elapsedTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
      elapsedTimeResults[i + RESULT_COUNT] = elapsedTime;

      start = chrono::steady_clock::now();
      mergeSort(arr3, size, compCountResults[i + RESULT_COUNT * 2], moveCountResults[i + RESULT_COUNT * 2]);
      end = chrono::steady_clock::now();
      elapsedTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
      elapsedTimeResults[i + RESULT_COUNT * 2] = elapsedTime;
      
      start = chrono::steady_clock::now();
      quickSort(arr4, size, compCountResults[i + RESULT_COUNT * 3], moveCountResults[i + RESULT_COUNT * 3]);
      end = chrono::steady_clock::now();
      elapsedTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
      elapsedTimeResults[i + RESULT_COUNT * 3] = elapsedTime;
      delete[] arr1;
      delete[] arr2;
      delete[] arr3;
      delete[] arr4;
    }
    printResults(compCountResults, moveCountResults, elapsedTimeResults, RESULT_COUNT, INTERVAL);
  }
}

int main() {
  int compCount;
  int moveCount;
  printf("------------------------Insertion Sort------------------------------\n");
  int arr1[] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
  const int size = sizeof(arr1) / sizeof(arr1[0]);
  insertionSort(arr1, size, compCount, moveCount);
  displayCompMoveCountsAndArray(arr1, size, compCount, moveCount);

  printf("------------------------Bubble Sort---------------------------------\n");
  int arr2[] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
  bubbleSort(arr2, size, compCount, moveCount);
  displayCompMoveCountsAndArray(arr2, size, compCount, moveCount);

  printf("------------------------Merge Sort----------------------------------\n");
  int arr3[] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
  mergeSort(arr3, size, compCount, moveCount);
  displayCompMoveCountsAndArray(arr3, size, compCount, moveCount);

  printf("------------------------Quick Sort----------------------------------\n");
  int arr4[] = {9, 6, 7, 16, 18, 5, 2, 12, 20, 1, 16, 17, 4, 11, 13, 8};
  quickSort(arr4, size, compCount, moveCount);
  displayCompMoveCountsAndArray(arr4, size, compCount, moveCount);

  performanceAnalysis();
}