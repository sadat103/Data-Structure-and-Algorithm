#include<iostream>
#include<stdio.h>
#define INFINITY 10000000000

using namespace std;

int main()
{

    int cn,sum,rem,i,j,k;
	printf("Total sum and Notes and multipliers\n");
    scanf("%d%d", &sum, &cn);

	int *Notes=new int[cn];
	int *mul=new int[cn];

	for (i = 0; i<cn; i++)
    {
        scanf("%d", &Notes[i]);
    }

	for (i = 0; i<cn; i++)
    {
        scanf("%d", &mul[i]);
    }

	int *table1=new int[sum + 1];
	table1[0] = 0;

	int **tblused = new int*[cn];
	for (i = 0; i < cn; i++)
	{
		tblused[i] = new int[sum + 1];
	}



	for (i = 1; i <= sum; i++)
    {
        table1[i] = INFINITY;
    }

	for (i = 0; i < cn; i++)
	{
		for (j = 0; j <= sum; j++)
        {
            tblused[i][j] = 0;
        }
	}


	for (i = 1; i <= sum; i++)
	{
		for (j = 0; j < cn; j++)
		{
			if (i - Notes[j] < 0)
            {
                continue;
            }

			rem = table1[i - Notes[j]];//using coin[j] the remaining value for which we have to need coin
			if ( Notes[j] <= i)
			{
				if (rem + 1 < table1[i] && rem != INFINITY && 1 + tblused[j][i - Notes[j]]  <= mul[j]) //not cross coin limit
				{
					table1[i] = rem + 1; //dynamic approach

					for (k = 0; k<cn; k++)
                    {
                        tblused[k][i] = tblused[k][i - Notes[j]]; //which which coin used and return coin and their using times
                        tblused[j][i] = 1 + tblused[j][i - Notes[j]] ;//dynamic approach
                      //  printf("%d%d",tblused[i][j]);

                    }
				}
			}

		}
	}

	if (table1[sum] != INFINITY)
	{
	    printf("notes needed\n");
		printf("%d\n", table1[sum]);
        printf("notes can be made by :\n");
		for (i = 0; i < cn; i++)
		{
			if (tblused[i][sum] != 0)
            {
                printf("using %d * %d\n", Notes[i], tblused[i][sum]);
            }
		}
	}

	else
    {
        printf("not possible \n");
    }

	return 0;
}
