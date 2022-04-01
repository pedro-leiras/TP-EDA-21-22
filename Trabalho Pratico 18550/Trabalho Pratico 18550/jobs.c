/**
 * @file jobs.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pr�tico da UC EDA (vers�o 1)
 * M�todos para manipular as Structs Job e ProcessPlan
 * 
 * @bug bugs desconhecidos.
*/

#include "header.h"

/**
*	@brief Cria novo Job.
*
*	Aloca mem�ria necess�ria para armazenar um job em mem�ria
*
*	@param [in] cod C�digo do Job
*	@param [in] o	Inicio da Lista de Opera��es
*
*/
Job* CreateJob(int cod, OperationsList* o) {
	Job* aux = (Job*)calloc(1, sizeof(Job));
	aux->cod = cod;
	aux->operations = o;

	return aux;
}

/**
* @brief Cria novo nodo para a Lista de Jobs
* Copia para o nodo da lista a informa��o de um job
* @param [in] j		Novo Job
* @return	Apontador para nodo criado
*/
ProcessPlan* CreateProcessPlanNode(Job* j) {
	ProcessPlan* newNode = (ProcessPlan*)calloc(1, sizeof(ProcessPlan));
	newNode->job.cod = j->cod;
	newNode->job.operations = j->operations;
	newNode->nextJob = NULL;

	return newNode;
}

/**
* @brief Insere um novo job na lista
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] newJob	Apontador do Job a adicionar
*/
ProcessPlan* InsertJobInProcessPlan(ProcessPlan* h, Job* newJob) {
	if (newJob == NULL) {
		return h;
	}

	ProcessPlan* aux = CreateProcessPlanNode(newJob);

	if (CheckJobExists(h, aux->job.cod)) {
		return h;
	}

	if (h == NULL) {
		h = aux;
	}else {
		ProcessPlan* tmp = h;
		while (tmp->nextJob != NULL) {
			tmp = tmp->nextJob;
		}
		tmp->nextJob = aux;
	}

	return h;
}

/**
* @brief Verifica se um job existe na Lista de Jobs
* Procura se o job est� presente na Lista de Jobs, atrav�s do c�digo
* @param [in] h		Inicio da Lista do ProcessPlan
* @param [in] cod	C�digo do Job a procurar
* @return	true - Job existe na lista; false - Job n�o est� presente na lista
*/
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

/**
* @brief Adiciona uma nova opera��o ao Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	C�digo do Job
* @param [in] o			Apontador da lista de Opera��es adicionar
* @return	Inicio da Lista do ProcessPlan
*/
ProcessPlan* AddNewOperationToJob(ProcessPlan* h, int jobCod, Operation* o) {
	if (h != NULL) {
		Job* aux = SearchJob(h, jobCod);
		if (aux != NULL) {
			aux->operations = InsertOperationInOperationsList(aux->operations, o);
		}
	}

	return h;
}

/**
* @brief Remove uma opera��o do Job
* @param [in] h				Inicio da Lista do ProcessPlan
* @param [in] jobCod		C�digo do Job
* @param [in] opCod			C�digo da Opera��o a remover
* @return	Inicio da Lista do ProcessPlan
*/
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

/**
* @brief Verifica se o Job existe. Se existir devolve endere�o do Job!
* @param [in] h		Inicio da Lista do ProcessPlan
* @param [in] cod	C�digo do Job a procurar
* @return	Apontador para o Job encontrado
*/
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

/**
* @brief Determinar o tempo m�nimo para completar o Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	C�digo do Job
* @return	Struct com o tempo m�nimo para completar o Job e as respetivas opera��es, com as m�quinas para obter esse valor
*/
OperationsMath GetMinTimeToCompleteJob(ProcessPlan* h, int jobCod) {
	OperationsMath aux = { 0, NULL };

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* auxOperations = job->operations;
			aux = GetMinTimeToCompleteOperations(auxOperations);
		}
	}

	return aux;
};

/**
* @brief Determinar o tempo m�ximo para completar o Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	C�digo do Job
* @return	Struct com o tempo m�ximo para completar o Job e as respetivas opera��es, com as m�quinas para obter esse valor
*/
OperationsMath GetMaxTimeToCompleteJob(ProcessPlan* h, int jobCod) {
	OperationsMath x = { 0, NULL };

	if (h != NULL) {
		Job* job = SearchJob(h, jobCod);
		if (job != NULL && job->operations != NULL) {
			OperationsList* auxOperations = job->operations;
			x = GetMaxTimeToCompleteOperations(auxOperations);
		}
	}

	return x;
};

