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
	if (h == NULL) {
		return false;
	}

	OperationsList* aux = h;

	while (aux != NULL) {
		if (aux->operation.cod == cod) {
			return true;
		}
		aux = aux->nextOperation;
	}

	return false;
}

Operation* SearchOperation(OperationsList* h, int cod) {
	if (h == NULL) {
		return NULL;
	}else {
		OperationsList* aux = h;
		while (aux != NULL) {
			if (aux->operation.cod == cod) {
				return (aux);
			}
			aux = aux->nextOperation;
		}
		return NULL;
	}
}

