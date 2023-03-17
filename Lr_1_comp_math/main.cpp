
#include <iostream>
#include <math.h>
#include<vector>

using namespace std;

struct Interval {
    double x0;
    double x1;
};


double mathFunc(double x, double a, double b, double c) {
    return a*pow(x, 2)*cos(b*x) - pow(c, x);
}


double xnUp(double xn, double b, double arg1, double arg2, double arg3) {
    return xn - mathFunc(xn, arg1, arg2, arg3)*(b - xn)/(mathFunc(b, arg1, arg2, arg3)
              - mathFunc(xn, arg1, arg2, arg3));
}


double xnDown(double xn, double a, double arg1, double arg2, double arg3) {
    return xn - mathFunc(xn, arg1, arg2, arg3)*(xn - a)/(mathFunc(xn, arg1, arg2, arg3)
              - mathFunc(a, arg1, arg2, arg3));
}


double getX(double (&xnFunc)(double, double, double, double, double),
            double arg1, double arg2, double arg3, double arg4, double arg5,
            double e=0.00007) {

    double x0 = arg1;
    double x1 = xnFunc(x0, arg2, arg3, arg4, arg5);

    while (abs(x1 - x0) > e) {
        x0 = x1;
        x1 = xnFunc(x0, arg2, arg3, arg4, arg5);
    }

    return x1;
}


vector<Interval> getIntervals(double start, double stop, double arg1, double arg2,
                              double arg3,  double dx=0.05) {
    vector<Interval> array;

    while (start < stop) {
        double fx0 = mathFunc(start, arg1, arg2, arg3);
        double fx1 = mathFunc(start + dx, arg1, arg2, arg3);

        if (fx0*fx1 < 0) {
            Interval interval = Interval();
            interval.x0 = start;
            interval.x1 = start + dx;

            array.push_back(interval);
        }

        start += dx;
    }

    return array;
}


double dFx(double x0, double arg1, double arg2, double arg3, double dx=0.01) {
    double fx0 = mathFunc(x0 - dx/2, arg1, arg2, arg3);
    double fx1 = mathFunc(x0 + dx/2, arg1, arg2, arg3);

    double result = (fx1 - fx0) / dx;
    return result;
}


double dFx2(double x0, double arg1, double arg2, double arg3, double dx=0.01) {
    double dF0 = dFx(x0 - dx/2, arg1, arg2, arg3);
    double dF1 = dFx(x0 + dx/2, arg1, arg2, arg3);

    double result = (dF1 - dF0) / dx;
    return result;
}


int main() {
    double arg1, arg2, arg3;
    double start, stop;

    cout << "Input (a, b, c) for a*(x^2)*cos(b*x) - c^x" << endl;

    cout << "\ta = ";
    cin >> arg1;

    cout << "\tb = ";
    cin >> arg2;

    cout << "\tc = ";
    cin >> arg3;


    cout << "\nInput interval [x0, x1] for search x*:" << endl;

    cout << "\tx0 = ";
    cin >> start;

    cout << "\tx1 = ";
    cin >> stop;

    // Interval [-1.5, 4.6]
    vector<Interval> intervals = getIntervals(start, stop, arg1, arg2, arg3);
    vector<double> result;

    for (int ind = 0; ind < intervals.size(); ind++) {
        Interval interval = intervals.at(ind);

        double a = interval.x0;
        double b = interval.x1;

        double df = dFx(a, arg1, arg2, arg3);
        double df2 = dFx2(a, arg1, arg2, arg3);

        if (df*df2 > 0) { result.push_back(getX(xnUp, a, b, arg1, arg2, arg3)); }
        else if (df*df2 < 0) { result.push_back(getX(xnDown, a, b, arg1, arg2, arg3)); }
        else { return -1; }
    }


    cout << endl;
    for (int ind = 0; ind < result.size(); ind++) {
        cout << "\nInterval: [" << intervals[ind].x0 << ", " << intervals[ind].x1 << "]. "
             << "\n\tF(x): [" << mathFunc(intervals[ind].x0, arg1, arg2, arg3) << ", "
                << mathFunc(intervals[ind].x1, arg1, arg2, arg3) << "]. "
             << "\n\tF'(x): [" << dFx(intervals[ind].x0, arg1, arg2, arg3) << ", "
                << dFx(intervals[ind].x1, arg1, arg2, arg3) << "]. "
             << "\n\tF''(x): [" << dFx2(intervals[ind].x0, arg1, arg2, arg3) << ", "
                << dFx2(intervals[ind].x1, arg1, arg2, arg3) << "]. "
             << "\n\tx" << ind + 1 << " = " << result.at(ind)
             << "\n\tF(x" << ind + 1 << ") = " << mathFunc(result.at(ind), arg1, arg2, arg3)
                << endl;
    }

    return 0;
}
