#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memvirt.h"
//struct result * memvirt(int num_procs, uint32_t num_frames, char * filename, uint32_t interval);
typedef struct processo
{
	uint32_t wstam, valores[100000], referencia[10000], maximototal,maximolocal,hit,miss, wsaux[50], index, pont2c;
	float taxaDePF;
}proce;
struct result * memvirt(int num_procs, uint32_t num_frames, char * filename, uint32_t interval)
{
	FILE *pila;
	uint32_t j,i,k,total=0,num_processos,proces=0,pag,auxiteracao,hit=0,continterval=0,match=0,totalmaxtotal,aux=0,totalinterval=0;
	num_processos=num_procs;
	float taxaPfTotal=0,tamtotalWS=0;
	proce *pro;
	struct result *resultado;
	resultado=calloc(1,sizeof(struct result));
	resultado->refs=calloc(num_processos,sizeof(uint32_t));
	resultado->pfs=calloc(num_processos,sizeof(uint32_t));
	resultado->pf_rate=calloc(num_processos,sizeof(uint32_t));
	//printf("----------%d----------",resultado->refs[0]);
	pro=calloc(num_processos,sizeof(proce));
	auxiteracao=num_frames/num_processos;
	for(i=0;i<num_processos;i++) { 
		pro[i].index=0;
		pro[i].maximolocal=auxiteracao;
		pro[i].maximototal=auxiteracao;
		pro[i].wstam=0;
		pro[i].hit=0;
		pro[i].miss=0;
		pro[i].pont2c=0;
	}
	pila = fopen(filename, "r");
	while (fscanf(pila, "%u%u", &proces, &pag)!=EOF){	
		
		hit=0;
	//	printf("----%d---\n",pro[proces].pont2c);
		if(pro[proces].pont2c>pro[proces].maximolocal-1)
			pro[proces].pont2c=0;
		if(pro[proces].index>pro[proces].maximolocal)
				pro[proces].index=pro[proces].maximolocal;
		for(i=0;i<pro[proces].index;i++){ // For verificando os data registrados no processo, procurando hit
			if(pro[proces].valores[i]==pag){ // Se deu hit, ele só ignora e segue pro proximo data.
		//		printf("HIT: %d, %d\n",proces,pag);
				pro[proces].referencia[i]=1;
				hit=1;
				pro[proces].hit++;
				break;	
				}
		}
		if(hit==0)
		{ 
			pro[proces].miss++;
			totalmaxtotal=0;
			for(j=0;j<num_processos;j++)
			{
				totalmaxtotal=totalmaxtotal+pro[j].maximototal;
				}
			//printf("-----%d----\n",totalmaxtotal);
			if(pro[proces].index==pro[proces].maximolocal) //1. Comparando se a tabela ja ta cheia e nao pode inserir mais, entao só substitui um valor da tabela (algorimto do relogio)
			{ //relogio
				if(pro[proces].pont2c>=pro[proces].maximolocal)
					pro[proces].pont2c=0;
				for(;;)
				{
					i=pro[proces].pont2c;
					if(pro[proces].referencia[i]==0)
					{
						pro[proces].valores[i]=pag;		
						pro[proces].pont2c++;
						break;		
					}else{
						pro[proces].referencia[i]=0;
						pro[proces].pont2c++;
						}
					if(pro[proces].pont2c>pro[proces].maximolocal-1)
						pro[proces].pont2c=0;
				}
			//	printf("Caso 1: %d, %d\n", proces,pag);
			}	
			else if(pro[proces].index<pro[proces].maximolocal && pro[proces].index<pro[proces].maximototal) //2. Aqui verifica se tem espaço livre no processo
			{ 
				pro[proces].valores[pro[proces].index]=pag;
				pro[proces].index++;
			//	printf("Caso 2: %d, %d\n", proces,pag);
			}
			else if(totalmaxtotal<num_frames && pro[proces].maximolocal>pro[proces].maximototal && pro[proces].index == pro[proces].maximototal) //3. Aqui verifica se o numero total de frames usados no processo, é menor que os de frames total, entao ele pode pegar um frame que ta livre.
			{ 
				pro[proces].maximototal++;
				pro[proces].valores[pro[proces].index]=pag;
				pro[proces].referencia[pro[proces].index]=0;
				pro[proces].index++;
			//	printf("Caso 3: %d, %d, referencia: %d\n", proces,pag,pro[proces].referencia[pro[proces].index]);
			}
			else if(pro[proces].index==pro[proces].maximototal && pro[proces].maximototal < pro[proces].maximolocal)  //4. Aqui ele deve buscar um frame livre de um outro processo
			{ 
				match=0;
			//	printf("Caso 4: %d, %d\n", proces,pag);
				for(i=0;i<num_processos;i++)
				{
					if(pro[i].maximolocal<pro[i].maximototal && pro[i].maximototal>1)
					{
						match=1;
						pro[i].maximototal--;
						pro[proces].maximototal++;
						pro[proces].valores[pro[proces].index]=pag;
						pro[proces].referencia[pro[proces].index]=0;
						pro[proces].index++;
						break;
					}
				}
			if(match==0) //Ele nao achou nenhum frame livre, consome do proprio frame
				{//Aqui ele deve só rodar o segunda chance
					//Relogio
					if(pro[proces].pont2c==pro[proces].maximolocal)
						pro[proces].pont2c=0;
					for(;;)
					{
					i=pro[proces].pont2c;
					if(pro[proces].referencia[i]==0)
					{
						pro[proces].valores[i]=pag;		
						pro[proces].pont2c++;
						break;		
					}else{
						pro[proces].referencia[i]=0;
						pro[proces].pont2c++;
						}
					if(pro[proces].pont2c>pro[proces].maximolocal-1)
						pro[proces].pont2c=0;
				}
					
				}
			}
		}		
		pro[proces].wsaux[pro[proces].wstam]=pag;
		pro[proces].wstam++;
		
		for(i=0;i<pro[proces].index;i++){ //colocando os valores numa variavel com todas as paginas usadas naquela iteração
					if(pag==pro[proces].wsaux[i]){
						match=1;
						break;
					}
				}
				if(match==0){
					pro[proces].wsaux[pro[proces].wstam]=pag;

		}

		match=0;
		continterval++;
		for(i=0;i<num_processos;i++){ //Printar
		//printf("Processo %d: \n",i);
		for(j=0;j<pro[i].index;j++){
			//	printf("%d\n", pro[i].valores[j]);			
			}
			//printf("\n");
}
		
		if(continterval==interval){ //Se der verdade, ele tem que recalcular o ws
			totalinterval++;
			continterval=0;
			total=0;
			for(i=0;i<num_processos;i++){ //Calcular o tamanho total dos ws
			//printf("Processo %d: \n",i);
			aux=0;
			for(j=0;j<pro[i].index;j++){
				for(k=0;k<pro[i].wstam;k++){
					if(pro[i].valores[j]==pro[i].wsaux[k]){
						aux++;
						break;
					}
				}
				
			}
			pro[i].wstam=aux;
			
				
				total=total+pro[i].wstam;
				
			}
			//printf(">>>%d<<<<\n",tamtotalWS);
			tamtotalWS+=total;
		
				if(total==0)
					total=1;
				//printf("total = %d\n",total);
			for(i=0;i<num_processos;i++){  //recalcular o tamanho maximo
				
				pro[i].maximolocal=(uint32_t)((float)pro[i].wstam/total*num_frames);
				if(pro[i].maximolocal==0){
					pro[i].maximolocal=1;
				}
				pro[i].wstam=0;
				//printf("Maximo local %d, ",pro[i].maximolocal);	
			}
		//	printf("\n");
		}
		
	}
	//pila = fclose(filename);
	
