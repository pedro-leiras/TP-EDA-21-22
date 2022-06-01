/**
 * @file jobs.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 2)
 * Metodos para manipular as Structs Job
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

	if (aux == NULL) {
		return NULL;
	}

	aux->cod = cod;
	aux->operations = o;

	return aux;
}

/**
* @brief Verifica se um job existe na Lista de Jobs
* Procura se o job esta presente na Lista de Jobs, atraves do codigo
* @param [in] h		Primeiro node da árvore do ProcessPlan
* @param [in] cod	Codigo do Job a procurar
* @return	true - Job existe na lista; false - Job nao esta presente na lista
*/
bool CheckJobExists(Node* h, int cod) {
	if (h != NULL) {
		Node* aux = h;
		while (aux != NULL) {
			if (aux->job.cod == cod) {
				return true;
			}
			if (aux->job.cod > cod) {
				aux = aux->leftTree;
			}
			else {
				aux = aux->rightTree;
			}
			
		}
	}

	return false;
}

/**
* @brief Adiciona uma nova operacao ao Job
* @param [in] h			Primeiro node da árvore do ProcessPlan
* @param [in] jobCod	Codigo do Job
* @param [in] o			Apontador da lista de Operacoes adicionar
* @return	Primeiro node da árvore ProcessPlan
*/
Node* AddNewOperationToJob(Node* h, int jobCod, Operation* o) {
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
* @param [in] h				Primeiro node da árvore do ProcessPlan
* @param [in] jobCod		Codigo do Job
* @param [in] opCod			Codigo da Operacao a remover
* @return	Primeiro node da árvore do ProcessPlan
*/
Node* RemoveOperationFromJob(Node* h, int jobCod, int opCod) {
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
* @param [in] h		Primeiro node da árvore do ProcessPlan
* @param [in] cod	Codigo do Job a procurar
* @return	Apontador para o Job encontrado
*/
Job* SearchJob(Node* h, int cod) {
	if (h == NULL) return NULL;
	if (h->job.cod == cod) return &h->job;
	else
	{
		if (h->job.cod > cod) return (SearchJob(h->leftTree, cod));
		else return (SearchJob(h->rightTree, cod));
	}
}

/**
* @brief Determinar o tempo minimo para completar o Job
* @param [in] h			Primeiro node da árvore do ProcessPlan
* @param [in] jobCod	Codigo do Job
* @return	Struct com o tempo minimo para completar o Job e as respetivas operacoes, com as maquinas para obter esse valor
*/
OperationsMath GetMinTimeToCompleteJob(Node* h, int jobCod) {
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
* @param [in] h			Primeiro node da árvore do ProcessPlan
* @param [in] jobCod	Codigo do Job
* @return	Struct com o tempo maximo para completar o Job e as respetivas operacoes, com as maquinas para obter esse valor
*/
OperationsMath GetMaxTimeToCompleteJob(Node* h, int jobCod) {
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