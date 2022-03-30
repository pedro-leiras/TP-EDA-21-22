#include "header.h";

int main() {

	Machine* M1 = CreateMachine(1, 4);
	Machine* M2 = CreateMachine(2, 5);
	Machine* M3 = CreateMachine(3, 2);
	Machine* M4 = CreateMachine(4, 1);

	MachinesList* machinesOp1 = NULL;
	machinesOp1 = InsertMachineInMachinesList(machinesOp1, M1);
	machinesOp1 = InsertMachineInMachinesList(machinesOp1, M2);

	Operation* O1 = CreateOperation(1, machinesOp1);
	OperationsList* OperationsJob1 = NULL;
	OperationsJob1 = InsertOperationInOperationsList(OperationsJob1, O1);

	Job* Job1 = CreateJob(1, OperationsJob1);

	ProcessPlan* p = NULL;
	p = InsertJobInProcessPlan(p, Job1);


	//--
	MachinesList* machinesOp2 = NULL;
	machinesOp2 = InsertMachineInMachinesList(machinesOp2, M3);
	machinesOp2 = InsertMachineInMachinesList(machinesOp2, M4);
	Operation* O2 = CreateOperation(2, machinesOp2);
	Job1 = AddNewOperationToJob(Job1, O2);

	MachinesList* machinesOp3 = NULL;
	machinesOp3 = InsertMachineInMachinesList(machinesOp3, M1);
	machinesOp3 = InsertMachineInMachinesList(machinesOp3, M3);
	Operation* O3 = CreateOperation(3, machinesOp3);
	
	Job1 = AddNewOperationToJob(Job1, O3);
	Job1 = RemoveOperationFromJob(Job1, 1);
	Job1 = RemoveOperationFromJob(Job1, 3);


	return 0;
}