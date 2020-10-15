#include <iostream>
#include <cmath>

using namespace std;
float A[100][100],B[100];
int n;
float *Gauss_seidel();
int main()
{
    cout<<"Enter the value of n: ";
    cin>>n;

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            cout<<"\nEnter the element A["<<i+1<<"]["<<j+1<<"]: ";
            cin>>A[i][j];
        }
    }

    for (int i=0; i<n;i++)
    {
        cout<<"\nEnter the element B["<<i+1<<"]: ";
        cin>>B[i];
    }

    float *p;
    p = Gauss_seidel();
    for (int i=0;i<n;i++)
    {
        cout<<"X["<<i+1<<"]: ";
        cout<<*(p+i)<<endl;
    }
    return 0;
}


float *Gauss_seidel()
{
    float k[n],e[n],C[n];
    static float x[100];
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            float sum=0;
            if (i!=j)
            {
                k[i]=sum + (A[i][j]/A[i][i]);
            }
        }
    }

    float maxi;
    maxi=k[0];
    for (int i=0;i<n;i++)
    {
        if (k[i]>maxi)
        {
            maxi=k[i];
        }
    }
    cout<<maxi<<endl;

    if (maxi>1)
    {
       cout<<"The Given scheme will not converge";
    }
    else
    {
        float error=100;
        while(error>0.1)
        {
            for (int i=0;i<n;i++)
            {
                C[i]=x[i];
            }
            for (int i=0;i<n;i++)
                {
                  float sum1=0;
                  for (int j=0;j<n;j++)
                      {
                         if (i!=j)
                           {
                             sum1=sum1+(A[i][j]*x[j]);
                           }
                      }
                  x[i]=(B[i]-sum1)/A[i][i];
                }
             error= abs(((C[0]-x[0])/x[0])*100);
             for (int i=0;i<n;i++)
             {
                 e[i]= abs(((C[i]-x[i])/x[i])*100);
                 if (e[i]>error)
                    {error=e[i];
                    }
             }

         }
    }
    return x;
}
