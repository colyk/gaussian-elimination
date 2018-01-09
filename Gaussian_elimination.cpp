#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

class Gauss
{
private:
    double **matrix;
    double *matrix_answers;
    int row;
    int col;
    const double eps = 1.e-4; // precision

    void create_matrix()
    {
        matrix_answers = new double[col];
        matrix = new double*[row];
        for (int z = 0; z < row; z++)
            matrix[z] = new double[col];
    }

public:
    Gauss(): row(4), col(4)
    {
        create_matrix();
    }
    Gauss(double i): row(i), col(i)
    {
        create_matrix();
    }
    Gauss(double i, double j): row(i), col(j)
    {
        create_matrix();
    }
    ~Gauss()
    {
        for (int z = 0; z < row; z++)
            delete[] matrix[z];
        delete[] matrix;
        delete[] matrix_answers;
    }

    void set_default_m1()
    {
        double example_m1[4][4] =
        {
            { 0, 1, 2, 3},
            { 1, 0, 1, 2},
            { 1, 2, 3, 4},
            { 0, 1, 3, 2}
        };
        double example_a1[4] = {8, 4, 10, 7};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++) matrix[i][j] = example_m1[i][j];
            matrix_answers[i] = example_a1[i];
        }
    }

    void set_default_m2()
    {
        double example_m1[4][4] =
        {
            { 2, 5, 4, 1},
            { 1, 3, 2, 1},
            { 2, 10, 9, 7},
            { 3, 8, 9, 2}
        };
        double example_a1[4] = {20, 11, 40, 37};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++) matrix[i][j] = example_m1[i][j];
            matrix_answers[i] = example_a1[i];
        }
    }

    void get_user_input()
    {
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

    void print()
    {
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

    void calculate_x(double *x)
    {
        if (abs(matrix[row-1][col-1]) < eps )
        {
            cout << "Uklad sprzeczny!";
            exit(1);
        }
        for (int k = row - 1; k >= 0; k--)
        {
            x[k] = matrix_answers[k];
            for (int i = 0; i < k; i++)
                matrix_answers[i] = matrix_answers[i] - matrix[i][k] * x[k];
        }
        for (int i = 0; i < col; i++)
            cout << setprecision(1) << setiosflags(ios::fixed | ios::showpoint) << "x" << i << " = " << x[i] << endl; //round(x[i]*100)/100. << endl;
    }

    void gauss_solve()
    {
        double *x, max;
        int index;
        x = new double[row]; // array of answers
        int k = 0;

        while (k < row)
        {
            for (int i = k; i < row; i++)
            {
                double temp = matrix[i][k];
                if (abs(temp) < eps) // if temp == 0
                {
                    cout << "Ten uklad nie mozliwie rozwazac za pomoca 1. metody.";
                    exit(1);
                }
                for (int j = 0; j < row; j++)
                    matrix[i][j] = matrix[i][j] / temp;
                matrix_answers[i] = matrix_answers[i] / temp;
                if (i == k)  continue;
                for (int j = 0; j < row; j++)
                    matrix[i][j] = matrix[i][j] - matrix[k][j];
                matrix_answers[i] = matrix_answers[i] - matrix_answers[k];
            }
            k++;
        }
        calculate_x(x);
    }

    void solve_row_max()
    {
        double *x, max;
        int index;
        x = new double[row];  // array of answers
        int k = 0;

        while (k < row)
        {
            max = abs(matrix[k][k]);
            index = k;
            for (int i = k + 1; i < row; i++)
            {
                if (abs(matrix[i][k]) > max)
                {
                    max = abs(matrix[i][k]);
                    index = i;
                }
            }

            if (max < eps)
            {
                cout << "Rozwiazanie jest mozliwe do uzyskania z powodu zerowy kolumny ";
                cout << index << " macierzy" << endl;
                exit(0);
            }
            cout<<"\n_____________"<<k<<endl;
            print();
            for (int j = 0; j < row; j++) //  row swap
            {
                double temp = matrix[k][j];
                matrix[k][j] = matrix[index][j];
                matrix[index][j] = temp;
            }
            double temp = matrix_answers[k];
            matrix_answers[k] = matrix_answers[index];
            matrix_answers[index] = temp;
print();
            for (int i = k; i < row; i++)
            {
                double temp = matrix[i][k];
                if (abs(temp) < eps) continue;
                for (int j = 0; j < row; j++)
                    matrix[i][j] = matrix[i][j] / temp;
                matrix_answers[i] = matrix_answers[i] / temp;
                if (i == k)  continue;
                for (int j = 0; j < row; j++)
                    matrix[i][j] = matrix[i][j] - matrix[k][j];
                matrix_answers[i] = matrix_answers[i] - matrix_answers[k];
            }
            k++;
        }
        calculate_x(x);
    }

    void solve_matrix_max()
    {
        int i, j, s, m, max_r, max_c, temp;
        double max;
        double *X;
        X = new double[row];
        int memory[row];
        double Y[row];
        double v;
        for (i = 0; i < row; i++)
            memory[i] = i;
        int k = 0;

        while (k < row)
        {
            max = 0;
            max_r = k;
            max_c = k;
            for (s = k; s < row; s++)
            {
                for (m = k; m < col; m++)
                {
                    if (abs(matrix[s][m]) > max)
                    {
                        max = abs(matrix[s][m]);
                        max_r = s;
                        max_c = m;
                    }
                }
            }
            if (max < eps)
            {
                cout << "Rozwiazanie jest mozliwe do uzyskania z powodu zerowy kolumny!";
                exit(1);
            }
            if ( k != max_r)
            {
                double emp;
                for (int j = 0; j < row; j++)
                {
                    emp = matrix[k][j];
                    matrix[k][j] = matrix[max_r][j];
                    matrix[max_r][j] = emp;
                }
                emp = matrix_answers[k];
                matrix_answers[k] = matrix_answers[max_r];
                matrix_answers[max_r] = emp;
            }

            if (k != max_c)
            {
                double emp;
                for (int j = 0; j < row; j++)
                {
                    emp = matrix[j][k];
                    matrix[j][k] = matrix[j][max_c];
                    matrix[j][max_c] = emp;
                }
                temp = memory[k];
                memory[k] = memory[max_c];
                memory[max_c] = temp;
            }

            for (int i = k; i < row; i++)
            {
                double temp = matrix[i][k];
                if (abs(temp) < eps) continue;
                for (int j = 0; j < row; j++)
                    matrix[i][j] = matrix[i][j] / temp;
                matrix_answers[i] = matrix_answers[i] / temp;
                if (i == k)  continue;
                for (int j = 0; j < row; j++)
                    matrix[i][j] = matrix[i][j] - matrix[k][j];
                matrix_answers[i] = matrix_answers[i] - matrix_answers[k];
            }
            k++;
        }
        for (int k = row - 1; k >= 0; k--)
        {
            Y[k] = matrix_answers[k];
            for (int i = 0; i < k; i++)
                matrix_answers[i] = matrix_answers[i] - matrix[i][k] * Y[k];
        }

        for (i = 0; i < row; i++)
            X[memory[i]] = Y[i];

        for (int i = 0; i < col; i++)
            cout << setprecision(1) << setiosflags(ios::fixed | ios::showpoint) << "x" << i << " = " << X[i] << endl;
    }
};

void incorrect_input()
{
    cout << "Incorrect choice! Try again!" << endl;
    exit(1);
}

int main()
{
    int method, menu;
    cout << "Pick method:\n1. Gauss method.\n2. Gauss method with max element in row.\n3. Gauss method with max element in matrix." << endl;
    cin >> method;
    cout << "Choose the type of input:\n1. The input from the user.\n2. Default matrix." << endl;
    cin >> menu;

    if (menu == 1)
    {
        int row;
        int col;
        cout << "Put count of rows: ";
        cin >> row;
        cout << "Put count of columns: ";
        cin >> col;
        if (col < row) incorrect_input();
        Gauss user_input(row, col);
        user_input.get_user_input();
        user_input.print();

        if (method == 1)
            user_input.gauss_solve();
        else if (method == 2)
            user_input.solve_row_max();
        else if (method == 3)
            user_input.solve_matrix_max();
        else incorrect_input();
    }
    else if (menu == 2)
    {
        cout << "Do wyboru 2 macierzy:\n1.(4x4) -1 0 1 2\n2.(4x4) 1 2 2 0\nPodaj numer: ";
        cin >> menu;
        Gauss default_matrix(4, 4);
        if (menu == 1)
        {
            default_matrix.set_default_m1();
            default_matrix.print();
        }
        else if (menu == 2)
        {
            default_matrix.set_default_m2();
            default_matrix.print();
        }
        else incorrect_input();

        if (method == 1)
            default_matrix.gauss_solve();
        else if (method == 2)
            default_matrix.solve_row_max();
        else if (method == 3)
            default_matrix.solve_matrix_max();
        else incorrect_input();
    }
    else incorrect_input();
    return 0;
}
