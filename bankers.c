#include <stdio.h>
#include<stdlib.h>

int isCompleted(int *arr, int size) {
	for (int i = 0; i < size; i++)
	{
		if(arr[i] == 0) {
			return 0;
		}
	}
	return 1;
}

int main()
{
	int processes, resources;
	int finished[10], result[10], ind = 0;
	int alloc[10][10], max[10][10], avail[10];

    printf("Enter the no. of processes : ");
	scanf("%d",&processes);
	printf("Enter the no. of resources : ");
	scanf("%d",&resources);

	printf("\n");

	printf("Enter the available amount of %d resources : ",resources);
	for(int i=0;i<resources;i++) {
		scanf("%d", &avail[i]);
	}

	for (int i = 0; i < processes; i++)
	{
		printf("Enter the amount of resources allocated to process %d : ",i);
		for(int j=0;j<resources;j++) {
			scanf("%d", &alloc[i][j]);
		}	
	}

	printf("\n");

	for (int i = 0; i < processes; i++)
	{
		printf("Enter the max amount of resources required for process %d : ",i);
		for(int j=0;j<resources;j++) {
			scanf("%d", &max[i][j]);
		}	
	}

	for (int i = 0; i < processes; i++) {
		finished[i] = 0;
	}

	int need[processes][resources];

	for (int i = 0; i < processes; i++) {
		for (int j = 0; j < resources; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	while(!isCompleted(finished, processes)) {

		int flag1 = 0;

		for (int i = 0; i < processes; i++)
		{
			if(finished[i] == 1) {
				continue;
			}
			int flag2 = 0;

			for (int j = 0; j < resources; j++)
			{
				if(need[i][j] > avail[j]) {
					flag2 = 1;
					break;
				}
			}
			if(flag2 == 0) {
				// the required number of resources are available
				result[ind] = i;
				ind++;

				for (int k = 0; k < resources; k++)
				{
					avail[k] += alloc[i][k];
				}

				finished[i] = 1;
				// process i is finished

				flag1 = 1;
			}
		}

		if(flag1 == 0) {
			printf("The system is not safe\n");	
			exit(0);
		}
	}

	printf("The safe sequence is \n");
	for (int i = 0; i < processes-1; i++)
	{
		printf(" P%d ->", result[i]);
	}
	printf(" P%d \n", result[processes-1]);

	return (0);
}