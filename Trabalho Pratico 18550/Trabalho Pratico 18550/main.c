#include "header.h";

int main() {

	Machine* M1 = CreateMachine(1, 4);
	Machine* M2 = CreateMachine(3, 5);
	MachinesList* machines = NULL;
	machines = InsertMachineInMachineList(machines, M1);
	machines = InsertMachineInMachineList(machines, M2);

	return 0;
}