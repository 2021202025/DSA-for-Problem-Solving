#include <iostream>

using namespace std;

template <class T> class newMatrix {
    int row;
    int column;
    int sz;
    T **numbers;
    const static int MAXSIZE = 500;

public:
    newMatrix(int row, int column) {
        this->row = row;
        this->column  = column;
        sz = 0;
        numbers = new T *[MAXSIZE];
        int i = 0;
        while (i < MAXSIZE) {
            numbers[i] = new T[3];
            i++;
        }
    }

    void insert(int row, int column, T value) {
        if (row > this->row) {
            cout << "Invalid" << endl;
        }
        else if (column > this->column) {
            cout << "Invalid" << endl;
        }
        else {
            numbers[sz][0] = row;
            numbers[sz][1] = column;
            numbers[sz][2] = value;
            sz++;
        }
    }

    newMatrix Transpose() {
        newMatrix transposedMatrix(column, row);
        transposedMatrix.sz = sz;

        int *elements = new int[column + 1];
        for (int i = 1; i <= column; i++) {
            elements[i] = 0;
        }

        for (int i = 0; i < sz; i++) {
            elements[(int)numbers[i][1]]++;
        }

        int *idx = new int[column + 1];

        idx[0] = 0;
        for (int i = 1; i <= column; i++) {
            idx[i] = idx[i - 1] + elements[i - 1];
        }

        for (int i = 0; i < sz; i++) {
            int finalRowPos = idx[(int)numbers[i][1]]++;
            transposedMatrix.numbers[finalRowPos][2] = numbers[i][2];
            transposedMatrix.numbers[finalRowPos][0] = numbers[i][1];
            transposedMatrix.numbers[finalRowPos][1] = numbers[i][0];
        }

        return transposedMatrix;
    }

    newMatrix AddMatrices(newMatrix other) {

        int firstMatPos = 0;
        int secondMatPos = 0;

        newMatrix SumMatrix(row, column);

        while (firstMatPos < sz and secondMatPos < other.sz) {
            if (numbers[firstMatPos][0] < other.numbers[secondMatPos][0] or
                    numbers[firstMatPos][0] == other.numbers[secondMatPos][0] and numbers[firstMatPos][1] < other.numbers[secondMatPos][1]) {
                SumMatrix.insert(numbers[firstMatPos][0], numbers[firstMatPos][1], numbers[firstMatPos][2]);
                firstMatPos++;
            }
            else if (numbers[firstMatPos][0] > other.numbers[secondMatPos][0] or
                     numbers[firstMatPos][0] == other.numbers[secondMatPos][0] and numbers[firstMatPos][1] > other.numbers[secondMatPos][1]) {
                SumMatrix.insert(other.numbers[secondMatPos][0], other.numbers[secondMatPos][1], other.numbers[secondMatPos][2]);
                secondMatPos++;
            }
            else if (numbers[firstMatPos][0] == other.numbers[secondMatPos][0] and numbers[firstMatPos][1] == other.numbers[secondMatPos][1]) {
                if (numbers[firstMatPos][2] + other.numbers[secondMatPos][2] != 0)
                    SumMatrix.insert(numbers[firstMatPos][0], numbers[firstMatPos][1], numbers[firstMatPos][2] + other.numbers[secondMatPos][2]);
                firstMatPos++; secondMatPos++;
            }
        }

        while (secondMatPos < other.sz) {
            SumMatrix.insert(other.numbers[secondMatPos][0], other.numbers[secondMatPos][1], other.numbers[secondMatPos][2]);
            secondMatPos++;
        }

        while (firstMatPos < sz) {
            SumMatrix.insert(numbers[firstMatPos][0], numbers[firstMatPos][1], numbers[firstMatPos][2]);
            firstMatPos++;
        }

        return SumMatrix;
    }

    newMatrix MultiplyMatrices(newMatrix other) {
        if (column == other.row) {
            other = other.Transpose();
            newMatrix ProductMatrix(row, other.row);


            int firstMatPos = 0;
            int secondMatPos = 0;

            for (firstMatPos = 0; firstMatPos < sz;) {
                int currRow = numbers[firstMatPos][0];
                for (secondMatPos = 0; secondMatPos < other.sz;) {

                    int currColumn = other.numbers[secondMatPos][0];

                    int a = firstMatPos;
                    int b = secondMatPos;

                    T result = 0;

                    while (a < sz and numbers[a][0] == currRow and b < other.sz and other.numbers[b][0] == currColumn) {
                        if (other.numbers[b][1] > numbers[a][1]) {
                            a++;
                        }
                        else if (other.numbers[b][1] < numbers[a][1]) {
                            b++;
                        }
                        else if (other.numbers[b][1] == numbers[a][1]) {
                            result = result + (numbers[a][2] * other.numbers[b][2]);
                            a++;
                            b++;
                        }
                    }
                    if (result != 0) {
                        ProductMatrix.insert(currRow, currColumn, result);
                    }

                    while (secondMatPos < other.sz and other.numbers[secondMatPos][0] == currColumn)
                        secondMatPos++;

                }

                while (firstMatPos < sz and numbers[firstMatPos][0] == currRow)
                    firstMatPos++;

            }

            return ProductMatrix;
        }

        else {
            cout << "Matrices can't be multiplied" << endl;
            newMatrix ProductMatrix(row, other.row);
            return ProductMatrix;
        }
    }

    void print()
    {
        cout << "\nRow\tColumn\tValue" << endl;

        for (int i = 0; i < sz; i++)
        {
            cout << numbers[i][0] << "\t " << numbers[i][1] << "\t " << numbers[i][2] << endl;
        }
    }


};

