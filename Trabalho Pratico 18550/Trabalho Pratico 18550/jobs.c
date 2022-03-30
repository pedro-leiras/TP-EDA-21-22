#include "header.h"

Job* CreateJob(int cod, OperationsList* o) {
	Job* aux = (Job*)calloc(1, sizeof(Job));
	aux->cod = cod;
	aux->operations = o;
	return aux;
}

ProcessPlan* CreateJobNode(Job* j) {
	ProcessPlan* newNode = (ProcessPlan*)calloc(1, sizeof(ProcessPlan));
	newNode->job.cod = j->cod;
	newNode->job.operations = j->operations;
	newNode->nextJob = NULL;

	return newNode;
}

ProcessPlan* InsertJobInProcessPlan(ProcessPlan* h, Job* newJob) {
	if (newJob == NULL) {
		return h;
	}

	ProcessPlan* aux = CreateJobNode(newJob);

	if (CheckJobExists(h, aux->job.cod)) {
		return h;
	}

	if (h == NULL) {
		h = aux;
	}
	else {
		ProcessPlan* tmp = h;
		while (tmp->nextJob != NULL) {
			tmp = tmp->nextJob;
		}
		tmp->nextJob = aux;
	}

	return h;
}

bool CheckJobExists(ProcessPlan* h, int cod) {
	if (h == NULL) {
		return false;
	}

	ProcessPlan* aux = h;

	while (aux != NULL) {
		if (aux->job.cod == cod) {
			return true;
		}
		aux = aux->nextJob;
	}

	return false;
}

ProcessPlan* AddNewOperationToJob(ProcessPlan* h, int jobCod, Operation* o) {
	if (h != NULL) {
		Job* aux = SearchJob(h, jobCod);
		if (aux != NULL)		//se encontrou o job
		{
			aux->operations = InsertOperationInOperationsList(aux->operations, o);
		}
	}
	return h;
}

ProcessPlan* RemoveOperationFromJob(ProcessPlan* h, int jobCod, int opCod) {
	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			if (job->operations->operation.cod == opCod) {				//primeira operacao
				OperationsList* aux = job->operations;
				job->operations = job->operations->nextOperation;		//head passa para a segunda operacao
				free(aux);
			}else {
				OperationsList* aux = job->operations;
				OperationsList* auxAnt = aux;
				while (aux && aux->operation.cod != opCod) {			//procura para remover
					auxAnt = aux;
					aux = aux->nextOperation;
				}
				if (aux != NULL) {									//se encontrou, remove
					auxAnt->nextOperation = aux->nextOperation;
					free(aux);
				}
			}
		}
	}
	return h;
}

ProcessPlan* ChangeOperationInJob(ProcessPlan* h, int jobCod, int opCod, int macCod, int newTime) {
	if (h != NULL) {
		Job* aux = SearchJob(h, jobCod);
		if (aux != NULL && aux->operations != NULL)		//se encontrou o job e contem operacoes
		{
			Operation* auxOperation = SearchOperation(aux->operations, opCod);
			if (auxOperation != NULL) {
				Machine* auxMachine = SearchMachine(auxOperation->machines, macCod);
				if (auxMachine != NULL) {
					auxMachine->time = newTime;
				}
			}
		}
	}
	return h;
}

Job* SearchJob(ProcessPlan* h, int cod) {
	if (h == NULL) {
		return NULL;
	}else {
		ProcessPlan* aux = h;
		while (aux != NULL) {
			if (aux->job.cod == cod) {
				return (aux);
			}
			aux = aux->nextJob;
		}
		return NULL;
	}
}

OperationsMath GetMinTimeToCompleteJob(ProcessPlan* h, int jobCod) {
	OperationsMath x = { 0, NULL };
	int minTime = 0;

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* auxOperations = job->operations;
			while (auxOperations != NULL) {											//percorrer todas as operacoes
				MachinesList* auxMachines = auxOperations->operation.machines;
				int aux = auxMachines->machine.time;								//atribui à aux o tempo da primeira maquina
				while (auxMachines != NULL) {										//percorrer todas as maquinas da operacao
					if (auxMachines->machine.time < aux) {							//comparar se o tempo da maquina e menor ao da auxiliar
						aux = auxMachines->machine.time;
					}
					auxMachines = auxMachines->nextMachine;
				}
				minTime += aux;
				auxOperations = auxOperations->nextOperation;
			}
			x.res = minTime;
		}
	}
	return x;
};

OperationsMath GetMaxTimeToCompleteJob(ProcessPlan* h, int jobCod) {
	OperationsMath x = { 0, NULL };
	int minTime = 0;

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* auxOperations = job->operations;
			while (auxOperations != NULL) {											//percorrer todas as operacoes
				MachinesList* auxMachines = auxOperations->operation.machines;
				int aux = auxMachines->machine.time;								//atribui à aux o tempo da primeira maquina
				while (auxMachines != NULL) {										//percorrer todas as maquinas da operacao
					if (auxMachines->machine.time > aux) {							//comparar se o tempo da maquina e superior ao da auxiliar
						aux = auxMachines->machine.time;
					}
					auxMachines = auxMachines->nextMachine;
				}
				minTime += aux;
				auxOperations = auxOperations->nextOperation;
			}
			x.res = minTime;
		}
	}
	return x;
};