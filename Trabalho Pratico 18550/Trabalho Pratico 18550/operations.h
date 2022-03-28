#pragma once

#include "machines.h";

typedef struct Operation {
	int cod;
	struct MachinesList* machines;

}Operation;

typedef struct OperationsList {
	struct Operation operation;
	struct OperationsList* nextOperation;
}OperationsList;

Operation* CreateOperation(int cod, MachinesList* m);
OperationsList* CreateOperationListNode(Operation* o);
OperationsList* InsertOperationInOperationList(OperationsList* h, Operation* newMOperation);
bool CheckIfOperationAlreadyExists(OperationsList* h, int cod);