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
