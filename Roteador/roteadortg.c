
// gcc -pthread roteadort.c

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "roteador.h"

#define maxprodutor 1
#define maxconsumidor 4

typedef struct FILA
{
	uint32_t info;
	struct FILA *next;
}Fila;

void *insereFila(uint32_t );
void produtor(uint32_t *);
void consumidor();
void *removeFila();
void imprimir(Fila *);
void *insereFilaRotas(Fila *, entrada);
uint32_t iptoint(int a, int b, int c, int d){
	return (uint32_t) (a<<24)+(b<<16)+(c<<8)+d;
}

uint32_t tamanhorotas,tamanhopacs,consome=0,cont=0,buffer=0,tamEnlace=0,*enlace;
entrada *rotasP;
pthread_mutex_t lock_x,lock_y;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

Fila *pila;

uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes, int num_pacotes, int num_enlaces){
	uint32_t i,j;
	rotasP = malloc(sizeof (entrada) * (tamanhorotas));
	rotasP=rotas;
	

	tamanhopacs=num_pacotes;
	tamanhorotas=num_rotas;
	tamEnlace=num_enlaces;
	
	enlace = malloc(sizeof (uint32_t) * (tamEnlace+1));
	for(i=0;i<num_enlaces+1;i++){
		enlace[i]=0;
	}
	pila = (Fila *) malloc (sizeof(Fila));
	
	pthread_t thread[maxprodutor+maxconsumidor];
	
	pthread_mutex_init(&lock_x, NULL);
	pthread_mutex_init(&lock_y, NULL);
	
	
	pthread_create(&thread[0], NULL, (void *) produtor, (void *) &pacotes);
	pthread_join(thread[0],NULL);
	
	removeFila(pila);
	for(j=1;j<5;j++)
		pthread_create(&thread[j], NULL, (void *) consumidor, (void *) NULL); 
		
	for(j=1;j<maxprodutor+maxconsumidor;j++)
	 	pthread_join(thread[j],NULL);
	 
	printf("\n\n");	
	printf("RESULTADO FINAL: ");
	for(i=0;i<num_enlaces+1;i++)
		printf("%d ",enlace[i]);
	
	//printf("ACABOU TUDO");
	//imprimir(pila);
	return enlace;

}


int main()
{
	entrada rotas[2] = { iptoint(5,4,1,0), 24, 1,
						 iptoint(5,4,0,0), 16, 2 };

	uint32_t 
	pacotes[2] = { iptoint(5,4,0,1), iptoint(5,4,1,1) };

	roteamento(rotas,2,pacotes,2,2);
	return 0;
	
}

void produtor(uint32_t *valor)
{

	while(cont < tamanhopacs)
	{	
		printf("trab3\n");
		pthread_mutex_lock(&lock_x);
		insereFila(valor[cont]);
		buffer++;
		cont++;
		pthread_mutex_unlock(&lock_x);
	}
	pthread_exit((void*) 0);	
}

void consumidor()
{
	printf("COMECEI\n");
	uint32_t pos=0,descart=0,maior=0,AUXILIAR=0,j,i;
	entrada *temp;
	temp = malloc(sizeof(entrada));
	while(consome < tamanhopacs){
	pos=0;
	descart=0;
	maior=0;
	temp= rotasP;
	pthread_mutex_lock(&lock_x);
	if(pila==NULL || consome == tamanhopacs){
		pthread_mutex_unlock(&lock_x);
		 break;
	 }
	else{
	AUXILIAR=pila->info;
	removeFila(pila);
	consome++;
	printf("%d\n",consome);
	
	pthread_mutex_unlock(&lock_x);
}

	for(j=0;j<tamanhorotas;j++){
		if(AUXILIAR>>((temp->mascara)) == (temp->endereco)>>((temp->mascara))){
				descart++;
			}
		if((AUXILIAR<<(temp->mascara)) > maior){
					maior=(AUXILIAR)<<(temp->mascara);
					pos=temp->enlace;
			}
		*(++temp);
			
		}
		temp=rotasP;
		if(descart==0){
			pthread_mutex_lock(&lock_x);
			enlace[0]++;
			pthread_mutex_unlock(&lock_x);
		}else if(descart==1){
			for(j=0;j<tamanhorotas;j++){
			if((AUXILIAR)>>(((temp->mascara))) == (temp->endereco)>>(((temp->mascara))))
			{
				pthread_mutex_lock(&lock_x);
				enlace[temp->enlace]++;
				pthread_mutex_unlock(&lock_x);
			}
			*(++temp);
		}
		}else{
			pthread_mutex_lock(&lock_x);
			enlace[pos]++;
			pthread_mutex_unlock(&lock_x);
	}


}
	for(i=0;i<tamEnlace+1;i++)
		printf("%d ",enlace[i]);
	printf("\n");
	printf("TERMINEI");
	pthread_exit((void*) 0);
}

void *removeFila()
{
	Fila *aux= pila->next;
	free(pila);
	pila = aux;
}


void *insereFila(uint32_t valor)
{
	Fila *aux = malloc(sizeof(Fila));
	Fila *first = malloc(sizeof(Fila));
	
	aux->info = valor;
	first = pila;
	
	while(pila -> next != NULL)
	{
		pila = pila -> next;
	}
	
	pila->next = aux;		  
	pila = first;
}

void imprimir(Fila *inicio)
{
	while (inicio)
	{
		printf("%d\n", inicio->info);
		inicio = inicio->next;
	}
}
