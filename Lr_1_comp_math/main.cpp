
#include <iostream>
#include <math.h>
#include<vector>

using namespace std;

struct Interval {
    double x0;
    double x1;
};


double mathFunc(double x, double a=2.93, double b=3.01, double c=2.1) {
    return a*pow(x, 2)*cos(b*x) - pow(c, x);
}


double xnUp(double xn, double b) {
    return xn - mathFunc(xn)*(b - xn)/(mathFunc(b) - mathFunc(xn));
}


double xnDown(double xn, double a) {
    return xn - mathFunc(xn)*(xn - a)/(mathFunc(xn) - mathFunc(a));
}


double getX(double (&xnFunc)(double, double), double arg1, double arg2, double e=0.00007) {
    cout << "\n" << endl;

    double x0 = arg1;
    double x1 = xnFunc(x0, arg2);
    cout << x1 << " ";

    while (abs(x1 - x0) > e) {
        x0 = x1;
        x1 = xnFunc(x0, arg2);

        cout << x1 << " ";
    }

    return x1;

    cout << "\n" << endl;
}


vector<Interval> getIntervals(double start, double stop, double dx=0.05) {
    vector<Interval> array;

    while (start < stop) {
        double fx0 = mathFunc(start);
        double fx1 = mathFunc(start + dx);

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


double dFx(double x0, double dx=0.01) {
    double fx0 = mathFunc(x0 - dx/2);
    double fx1 = mathFunc(x0 + dx/2);

    double result = (fx1 - fx0) / dx;
    return result;
}


double dFx2(double x0, double dx=0.01) {
    double dF0 = dFx(x0 - dx/2);
    double dF1 = dFx(x0 + dx/2);

    double result = (dF1 - dF0) / dx;
    return result;
}


int main() {
    vector<Interval> intervals = getIntervals(-1.5, 4.6);
    vector<double> result;

    for (int ind = 0; ind < intervals.size(); ind++) {
        Interval interval = intervals.at(ind);

        double a = interval.x0;
        double b = interval.x1;

        double df = dFx(a);
        double df2 = dFx2(a);

        if (df*df2 > 0) { result.push_back(getX(xnUp, a, b)); }
        else if (df*df2 < 0) { result.push_back(getX(xnDown, a, b)); }
        else { return -1; }
    }


    cout << endl;
    for (int ind = 0; ind < result.size(); ind++) {
        cout << "Interval: [" << intervals[ind].x0 << ", " << intervals[ind].x1 << "]. "
             << "F(x): [" << mathFunc(intervals[ind].x0) << ", " << mathFunc(intervals[ind].x1) << "]. "
             << "F'(x): [" << dFx(intervals[ind].x0) << ", " << dFx(intervals[ind].x1) << "]. "
             << "F''(x): [" << dFx2(intervals[ind].x0) << ", " << dFx2(intervals[ind].x1) << "]. "
             << "x" << ind + 1 << " = " << result.at(ind) << endl;
    }


    cout << mathFunc(1.70777) << "  " << mathFunc(1.75) << endl;


    return 0;
}
