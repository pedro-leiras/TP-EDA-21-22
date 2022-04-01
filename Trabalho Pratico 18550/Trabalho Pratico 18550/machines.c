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
	if (h != NULL) {
		MachinesList* aux = h;
		while (aux != NULL) {
			if (aux->machine.cod == cod) {
				return true;
			}
			aux = aux->nextMachine;
		}
	}

	return false;
}

Machine* SearchMachine(MachinesList* h, int cod) {
	if (h != NULL) {
		MachinesList* aux = h;
		while (aux != NULL) {
			if (aux->machine.cod == cod) {
				return (aux);
			}
			aux = aux->nextMachine;
		}
	}

	return NULL;
}

int SumMachineTime(MachinesList* h) {
	int sum = 0;
	while (h != NULL) {
		sum += h->machine.time;
		h = h->nextMachine;
	}

	return sum;
}

int CountMachines(MachinesList* h) {
	int count = 0;
	while (h != NULL) {
		count++;
		h = h->nextMachine;
	}

	return count;
}

Machine* ChangeMachineTime(Machine* h, int newTime) {
	if (h != NULL) {
		h->time = newTime;
	}
	return h;
}

int GetMinMachineTime(MachinesList* h) {
	int aux = 0;
	if (h != NULL) {
		aux = h->machine.time;									//atribui à aux o tempo da primeira maquina
		while (h != NULL) {										//percorrer todas as maquinas da operacao
			if (h->machine.time < aux) {						//comparar se o tempo da maquina e menor ao da aux
				aux = h->machine.time;
			}
			h = h->nextMachine;
		}
	}

	return aux;
}

int GetMaxMachineTime(MachinesList* h) {
	int aux = 0;
	if (h != NULL) {
		aux = h->machine.time;									//atribui à aux o tempo da primeira maquina
		while (h != NULL) {										//percorrer todas as maquinas da operacao
			if (h->machine.time > aux) {						//comparar se o tempo da maquina e maior ao da aux
				aux = h->machine.time;
			}
			h = h->nextMachine;
		}
	}

	return aux;
}