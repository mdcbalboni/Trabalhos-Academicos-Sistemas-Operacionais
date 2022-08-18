#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roteador.h"

typedef char *string;

typedef struct FILA
{
	entrada derp;
	struct FILA *next;
}fila;

fila *push(fila *u, entrada valor){

	int aux;
	char aux2;
   fila *temp = u;
   fila *novo = (fila*)malloc(sizeof(fila));
   novo -> derp.endereco = valor.endereco;
   aux=valor.mascara/8;
   aux2= aux + '0';
   novo -> derp.mascara = aux2;
   novo -> derp.enlace = valor.enlace + '0';
   novo -> next = NULL;

	if(temp == NULL)
		temp = novo;
		else{
   while(temp -> next != NULL)
   {
    temp = temp -> next;
   }

   temp->next = novo;
}


return u;		  
}

fila* pop(fila* f){
 	if(f->next == NULL)
	   return NULL;
	fila *temp = f -> next;
	free(f);
	return temp;
}

void imprimir(fila *inicio)
{
   while (inicio)
   {
       printf("%u\n", inicio->derp.endereco);
       printf("%c\n",inicio->derp.mascara);
		printf("%c\n",inicio->derp.enlace);
       inicio = inicio->next;
   }

}


uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes, int num_pacotes, int num_enlaces)
{
	int i, j,descart,entrou[num_rotas],entrouM[num_rotas],maior=0,pos;
	uint32_t v[num_pacotes], *resultado,enlace[num_enlaces+1];
	resultado=malloc(sizeof(uint32_t));
	resultado=enlace;
	fila *q = malloc(sizeof(fila));
	fila *temp = malloc(sizeof(fila));
	for(i=0;i<num_rotas;i++){
		
		push(q, rotas[i]);
	}
	for(i=0;i<num_enlaces+1;i++){
		
		enlace[i]=0;
	}
	
	for(i=0;i<num_pacotes;i++){
		
		v[i] = pacotes[i]; 
	 
	}
	
	for(i=0;i<num_pacotes;i++){
		pos=0;
		maior=0;
		descart=0;
		temp = q->next;
		for(j=0;j<num_rotas;j++){
			entrou[j]=0;
			entrouM[j]=0;
		}
		for(j=0;j<num_rotas;j++){

			if((v[i])>>((8*(temp->derp.mascara-'0'))) == (temp->derp.endereco)>>((8*(temp->derp.mascara-'0'))))
			{
				entrou[descart]=j+1;
				//printf("entrou aqui: %d\n",j+1);
				entrouM[descart]=8*(temp->derp.mascara-'0');
				descart++;
				//printf("a");
			}
			
			temp = temp->next;
		}	
		//for(j=0;j<descart;j++){
		//	printf("%d \n", entrouM[j]);
			
			
			//}
			//printf("%d \n", v[i]);
		//printf("Qual posição entrar: %d\n",enlace[entrou[0]]);
		if(descart==1)
		printf("QUal meu discart %d\n",enlace[entrou[0]]);
		if(descart==0){
				enlace[0]++;
		}else if(descart==1){
			
			enlace[entrou[0]]++;
		}else{
			for(j=0;j<descart;j++){
				if(((v[i])<<entrouM[j]) > maior){
					maior=(v[i])<<entrouM[j];
					pos=entrou[j];
					
					
					}	
			}
			enlace[pos]++;
		
	}
}
		

	for(i=0;i<num_enlaces+1;i++){
		
		printf("%d\n",enlace[i]);
	}
	
	return resultado;
}

uint32_t iptoint(int a, int b, int c, int d){
	return (uint32_t) (a<<24)+(b<<16)+(c<<8)+d;
}

int main()
{	
	entrada rotas[256];
	uint32_t pacotes[1280];
	
	int i,j;

	for (i=0; i<64; i++){
		for(j=0; j<4; j++){
			/* rotas com overlap de prefixo */
			rotas[i*4+j].endereco = iptoint(10+i,1<<j,0,0);
			rotas[i*4+j].mascara = 16+j;
			rotas[i*4+j].enlace = j+1;

			pacotes[(i*4+j)*4] = iptoint(10+i,1<<j,0,1);
			pacotes[(i*4+j)*4+1] = iptoint(10+i,1<<j,0,2);
			pacotes[(i*4+j)*4+2] = iptoint(10+i,1<<j,0,3);
			pacotes[(i*4+j)*4+3] = iptoint(10+i,1<<j,0,4);

		}
	}


	/* pacotes para serem descartados */
	//for  (i=1024; i<1280; i++)
		//pacotes[i] = iptoint(99,93,11,1);

	roteamento(rotas, 256, pacotes, 1280, 5);
		
	return 0;
}

