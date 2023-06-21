#include<stdio.h>
#include<stdlib.h>
#define DISK_SIZE 200

void bubbleSort(int *arr, int size) {
    int temp;
    for(int i=0;i<size;i++) {
        for(int j=0;j<size-i-1;j++) {
            if(arr[j]>arr[j+1])
	            {
		            temp=arr[j];
		            arr[j]=arr[j+1];
		            arr[j+1]=temp;
	            }
        }
    }
}

void fcfs(int *arr , int size ,int head) {
    int total_seek_count = 0;
    int current_head = head;

    printf("\nThe sequence of head movement\n");
    printf("%d ",current_head);

    for(int i=0;i<size;i++) {
        int seektime;
        if(current_head > arr[i]) {
            seektime = current_head - arr[i];
        }
        else {
            seektime = arr[i] - current_head;
        }

        total_seek_count += seektime;
        current_head = arr[i];
        printf("%d ",current_head);
    }

    printf("\nThe total number of seek operations in FCFS = %d\n" , total_seek_count);
}



// goes left then right
void scan(int *arr, int n, int head) {
    int pivot, left, right, seektime;
    int total_seek_count = 0, current_head = head;
    int *temp_arr = malloc(sizeof(int) * (n+1));
    for(int i=0;i<n;i++) {
        temp_arr[i] = arr[i];
    }
    temp_arr[n] = head;
    bubbleSort(temp_arr,n+1);
    for(int i=n;i>=0;i--) {
        if(temp_arr[i] == head) {
            pivot = i;
            break;
        }
    }
    left = pivot-1;
    right = pivot+1;

    printf("\nThe sequence of head movement\n");
    printf("%d ",current_head);

    while(left>=0) {
        seektime = current_head-temp_arr[left];
        total_seek_count += seektime;
        current_head = temp_arr[left];
        printf("%d ",current_head);
        left--;
    }

    seektime = current_head - 0;
    total_seek_count += seektime;
    current_head = 0;
    printf("%d ",current_head);

    while(right<n+1) {
        seektime = temp_arr[right] - current_head;
        total_seek_count += seektime;
        current_head = temp_arr[right];
        printf("%d ",current_head);
        right++;
    }

    printf("\nThe total number of seek operations in SCAN = %d\n" , total_seek_count);
}

// goes right 
void cscan(int *arr, int n, int head) {
    int pivot, left, right, seektime;
    int total_seek_count = 0, current_head = head;
    int *temp_arr = malloc(sizeof(int) * (n+1));
    for(int i=0;i<n;i++) {
        temp_arr[i] = arr[i];
    }
    temp_arr[n] = head;
    bubbleSort(temp_arr,n+1);
    for(int i=n;i>=0;i--) {
        if(temp_arr[i] == head) {
            pivot = i;
            break;
        }
    }
    left = pivot-1;
    right = pivot+1;

    printf("\nThe sequence of head movement\n");
    printf("%d ",current_head);

    while(right<n+1) {
        seektime = temp_arr[right] - current_head;
        total_seek_count += seektime;
        current_head = temp_arr[right];
        printf("%d ",current_head);
        right++;
    }

    seektime = (DISK_SIZE-1) - current_head;
    total_seek_count += seektime;
    current_head = DISK_SIZE-1;
    printf("%d ",current_head);

    seektime = current_head - 0;
    total_seek_count += seektime;
    current_head = 0;
    printf("%d ",current_head);

    int st = 0;
    while(st<=left) {
        seektime = temp_arr[st] - current_head;
        total_seek_count += seektime;
        current_head = temp_arr[st];
        printf("%d ",current_head);
        st++;
    }
    printf("\nThe total number of seek operations in C-SCAN  = %d\n" , total_seek_count);
}

int main() {
    int n , head;
    printf("Enter no. of requests : ");
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    printf("Enter the request sequence\n");
    for(int i=0;i<n;i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the current position of head : ");
    scanf("%d", &head);

    fcfs(arr, n, head);
    scan(arr, n, head);
    cscan(arr, n, head);

    return 0;
}