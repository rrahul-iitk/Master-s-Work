#include <iostream>
#include<cmath>
#include<fstream>

using namespace std;
float T[100][100];
float dx, dy;
int n;
float T1,q,T3,T4;
float sp,sc,k;
float f[100],g[100],b[100],e[100];
float *thomasalgorithm();

int main()
{
    T1=300;q=0;T3=600;T4=500;
    k=0.00002;
    float x,y;
    cout<<"Enter the source value(Sp): ";
    cin>>sp;
    cout<<"Enter the source flux(Sc): ";
    cin>>sc;
    cout<<"Enter the number of intervals: ";
    cin>>n;
    cout<<"Enter the x-length of the plate: ";
    cin>>x;
    cout<<"Enter the y-length of the plate: ";
    cin>>y;
    dx=x/n;
    dy=y/n;
    float ap[n][n],aw[n][n],ae[n][n],an[n][n],as[n][n];
    for (int i=0; i<n; i++)
     {
       for (int j=0;j<n; j++)
        {
           if (i==0)
            {
              as[i][j]=(k*dx*2)/dy;
            }
            else
            {
              as[i][j]=(k*dx)/dy;
            }
            if (j==0)
            {
              aw[i][j]=(k*dy*2)/dx;
            }
            else {aw[i][j]=(k*dy)/dx;}
            if (i==n-1)
            {
              an[i][j]=(k*dx*2)/dy;
            }
            else{an[i][j]=(k*dx)/dy;}
            if (j==n-1)
            {
                 ae[i][j]=0;
            }
            else{ae[i][j]=(k*dy)/dx;}
       }
     }
     for (int i=0;i<n;i++)
     {
         for (int j=0;j<n;j++)
         {
             ap[i][j]=as[i][j]+an[i][j]+ae[i][j]+aw[i][j];
         }
     }

  float error=100;
  while(error>0.0000001)
 {
    //Horizontal Sweeping

    for (int i=0; i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            //for the uppermost and lowermost//
            if ((i==0)||(i==n-1))
            {
                if (i==0)
                {  if (j==0)
                    {
                      e[j]=0;
                      f[j]=ap[i][j];
                      g[j]=-ae[i][j];
                      b[j]=(sc*dx*dy)+((aw[i][j])*T1)+((as[i][j])*T3)+((an[i][j])*T[i+1][j]);
                    }
                   else
                    {
                      e[j]=-aw[i][j];
                      f[j]=ap[i][j];
                      if (j<n-1)
                       {
                         g[j]=-ae[i][j];
                         b[j]=(sc*dx*dy)+((as[i][j])*T3)+((an[i][j])*T[i+1][j]);
                       }
                      else
                       {g[j]=0;
                        b[j]=(sc*dx*dy)+(q*dy)+((as[i][j])*T3)+((an[i][j])*T[i+1][j]);
                       }
                     }
                  }
                else
                {
                if (j==0)
                    {
                      e[j]=0;
                      f[j]=ap[i][j];
                      g[j]=-ae[i][j];
                      b[j]=(sc*dx*dy)+((aw[i][j])*T1)+((an[i][j])*T4)+((as[i][j])*T[i-1][j]);
                    }
                   else
                    {
                      e[j]=-aw[i][j];
                      f[j]=ap[i][j];
                      if (j<n-1)
                       {
                         g[j]=-ae[i][j];
                         b[j]=(sc*dx*dy)+((an[i][j])*T4)+((as[i][j])*T[i-1][j]);
                       }
                      else
                       {g[j]=0;
                        b[j]=(sc*dx*dy)+(q*dy)+((an[i][j])*T4)+((as[i][j])*T[i-1][j]);
                       }
                     }
                }
            }

            else
            {
              if (j==0)
                    {
                      e[j]=0;
                      f[j]=ap[i][j];
                      g[j]=-ae[i][j];
                      b[j]=(sc*dx*dy)+((aw[i][j])*T1)+((as[i][j])*T[i-1][j])+((an[i][j])*T[i+1][j]);
                    }
                   else
                    {
                      e[j]=-aw[i][j];
                      f[j]=ap[i][j];
                      if (j<n-1)
                       {
                         g[j]=-ae[i][j];
                         b[j]=(sc*dx*dy)+((as[i][j])*T[i-1][j])+((an[i][j])*T[i+1][j]);
                       }
                      else
                       {g[j]=0;
                        b[j]=(sc*dx*dy)+(q*dy)+((as[i][j])*T[i-1][j])+((an[i][j])*T[i+1][j]);
                       }
                     }
             }
           }

           float *p;
           p= thomasalgorithm();
           for (int j=0;j<n;j++)
           {
               T[i][j]=*(p+j);
           }
     }
     /*End for horizontal sweep*/
     /*for vertical sweep*/
    for (int j=0; j<n;j++)
     {
        for (int i=0;i<n;i++)
        {
            //for the uppermost and lowermost//
            if ((j==0)||(j==n-1))
            {
                if (j==0)
                {  if (i==0)
                    {
                      e[i]=0;
                      f[i]=ap[i][j];
                      g[i]=-an[i][j];
                      b[i]=(sc*dx*dy)+((aw[i][j])*T1)+((as[i][j])*T3)+((ae[i][j])*T[i][j+1]);
                    }
                   else
                    {
                      e[i]=-as[i][j];
                      f[i]=ap[i][j];
                      if (i<n-1)
                       {
                         g[i]=-an[i][j];
                         b[i]=(sc*dx*dy)+((aw[i][j])*T1)+((ae[i][j])*T[i][j+1]);
                       }
                      else
                       {g[i]=0;
                        b[i]=(sc*dx*dy)+((aw[i][j])*T1)+((an[i][j])*T4)+((ae[i][j])*T[i][j+1]);
                       }
                     }
                  }
                else
                {
                if (i==0)
                    {
                      e[i]=0;
                      f[i]=ap[i][j];
                      g[i]=-an[i][j];
                      b[i]=(sc*dx*dy)+((as[i][j])*T3)+(q*dy)+((aw[i][j])*T[i][j-1]);
                    }
                   else
                    {
                      e[i]=-as[i][j];
                      f[i]=ap[i][j];
                      if (i<n-1)
                       {
                         g[i]=-an[i][j];
                         b[i]=(sc*dx*dy)+(q*dy)+((aw[i][j])*T[i][j-1]);
                       }
                      else
                       {g[i]=0;
                        b[i]=(sc*dx*dy)+(q*dy)+((an[i][j])*T4)+((aw[i][j])*T[i][j-1]);
                       }
                     }
                }
            }

            else
            {
              if (i==0)
                    {
                      e[i]=0;
                      f[i]=ap[i][j];
                      g[i]=-an[i][j];
                      b[i]=(sc*dx*dy)+((as[i][j])*T3)+((aw[i][j])*T[i][j-1])+((ae[i][j])*T[i][j+1]);
                    }
                   else
                    {
                      e[i]=-as[i][j];
                      f[i]=ap[i][j];
                      if (i<n-1)
                       {
                         g[i]=-an[i][j];
                         b[i]=(sc*dx*dy)+((aw[i][j])*T[i][j-1])+((ae[i][j])*T[i][j+1]);
                       }
                      else
                       {g[i]=0;
                        b[i]=(sc*dx*dy)+((an[i][j])*T4)+((aw[i][j])*T[i][j-1])+((ae[i][j])*T[i][j+1]);
                       }
                     }
             }
           }
           float *p;
           p= thomasalgorithm();
           for (int i=0;i<n;i++)
           {
               T[i][j]=*(p+i);
           }
     }
     float a[n];
     for (int i=0;i<n;i++)
     {
         a[i]=((q*dx)/(2*k))+T[i][n-1];
     }
     /*end of vertical sweep*/
     float sum1=0;
     float sum=0;
     for (int i=0;i<n;i++)
     {
         for (int j=0;j<n;j++)
         {
             sum= sum + ((ap[i][j])*T[i][j]);
             if((i==0)||(i==n-1))
             {if (i==0)
             {
                 if (j==0)
                 {
                    sum1= sum1+ (aw[i][j]*T1)+(as[i][j]*T3)+((an[i][j])*T[i+1][j])+((ae[i][j])*T[i][j+1])-((ap[i][j])*T[i][j]);//add source term for source problem
                 }
                 else{
                     if(j<n-1)
                    {sum1= sum1+ (aw[i][j]*(T[i][j-1]))+(as[i][j]*T3)+((an[i][j])*T[i+1][j])+((ae[i][j])*T[i][j+1])-((ap[i][j])*T[i][j]);}
                    else
                    {sum1= sum1+ (aw[i][j]*(T[i][j-1]))+(as[i][j]*T3)+((an[i][j])*T[i+1][j])+((ae[i][j])*a[i])-((ap[i][j])*T[i][j]);
                    }
                   }
             }
             else {
                if (j==0)
                 {
                    sum1= sum1+ (aw[i][j]*T1)+(as[i][j]*(T[i-1][j]))+((an[i][j])*T4)+((ae[i][j])*T[i][j+1])-((ap[i][j])*T[i][j]);//add source term for source problem
                 }
                 else{
                     if(j<n-1)
                    {sum1= sum1+ (aw[i][j]*(T[i][j-1]))+(as[i][j]*T[i-1][j])+((an[i][j])*T4)+((ae[i][j])*T[i][j+1])-((ap[i][j])*T[i][j]);}
                    else
                    {sum1= sum1+ (aw[i][j]*(T[i][j-1]))+(as[i][j]*T[i-1][j])+((an[i][j])*T4)+((ae[i][j])*a[i])-((ap[i][j])*T[i][j]);
                    }
                   }
             }
           }
           else {if (j==0)
                 {
                    sum1= sum1+ (aw[i][j]*T1)+(as[i][j]*(T[i-1][j]))+((an[i][j])*T[i+1][j])+((ae[i][j])*T[i][j+1])-((ap[i][j])*T[i][j]);//add source term for source problem
                 }
                 else{
                     if(j<n-1)
                    {sum1= sum1+ (aw[i][j]*(T[i][j-1]))+(as[i][j]*T[i-1][j])+((an[i][j])*T[i+1][j])+((ae[i][j])*T[i][j+1])-((ap[i][j])*T[i][j]);}
                    else
                    {sum1= sum1+ (aw[i][j]*(T[i][j-1]))+(as[i][j]*T[i-1][j])+((an[i][j])*T[i+1][j])+((ae[i][j])*a[i])-((ap[i][j])*T[i][j]);
                    }
                   }
                }
     }}
     error=sum1/sum;
     cout<<error<<endl;

   }


   for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
    {
        cout<<T[i][j];
        cout<<"..";
    }
    cout<<endl;
   }
   // Writing to the text file
  // Writing to the text file
   ofstream myfile;
   myfile.open("neumann_1.dat");
   if(myfile.is_open())
   {

   		myfile<<"title = Problem-4 Plot"<<endl;
    	myfile<<"variables = x,y,temp"<<endl;
    	myfile<<"zone i="<<n<<", j="<<n<<", f=point"<<endl;

       for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
    {


        	myfile<<(j*dy+(dy/2))<<"\t"<<(i*dx+(dx/2))<<"\t"<<T[i][j]<<endl;



    }
    myfile<<endl;
   }
   cout<<"Successfully written";}
   else{cout<<"Error occured";}
  return 0;
}

float *thomasalgorithm()
{
    float f1[n],g1[n],r[n],e1[n];
    static float x[100];
    for (int i=0;i<n;i++)
    {if (i==0)
       {e1[i]=0;
           f1[i]=f[i];
           g1[i]=g[i];
       }
       else
       { e1[i]=e[i]/f1[i-1];
           f1[i]=f[i]-(e1[i]*g1[i-1]);
           if (i<n-1)
           {
               g1[i]=g[i];
           }
           else
           {g1[i]=0;}
       }
    }
    for (int i=0;i<n;i++)
     { if (i==0)
       {r[i]=b[i];}
       else
        {
         r[i]=b[i]-(e1[i]*r[i-1]);
        }
     }
    int k=n-1;
    while (k>=0)
    {  if (k==n-1)
        {
            x[k]=r[k]/f1[k];
        }
        else
        {
           x[k]=(r[k]-(g1[k]*x[k+1]))/f1[k];
        }
        k=k-1;
    }
    return x;
}
