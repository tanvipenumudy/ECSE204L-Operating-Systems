#include <stdio.h>
int main(){
char str1[40]="abc";
char str2[40]="def";
    for(int i=0;str1[i]!='\0';++i){
        printf("i=%d\n",i);}
    for(int j=0;str2[j]!='\0';++j,++i){
        str1[i]=str2[j];}
    str1[i]='\0';
    printf("After Concatenating both Strings: ");
    puts(str1);
    return 0;
}