int main()
{

    int n;
    cout << "Choose an operation: " << endl;
    cout << "1) Add 2 Matrices " << endl;
    cout << "2) Multiply 2 Matrices " << endl;
    cout << "3) Transpose a Matrix " << endl;
    cin >> n;

    if (n == 1) {
        int rows1, columns1;
        cout << "\nEnter dimensions of matrix 1 " << endl;
        cin >> rows1 >> columns1;
        double x[rows1][columns1];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                cin >> x[i][j];
            }
        }

        int rows2, columns2;
        cout << "\nEnter dimensions of matrix 2 " << endl;
        cin >> rows2 >> columns2;
        double y[rows2][columns2];
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < columns2; j++) {
                cin >> y[i][j];
            }
        }

        newMatrix<float> first(rows1, columns1);
        newMatrix<float> second(rows2, columns2);

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                if (x[i][j] != 0) {
                    first.insert(i, j, x[i][j]);
                }
            }
        }
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < columns2; j++) {
                if (y[i][j] != 0) {
                    second.insert(i, j, y[i][j]);
                }
            }
        }

        cout << "\nAddition: ";
        auto result = first.AddMatrices(second);
        result.print();
    }

    else if (n == 2) {
        int rows1, columns1;
        cout << "\nEnter dimensions of matrix 1 " << endl;
        cin >> rows1 >> columns1;
        double x[rows1][columns1];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                cin >> x[i][j];
            }
        }

        int rows2, columns2;
        cout << "\nEnter dimensions of matrix 2 " << endl;
        cin >> rows2 >> columns2;
        double y[rows2][columns2];
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < columns2; j++) {
                cin >> y[i][j];
            }
        }

        newMatrix<double> first(rows1, columns1);
        newMatrix<double> second(rows2, columns2);

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                if (x[i][j] != 0) {
                    first.insert(i, j, x[i][j]);
                }
            }
        }
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < columns2; j++) {
                if (y[i][j] != 0) {
                    second.insert(i, j, y[i][j]);
                }
            }
        }

        cout << "\nMultiplication: ";
        auto result = first.MultiplyMatrices(second);
        result.print();
    }

    else if (n == 3) {
        int rows1, columns1;
        cout << "\nEnter dimensions of matrix " << endl;
        cin >> rows1 >> columns1;
        double x[rows1][columns1];
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                cin >> x[i][j];
            }
        }


        newMatrix<double> first(rows1, columns1);

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < columns1; j++) {
                if (x[i][j] != 0) {
                    first.insert(i, j, x[i][j]);
                }
            }
        }


        cout << "\nTranspose: ";
        newMatrix<double> a = first.Transpose();
        a.print();
    }
    else {
        cout << "\nInvalid Operation" << endl;
    }

    return 0;
}