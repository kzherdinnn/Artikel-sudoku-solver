#include <iostream>
using namespace std;

const int N = 9;

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    // cek apakah angka sudah ada di baris
    for (int c = 0; c < N; c++) {
        if (grid[row][c] == num) {
            return false;
        }
    }
    // cek apakah angka sudah ada di kolom
    for (int r = 0; r < N; r++) {
        if (grid[r][col] == num) {
            return false;
        }
    }
    // cek apakah angka sudah ada di kotak 3x3
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int r = boxRow; r < boxRow + 3; r++) {
        for (int c = boxCol; c < boxCol + 3; c++) {
            if (grid[r][c] == num) {
                return false;
            }
        }
    }
    // jika aman
    return true;
}

bool solveBacktracking(int grid[N][N], int row, int col) {
    // basis: jika sudah mencapai baris terakhir dan kolom terakhir
    if (row == N - 1 && col == N) {
        return true;
    }
    // jika sudah mencapai kolom terakhir, lanjut ke baris berikutnya
    if (col == N) {
        row++;
        col = 0;
    }
    // jika kotak tidak kosong, lanjut ke kotak berikutnya
    if (grid[row][col] != 0) {
        return solveBacktracking(grid, row, col + 1);
    }
    // mencoba angka dari 1 sampai 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveBacktracking(grid, row, col + 1)) {
                return true;
            }
            // backtrack
            grid[row][col] = 0;
        }
    }
    // jika tidak ada solusi yang mungkin
    return false;
}

int main() {
    int n;
    printf("Masukkan jumlah grid: ");
    cin >> n;
    int grid[N][N];
    printf("Masukkan angka untuk setiap kotak, gunakan 0 untuk kotak kosong:\n");
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cin >> grid[row][col];
        }
    }
    
    if (solveBacktracking(grid, 0, 0)) {
        printf("Solusi:\n");
        printGrid(grid);
    } else {
        printf("Tidak ada solusi yang mungkin.\n");
    }
    
    return 0;
}

