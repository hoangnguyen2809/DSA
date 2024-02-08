#include<iostream>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;

std::vector<std::vector<int>> matrixMultiply(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << std::setw(8) << value << " ";
        }
        std::cout << std::endl;
    }
}


// Function to add two matrices
std::vector<std::vector<int>> addMatrix(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));  // Resize C to match the dimensions of A and B

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Function to subtract two matrices
std::vector<std::vector<int>> subtractMatrix(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
   int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));  // Resize C to match the dimensions of A and B

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}


std::vector<std::vector<int>> strassen_matrix_multiply(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B)
{
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;

    std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> C11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C22(newSize, std::vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // std::cout << "Matrix A11:\n";
    // printMatrix(A11);

    // std::cout << "Matrix A12:\n";
    // printMatrix(A12);

    // std::cout << "Matrix A21:\n";
    // printMatrix(A21);

    // std::cout << "Matrix A22:\n";
    // printMatrix(A22);

    // std::cout << "Matrix B11:\n";
    // printMatrix(B11);

    // std::cout << "Matrix B12:\n";
    // printMatrix(B12);

    // std::cout << "Matrix B21:\n";
    // printMatrix(B21);

    // std::cout << "Matrix B22:\n";
    // printMatrix(B22);


    std::vector<std::vector<int>> P1(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P2(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P3(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P4(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P5(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P6(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P7(newSize, std::vector<int>(newSize));

    P1 = strassen_matrix_multiply(A11, subtractMatrix(B12, B22));
    P2 = strassen_matrix_multiply(addMatrix(A11, A12), B22);
    P3 = strassen_matrix_multiply(addMatrix(A21, A22), B11);
    P4 = strassen_matrix_multiply(A22, subtractMatrix(B21, B11));
    P5 = strassen_matrix_multiply(addMatrix(A11, A22), addMatrix(B11, B22));
    P6 = strassen_matrix_multiply(subtractMatrix(A12, A22), addMatrix(B21, B22));
    P7 = strassen_matrix_multiply(subtractMatrix(A11, A21), addMatrix(B11, B12));

    C11 = addMatrix(subtractMatrix(addMatrix(P5, P4), P2), P6);
    C12 = addMatrix(P1, P2 );
    C21 = addMatrix(P3, P4);
    C22 = subtractMatrix(subtractMatrix(addMatrix(P5, P1), P3), P7);

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;

}

void print(string display, vector<vector<int> > matrix,
		int start_row, int start_column, int end_row,
		int end_column)
{
	cout << endl << display << " =>" << endl;
	for (int i = start_row; i <= end_row; i++) {
		for (int j = start_column; j <= end_column; j++) {
			cout << setw(10);
			cout << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void add_matrix(vector<vector<int> > matrix_A,
				vector<vector<int> > matrix_B,
				vector<vector<int> >& matrix_C,
				int split_index)
{
	for (auto i = 0; i < split_index; i++)
		for (auto j = 0; j < split_index; j++)
			matrix_C[i][j]
				= matrix_A[i][j] + matrix_B[i][j];
}

vector<vector<int> >
multiply_matrix(vector<vector<int> > matrix_A,
				vector<vector<int> > matrix_B)
{
	int col_1 = matrix_A[0].size();
	int row_1 = matrix_A.size();
	int col_2 = matrix_B[0].size();
	int row_2 = matrix_B.size();

	if (col_1 != row_2) {
		cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return {};
	}

	vector<int> result_matrix_row(col_2, 0);
	vector<vector<int> > result_matrix(row_1,
									result_matrix_row);

	if (col_1 == 1)
		result_matrix[0][0]
			= matrix_A[0][0] * matrix_B[0][0];
	else {
		int split_index = col_1 / 2;

		vector<int> row_vector(split_index, 0);
		vector<vector<int> > result_matrix_00(split_index,
											row_vector);
		vector<vector<int> > result_matrix_01(split_index,
											row_vector);
		vector<vector<int> > result_matrix_10(split_index,
											row_vector);
		vector<vector<int> > result_matrix_11(split_index,
											row_vector);

		vector<vector<int> > a00(split_index, row_vector);
		vector<vector<int> > a01(split_index, row_vector);
		vector<vector<int> > a10(split_index, row_vector);
		vector<vector<int> > a11(split_index, row_vector);
		vector<vector<int> > b00(split_index, row_vector);
		vector<vector<int> > b01(split_index, row_vector);
		vector<vector<int> > b10(split_index, row_vector);
		vector<vector<int> > b11(split_index, row_vector);

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				a00[i][j] = matrix_A[i][j];
				a01[i][j] = matrix_A[i][j + split_index];
				a10[i][j] = matrix_A[split_index + i][j];
				a11[i][j] = matrix_A[i + split_index]
									[j + split_index];
				b00[i][j] = matrix_B[i][j];
				b01[i][j] = matrix_B[i][j + split_index];
				b10[i][j] = matrix_B[split_index + i][j];
				b11[i][j] = matrix_B[i + split_index]
									[j + split_index];
			}

		add_matrix(multiply_matrix(a00, b00),
				multiply_matrix(a01, b10),
				result_matrix_00, split_index);
		add_matrix(multiply_matrix(a00, b01),
				multiply_matrix(a01, b11),
				result_matrix_01, split_index);
		add_matrix(multiply_matrix(a10, b00),
				multiply_matrix(a11, b10),
				result_matrix_10, split_index);
		add_matrix(multiply_matrix(a10, b01),
				multiply_matrix(a11, b11),
				result_matrix_11, split_index);

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				result_matrix[i][j]
					= result_matrix_00[i][j];
				result_matrix[i][j + split_index]
					= result_matrix_01[i][j];
				result_matrix[split_index + i][j]
					= result_matrix_10[i][j];
				result_matrix[i + split_index]
							[j + split_index]
					= result_matrix_11[i][j];
			}

		result_matrix_00.clear();
		result_matrix_01.clear();
		result_matrix_10.clear();
		result_matrix_11.clear();
		a00.clear();
		a01.clear();
		a10.clear();
		a11.clear();
		b00.clear();
		b01.clear();
		b10.clear();
		b11.clear();
	}
	return result_matrix;
}

int main() 
{
    int n = 512;

    std::vector<std::vector<int>> A(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> B(n, std::vector<int>(n, 0));

    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Fill matrices A and B with random integers
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = (rand() % 10) + 1;  // No need to divide by RAND_MAX if you want integers
            B[i][j] = (rand() % 10) + 1;
        }
    }

    // Print matrix A
    // std::cout << "Matrix A:\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         std::cout << std::setw(8) << A[i][j] << " ";  // Adjust width as needed
    //     }
    //     std::cout << std::endl;
    // }

    // Print matrix B
    // std::cout << "Matrix B" << std:: endl;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         std::cout << std::setw(8) << B[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> C = multiply_matrix(A, B);
    auto end_time = std::chrono::high_resolution_clock::now() ;

    // Print matrix 
    std::cout << "Using strassen, A * B = " << std::endl;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         std::cout << std::setw(15) << C[i][j] << " ";
    //     }
    //     std::cout << std::endl; 
    // }   

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Matrix multiplication took " << duration << " microseconds." << std::endl;



    auto start_time1 = std::chrono::high_resolution_clock::now();
    C = matrixMultiply(A, B);
    auto end_time1 = std::chrono::high_resolution_clock::now() ;

    //Print matrix 
    std::cout << "Using normal mm, A * B = " << std::endl;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         std::cout << std::setw(15) << C[i][j] << " ";
    //     }
    //     std::cout << std::endl; 
    // }   

    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end_time1 - start_time1).count();
    std::cout << "Matrix multiplication took " << duration1 << " microseconds." << std::endl;
    return 0;
}