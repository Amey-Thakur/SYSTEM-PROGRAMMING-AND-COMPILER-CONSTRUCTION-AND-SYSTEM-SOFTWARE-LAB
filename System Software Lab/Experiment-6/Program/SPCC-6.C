#include<stdio.h>
#include<conio.h>
#include<string.h>
int main()
{
char A[12][12]={"T=A B","X=T"};
char B;
int OP=0;
printf("MOV %c,R1\n",A[0][2]);
printf("MOV %c,R2\n",A[0][4]);

B=A[0][3];
printf("THERE ARE TWO EXPRESSIONS: \n1.T=A OP B\n2.X=T\nCHOOSE THE OP VALUE FROM OPTION\n1.+\n2.-\n3.*\n4./\n");
scanf("%d",&OP);
switch(OP)
{
case 1:
printf("ADD R1,R2\n");
break;
case 2:
printf("SUB R1,R2\n");
break;
case 3:
printf("MUL R1,R2\n");
break;
case 4:
printf("DIV R1,R2\n");
break;
default:
break;
}
printf("MOV R1,x");
getch();
}
