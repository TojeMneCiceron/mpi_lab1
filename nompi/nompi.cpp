#include <iostream>
using namespace std;

const double A = 0, B = sqrt(3), E = 1;

double F(double s)
{
    return s / sqrt(4 - s * s);
}

double Calc(int bg, int ed, double h)
{
    double sum = 0;

    for (int i = bg; i < ed; i++)
    {
        double s = A + h * i;
        sum += F(s);
    }

    return h * sum;
}

int main()
{
    double time = clock();
    int n = 1000000;

    double res = Calc(0, n, (B - A) / n);

    //double error = abs(res - E) / E;

    time = clock() - time;
    cout << "time = " << time / CLOCKS_PER_SEC << "\nsum = " << res << "\ne = " << abs(res - E) / E;

}