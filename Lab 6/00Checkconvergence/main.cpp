// 00CheckConvergence.cpp
// Check the convergence of the Traezium Rule,
// while also demo'ing memory allocation and de-allocation
// Week 07: CS319 - Scientific Computing
#include <iostream>
#include <cmath>  // For exp()
#include <iomanip>
#include <string>
#include <time.h>
//THIS IS THE CODE FOR 2D QUADRATURE

//double f(double x){return(exp(x));}   // definition
//double ans_true1 = exp(1.0)-1.0; // true value of integral
double f(double x1, double x2){return(exp(x1+x2));}
double a=0.0, b=1.0;  // limits of int in both x1 and x2
double ans_true2D = pow(exp(1.0)-1.0,2); // true value

//double Quad1(double *x, double *y, unsigned int N);
//double Quad2(double *x, double *y, unsigned int N);
double Quad2D(double **y, double *w, unsigned int N);

void print_nparray(unsigned *x, int n, std::string str);
void print_nparray(double *x, int n, std::string str);

int main(void )
{
    unsigned K = 8;  // number of cases to check (check 8 different values of N); for time change this to 4
    unsigned Ns[K];   // Number of intervals
    double Errors[K], Times[K];
    double a=0.0, b=1.0; // limits of integration
    double *x1, *x2, *w, **y; // quadrature points and values.

    for (unsigned k=0; k<K; k++)
    {
        unsigned N = pow(2,k+2); // for time change the 2 to 8
        Ns[k] = N;
        x1 = new double[N+1];
        x2 = new double[N+1]; // dynamic memory allocation
        for(unsigned i = 0; i < N+1; i++)
        {
            x1[i] = a+i*(b-a)/N;
            x2[i] = a+i*(b-a)/N;
        }
        y = new double * [N+1];
        for(unsigned i = 0; i < N+1; i++)
        y[i] = new double[N+1];

        for (unsigned i=0; i<N+1; i++)
            for (unsigned j=0; j<N+1; j++)
                y[i][j] = f(x1[i], x2[j]);

        double h = (b-a)/double(N);

        // Define the weights for 1D Trapezium Rule
        // These are [1,2,2,2, ..., 2,1]/2
        w = new double[N+1];
        w[0]=h/2.0;
        for (unsigned i=1; i<N; i++)
            w[i]=h;
        w[N]=h/2.0;

        clock_t start;
        start=clock();

        double est1 = Quad2D(y, w, N);
        double error1 = fabs(ans_true2D - est1);
        Errors[k] = error1;
        double diff = (float)(clock()-start);
        //std::cout<< "N = " << N << " Time=" << diff << std::endl;
        Times[k] = diff/CLOCKS_PER_SEC;

        delete [] x1;
        delete [] x2;
        for(unsigned i = 0; i < N+1; i++)
            delete [] y[i];
        delete [] y;

    }

    print_nparray(Ns, K, "N");
    print_nparray(Errors, K, "Trap2D");
    print_nparray(Times, K, "Times");
    return(0);
}

double Quad1(double *x, double *y, unsigned N)
{
    double h = (x[N]-x[0])/double(N);
    double Q = 0.5*(y[0]+y[N]);
    for (unsigned int i=1; i<N; i++)
        Q += y[i];
    Q *= h;
    return(Q);
}

double Quad2(double *x, double *y, unsigned int N)
{
    double h = (x[N]-x[0])/double(N);
    double Q = y[0]+y[N];
    for (unsigned int i=1; i<=N-1; i+=2)
        Q += 4*y[i];
    for (unsigned int i=2; i<=N-2; i+=2)
        Q += 2*y[i];
    Q *= h/3.0;
    return(Q);
}

double Quad2D(double **y, double *w,  unsigned N)
{
    double Q;

    Q=0;
    for (unsigned i=0; i<=N; i++)
        for (unsigned j=0; j<=N; j++)
            Q += w[i]*w[j]*y[i][j];

    return(Q);
}


void print_nparray(unsigned *x, int n, std::string str)
{
    std::cout << str << "=np.array([";
    std::cout << x[0];
    for (int i=1; i<n; i++)
        std::cout << ", " << x[i];
    std::cout << "])" << std::endl;
}

void print_nparray(double *x, int n, std::string str)
{
    std::cout << str << "=np.array([";
    std::cout << std::scientific << std::setprecision(6);
    std::cout << x[0];
    for (int i=1; i<n; i++)
        std::cout << ", " << x[i];
    std::cout << "])" << std::endl;
}

