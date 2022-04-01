#include "header.h";

int main() {
	ProcessPlan* p = NULL;
	//p = ReadProcessPlanFile("data.txt", p);

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
	p = InsertJobInProcessPlan(p, Job1);

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

	float y = GetAverageOperationTime(p, 1, 3);

	return 0;
}


//TODO: perceber como desfragmentar cada linha
ProcessPlan* ReadProcessPlanFile(char* path, ProcessPlan* p) {
	FILE* fp = fopen(path, "r");
	char buffer[256];
	int result;
	if (fp == NULL)
	{
		printf("Error: could not open file %s", path);
		return p;
	}

	while (fgets(buffer, 256, fp)) {
		char line[250];
		char* machines;
		char machine[250];
		char* auxMach;
		char* macData;
		int machCod, machTime;
		strcpy(line, buffer);

		machines = strtok(line, "()");
		while (machines != NULL) {
			if (strcmp(machines, ";") != 0) {
				strcpy(machine, machines);
				auxMach = strtok(machine, "{}");
				/*while (auxMach != NULL) {
					printf("%s", auxMach);
					macData = strtok(auxMach, ",");
					machCod = macData;
					while (macData != NULL) {
						macData = strtok(auxMach, ",");
						machTime = macData;
						auxMach = strtok(NULL, ",");
					}
					auxMach = strtok(NULL, "{}");
				}*/
			}
	
			machines = strtok(NULL, "()");
		}
	}
		
	fclose(fp);

	return p;
}