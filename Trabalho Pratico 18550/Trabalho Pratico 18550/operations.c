/**
 * @file operations.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho prático da UC EDA (versão 1)
 * Métodos para manipular as Structs Operation e OperationsList
 *
 * @bug bugs desconhecidos.
*/

#include "header.h"

/**
*	@brief Cria novo Operation.
*
*	Aloca memória necessária para armazenar um operation em memória
*
*	@param [in] cod Código da Operation
*	@param [in] m	Inicio da Lista de Máquinas
*
*/
Operation* CreateOperation(int cod, MachinesList* m) {
	Operation* aux = (Operation*)calloc(1, sizeof(Operation));
	aux->cod = cod;
	aux->machines = m;

	return aux;
}

/**
* @brief Cria novo nodo para a Lista de Jobs
* Copia para o nodo da lista a informação de um job
* @param [in] j	Novo Job
* @param [out] Apontador para nodo criado
*/
OperationsList* CreateOperationListNode(Operation* o) {
	OperationsList* newNode = (OperationsList*)calloc(1, sizeof(OperationsList));
	newNode->operation.cod = o->cod;
	newNode->operation.machines = o->machines;
	newNode->nextOperation = NULL;

	return newNode;
}

OperationsList* InsertOperationInOperationsList(OperationsList* h, Operation* newOperation) {
	if (newOperation == NULL) {
		return h;
	}

	OperationsList* aux = CreateOperationListNode(newOperation);

	if (CheckOperationExists(h, aux->operation.cod)) {
		return h;
	}

	if (h == NULL) {
		h = aux;
	}else {
		OperationsList* tmp = h;
		while (tmp->nextOperation != NULL) {
			tmp = tmp->nextOperation;
		}
		tmp->nextOperation = aux;
	}

	return h;
}

bool CheckOperationExists(OperationsList* h, int cod) {
	if (h != NULL) {
		OperationsList* aux = h;
		while (aux != NULL) {
			if (aux->operation.cod == cod) {
				return true;
			}
			aux = aux->nextOperation;
		}
	}

	return false;
}

Operation* SearchOperation(OperationsList* h, int cod) {
	if (h != NULL) {
		OperationsList* aux = h;
		while (aux != NULL) {
			if (aux->operation.cod == cod) {
				return (aux);
			}
			aux = aux->nextOperation;
		}
	}

	return NULL;
}

float GetAverageOperationTime(ProcessPlan* h, int jobCod, int opCod) {
	int sum = 0, i = 0;
	float res = -1;

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			Operation* auxOperation = SearchOperation(job->operations, opCod);
			if (auxOperation != NULL) {
				MachinesList* auxMachines = auxOperation->machines;
				sum = SumMachineTime(auxMachines);
				i = CountMachines(auxMachines);
				if (i != 0) {
					res = sum / (float)i;
				}
			}
		}
	}

	return res;
}

ProcessPlan* ChangeOperationInJob(ProcessPlan* h, int jobCod, int opCod, int macCod, int newTime) {
	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			Operation* auxOperation = SearchOperation(job->operations, opCod);
			if (auxOperation != NULL) {
				Machine* auxMachine = SearchMachine(auxOperation->machines, macCod);
				auxMachine = ChangeMachineTime(auxMachine, newTime);
			}
		}
	}

	return h;
}

OperationsMath GetMinTimeToCompleteOperations(OperationsList* h) {
	OperationsMath x = { 0, NULL };
	Machine* auxMachine;
	MachinesList* auxMachineList;
	Operation* auxOperation;

	while (h != NULL) {
		auxMachineList = NULL;
		auxMachine = GetMachineWithLowerTime(h->operation.machines);							//obtem a struct da maquina com menor tempo da operacao iterada
		if (auxMachine != NULL) {
			x.res += auxMachine->time;															//vai somando o tempo minimo de todas as maquinas
			auxMachineList = InsertMachineInMachinesList(auxMachineList, auxMachine);			//cria uma lista de maquinas com a maquina de menor tempo
			auxOperation = CreateOperation(h->operation.cod, auxMachineList);					//cria a operacao
			x.operations = InsertOperationInOperationsList(x.operations, auxOperation);			//insere a operacao criada na lista de operaçoes a retornar
		}
		h = h->nextOperation;
	}

	return x;
}

OperationsMath GetMaxTimeToCompleteOperations(OperationsList* h) {
	OperationsMath x = { 0, NULL };
	Machine* auxMachine;
	MachinesList* auxMachineList;
	Operation* auxOperation;

	while (h != NULL) {
		auxMachineList = NULL;
		auxMachine = GetMachineWithHigherTime(h->operation.machines);							//obtem a struct da maquina com maior tempo da operacao iterada
		if (auxMachine != NULL) {
			x.res += auxMachine->time;															//vai somando o maior tempo de todas as maquinas
			auxMachineList = InsertMachineInMachinesList(auxMachineList, auxMachine);			//cria uma lista de maquinas com a maquina de maior tempo
			auxOperation = CreateOperation(h->operation.cod, auxMachineList);					//cria a operacao
			x.operations = InsertOperationInOperationsList(x.operations, auxOperation);			//insere a operacao criada na lista de operaçoes a retornar
		}
		h = h->nextOperation;
	}

	return x;
}

void ListOperations(OperationsList* h) {
	if (h != NULL) {
		printf("Codigo Operacao: %d - Maquinas: \n", h->operation.cod);
		ListMachines(h->operation.machines);
		while (h->nextOperation != NULL) {
			h = h->nextOperation;
			printf("Codigo Operacao: %d - Maquinas: \n", h->operation.cod);
			ListMachines(h->operation.machines);	
		};
	}
}