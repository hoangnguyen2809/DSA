#include<iostream>
#include <vector>


void print_array(std::vector<int>& A)
{
    for (auto i : A){
        std::cout << i << " ";
    }
}



void merge(std::vector<int>& A, int left, int mid, int right)
{
    int leftArrSize = mid - left +1;
    int rightArrSize = right - mid;

    std::vector<int> leftArr(leftArrSize);
    std::vector<int> rightArr(rightArrSize);

    for (int i = 0; i < leftArrSize; i++) {
        leftArr[i] = A[left + i];
    }

    for (int j = 0; j < rightArrSize; j++) {
        rightArr[j] = A[mid + 1 + j];
    }
    int i = 0, j = 0;

    for (int k = left; k <= right; k++)
    {
        if (leftArr[i] <= rightArr[j])
        {
            A[k] = leftArr[i];
            i++;
        }
        else
        {
            A[k] = rightArr[j];
            j++;
        }
    }
}

void mergeSort(std::vector<int>& A, int left, int right)
{
    if (left < right)
    {
        int p = (left+right)/2;
        mergeSort(A, left, p);
        mergeSort(A, p+1, right);
        merge(A, left, p, right);
    }
}

int main()
{
    std::vector<int> array{ 10,15,22,4, 20, 30 };
    mergeSort(array, 0, array.size()-1);
    print_array(array);

    return 0;
}