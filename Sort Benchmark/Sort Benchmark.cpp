#include <iostream>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void bubbleSort(int *A, int n);

void maxHeapify(int *A, int i, int n);
void buildMaxHeap(int *A, int n);
void heapSort(int *A, int n);

void insertionSort(int *A, int n);

void merge(int *A, int p, int q, int r);
void mergeSort(int *A, int p, int r);

int partition(int *A, int p, int r);
void quickSort(int *A, int p, int r);

void selectionSort(int *A, int n);

int main() {

	int number = 10000;
	clock_t bubbleSortTime, heapSortTime, insertionSortTime, mergeSortTime, quickSortTime, selectionSortTime;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, 1000);

	int *numbers = (int *)calloc(number, sizeof(int));
	int *temp = (int *)calloc(number, sizeof(int));

	for (int i = 0; i < number; i++) {
		*(numbers + i) = dist(gen);
	}

	//Bubble Sort
	for (int i = 0; i < number; i++) {
		*(temp + i) = *(numbers + i);
	}
	bubbleSortTime = clock();
	bubbleSort(temp, number);
	bubbleSortTime = clock() - bubbleSortTime;
	cout << "BBL Sort : " << bubbleSortTime << endl;

	//Heap Sort
	for (int i = 0; i < number; i++) {
		*(temp + i) = *(numbers + i);
	}
	heapSortTime = clock();
	heapSort(temp, (number - 1));
	heapSortTime = clock() - heapSortTime;
	cout << "HEP Sort : " << heapSortTime << endl;

	//Insertion Sort
	for (int i = 0; i < number; i++) {
		*(temp + i) = *(numbers + i);
	}
	insertionSortTime = clock();
	insertionSort(temp, number);
	insertionSortTime = clock() - insertionSortTime;
	cout << "INS Sort : " << insertionSortTime << endl;

	//Merge Sort
	for (int i = 0; i < number; i++) {
		*(temp + i) = *(numbers + i);
	}
	mergeSortTime = clock();
	mergeSort(temp, 0, (number - 1));
	mergeSortTime = clock() - mergeSortTime;
	cout << "MRG Sort : " << mergeSortTime << endl;

	//Quick Sort
	for (int i = 0; i < number; i++) {
		*(temp + i) = *(numbers + i);
	}
	quickSortTime = clock();
	quickSort(temp, 0, (number - 1));
	quickSortTime = clock() - quickSortTime;
	cout << "QCK Sort : " << quickSortTime << endl;

	//Selection Sort
	for (int i = 0; i < number; i++) {
		*(temp + i) = *(numbers + i);
	}
	selectionSortTime = clock();
	selectionSort(temp, number);
	selectionSortTime = clock() - selectionSortTime;
	cout << "SEL Sort : " << selectionSortTime << endl;
	
	return 0;
}

//Bubble Sort
void bubbleSort(int *A, int n) {
	bool isSwapped;
	int i, temp;
	do {
		isSwapped = false;
		for (i = 0; i < n; i++) {
			if (A[i - 1] > A[i]) {
				temp = A[i - 1];
				A[i - 1] = A[i];
				A[i] = temp;
				isSwapped = true;
			}
		}
	} while (isSwapped);
}

//Heap Sort
void maxHeapify(int *A, int i, int n) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest;
	if (left <= n && *(A + left) > *(A + i)) {
		largest = left;
	}
	else {
		largest = i;
	}

	if (right <= n && *(A + right) > *(A + largest)) {
		largest = right;
	}

	if (largest != i) {
		swap(*(A + i), *(A + largest));
		maxHeapify(A, largest, n);
	}
}
void buildMaxHeap(int *A, int n) {
	for (int i = n / 2; i >= 0; i--) {
		maxHeapify(A, i, n);
	}
}
void heapSort(int *A, int n) {
	int length = n;
	buildMaxHeap(A, n);
	for (int i = length; i > 0; i--) {
		swap(*(A), *(A + i));
		n--;
		maxHeapify(A, 0, n);
	}
}

//Insertion Sort
void insertionSort(int *A, int n) {
	int i, j, key;
	for (j = 1; j < n; j++) {
		key = A[j];
		i = j - 1;
		while (i >= 0 && A[i]>key) {
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

//Merge Sort
void merge(int *A, int p, int q, int r) {
	int i, j;
	int m = q - p + 1;
	int n = r - q;

	int *left = (int *)calloc(m+1, sizeof(int));
	int *right = (int *)calloc(n+1, sizeof(int));

	for (i = 0; i < m; i++) {
		*(left + i) = *(A + (p + i));
	}
	for (j = 0; j < n; j++) {
		*(right + j) = *(A + (q + j + 1));
	}

	*(left + m) = INT_MAX;
	*(right + n) = INT_MAX;

	i = j = 0;

	for (int k = p; k <= r; k++) {
		if (*(left + i) <= *(right + j)) {
			*(A + k) = *(left + i);
			i++;
		}
		else {
			*(A + k) = *(right + j);
			j++;
		}
	}
}
void mergeSort(int *A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, (q + 1), r);
		merge(A, p, q, r);
	}
}

//Quick Sort
int partition(int *A, int p, int r) {
	int x = *(A + r);
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (*(A + j) <= x) {
			i++;
			swap(*(A + i), *(A + j));
		}
	}
	swap(*(A + (i + 1)), *(A + r));
	return i + 1;
}
void quickSort(int *A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quickSort(A, p, (q - 1));
		quickSort(A, (q + 1), r);
	}
}

//Selection Sort
void selectionSort(int *A, int n) {
	int i, j, indexOfMinimum, temp;
	for (i = 0; i < (n - 1); i++) {
		indexOfMinimum = i;
		for (j = (i + 1); j < n; j++) {
			if (A[j] < A[indexOfMinimum]) {
				indexOfMinimum = j;
			}
		}
		temp = A[i];
		A[i] = A[indexOfMinimum];
		A[indexOfMinimum] = temp;
	}
}