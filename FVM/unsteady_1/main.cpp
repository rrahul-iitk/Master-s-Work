#include <iostream>
#include<cmath>
#include<fstream>

using namespace std;
float T[10000][200][200];
int n;
float T1,T2,T3,T4;
float sp,sc,k,rho,count;
float f[200],g[200],b[200],e[200];
float *thomasalgorithm();

int main()
{
    T1=300;T2=1000;T3=600;T4=500;
    k=0.00002;//thermal conductivity of mild steel
    rho=1;//density of the mild steel
    float x,y;
    float dx,dy,dt;
    float temp[200][200];
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
    cout<<"Enter the value of time step:";
    cin>>dt;
    dx=x/n;
    dy=y/n;
    float ap[n][n],aw[n][n],ae[n][n],an[n][n],as[n][n],apo;
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
                 ae[i][j]=(k*dy*2)/dx;
            }
            else{ae[i][j]=(k*dy)/dx;}
       }
     }
     apo=(rho*dx*dy)/dt;
     for (int i=0;i<n;i++)
     {
         for (int j=0;j<n;j++)
         {
             ap[i][j]=as[i][j]+an[i][j]+ae[i][j]+aw[i][j]-(sp*dx*dy)+apo;
         }
     }
  float initial_temp;
  cout<<"Enter the initial temperature of the plate:";
  cin>>initial_temp;
  for(int i=0;i<n;i++)
  {
      for(int j=0;j<n;j++)
      {
          T[0][i][j]=initial_temp;
      }
  }

  float er[200][200];
  float error1=1000;
  float error2;
  int t=0;
  while(error1>0.01)
  {
    t=t+1;
    float error=1000;
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
                      b[j]=(sc*dx*dy)+((aw[i][j])*T1)+((as[i][j])*T3)+((an[i][j])*temp[i+1][j])+(apo*T[t-1][i][j]);
                    }
                   else
                    {
                      e[j]=-aw[i][j];
                      f[j]=ap[i][j];
                      if (j<n-1)
                       {
                         g[j]=-ae[i][j];
                         b[j]=(sc*dx*dy)+((as[i][j])*T3)+((an[i][j])*temp[i+1][j])+(apo*T[t-1][i][j]);
                       }
                      else
                       {g[j]=0;
                        b[j]=(sc*dx*dy)+((ae[i][j])*T2)+((as[i][j])*T3)+((an[i][j])*temp[i+1][j])+(apo*T[t-1][i][j]);
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
                      b[j]=(sc*dx*dy)+((aw[i][j])*T1)+((an[i][j])*T4)+((as[i][j])*temp[i-1][j])+(apo*T[t-1][i][j]);
                    }
                   else
                    {
                      e[j]=-aw[i][j];
                      f[j]=ap[i][j];
                      if (j<n-1)
                       {
                         g[j]=-ae[i][j];
                         b[j]=(sc*dx*dy)+((an[i][j])*T4)+((as[i][j])*temp[i-1][j])+(apo*T[t-1][i][j]);
                       }
                      else
                       {g[j]=0;
                        b[j]=(sc*dx*dy)+((ae[i][j])*T2)+((an[i][j])*T4)+((as[i][j])*temp[i-1][j])+(apo*T[t-1][i][j]);
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
                      b[j]=(sc*dx*dy)+((aw[i][j])*T1)+((as[i][j])*temp[i-1][j])+((an[i][j])*temp[i+1][j])+(apo*T[t-1][i][j]);
                    }
                   else
                    {
                      e[j]=-aw[i][j];
                      f[j]=ap[i][j];
                      if (j<n-1)
                       {
                         g[j]=-ae[i][j];
                         b[j]=(sc*dx*dy)+((as[i][j])*temp[i-1][j])+((an[i][j])*temp[i+1][j])+(apo*T[t-1][i][j]);
                       }
                      else
                       {g[j]=0;
                        b[j]=(sc*dx*dy)+((ae[i][j])*T2)+((as[i][j])*temp[i-1][j])+((an[i][j])*temp[i+1][j])+(apo*T[t-1][i][j]);
                       }
                     }
             }
           }

           float *p;
           p= thomasalgorithm();
           for (int j=0;j<n;j++)
           {
               temp[i][j]=*(p+j);
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
                      b[i]=(sc*dx*dy)+((aw[i][j])*T1)+((as[i][j])*T3)+((ae[i][j])*temp[i][j+1])+(apo*T[t-1][i][j]);
                    }
                   else
                    {
                      e[i]=-as[i][j];
                      f[i]=ap[i][j];
                      if (i<n-1)
                       {
                         g[i]=-an[i][j];
                         b[i]=(sc*dx*dy)+((aw[i][j])*T1)+((ae[i][j])*temp[i][j+1])+(apo*T[t-1][i][j]);
                       }
                      else
                       {g[i]=0;
                        b[i]=(sc*dx*dy)+((aw[i][j])*T1)+((an[i][j])*T4)+((ae[i][j])*temp[i][j+1])+(apo*T[t-1][i][j]);
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
                      b[i]=(sc*dx*dy)+((as[i][j])*T3)+((ae[i][j])*T2)+((aw[i][j])*temp[i][j-1])+(apo*T[t-1][i][j]);
                    }
                   else
                    {
                      e[i]=-as[i][j];
                      f[i]=ap[i][j];
                      if (i<n-1)
                       {
                         g[i]=-an[i][j];
                         b[i]=(sc*dx*dy)+((ae[i][j])*T2)+((aw[i][j])*temp[i][j-1])+(apo*T[t-1][i][j]);
                       }
                      else
                       {g[i]=0;
                        b[i]=(sc*dx*dy)+((ae[i][j])*T2)+((an[i][j])*T4)+((aw[i][j])*temp[i][j-1])+(apo*T[t-1][i][j]);
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
                      b[i]=(sc*dx*dy)+((as[i][j])*T3)+((aw[i][j])*temp[i][j-1])+((ae[i][j])*temp[i][j+1])+(apo*T[t-1][i][j]);
                    }
                   else
                    {
                      e[i]=-as[i][j];
                      f[i]=ap[i][j];
                      if (i<n-1)
                       {
                         g[i]=-an[i][j];
                         b[i]=(sc*dx*dy)+((aw[i][j])*temp[i][j-1])+((ae[i][j])*temp[i][j+1])+(apo*T[t-1][i][j]);
                       }
                      else
                       {g[i]=0;
                        b[i]=(sc*dx*dy)+((an[i][j])*T4)+((aw[i][j])*temp[i][j-1])+((ae[i][j])*temp[i][j+1])+(apo*T[t-1][i][j]);
                       }
                     }
             }
           }
           float *p;
           p= thomasalgorithm();
           for (int i=0;i<n;i++)
           {
               temp[i][j]=*(p+i);
           }
     }
     /*end of vertical sweep*/
   float sum1=0;
     float sum=0;
     for (int i=0;i<n;i++)
     {
         for (int j=0;j<n;j++)
         {
             sum= sum + ((ap[i][j])*temp[i][j]);
             if((i==0)||(i==n-1))
             {if (i==0)
             {
                 if (j==0)
                 {
                    sum1= sum1+ (aw[i][j]*T1)+(as[i][j]*T3)+((an[i][j])*temp[i+1][j])+((ae[i][j])*temp[i][j+1])-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);//add source term for source problem
                 }
                 else{
                     if(j<n-1)
                    {sum1= sum1+ (aw[i][j]*(temp[i][j-1]))+(as[i][j]*T3)+((an[i][j])*temp[i+1][j])+((ae[i][j])*temp[i][j+1])-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);}
                    else
                    {sum1= sum1+ (aw[i][j]*(temp[i][j-1]))+(as[i][j]*T3)+((an[i][j])*temp[i+1][j])+((ae[i][j])*T2)-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);
                    }
                   }
             }
             else {
                if (j==0)
                 {
                    sum1= sum1+ (aw[i][j]*T1)+(as[i][j]*(temp[i-1][j]))+((an[i][j])*T4)+((ae[i][j])*temp[i][j+1])-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);//add source term for source problem
                 }
                 else{
                     if(j<n-1)
                    {sum1= sum1+ (aw[i][j]*(temp[i][j-1]))+(as[i][j]*temp[i-1][j])+((an[i][j])*T4)+((ae[i][j])*temp[i][j+1])-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);}
                    else
                    {sum1= sum1+ (aw[i][j]*(temp[i][j-1]))+(as[i][j]*temp[i-1][j])+((an[i][j])*T4)+((ae[i][j])*T2)-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);
                    }
                   }
             }
           }
           else {if (j==0)
                 {
                    sum1= sum1+ (aw[i][j]*T1)+(as[i][j]*(temp[i-1][j]))+((an[i][j])*temp[i+1][j])+((ae[i][j])*temp[i][j+1])-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);//add source term for source problem
                 }
                 else{
                     if(j<n-1)
                    {sum1= sum1+ (aw[i][j]*(temp[i][j-1]))+(as[i][j]*temp[i-1][j])+((an[i][j])*temp[i+1][j])+((ae[i][j])*temp[i][j+1])-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);}
                    else
                    {sum1= sum1+ (aw[i][j]*(temp[i][j-1]))+(as[i][j]*temp[i-1][j])+((an[i][j])*temp[i+1][j])+((ae[i][j])*T2)-((ap[i][j])*temp[i][j])+(apo*T[t-1][i][j])+(sc*dx*dy);}
                    }
                   }
                }
     }
     error2=(sum1/sum);
     if (error2<0)
     {
         error=((-1)*error2);
     }
     else{error=error2;}
    // cout<<error<<endl;
   }

    for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
    {
        T[t][i][j]=temp[i][j];
    }
   }
   error1= abs(((T[t][0][0]-T[t-1][0][0])/T[t-1][0][0]))*100;

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            er[i][j]= abs(((T[t][i][j]-T[t-1][i][j])/T[t-1][i][j]))*100;
            if (er[i][j]>error1)
             {
              error1=er[i][j];
             }
        }
    }
  //  cout<<"......"<<endl;
   // cout<<error1<<endl;
   // cout<<"......"<<endl;
    count=t;
  }
   // Writing to the text file
  // Writing to the text file
   ofstream myfile;
   myfile.open("Unsteady_1.dat");
   if(myfile.is_open())
   {
   		for(int k=0;k<=count;k++){

   		myfile<<"title = Problem-4 Plot"<<endl;
    	myfile<<"variables = x,y,temp"<<endl;
    	myfile<<"zone i="<<n<<", j="<<n<<", f=point"<<endl;
    	myfile<<"SolutionTime= "<<k<<endl;
       for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
    {


        	myfile<<(j*dy+(dy/2))<<"\t"<<(i*dx+(dx/2))<<"\t"<<T[k][i][j]<<endl;



    }
    myfile<<endl;
   }

   //cout<<"Successfully Written"<<endl;
   }}
   else{cout<<"Error"<<endl;}
   cout<<"Succesfully written";

   myfile.close();
   for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
    {
        cout<<T[t][i][j];
        cout<<"  ";
    }
    cout<<endl;
   }
   cout<<count;
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
