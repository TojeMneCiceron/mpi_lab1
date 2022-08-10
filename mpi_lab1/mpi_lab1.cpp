#include <iostream>
#include "mpi.h"
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

void GetIndices(int rank, int np, int &bg, int &ed)
{   
    bg = np * rank;
    ed = np + bg;
}

int main(int argc, char** argv)
{
    MPI_Status status;
	MPI_Init(&argc, &argv);
    double time = MPI_Wtime();

    int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 1000000;
    int bg, ed;
    GetIndices(rank, n / size, bg, ed);

    double res = Calc(bg, ed, (B - A) / n);

    double sum;    
    MPI_Reduce(&res, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    time = MPI_Wtime() - time;

    double max_time;
    MPI_Reduce(&time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
        cout << "time = " << max_time << "\nsum = " << sum << "\ne = " << abs(sum - E) / E;
    
	MPI_Finalize();
	return 0;
}