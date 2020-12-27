#include<stdio.h>
#include<time.h>
void knapsack(float capacity, int n, float weight[], float profit[], int index[])
{
	float x[20], totalprofit,y;
	int i,j;
	y=capacity;
	totalprofit=0;
	for(i=0;i < n;i++)
		x[i]=0.0;
	for(i=0;i < n;i++)
	{
		if(weight[i] > y)
			break;
		else
		{
			x[i]=1.0;
			totalprofit=totalprofit+profit[i];
			y=y-weight[i];
		}
	}
	if(i < n)
		x[i]=y/weight[i];

    totalprofit=totalprofit+(x[i]*profit[i]);
    /*for(i=0;i < n;i++)
    {
        printf("%f\t",x[i]);
    }*/
	printf("\nTotal profit %f\n", totalprofit);
	for(i=0;i < n;i++)
		if(x[i]==1.0)
			printf("\n %d \t %f \t %f", index[i]+1, weight[i], profit[i]);
		else if(x[i] > 0.0)

			printf("\n %d \t %f \t %f", index[i]+1,x[i]*weight[i],x[i]*profit[i]);

}
int main()
{
	float weight[20],profit[20],ratio[20], t1,t2,t3,t4;
	int n;
	int index[20];
    float capacity;
	int i,j;
	printf("Enter number of objects:  ");
	scanf("%d", &n);
	printf("\nEnter the capacity of knapsack: ");
	scanf("%f", &capacity);
	for(i=0;i < n;i++)
	{

		printf("\nEnter weight: ");
		scanf("%f", &weight[i]);
		printf("Enter profit: ");
		scanf("%f", &profit[i]);
		index[i]=i;
		ratio[i]=profit[i]/weight[i];
	}
	for(i=0;i < n;i++)
		for(j=0;j < n;j++)
		{
			if(ratio[i] > ratio[j])
			{
				t1=ratio[i];
                ratio[i]=ratio[j];
				ratio[j]=t1;
				t2=weight[i];
				weight[i]=weight[j];
				weight[j]=t2;
				t3=profit[i];
				profit[i]=profit[j];
				profit[j]=t3;
				t4=index[i];
				index[i]=index[j];
				index[j]=t4;
			}
		}
	knapsack(capacity,n,weight,profit,index);
}