	//printf("\n");
	if(continterval>0)
	{
		totalinterval++;
		total=0;
		for(i=0;i<num_processos;i++)
		{ //Calcular o tamanho total dos ws
			//printf("Processo %d: \n",i);
			aux=0;
			for(j=0;j<pro[i].index;j++)
			{
				for(k=0;k<pro[i].wstam;k++)
				{
					if(pro[i].valores[j]==pro[i].wsaux[k])
					{
						aux++;
						break;
					}
				}
			}
		pro[i].wstam=aux;
		total=total+pro[i].wstam;
	
		}
		
	}
	/*for(i=0;i<num_processos;i++)
	{
	 	printf("Processo %d:\n",i);
		for(j=0;j<pro[i].maximototal;j++)
		{
			printf("(%d %d)",pro[i].valores[j],pro[i].referencia[j]);
		}
		printf("\n");
	}*/
	aux=0;
	for(i=0;i<num_processos;i++){
		//printf("processo %d: \n",i);
		if(pro[i].miss+pro[i].hit==0)
			continue;
		pro[i].taxaDePF=(pro[i].miss/(float)(pro[i].miss+pro[i].hit))*100;
		taxaPfTotal+=pro[i].taxaDePF;
		//printf("Numero de referencias: %d\n", pro[i].miss+pro[i].hit);
		//printf("Numero de page fault: %d\n", pro[i].miss);
		//printf("Taxa de page fault: %.2f \n", pro[i].taxaDePF);
		//printf("Ponteiro segunda chance: %u \n", pro[i].pont2c);
		
		aux++;
		//printf("\n");
		}
		taxaPfTotal=taxaPfTotal/aux;
	//	printf("Taxa dos WC de toda a simulação é: %u\n",(uint32_t)((float)tamtotalWS/(float)(totalinterval)));
		//printf("\nTaxa de page Fault total é: %.2f\n",taxaPfTotal);
		for(i=0;i<num_processos;i++)
		{
			resultado->refs[i]=pro[i].miss+pro[i].hit;
			resultado->pfs[i]=pro[i].miss;
			resultado->pf_rate[i]=pro[i].taxaDePF;
		}
		//printf("---%d---\n",totalinterval);
			resultado->avg_ws=(uint32_t)((float)tamtotalWS/totalinterval);
			resultado->total_pf_rate=taxaPfTotal;
	return resultado;
}
