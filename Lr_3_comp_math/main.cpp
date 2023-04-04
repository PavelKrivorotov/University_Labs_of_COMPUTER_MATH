#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int factorial(int value) {
    if (value < 0) { return 0; }

    int result = 1;
    for (int i = 1; i < value + 1; i ++) {
        result *= i;
    }

    return result;
}


vector<vector<double>> getDifferences(vector<double> yArray) {
    vector<vector<double>> result;
    result.push_back(yArray);

    int index = 0;
    while(result.at(index).size() > 1) {
        vector<double> currentDiff = result.at(index);
        vector<double> newDiff;

        for (int ind = 0; ind < (currentDiff.size() - 1); ind++) {
            double diffY = (currentDiff.at(ind + 1) - currentDiff.at(ind));
            newDiff.push_back(diffY);
        }

        result.push_back(newDiff);
        index += 1;
    }

    return result;
}


vector<double> getKoeffs(vector<vector<double>> differences, double h) {
    vector<double> result;
    result.push_back(differences.at(0).at(0));

    int index = 1;
    while (index < differences.size()) {
        double koef = differences.at(index).at(0) / (factorial(index) * pow(h, index));
        result.push_back(koef);
        index += 1;
    }

    return result;
}


double getFx(double x, vector<double> xArray, vector<double> koeffs) {
    double y = koeffs.at(0);

    for (int ind1 = 1; ind1 < koeffs.size(); ind1++) {
        double tmp = koeffs.at(ind1);

        int ind2 = 0;
        while (ind2 < ind1) {
            tmp *= (x - xArray.at(ind2));
            ind2 += 1;
        }

        y += tmp;
    }

    return y;
}


void showDifferences(vector<vector<double>> differences) {
    cout << "\nDifferences of Y:" << endl;

    for (int ind1 = 0; ind1 < differences.size(); ind1++) {
        cout << "Y" << ind1 << " = " << "[";
        for (int ind2 = 0; ind2 < differences.at(ind1).size(); ind2++) {
            cout << differences[ind1][ind2] << ", ";
        }
        cout << "]" << endl;
    }
}


void showKoeffs(vector<double> koeffs) {
    cout << "\nKoeffs of Lagrange:" << endl;

    for (int ind = 0; ind < koeffs.size(); ind++) {
        cout << "a" << ind << " = " << koeffs.at(ind) << endl;
    }
}


int main() {
    vector<double> xValues;
    vector<double> yValues;
    double h;
    double x;


    cout << "Input X-values: ";
    for (int ind = 0; ind < 5; ind++) {
        double val;
        cin >> val;
        xValues.push_back(val);
    }

    cout << "Input Y-values: ";
    for (int ind = 0; ind < 5; ind++) {
        double val;
        cin >> val;
        yValues.push_back(val);
    }

    cout << "\nInput X(i+1) - X(i) difference: ";
    cin >> h;


//    xValues = {0.52, 0.79, 1.06, 1.33, 1.6};
//    yValues = {0.05, 0.19, 0.35, 0.79, 1.4};
//    h = 0.27;


    vector<vector<double>> differences;
    differences = getDifferences(yValues);
    showDifferences(differences);

    vector<double> koeffs = getKoeffs(differences, h);
    showKoeffs(koeffs);

    while (true) {
        cout << "\n\nInput X for calculation: ";
        cin >> x;

        if (x == -999) { break; }

        double result = getFx(x, xValues, koeffs);
        cout << "Value in X = " << x << ": " << result << endl;
    }

    return 0;
}
