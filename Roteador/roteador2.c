#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *string;

typedef struct FILA
{
	string pacote;
	struct FILA *next;
}fila;

int main()
{
	FILE *fp;
	fp = fopen("Entrada.txt","r");
	char line[20];
	char ip[15];
	int sizeIP;
	char bits[2];
	char enlasse;
	int octetoA=0, octetoB = 0, octetoC = 0, octetoD = 0;
	int i,j=0,k=0,bitsSize, valorInt;
	while (fgets(line, sizeof(line), fp))
	{
		j=0,k=0,sizeIP=0,bitsSize=0;
		for(i=0;i<strlen(line);i++)
		{
			if(line[i] == '/')
			{
				j++;
				break;
			}
			ip[i]=line[i];
			j++;
			sizeIP++;
		}
		for(i=j;i<strlen(line);i++)
		{
			if(line[i] == ' ')
			{
				k++;
				break;
			}
			bits[bitsSize]=line[i];
			bitsSize++;
			k++;
		}
		enlasse = line[j+k];
		
		printf("IP: ");
		for(i=0;i<sizeIP;i++)
			printf("%c",ip[i]);
		printf("\n\n");
		
		
		
	}
	
	
	//converter pra int
	for (i = 0; i < sizeIP; i++)
		{
			if(ip[i] == '.')
				break;
			octetoA = 10 * octetoA + (ip[i] - '0');
		}
			
		for (i = i+1; i < sizeIP; i++)
		{
			if(ip[i] == '.')
				break;
			octetoB = 10 * octetoB + (ip[i] - '0');
		}
			
		for (i = i+1; i < sizeIP; i++)
		{
			if(ip[i] == '.')
				break;
			octetoC = 10 * octetoC + (ip[i] - '0');
		}
			
		for (i = i+1; i < sizeIP; i++)
		{
			if(ip[i] == '.')
				break;
			octetoD = 10 * octetoD + (ip[i] - '0');
		}
	
		
		
	printf("bits: ");
	for(i=0;i<bitsSize;i++)
	printf("%c",bits[i]);
	printf("\n\n");
	
	printf("enlasse: %c",enlasse);
	printf("\n\n");
		
	printf ("%d - %d - %d - %d" ,octetoA,octetoB,octetoC,octetoD);
	
	
    fclose(fp);
	
	/*
	fscanf(fp, "%s %s\n", ch, ch2);
	
	printf("%s - %s\n", ch, ch2);
	
	bits = strtok(ch, "/");
	
	printf("%s\n",bits);

	while (fgets(line, sizeof(line), fp))
	{
		copy= line;
		printf("line: %s\n", copy);
		number = strtok(copy, ".");
		strncpy(copy, line, 4);
		printf("line depois de strtok: %s\n\n", line);
		//printf("string number: %s\n", number);
		//printf("valor line[2]: %c\n", line[2]);
	}
	*/
	
	return 0;
}
