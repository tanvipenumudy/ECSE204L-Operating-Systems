#include <stdio.h>
#include <stdlib.h>

int main()
{
    int head=40;
    int tracks[]={45, 6, 8, 22, 176, 27, 77, 33, 30, 168, 190, 1, 3};
    int trackslen=sizeof tracks / sizeof tracks[0];
    int seektime=0;
    
    for(int i=0;i<trackslen;i++){
        printf("%d ", tracks[i]);
        seektime+=abs(head-tracks[i]);
        head=tracks[i];
    }
    
    printf("\nFCFS Seek Time = %d", seektime);

    return 0;
}
