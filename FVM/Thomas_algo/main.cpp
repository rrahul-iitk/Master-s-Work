#include <iostream>
#include<math.h>
using namespace std;

int main()
{
    int n;
    float A[100][100], B[100];
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

     for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            cout<<A[i][j]<<"   ";
        }
        cout<<endl;
    }
    cout<<"\n\n\n";

    for (int c=0;c<n;c++)
      {
        cout<<"\nEnter the element B["<<c<<"]=";
        cin>>B[c];
      }
    for (int j=0;j<n;j++)
        {
            cout<<B[j]<<"   ";
        }
    cout<<endl;
    int i,j;
    float L[n][n],U[n][n],C[n];
    float x[n];

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            L[i][j]=0;
            U[i][j]=0;
        }
    }

    for (i=0;i<n;i++)
    {
       for (j=0;j<n;j++)
       {
          if ((i==0)&&(j==0))
           {
            //if (j==0)
            //{
            L[i][i]=1;
            U[i][i]=A[i][i];
            U[i][i+1]=A[i][i+1];
            //}
           }

         if (i>0)
         {
            if (i==j)
            {
               L[i][i]=1;
               L[i][i-1]=A[i][i-1]/U[i-1][i-1];
               U[i][i]=A[i][i]-(L[i][i-1]*A[i-1][i]);
               if (i<n-1)
               {
                  U[i][i+1]=A[i][i+1];
               }
            }
          }

       }
    }

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            cout<<L[i][j]<<"   ";
        }
        cout<<endl;
    }
    cout<<"\n\n\n";

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            cout<<U[i][j]<<"   ";
        }
        cout<<endl;
    }

    for (i=0;i<n;i++)
     {
       if (i==0)
       {
          C[i]=B[i];
       }

       else
        {
         C[i]=B[i]-(L[i][i-1]*C[i-1]);
        }
     }
     for (int i=0;i<n;i++)
       {
        cout<<"C["<<i+1<<"]: ";
        cout<<C[i]<<endl;
       }

    int k=n-1;
    cout<<k<<endl;
    while (k>=0)
    {
        if (k==n)
        {
            x[k]=C[k]/U[k][k];
        }

        else
        {
           x[k]=(C[k]-(A[k][k+1]*x[k+1]))/U[k][k];
        }
        k=k-1;
    }
    for (int i=0;i<n;i++)
    {
        cout<<"X["<<i+1<<"]: ";
        cout<<x[i]<<endl;
    }
    return 0;
}


