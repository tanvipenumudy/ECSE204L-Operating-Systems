#include <stdio.h>
#include <stdlib.h>


void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
    for (i = 0; i < n - 1; i++) { 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 
        swap(&arr[min_idx], &arr[i]); 
    } 
}

int main()
{
    int endtrack=199;
    int direction=1;
    int head=40;
    int tracks[]={45, 6, 8, 22, 176, 27, 77, 33, 30, 168, 190, 1, 3};
    int trackslen=sizeof tracks / sizeof tracks[0];
    selectionSort(tracks,trackslen);
    
    int first=0;
    
    for(int i=0;i<trackslen;i++){
        if(head<=tracks[i]){
            first=i;
            break;
        }
    }
    
    
    int seektime=0;
    if(direction==1){
        
        for(int i=first;i<trackslen;i++){
            printf("%d ",tracks[i]);
            seektime+=abs(head-tracks[i]);
            head=tracks[i];
        }
    
        for(int i=first-1;i>=0;i--){
            printf("%d ",tracks[i]);
            seektime+=abs(head-tracks[i]);
            head=tracks[i];
        }
    }
    
    else{
        
        for(int i=first-1;i>=0;i--){
            printf("%d ",tracks[i]);
            seektime+=abs(head-tracks[i]);
            head=tracks[i];
        }
        
        for(int i=first;i<trackslen;i++){
            printf("%d ",tracks[i]);
            seektime+=abs(head-tracks[i]);
            head=tracks[i];
        }
    }

    printf("\nLOOK Seek Time = %d", seektime);

    return 0;
}
