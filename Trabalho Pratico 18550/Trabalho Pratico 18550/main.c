#include "header.h";

int main() {

	Machine* M1 = CreateMachine(1, 4);
	Machine* M2 = CreateMachine(2, 4);
	Machine* M3 = CreateMachine(3, 5);
	Machine* M4 = CreateMachine(4, 5);

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
	MachinesList* machinesOp3 = NULL;
	machinesOp3 = InsertMachineInMachinesList(machinesOp3, M1);
	machinesOp3 = InsertMachineInMachinesList(machinesOp3, M3);
	Operation* O3 = CreateOperation(3, machinesOp3);

	p = AddNewOperationToJob(p, 1, O2);
	p = AddNewOperationToJob(p, 1, O3);
	p = RemoveOperationFromJob(p, 1, 1);
	p = ChangeOperationInJob(p, 1, 3, 3, 10);
	OperationsMath x;
	x = GetMinTimeToCompleteJob(p, 1);
	x = GetMaxTimeToCompleteJob(p, 1);
	return 0;
}