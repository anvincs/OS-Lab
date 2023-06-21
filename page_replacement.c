#include<stdio.h>
#include<stdlib.h>

struct page {
    int value;
    int lastUsed;
};

struct page frames[3];

void initialize() {
    for(int i=0;i<3;i++) {
        frames[i].value = -1;
        frames[i].lastUsed = -1;
    }
}

void displayRow(int in) {
    printf("   %d         ", in);
            for(int i=0;i<3;i++) {
                if(frames[i].value == -1) {
                    printf("-        ");
                }
                else {
                printf("%d        ", frames[i].value);
                }
            }
            printf("\n");
}

// First In First Out
void fifo(int *arr, int size) {

    initialize();

    int pageFault = 0, pageHit = 0;
    int nt = 0;

    printf("                FIFO                   \n");

    printf("Incoming   Frame 1   Frame 2   Frame 3\n");

    for(int i=0;i<size;i++) {

        if(frames[nt].value == -1) {
            frames[nt].value = arr[i];
            nt = (nt + 1)%3;
            pageFault++;
            displayRow(arr[i]);

            continue;
        }

        int flag = 0;

        for(int j=0;j<3;j++) {

            if(arr[i] == frames[j].value) {
                pageHit++;
                flag = 1;
                displayRow(arr[i]);
                break;
            }
        }

        // replacement
        if(flag == 0) {
            frames[nt].value = arr[i];
            nt = (nt + 1)%3;
            pageFault++;
            displayRow(arr[i]);
        }
    }

    printf("Page Fault = %d\n", pageFault);
    printf("Page Hit = %d\n", pageHit);

}

// Least Recently Used
void lru(int *arr, int size) {
    
    initialize();

    int pageFault = 0, pageHit = 0;
    int nt = 0;

    printf("                LRU                    \n");

    printf("Incoming   Frame 1   Frame 2   Frame 3\n");

    for(int i=0;i<size;i++) {


        if(frames[nt].value == -1) {
            frames[nt].value = arr[i];
            frames[nt].lastUsed = i;
            nt++;
            pageFault++;
            displayRow(arr[i]);

            continue;
        }

        int flag = 0;

        for(int j=0;j<3;j++) {

            if(arr[i] == frames[j].value) {
                pageHit++;
                frames[j].lastUsed = i;
                flag = 1;
                displayRow(arr[i]);
                break;
            }
        }

        // replacement
        if(flag == 0) {
            int low_lu = 999999;
            int low_ind;
            for (int j = 0; j < 3; j++)
            {
                if(frames[j].lastUsed < low_lu) {
                    low_lu = frames[j].lastUsed;
                    low_ind = j;
                }
            }
            frames[low_ind].value = arr[i];
            frames[low_ind].lastUsed = i;
            pageFault++;

            displayRow(arr[i]);
        }
        
    }

    printf("Page Fault = %d\n", pageFault);
    printf("Page Hit = %d\n", pageHit);

}

// Least Frequently Used
void lfu(int *arr, int size, int * freq) {

    initialize();

    int pageFault = 0, pageHit = 0;
    int nt = 0;

    printf("                LFU                    \n");

    printf("Incoming   Frame 1   Frame 2   Frame 3\n");

    for (int i = 0; i < size; i++)
    {

        if(frames[nt].value == -1) {
            frames[nt].value = arr[i];
            frames[nt].lastUsed = i;
            freq[arr[i]]++;
            nt++;
            pageFault++;
            displayRow(arr[i]);

            continue;
        }

        int flag = 0;

        for(int j=0;j<3;j++) {

            if(arr[i] == frames[j].value) {
                pageHit++;
                frames[j].lastUsed = i;
                freq[arr[i]]++;
                flag = 1;
                displayRow(arr[i]);
                break;
            }
        }

        // replacement
        if(flag == 0) {
            int low_freq = 999999;
            int low_lu = 999999;
            int low_ind;

            for(int j=0;j<3;j++) {
                if(freq[frames[j].value] <= low_freq)  {
                    if(freq[frames[j].value] == low_freq) {
                        if(frames[j].lastUsed > low_lu) {
                            continue;
                        }
                    }
                    low_freq = freq[frames[j].value];
                    low_lu = frames[j].lastUsed;
                    low_ind = j;
                }
            }

            freq[frames[low_ind].value]--;
            frames[low_ind].value = arr[i];
            frames[low_ind].lastUsed = i;
            freq[arr[i]]++;
            pageFault++;

            displayRow(arr[i]);

        }
    }

    printf("Page Fault = %d\n", pageFault);
    printf("Page Hit = %d\n", pageHit);
    
}

int main() {

    int n, largestPageNum = 0;
    printf("Enter no. of pages : ");
    scanf("%d", &n);

    int *pages = malloc(n * sizeof(int));
    
    printf("Enter the page sequence\n");
    for(int i=0;i<n;i++) {
        scanf("%d", &pages[i]);
        if(pages[i] > largestPageNum) {
            largestPageNum = pages[i];
        }
    }

    int *freqArr = malloc(sizeof(int) * (largestPageNum + 1));

    // initialising frequency array to 0
    for (int i = 0; i <= largestPageNum; i++)
    {
        freqArr[i] = 0;
    }

    fifo(pages, n);
    lru(pages, n);
    lfu(pages, n, freqArr);


    return 0;
}