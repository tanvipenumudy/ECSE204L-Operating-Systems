#include <stdio.h>
#include <stdlib.h>


int deleteElement(int arr[], int n, int x) 
{ 
   int i; 
   for (i=0; i<n; i++) 
      if (arr[i] == x) 
         break; 
  
   if (i < n) 
   { 
     n = n - 1; 
     for (int j=i; j<n; j++) 
        arr[j] = arr[j+1]; 
   } 
  
   return n; 
} 

int main()
{
    int head=40;
    int tracks[]={45, 6, 8, 22, 176, 27, 77, 33, 30, 168, 190, 1, 3};
    int trackslen=sizeof tracks / sizeof tracks[0];
    int seektime=0;
    int n=trackslen;
    
    for(int i=0;i<trackslen;i++){
        int temp=1000000;
        int index=0;
        for(int j=0;j<n;j++){
            if(abs(head-tracks[j])<temp){
                temp=abs(head-tracks[j]);
                index=j;
            }
        }
        printf("%d ",tracks[index]);
        head=tracks[index];
        seektime+=temp;
        n=deleteElement(tracks, n, tracks[index]);
    }
    
    printf("\nSSTF Seek Time = %d", seektime);

    return 0;
}
