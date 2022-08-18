#include "memvirt.h"
#include "simpletest.h"
#include <assert.h>

void test1() // Esse teste, testa todos os casos de remoção e inserção e também problema de calcular ws
{
	//int i;
	struct result * resultFinal;
	WHEN("Esse teste, testa todos os casos de remoção e inserção e também problema de calcular ws");
	resultFinal = memvirt(4, 13, "entrada.txt", 3);
	assert(resultFinal);

	THEN("Deve ter 4-6-3-0 referencias respectivamente");
	isEqual(resultFinal->refs[0], 4, 1);
	isEqual(resultFinal->refs[1], 6, 1);
	isEqual(resultFinal->refs[2], 3, 1);
	isEqual(resultFinal->refs[3], 0, 1);
		
	THEN("Deve ter 0-4-6-2 miss respectivamente")	;
	isEqual(resultFinal->pfs[0], 4, 1);
	isEqual(resultFinal->pfs[1], 6, 1);
	isEqual(resultFinal->pfs[2], 2, 1);
	isEqual(resultFinal->pfs[3], 0, 1);

	THEN("Deve ter porcetagem de miss de 100% - 100% - 66.67%");
	
	isEqual(resultFinal->pf_rate[0], 100, 1);
	isEqual(resultFinal->pf_rate[1], 100, 1);
	isEqual(resultFinal->pf_rate[2], 66.67, 1);

	THEN("Deve ter como o arredondamento da taxa média de WS como 1");
	isEqual(resultFinal->avg_ws, 1, 1);	
	
	THEN("Deve ter como taxa de page fault de 88.89% ");
	isEqual(resultFinal->total_pf_rate, 88.89, 1);	
}

void test2() //Teste para verificar se o relogio funciona, ele entra no segunda chance 3 vezes durante essa execução
{
	//int i;
	struct result * resultFinal;
	WHEN("Teste para verificar se o relogio funciona, ele entra no segunda chance 3 vezes durante essa execução");
	resultFinal = memvirt(1, 3, "entrada2.txt", 18);
	assert(resultFinal);

	THEN("Deve ter 18 referencias");
	isEqual(resultFinal->refs[0], 18, 1);
		
	THEN("Deve ter 9 miss respectivamente")	;
	isEqual(resultFinal->pfs[0], 9, 1);

	THEN("Deve ter porcetagem de miss de 50%");
	
	isEqual(resultFinal->pf_rate[0], 50, 1);

	THEN("Ele teve apenas 1 intervalo com o ws 3.");
	isEqual(resultFinal->avg_ws, 3, 1);	
	
	THEN("Deve ter como taxa de page fault de 50% ");
	isEqual(resultFinal->total_pf_rate, 50, 1);	
}

void test3() //Teste para verificar se o relogio funciona, ele entra no segunda chance 3 vezes durante essa execução
{
	//int i;
	struct result * resultFinal;
	WHEN("Teste para verificar se o relogio funciona, ele entra no segunda chance 3 vezes durante essa execução");
	resultFinal = memvirt(4, 4, "entrada3.txt", 1);
	assert(resultFinal);

	THEN("Deve ter 2 - 1- 1 - 1 referencias respectivamente");
	isEqual(resultFinal->refs[0], 2, 1);
	isEqual(resultFinal->refs[1], 1, 1);
	isEqual(resultFinal->refs[2], 1, 1);
	isEqual(resultFinal->refs[3], 1, 1);
		
	THEN("Deve ter 2 - 1 - 1 -  1  miss ")	;
	isEqual(resultFinal->pfs[0], 2, 1);
	isEqual(resultFinal->pfs[1], 1, 1);
	isEqual(resultFinal->pfs[2], 1, 1);
	isEqual(resultFinal->pfs[3], 1, 1);
	

	THEN("Deve ter porcetagem de miss de 100 -- 100 -- 100 -- 100 %");
	
	isEqual(resultFinal->pf_rate[0], 100, 1);
	isEqual(resultFinal->pf_rate[1], 100, 1);
	isEqual(resultFinal->pf_rate[2], 100, 1);
	isEqual(resultFinal->pf_rate[3], 100, 1);

	THEN("Ele teve um ws medio de 1.");
	isEqual(resultFinal->avg_ws, 1, 1);	
	
	THEN("Deve ter como taxa de page fault de % ");
	isEqual(resultFinal->total_pf_rate, 100, 1);	
}



int main()
{

	DESCRIBE("Simulador de paginacao");

	test1();
	test2();
	test3();
	GRADEME();

	if (grade==maxgrade)
		return 0;
	else 
		return grade;

}
