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
*	@brief Cria nova Operation.
*
*	Aloca memória necessária para armazenar uma Operation em memória
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
* @brief Cria novo nodo para a Lista de Operações
* Copia para o nodo da lista a informação de uma Operation
* @param [in] o		Nova Operation
* @return	Apontador para nodo criado
*/
OperationsList* CreateOperationListNode(Operation* o) {
	OperationsList* newNode = (OperationsList*)calloc(1, sizeof(OperationsList));
	newNode->operation.cod = o->cod;
	newNode->operation.machines = o->machines;
	newNode->nextOperation = NULL;

	return newNode;
}

/**
* @brief Insere uma nova Operation na lista
* @param [in] h				Inicio da Lista de Operações
* @param [in] newOperation	Apontador da Operation a adicionar
*/
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

/**
* @brief Verifica se uma Operation existe a Lista de Operações
* Procura se a Operation está presente na Lista de Operações, através do código
* @param [in] h		Inicio da Lista do OperationsList
* @param [in] cod	Código da Operation a procurar
* @return	true - Operation existe na lista; false - Operation não está presente na lista
*/
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

/**
* @brief Verifica se a Operation existe. Se existir devolve endereço da Operation!
* @param [in] h		Inicio da Lista do OperationsList
* @param [in] cod	Código da Operation a procurar
* @return	Apontador para a Operation encontrada
*/
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

/**
* @brief Determina a quantidade média de unidades de tempo necessárias para completar uma operação
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	Código da Job
* @param [in] opCod		Código da Operation
* @return	Quantidade média de unidades de tempo em float
*/
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

/**
* @brief Altera os dados de uma Operação
* @param [in] h				Inicio da Lista do ProcessPlan
* @param [in] jobCod		Código da Job
* @param [in] opCod			Código da Operation
* @param [in] macCod		Código da Machine
* @param [in] newMacCod		Novo código da Machine
* @param [in] newTime		Novo tempo da Machine
* @return	Inicio da Lista do ProcessPlan
*/
ProcessPlan* ChangeOperationInJob(ProcessPlan* h, int jobCod, int opCod, int macCod, int newMacCod, int newTime) {
	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			Operation* auxOperation = SearchOperation(job->operations, opCod);
			if (auxOperation != NULL) {
				Machine* auxMachine = SearchMachine(auxOperation->machines, macCod);
				auxMachine = ChangeMachine(auxMachine, newMacCod, newTime);
			}
		}
	}

	return h;
}

/**
* @brief Determina a quantidade mínima de unidades de tempo necessárias para completar uma operação
* @param [in] h		Inicio da Lista do ProcessPlan
* @return	Struct com o resultado e respetivas operações onde o resultado foi obtido
*/
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

/**
* @brief Determina a quantidade máxima de unidades de tempo necessárias para completar uma operação
* @param [in] h		Inicio da Lista do ProcessPlan
* @return	Struct com o resultado e respetivas operações onde o resultado foi obtido
*/
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

/**
* @brief Lista todas as operações de uma Lista de Operações
* @param [in] h		Inicio da Lista de Operações
*/
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