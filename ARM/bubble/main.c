#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void bubble(int a[], int n);

void init(int a[], int n)
{
int i;
srand(time(NULL));
for (i = 0; i < n; i++)
a[i] = rand()%100;
return ;
}

void print(int a[], int n)
{
int i;
for (i = 0; i < n; i++)
printf("%3d",a[i]);
printf("\n");
return ;
}
int main(void)
{
int a[20];
init(a, 20);
print(a,20);

bubble(a,20);

print(a,20);
return 0;
}

