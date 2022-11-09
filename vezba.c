#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	FILE* fp1;
	int ispis = 0;
	long int period = 20000L;
	char *str;
	char tval1,tval2,tval3,tval4, cond = 0;
	size_t num_of_bytes = 6;
	int button_new = 0, button_old = 0;

	while(1) 
	{
		// Upali diode
		fp1 = fopen("/dev/led", "w");
		if(fp1 == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		
		fprintf(fp1, "0x0%x", ispis);
		
		if(fclose(fp1))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}
		usleep(1);
		
		//Citanje vrednosti tastera
		fp1 = fopen ("/dev/button", "r");
		if(fp1==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}


		str = (char *)malloc(num_of_bytes+1); 
		getline(&str, &num_of_bytes, fp1); 

		if(fclose(fp1))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}

		if (str[5] - 48 == 1)
			cond = 1;
		else if (str[4] - 48 == 1)
			cond = 2;
		else 
			cond  = 0;
		free(str);
		
		button_new = cond;
		if (button_new != button_old)
		{
			if (button_new == 1)
			{
				if (ispis <= 14)
					ispis += 1;
			}
			else if (button_new == 2)
			{
				if (ispis >= 1)
					ispis -= 1;
			}
			button_old = button_new;
		}
		usleep(1);
	}
	return 0;
}
