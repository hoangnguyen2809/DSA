#include<iostream>
#include<vector>
#include <limits.h>
#include<ctime>
#include<chrono>
#include <thread>

using namespace std;


int cutRod (int price[], int n)
{
    if (n == 0) return 0;
    
    int q = INT_MIN; 
    for (int i = 1; i <= n; ++i) {
        q = max(q, price[i] + cutRod(price, n - i));
    }
    return q;
}

int memoized_cutRodAux(int price[], int n, vector<int>& r) {
    if (r[n] >= 0) return r[n];
    
    int q;
    if (n == 0) {
        q = 0;
    } 
    else 
    {
        q = INT_MIN;
    }

    for (int i = 1; i <= n; ++i) {
        q = max(q, price[i] + memoized_cutRodAux(price, n - i, r));
    }
    
    r[n] = q;
    return q;
}

int memoized_cutRod(int price[], int n)
{
    vector<int> r(n + 1, INT_MIN); 
    return memoized_cutRodAux(price, n, r);
}



int main()
{
    int arr[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30, 
                    35, 37, 40, 43, 47, 52, 56, 58, 60, 66,
                    69, 73, 77 ,85, 90, 93, 95, 96, 102, 106 };
    int size = 30;
    

    
    auto start_time = std::chrono::high_resolution_clock::now();
    int result = memoized_cutRod(arr, size);
    auto end_time = std::chrono::high_resolution_clock::now();
    cout << "Maximum Obtainable Value is " << result;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "\nCut rod performed in " << duration << " microseconds." << std::endl;
    return 0;
}