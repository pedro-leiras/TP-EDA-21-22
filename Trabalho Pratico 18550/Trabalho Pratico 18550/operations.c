#include "operations.h"
#include "machines.h"

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

OperationsList* InsertOperationInOperationList(OperationsList* h, Operation* newMOperation) {
	if (newMOperation == NULL) {
		return h;
	}

	OperationsList* aux = CreateOperationListNode(newMOperation);

	if (CheckIfMachineAlreadyExists(h, aux->operation.cod)) {
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

bool CheckIfOperationAlreadyExists(OperationsList* h, int cod) {
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