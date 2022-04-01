/**
 * @file jobs.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho prático da UC EDA (versão 1)
 * Métodos para manipular as Structs Job e ProcessPlan
 * 
 * @bug bugs desconhecidos.
*/

#include "header.h"

/**
*	@brief Cria novo Job.
*
*	Aloca memória necessária para armazenar um job em memória
*
*	@param [in] cod Código do Job
*	@param [in] o	Inicio da Lista de Operações
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
* Copia para o nodo da lista a informação de um job
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
* Procura se o job está presente na Lista de Jobs, através do código
* @param [in] h		Inicio da Lista do ProcessPlan
* @param [in] cod	Código do Job a procurar
* @return	true - Job existe na lista; false - Job não está presente na lista
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
* @brief Adiciona uma nova operação ao Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	Código do Job
* @param [in] o			Apontador da lista de Operações adicionar
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
* @brief Remove uma operação do Job
* @param [in] h				Inicio da Lista do ProcessPlan
* @param [in] jobCod		Código do Job
* @param [in] opCod			Código da Operação a remover
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
* @brief Verifica se o Job existe. Se existir devolve endereço do Job!
* @param [in] h		Inicio da Lista do ProcessPlan
* @param [in] cod	Código do Job a procurar
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
* @param [in] jobCod	Código do Job
* @return	Struct com o tempo mínimo para completar o Job e as respetivas operações, com as máquinas para obter esse valor
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
* @brief Determinar o tempo máximo para completar o Job
* @param [in] h			Inicio da Lista do ProcessPlan
* @param [in] jobCod	Código do Job
* @return	Struct com o tempo máximo para completar o Job e as respetivas operações, com as máquinas para obter esse valor
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

