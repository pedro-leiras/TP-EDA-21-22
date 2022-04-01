/**
 * @file jobs.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 1)
 * Métodos para manipular as Structs Job e ProcessPlan
 * 
 * @bug bugs desconhecidos.
*/

#include "header.h"

/**
*	@brief Cria novo Job.
*
*	Aloca memoria necessaria para armazenar um job em memoria
*
*	@param [in] cod Codigo do Job
*	@param [in] o	Inicio da Lista de Operacoes
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
* Copia para o nodo da lista a informacao de um job
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
* Procura se o job esta presente na Lista de Jobs, através do codigo
* @param [in] h		Inicio da Lista do ProcessPlan
* @param [in] cod	Codigo do Job a procurar
* @return	true - Job existe na lista; false - Job nao esta presente na lista
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
* @brief Adiciona uma nova operacao ao Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	Codigo do Job
* @param [in] o			Apontador da lista de Operacoes adicionar
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
* @brief Remove uma operacao do Job
* @param [in] h				Inicio da Lista do ProcessPlan
* @param [in] jobCod		Codigo do Job
* @param [in] opCod			Codigo da Operacao a remover
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
* @brief Verifica se o Job existe. Se existir devolve endereco do Job!
* @param [in] h		Inicio da Lista do ProcessPlan
* @param [in] cod	Codigo do Job a procurar
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
* @brief Determinar o tempo mínimo para completar o Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	Codigo do Job
* @return	Struct com o tempo mínimo para completar o Job e as respetivas operacoes, com as maquinas para obter esse valor
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
* @brief Determinar o tempo maximo para completar o Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	Codigo do Job
* @return	Struct com o tempo maximo para completar o Job e as respetivas operacoes, com as maquinas para obter esse valor
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

