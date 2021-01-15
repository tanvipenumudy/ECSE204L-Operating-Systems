
#include <stdio.h>
#include <string.h>
int main(){
	char a[40]="qwertytrewq";
	printf("The String is %s",a);
	int len;
	int flag=0;
	len=strlen(a);
	for(int i=0; i<len ;i++){
	if(a[i]!=a[len-i-1]){
	flag=1;
        break;}
	}

	if(flag){
	printf(" is not a Palindrome");}
	else{
	printf(" is a Palindrome");}
	return 0;
	}
	

	
	
    
  
    
 
