#include<iostream>
#include <vector>


void print_array(std::vector<int>& A)
{
    for (auto i : A){
        std::cout << i << " ";
    }
}

void insertionSort(std::vector<int> &arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i-1;
        while (j>=0 && arr[j] >= key)
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }
}

int main()
{
    std::vector<int> array{ 10,15,22,4, 20, 30 };
    insertionSort(array);
    print_array(array);

    return 0;
}