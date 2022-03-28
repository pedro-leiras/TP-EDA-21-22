#include "header.h";

int main() {

	Machine* M1 = CreateMachine(1, 4);
	Machine* M2 = CreateMachine(3, 5);
	MachinesList* machinesOp1 = NULL;
	machinesOp1 = InsertMachineInMachineList(machinesOp1, M1);
	machinesOp1 = InsertMachineInMachineList(machinesOp1, M2);

	Operation* O1 = CreateOperation(1, machinesOp1);
	OperationsList* OperationsJob1 = NULL;
	OperationsJob1 = InsertOperationInOperationList(OperationsJob1, O1);

	return 0;
}