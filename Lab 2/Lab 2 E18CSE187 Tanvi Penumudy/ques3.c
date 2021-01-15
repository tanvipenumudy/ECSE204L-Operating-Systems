#include <stdio.h>
int main(){
int t1=0;
int t2=1;
int t3;
for(int i=0;i<=10;i++){
printf("\n%d",t1);
t3=t1+t2;
t1=t2;
t2=t3;
}
return 0;
}


