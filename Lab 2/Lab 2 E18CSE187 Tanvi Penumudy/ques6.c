#include <stdio.h>
int main(){
int flag = 0;
int num = 13;
for(int i=2;i<=num/2;++i){
	if(num%i==0){
        flag = 1;
        break;}}
    if(num==1){
        printf("Number is neither Prime nor Composite");}
    else {
        if(flag==0){
            printf("%d is Prime", num);}
        else{
            printf("%d is Composite", num);}
    }
    return 0;
}