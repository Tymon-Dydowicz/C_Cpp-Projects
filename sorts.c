#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int arr[1500000];
int count[1500000];
int output[1500000];

void MakeArray1(int arr[], int len) {
    for (int i=0; i < len; i++){
        arr[i] = rand();
    }
}

void MakeArray2(int arr[], int len) {
    for (int i=0; i < len; i++){
        arr[i] = rand() % len;
    }
}

void MakeArrayAsc(int arr[], int len) {
    for (int i=0; i<len; i++) {
        arr[i] = i+1;
    }
}

void MakeArrayDes(int arr[], int len) {
    for (int i=0; i<len; i++) {
        arr[i] = len-i-1;
    }
}

void MakeArrayConst(int arr[], int len) {
    for (int i=0; i<len; i++) {
        arr[i] = 4;
    }
}

void MakeArrayA(int arr[], int len) {
    for (int i=0; i<len/2; i++){
        arr[i] = 2*i+1;
        arr[len-1-i] = 2*i; 
    }
}

void MakeArrayV(int arr[], int len) {
    for (int i=0; i<len/2; i++){
        arr[len/2-i-1] = 2*i+1;
        arr[len/2+i] = 2*i; 
    }
}

void swap(int *a, int *b){
    int e = *a;
    *a = *b;
    *b = e;
}

void Swap (int arr[], int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void PrintArray (int arr[], int size) {
    for (int i=0; i<size; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void BubbleSort (int arr[], int size) {
    for (int i=0; i<size; i++) {
        for (int j=0; j<size-i-1; j++){
            if (arr[j] > arr[j+1]) {
                Swap(arr, j, j+1);
            }
        }
    }
}

void SelectionSort (int arr[], int size) {
    for (int i=0; i<size; i++) {
        int mem = i;
        int min = arr[i];
        for(int j=i+1; j<size; j++){
            if (min > arr[j]) {
                mem = j;
                min = arr[j];
            }
        }
        Swap(arr, i, mem);
    }
}

void InsertionSort (int arr[], int size) {
    for (int i=1; i<size; i++) {
        int mem = arr[i];
        int idx = i;
        for (int j=i-1; j>=0; j--) {
            if (mem < arr[j]) {
                Swap(arr, j, idx--);
            }
        }
    }
}

void SortFam (int arr[], int size, int root) {
    int max = root;
    int left = (2*root)+1;
    int right = (2*root)+2;
    if (left < size && arr[left] > arr[max]) {
        max = left;
    }
    if (right < size && arr[right] > arr[max]) {
        max = right;
    }

    if (max != root) {
        Swap(arr, root, max);
        SortFam(arr, size, max);
    }
}

void HeapSort (int arr[], int size, int root) {
    for (int i = (size/2)-1; i >= 0; i--) {
        SortFam(arr, size, i);
    }

    for (int i = size-1; i >= 0; i--) {
        Swap(arr, 0, i);
        SortFam(arr, i, 0);
    }
}

void QuickSort (int arr[], int start, int end) {
    int i, j, pivot, temp;
    if(start<end){
      pivot=start;
      i=start;
      j=end;
      while(i<j){
         while(arr[i]<=arr[pivot]&&i<end)
         i++;
         while(arr[j]>arr[pivot])
         j--;
         if(i<j){
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
         }
      }
      temp=arr[pivot];
      arr[pivot]=arr[j];
      arr[j]=temp;
      QuickSort(arr,start,j-1);
      QuickSort(arr,j+1,end);
    }
}

int partition(int array[], int low, int high) {
    swap(&arr[(low + high + 1) / 2], &arr[high]);
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort_A_V(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort_A_V(array, low, pi - 1);
    quickSort_A_V(array, pi + 1, high);
  }
}

void ShellSort (int arr[], int size) {
    for (int interval = size / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < size; i += 1) {
      int temp = arr[i];
      int j;
      for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
        arr[j] = arr[j - interval];
      }
      arr[j] = temp;
    }
  }
}

void CountingSort (int arr[], int size) {

    int max = arr[0];
    for (int i = 1; i < size; i++) {
      if (arr[i] > max)
        max = arr[i];
    }


    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void merge(int arr[], int p, int q, int r) {


  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = p;


  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void MergeSort(int arr[], int l, int r) {
  if (l < r) {


    int m = l + (r - l) / 2;

    MergeSort(arr, l, m);
    MergeSort(arr, m + 1, r);


    merge(arr, l, m, r);
  }
}

int main() {
    srand(time(NULL));

    for (int i = 1; i <= 1; i++) {
        int size = 20000*15
        *i;
        MakeArrayV(arr, size);


        clock_t start, end;
        float time;
        start = clock();

        //InsertionSort(arr, size); //OK
        //BubbleSort(arr, size); //OK
        //SelectionSort(arr, size); //OK
        QuickSort(arr, 0, size-1); //OK
        //quickSort_A_V(arr, 0, size-1);
        //ShellSort(arr, size); //OK
        //HeapSort(arr, size, 0); //OK
        //CountingSort(arr, size);
        //MergeSort(arr, 0, size-1);


        end = clock();
        time =  (double) (end - start) / CLOCKS_PER_SEC;
        fprintf(data, "%f \n", time);
        fprintf(data, "Time taken %f s and the number of elements is %i \n", time, size);
    }
    fprintf(data, "\n");
    fclose(data);

    return 0;
}