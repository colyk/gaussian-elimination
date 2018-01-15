#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

void print(double **matrix, double *matrix_answers, int row)
{
    int col = row;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout.width(4);
            cout << matrix[i][j];
        }
        cout << "  |  " << matrix_answers[i] << endl;
    }
    cout << endl;
}


void incorrect_input()
{
    cout << "Incorrect input! Try again!" << endl;
    exit(1);
}


void cholieski(double **matrix, double *matrix_answers, int row)
{
    double y[row];
    double x[row];
    int col = row;
    double **L;
    L = new double*[row];
    for (int z = 0; z < row; z++)
        L[z] = new double[col];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            int sum = 0;
            if (j == i) // diagonal
            {
                for (int k = 0; k < j; k++)
                    sum += pow(L[j][k], 2);
                if (matrix[j][j] - sum < 0)
                {
                    cout << "Pierwiastek z liczby ujemnej!";
                    incorrect_input();
                }
                L[j][j] = sqrt(matrix[j][j] - sum);
            }
            else
            {
                for (int k = 0; k < j; k++)
                    sum += (L[i][k] * L[j][k]);
                L[i][j] = (matrix[i][j] - sum) / L[j][j];
                L[j][i] = L[i][j];      // uzupelnienie symetryczne
            }
        }
    }
    print(L, matrix_answers, row);
    // wyleczanie Y
    for (int k = 0; k < row; k++)
    {
        double res = 0;
        for (int i = 0; i < k; i++)
            res += L[k][i] * y[i];
        y[k] = (matrix_answers[k] - res) / L[k][k];
    }
//    for (int i = 0; i < col; i++)
//        cout << setprecision(5) << setiosflags(ios::fixed | ios::showpoint) << "y" << i+1 << " = " << y[i] << endl;
    for (int k = row - 1; k >= 0; k--)
    {
        double res = 0;
        for (int i = row - 1; i > k; i--)
            res += L[k][i] * x[i];
        x[k] = (y[k] - res) / L[k][k];
    }
    cout << "_______________________\n";
    for (int i = 0; i < col; i++)
        cout << setprecision(5) << setiosflags(ios::fixed | ios::showpoint) << "x" << i + 1 << " = " << x[i] << endl;

}


int check_matrix(double **matrix, int row)
{
    // sprawdzanie na symetrycznosc
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrix[i][j] != matrix[j][i]) return 1;
        }
    }
    return 0;
}


int main()
{
    double **matrix;
    double *matrix_answers;
    int row = 2;
    int col = row;
    int set_mat = 2;
    cout << "1. Podac macierz.\n2. Standardowa macierz.\nWybor: ";
    cin >> set_mat;
    if (set_mat == 2)
    {
        row = 4;
        col = row;
        matrix_answers = new double[col];
        matrix = new double*[row];
        for (int z = 0; z < row; z++)
            matrix[z] = new double[col];
        double example_m1[4][4] =
        {
            { 1, -2, 3, 1},
            { -2, 5, -8, 1},
            { 3, -8, 17, -7},
            { 1, 1, -7, 18}
        };
        double example_a1[4] = {1, -1, 3, -4};
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++) matrix[i][j] = example_m1[i][j];
            matrix_answers[i] = example_a1[i];
        }
    }
    else if (set_mat == 1)
    {
        cout << "Podaj illosc kolumn: ";
        cin >> col;
        row = col;
        matrix_answers = new double[col];
        matrix = new double*[row];
        for (int z = 0; z < row; z++)
            matrix[z] = new double[col];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << "matrix[" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
            }
            cout << "matrix row " << i << " answer: ";
            cin >> matrix_answers[i];
        }
    }
    else incorrect_input();

    if (check_matrix(matrix, row)) incorrect_input();
    print(matrix, matrix_answers, row);
    cholieski(matrix, matrix_answers, row);
    return 0;
}
