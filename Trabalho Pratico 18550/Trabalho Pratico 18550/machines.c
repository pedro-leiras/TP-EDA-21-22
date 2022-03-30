#include "header.h"

Machine* CreateMachine(int cod, int time) {
	Machine* aux = (Machine*)calloc(1, sizeof(Machine));
	aux->cod = cod;
	aux->time = time;

	return aux;
}

MachinesList* CreateMachineListNode(Machine* m) {
	MachinesList* newNode = (MachinesList*)calloc(1, sizeof(MachinesList));
	newNode->machine.cod = m->cod;
	newNode->machine.time = m->time;
	newNode->nextMachine = NULL;

	return newNode;
}

MachinesList* InsertMachineInMachinesList(MachinesList* h, Machine* newMachine) {
	if (newMachine == NULL) {
		return h;
	}

	MachinesList* aux = CreateMachineListNode(newMachine);

	if (CheckMachineExists(h, aux->machine.cod)) {
		return h;
	}

	if (h == NULL) {
		h = aux;
	}else {
		MachinesList* tmp = h;
		while (tmp->nextMachine != NULL) {
			tmp = tmp->nextMachine;
		}
		tmp->nextMachine = aux;
	}

	return h;
}

bool CheckMachineExists(MachinesList* h, int cod) {
	if (h == NULL) {
		return false;
	}

	MachinesList* aux = h;

	while (aux != NULL) {
		if (aux->machine.cod == cod) {
			return true;
		}
		aux = aux->nextMachine;
	}

	return false;
}