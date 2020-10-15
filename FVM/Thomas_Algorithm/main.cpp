#include <iostream>
#include<math.h>
using namespace std;

int n;
float A[100][100], B[100];
float *thomasalgorithm();

int main()
{

    cout<<"Enter the value of n:";
    cin>>n;
    for (int a=0;a<n;a++)
     {
       for (int b=0;b<n;b++)
        {
        cout<<"\nEnter the element A["<<a+1<<b+1<<"]=";
        cin>>A[a][b];
        }
     }

    for (int c=0;c<n;c++)
      {
        cout<<"\nEnter the element B["<<c<<"]=";
        cin>>B[c];
      }
    float P[n];
    float *p;
    p = thomasalgorithm();
    for(int a=0;a<n;a++)
    {
      cout<<"X["<<a+1<<"]: ";
      P[a]=*(p+a);
      cout<<P[a]<<endl;
    }

    return 0;
}

float *thomasalgorithm()
{
    float f[n],g[n],r[n],e[n];
    static float x[100];

    for (int i=0;i<n;i++)
    {
       if (i==0)
       {
           e[i]=0;
           f[i]=A[i][i];
           g[i]=A[i][i+1];
       }
       else
       {
           e[i]=A[i][i-1]/f[i-1];
           f[i]=A[i][i]-(e[i]*g[i-1]);
           if (i<n-1)
           {
               g[i]=A[i][i-1];
           }
           else
           {
               g[i]=0;
           }
       }
    }


    for (int i=0;i<n;i++)
     {
       if (i==0)
       {
          r[i]=B[i];
       }

       else
        {
         r[i]=B[i]-(e[i]*r[i-1]);
        }
     }


    int k=n-1;

    while (k>=0)
    {
        if (k==n-1)
        {
            x[k]=r[k]/f[k];
        }

        else
        {
           x[k]=(r[k]-(g[k]*x[k+1]))/f[k];
        }
        k=k-1;
    }

    /*for (int a=0; a<n;a++)
    {
        cout<<x[a]<<endl;
    }*/
    return x;
}
