#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printMatrix(vector<vector<double>> matrix, int rowCount = 4, int colCount = 5);
void printResult(vector<double> result, int size = 4);


void fillMatrix(vector<vector<double>> &matrix) {
    vector<double> row1 = vector<double>();
    row1.push_back(0.0);
    row1.push_back(0.0);
    row1.push_back(0.0);
    row1.push_back(0.0);
    row1.push_back(0.0);

    matrix.push_back(row1);
    matrix.push_back(row1);
    matrix.push_back(row1);
    matrix.push_back(row1);

    cout << "Input matrix by rows:" << endl;

    for (int index1 = 0; index1 < 4; index1++) {
        for (int index2 = 0; index2 < 5; index2++) {
            cin >> matrix[index1][index2];
            cout << " ";
        }

        cout << endl;
    }
}


void replaceRow(vector<vector<double>> &matrix) {

}


void firstStep(vector<vector<double>> &matrix, int rowCount = 4, int colCount = 5) {
    int row = 0;
    int col = 0;
    while (row < rowCount - 1) {
        // Check first element; Replace row if element is 0;
         if (matrix[row][col] == 0.0) { replaceRow(matrix); }

        for (int index1 = row + 1; index1 < rowCount; index1++) {
            double koeff = (double)matrix[index1][col] / (double)matrix[row][col];

            for (int index2 = col; index2 < colCount; index2++) {
                matrix[index1][index2] = matrix[index1][index2] - koeff*matrix[row][index2];
            }

//            printMatrix(matrix);
        }

        row += 1;
        col += 1;

        printMatrix(matrix);
    }
}


vector<double> secondStep(vector<vector<double>> &matrix, int rowCount = 4, int colCount = 5) {
    vector<double> result = vector<double>();
    result.push_back(0.0);
    result.push_back(0.0);
    result.push_back(0.0);
    result.push_back(0.0);

    int row = rowCount;
    int col = colCount - 2;
    while (row > 0) {
        double res = matrix[row - 1][colCount - 1];

        for (int index = 0; index < colCount - 1; index++) {
            if (index != col) {
                res -= result[index]*matrix[row -1][index];
            }
        }

        res /= (double)matrix[row - 1][col];
        result[col] = res;

        row -= 1;
        col -= 1;
    }

    return result;
}


void printMatrix(vector<vector<double>> matrix, int rowCount, int colCount) {
    for (int index1 = 0; index1 < rowCount; index1++) {
        for (int index2 = 0; index2 < colCount; index2++) {
            cout << matrix[index1][index2] << "\t";

            if (index2 == colCount - 2) {
                cout << "| ";
            }
        }

        cout << endl;
    }

    cout << endl;
}


void printResult(vector<double> result, int size) {
    cout << endl;

    for (int index = 0; index < size; index++) {
        cout << result[index] << "\t";
    }

    cout << endl;
}


int main() {
    vector<vector<double>> matrix = vector<vector<double>>();
//    fillMatrix(matrix);

    vector<double> row1 = vector<double>();
    row1.push_back(2.0);
    row1.push_back(4.0);
    row1.push_back(7.0);
    row1.push_back(4.0);
    row1.push_back(2.0);
    matrix.push_back(row1);

    vector<double> row2 = vector<double>();
    row2.push_back(4.0);
    row2.push_back(1.0);
    row2.push_back(6.0);
    row2.push_back(2.0);
    row2.push_back(0.0);
    matrix.push_back(row2);

    vector<double> row3 = vector<double>();
    row3.push_back(8.0);
    row3.push_back(3.0);
    row3.push_back(6.0);
    row3.push_back(7.0);
    row3.push_back(3.0);
    matrix.push_back(row3);

    vector<double> row4 = vector<double>();
    row4.push_back(6.0);
    row4.push_back(3.0);
    row4.push_back(5.0);
    row4.push_back(7.0);
    row4.push_back(1.0);
    matrix.push_back(row4);


    cout << "\nInput matrix:" << endl;
    printMatrix(matrix);

    cout << "Worked firstStep function:" << endl;
    firstStep(matrix);


    vector<double> result = secondStep(matrix);

    cout << "Result (X1, X2, X3, X4):";
    printResult(result);    

    return 0;
}
