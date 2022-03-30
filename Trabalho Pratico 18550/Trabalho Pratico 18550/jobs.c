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

Job* AddNewOperationToJob(Job* j, Operation* o) {
	if (j == NULL) {
		return j;
	}

	Job* aux = j;
	aux->operations = InsertOperationInOperationsList(aux->operations, o);
	return aux;
}

Job* RemoveOperationFromJob(Job* j, int cod) {
	if (j == NULL) {
		return j;
	}
	if (cod == NULL) {
		return j;
	}

	if (j->operations->operation.cod == cod) {				//primeira operacao
		OperationsList* aux = j->operations;
		j->operations = j->operations->nextOperation;
		free(aux);
	}else {
		OperationsList* aux = j->operations;
		OperationsList* auxAnt = aux;
		while (aux && aux->operation.cod != cod) {			//procura para revover
			auxAnt = aux;
			aux = aux->nextOperation;
		}
		if (aux != NULL) {									//se encontrou, remove
			auxAnt->nextOperation = aux->nextOperation;
			free(aux);
		}
	}

	return j;
}