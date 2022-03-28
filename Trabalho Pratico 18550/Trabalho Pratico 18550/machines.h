#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct Machine {
	int cod;
	int time;
}Machine;

typedef struct MachinesList {
	struct Machine machine;
	struct MachinesList* nextMachine;
}MachinesList;

Machine* CreateMachine(int* cod, int* time);
MachinesList* CreateMachineListNode(Machine* m);
MachinesList* InsertMachineInMachineList(MachinesList* h, Machine* newMachine);
bool CheckIfMachineAlreadyExists(MachinesList* h, int cod);