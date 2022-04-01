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
	if (h != NULL) {
		ProcessPlan* aux = h;
		while (aux != NULL) {
			if (aux->job.cod == cod) {
				return true;
			}
			aux = aux->nextJob;
		}
	}

	return false;
}

ProcessPlan* AddNewOperationToJob(ProcessPlan* h, int jobCod, Operation* o) {
	if (h != NULL) {
		Job* aux = SearchJob(h, jobCod);
		if (aux != NULL) {		//se encontrou o job
			aux->operations = InsertOperationInOperationsList(aux->operations, o);
		}
	}

	return h;
}

ProcessPlan* RemoveOperationFromJob(ProcessPlan* h, int jobCod, int opCod) {
	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* aux = job->operations;
			OperationsList* auxAnt = aux;
			if (aux->operation.cod == opCod) {				            //primeira operacao
				job->operations = job->operations->nextOperation;		//head passa para a segunda operacao
				free(aux);
			}else {
				while (aux && aux->operation.cod != opCod) {			//procura para remover
					auxAnt = aux;
					aux = aux->nextOperation;
				}
				if (aux != NULL) {									    //se encontrou, remove
					auxAnt->nextOperation = aux->nextOperation;
					free(aux);
				}
			}
		}
	}

	return h;
}

Job* SearchJob(ProcessPlan* h, int cod) {
	if (h != NULL) {
		ProcessPlan* aux = h;
		while (aux != NULL) {
			if (aux->job.cod == cod) {
				return (aux);
			}
			aux = aux->nextJob;
		}
	}

	return NULL;
}

OperationsMath GetMinTimeToCompleteJob(ProcessPlan* h, int jobCod) {
	OperationsMath x = { 0, NULL };

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* auxOperations = job->operations;
			x.res = GetMinTimeToCompleteOperations(auxOperations);
		}
	}

	return x;
};

OperationsMath GetMaxTimeToCompleteJob(ProcessPlan* h, int jobCod) {
	OperationsMath x = { 0, NULL };

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* auxOperations = job->operations;
			x.res = GetMaxTimeToCompleteOperations(auxOperations);
		}
	}

	return x;
};

