clear all
clc
syms x
q= input('Enter the value of q = ');
H= input('Enter the value of H = '); 
G= input('Enter the value of G = ');
f=q*x;
disp(f);

d=-(G+(q/6)+H);
disp(d);

p=(q*(x^3))/6;
Q=-(p+(H*x)+d);
fprintf('Exact Form\n');
disp(Q);
R=diff(Q,x);
fprintf('1st differentiation\n');
disp(R);

a= input('Enter the lower limit of the interval= ');
b= input('Enter the upper limit of the interval= ');
n= input('Enter the number of intervals= ');
fprintf ('Do you want mesh to be 1.Uniform or 2.Non uniform?\n');
variable= input('');
h=zeros(1,n);
if variable==1
    fprintf('Uniform Mesh\n');
    for i=1:n
        h(i)= (b-a)/n;
    end
else
    fprintf('Non-uniform Mesh\n');
    for i=1:n
        h(i)= input('Enter the value of interval:');
    end
end
fprintf('Intervals\n');
disp(h);

t=zeros(1,n);
for i=1:n+1
    if i==1
        t(i)=a;
    else
        t(i)=t(i-1)+h(i-1);
    end
end
%disp(t);

if (t(n+1)>=0.999*b && t(n+1)<=1.001*b)
    fprintf('Node points\n');
    disp(t);
else
     fprintf('Error!!! Please Enter correct data.');
     %for i=1:n
     %   h(i)= input('Enter the value of interval:');
     % end
     break;
end

%Defining The Shape function
for i=1:n+1
    for j=1:n
        if (i==1 || i==n+1)
            if (i==1)
               N(i,i)= (t(i+1)-x)/h(i);
            end
            if (i==n+1 && j==n)
               N(i,j)= (x-t(i-1))/h(i-1);
            else
               N(i,j)=0;
            end
        else
            if (j==i-1 || j==i)
                if (j==i-1)
                   N(i,j)= (x-t(i-1))/h(i-1);
                else
                   N(i,j)= (t(i+1)-x)/h(i);
                end
            else
                N(i,j)=0;
            end
        end
    end
end
fprintf('Shape Functions\n');
disp (N)

M= diff(N,x);
fprintf('1st differentiation of Shape Functions\n');
disp(M)

%Calculation of Stiffness Matrix
K= zeros(n);
for i=1:n
    for j=1:n
        for k=1:n
            sum= int((M(i,k)*M(j,k)),t(k),t(k+1));
            K(i,j)= sum + K(i,j);
        end
    end
end
fprintf('Stiffness Matrix\n');
disp(K)
%K1=inv(K);
%disp(K1);

%Calculation of Force Vector
Z=zeros(1,n);
for i=1:n
    sum2=0;
    for j=1:n
        p= int((N(i,j)*f),t(j),t(j+1));
        q1= H*subs(N(i,1),x,0);
        r= G*int((N(i,j)*N(n+1,j)),t(j),t(j+1));
        s= p+q1-r;
        sum2= s + sum2;
    end
    Z(i)=sum2;
end
F=Z';
fprintf('Force Vector Matrix\n');
disp(F);
%Calculation of Displacement vector
%d=inv(K)*F;
%d=K\F; % As inv(K)*F can be slower and less accurate
L=zeros(n,n);
U=zeros(n,n);
 for i=1:n
     for j=1:n
         if (i==1 && j==1)
             L(i,i)=1;
             U(i,i)=K(i,i);
             U(i,i+1)=K(i,i+1);
         end
         if (i==j && i~=1)
             L(i,i)=1;
             L(i,i-1)=K(i,i-1)/U(i-1,i-1);
             U(i,i)=K(i,i)-(L(i,i-1)*K(i-1,i));
             if (i<n)
              U(i,i+1)=K(i,i+1);
             end
         end
     end
 end
 C=zeros(i,1);
 for i=1:n
     if (i==1)
         C(i,1)=Z(i);
     else 
         C(i,1)=Z(i)-(L(i,i-1)*Z(i-1));
     end
 end
 k=n;
 x=zeros(k,1);
 while (k>0)
     if (k==n)
         x(k,1)=C(k,1)/U(k,k);
     else
         x(k,1)=(C(k,1)-(K(i-1)*x(k+1)))/U(k,k);
     end
 end
 %disp(L);
 %disp(U);
 disp(x);
fprintf('Dispacement Matrix\n');
disp(d);

for i=1:n
    sum3=0;
    for j=1:n
        if(i<n)
         sum3= (d(j)*N(j,i))+sum3;
        else
            sum3= d(j)*N(j,i)+(G*N(n+1,n))+sum3;
        end
    end
    U(i,1)=sum3;
end
fprintf('Piecewise distribution of function u\n');
disp(U);

U1= zeros(n+1,1);
for i=1:n+1
    if (i<n+1)
        U1(i)=subs(U(i,1),x,t(i));
    else
        U1(i)=subs(U(n,1),x,t(i));
    end
end
fprintf('Value of function u at each node points\n');
disp(U1);
plot(t,U1,'-bo');
xlabel('x')
ylabel('u(x)')
set (gca,'fontsize',14);
    
V=diff(U,x);
disp(V);

s=zeros(n,1);
for i=1:n
    s(i)=(t(i)+t(i+1))/2;
end
fprintf('Midpoints at each interval\n');
disp(s);

e=zeros(n,1);
e1=zeros(n,1);
e2=zeros(n,1);
r1=zeros(n,1);
for i=1:n
    e1(i)=subs(V(i),x,s(i));
    e2(i)=subs(R,x,s(i));
    r1(i)=(e1(i)-e2(i))/(q/2);
    e(i,1)=abs(r1(i));
end
%disp(e1);
%disp(e2);
%disp(r1);
fprintf('Error value\n');
disp(e);
    









        



     



    