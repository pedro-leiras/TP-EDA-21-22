#include "header.h"

Operation* CreateOperation(int cod, MachinesList* m) {
	Operation* aux = (Operation*)calloc(1, sizeof(Operation));
	aux->cod = cod;
	aux->machines = m;

	return aux;
}

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
		if (job != NULL && job->operations != NULL)		//se encontrou o job e contem operacoes
		{
			Operation* auxOperation = SearchOperation(job->operations, opCod);
			if (auxOperation != NULL) {
				Machine* auxMachine = SearchMachine(auxOperation->machines, macCod);
				auxMachine = ChangeMachineTime(auxMachine, newTime);
			}
		}
	}

	return h;
}

int GetMinTimeToCompleteOperation(Operation h) {
	int aux = 0;
	if (h.machines != NULL) {
		MachinesList* auxMachines = h.machines;
		aux = GetMinMachineTime(auxMachines);
	}

	return aux;
}

int GetMaxTimeToCompleteOperation(Operation h) {
	int aux = 0;
	if (h.machines != NULL) {
		MachinesList* auxMachines = h.machines;
		aux = GetMaxMachineTime(auxMachines);
	}

	return aux;
}

int GetMinTimeToCompleteOperations(OperationsList* h) {
	int aux = 0;												//total da soma do tempo min de cada operacao
	while (h != NULL) {
		Operation auxOperation = h->operation;
		aux += GetMinTimeToCompleteOperation(auxOperation);
		h = h->nextOperation;
	}

	return aux;
}

int GetMaxTimeToCompleteOperations(OperationsList* h) {
	int aux = 0;												//total da soma do tempo max de cada operacao
	while (h != NULL) {
		Operation auxOperation = h->operation;
		aux += GetMaxTimeToCompleteOperation(auxOperation);
		h = h->nextOperation;
	}

	return aux;
}