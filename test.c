#include <stdio.h>

int main(int argc, char const *argv[])
{
	char 	*a = "abc"; // 01100001
	int		bit = 0;
	int		i = 0;

	while (a[i])
	{
		bit = 0;
		while (bit != 8)
		{
			if (a[i] & (0x80 >> bit++))
				printf("1");
			else
				printf("0");
		}
		printf("\n");
		i++;
	}
	
	int	end = 0;
	while (end != 8)
	{
		printf("0");
	}
	

	

	
	

	return 0;ff
}
ddfff