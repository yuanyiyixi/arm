#include <stdio.h>
int main(void)
{
const char *src = "Hello world";
const char *p = src;
char a[20];
char *dst = a;
char *dst_print = dst;
int ch;
__asm
{
loop:
ldrb ch,[src],#1
strb ch,[dst],#1
cmp ch,#0
bne loop
}
printf("Original string:%s\n",p);
printf("Copied string:%s\n",dst_print);
return 0;
}