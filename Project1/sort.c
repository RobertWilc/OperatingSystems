#include <stdio.h>
#include <string.h>

struct student
{
	char name[50];
};
int main()
{
	struct student Std[50];
	char name[50][50], temp[50];
	int i = 0, j, n;

	while( scanf("%s", name[i]) != EOF )
	{
		i++;
	}

	int it = i;
	for(i = 0; i < it - 1; i++)
	{
		for(j = i+1; j < it; j++)
		{
			if ( strcmp(name[i], name[j]) > 0)
			{
				strcpy(temp, name[i]);
				strcpy(name[i], name[j]);
				strcpy(name[j], temp);
			}
		}
	}

	//sorted names
	for( i = 0; i < it; i++)
	{
		printf("%s\n", name[i]);
	}
}
