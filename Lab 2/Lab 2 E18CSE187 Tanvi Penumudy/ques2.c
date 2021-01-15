#include <stdio.h>
	int main(){
	int a=1234;
	int rev=0;
	while(a!=0){
	rev=rev*10;
	rev=rev+a%10;
	a=a/10;}
	printf("The reversed number is %d",rev);
	return 0;
	}
