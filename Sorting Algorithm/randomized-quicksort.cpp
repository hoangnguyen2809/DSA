#include<iostream>
#include<vector>
#include<ctime>
#include<chrono>
#include<cmath>

int partition(std::vector<int>& A, int l, int r)
{
    int x = A[r];
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

int randomized_partition(std::vector<int>& A, int l, int r)
{
    int i = std::rand() % (r - l + 1) + l;
    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;
    return partition(A, l, r);
}

void randomized_quicksort(std::vector<int>& A, int l, int r)
{
    if (l < r)
    {
        int q = randomized_partition(A, l, r);
        randomized_quicksort(A, l, q - 1);
        randomized_quicksort(A, q + 1, r);
    }
}

void print_array(std::vector<int>& A)
{
    for (auto i : A){
        std::cout << i << " ";
    }
}

void insertion_sort(std::vector<int>& A)
{
    for (int i = 1; i < A.size(); i++)
    {
        int temp = A[i];
        int j = i-1;
        while (j>= 0 && A[j] > temp)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = temp;
    }
}

void randomized_quicksort_variant(std::vector<int>& A, int l, int r, int k)
{
    if (l < r)
    {
        if (r - l + 1 <= k)
        {
            insertion_sort(A);
        }
        else
        {
            int q = randomized_partition(A, l, r);
            randomized_quicksort_variant(A, l, q - 1, k);
            randomized_quicksort_variant(A, q + 1, r, k);
        }
    }

    if (l == 0 && r == A.size() - 1)  // Corrected condition
    {
        insertion_sort(A);
    }
}



int main() {
    std::srand(std::time(nullptr)); // Seed the random number generator

    std::vector<int> test_array;
    int i;
    while (true) {
        std::cout << "Enter i: ";
        std::cin >> i;
        if (i == -1)
            break;

        int n = std::pow(2, i) * 1000;
        test_array.clear(); // Clear the test array before generating a new one
        for (int j = 0; j < n; j++) {
            int randomNumber = std::rand() % 101; // Generate random number between 0 and 100
            test_array.push_back(randomNumber);
        }

        std::cout << "Test array: ";
        print_array(test_array);

        // auto start_time = std::chrono::high_resolution_clock::now();
        // randomized_quicksort(test_array, 0, n - 1);
        // auto end_time = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        // std::cout << "\nRandomized quicksort variant performed in " << duration << " microseconds." << std::endl;

        auto start_time = std::chrono::high_resolution_clock::now();
        randomized_quicksort_variant(test_array, 0, n - 1, 2);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        std::cout << "\nRandomized quicksort variant performed in " << duration << " microseconds." << std::endl;
    }

    return 0;
}
