/**
 * @file processPlan.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 1)
 * Metodos para manipular a arvore do ProcessPlan
 *
 * @bug bugs desconhecidos.
*/

#include "header.h"

/**
*	@brief Inicializa a arvore
*
*/
PtrNode InitTree() {
	return NULL;
}

/**
*	@brief Cria novo node da arvore.
*
*	Aloca memoria necessaria para armazenar um node da arvore em memoria
*
*	@param [in] j	Apontador do Job a adicionar
*	@return			Nodo criado
*/
Node* NewNode(Job* j) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}

	node->job.cod = j->cod;
	node->job.operations = j->operations;
	node->leftTree = NULL;
	node->rightTree = NULL;

	return node;
}


/**
*	@brief Adiciona job a arvore. (recursivo)
*
*	Adiciona um job a arvore, verificando o codigo do Job de forma a escolher o ramo a adicionar
*
*	@param [in] root	Node da arvore
*	@param [in] j		Apontador do Job a adicionar
*	@return		Primeiro node da arvore	
*/
Node* AddNode(Node* root, Job* j) {
	if (root == NULL) {		//arvore vazia
		root = NewNode(j);
	}else {
		if (CheckJobExists(root, j->cod)) {
			return root;
		}
		if (root->job.cod > j->cod) {		//Insere à esquerda
			root->leftTree = AddNode(root->leftTree, j);
		}else {
			if (root->job.cod < j->cod) {		//Insere à direita
				root->rightTree = AddNode(root->rightTree, j);
			}
		}
	}
	return root;
}

/**
*	@brief Remove job da arvore. (recursivo)
*
*	Procura se o Job existe na arvore e de forma recursiva encontra o ramo onde se encontra. Uma vez encontrado remove.
*
*	@param [in] root	Node da arvore
*	@param [in] j		Apontador do Job a adicionar
*	@return		Primeiro node da arvore
*/
PtrNode RemoveJob(PtrNode root, int codJob) {
	if (root == NULL) {			//árvore vazia ou inexistente
		return NULL;
	}

	Job* j = SearchJob(root, codJob);

	if (j != NULL) {
		if (root->job.cod > j->cod){
			root->leftTree = RemoveJob(root->leftTree, j);
		}else {
			if (root->job.cod < j->cod) {
				root->rightTree = RemoveJob(root->rightTree, j);
			}else {
				root = DeleteCurrentNode(root);
			}
		}
	}
	return root;
}

/**
*	@brief Remove node da arvore.
*
*	Verifica a existencia de sub-arvores e remove o node indicado
*
*	@param [in] root	Node da arvore
*	@return		Primeiro node da arvore
*/
PtrNode DeleteCurrentNode(PtrNode root) {
	PtrNode aux;
	if (root == NULL) return NULL;	//Nada para apagar!

	if (root->leftTree == NULL && root->rightTree == NULL) {	//único nodo
		DestroyNode(&root);
		return NULL;
	}
	else
		if (root->leftTree == NULL) {		//só tem sub-arvore direita...ligar à direita
			aux = root;
			root = root->rightTree;
			DestroyNode(&aux);
		}
		else
		{
			if (root->rightTree == NULL) {	//só com sub-arvore esquerda
				aux = root;
				root = root->leftTree;
				DestroyNode(&aux);
			}
			else       //com sub-arvores esquerda e direita
			{
				//substitui pelo menor da sub-arvore direita
				root->job = FindMin(root->rightTree)->job;
				//elimina o menor da sub-arvore direita
				root->rightTree = RemoveJob(root->rightTree, &root->job);
			}
		}
	return root;
}

/**
*	@brief Remove node da arvore na memoria.
*
*	Liberta da memoria um node indicado
*
*	@param [in] p	Node da arvore
*/
void DestroyNode(Node** p) {	
	if (*p != NULL) {
		free(*p);
		*p = NULL;
	}
}

/**
*	@brief Encontra o node mais pequeno da arvore (recursivo)
*
*	Encontra o node com o codigo de Job mais pequeno (mais a esquerda)
*
*	@param [in] root	Node da arvore
* 	@return		Node com o codigo de Job mais pequeno da arvore
*/
PtrNode FindMin(PtrNode root) {
	if (root->leftTree == NULL) return root;
	else
		return(FindMin(root->leftTree));
}

/**
*	@brief Conta quantos nodes tem a arvore
*
*	Conta o total de nodes existentes na arvore
*
*	@param [in] r	Node da arvore
* 	@return		Total de nodes
*/
int TreeSize(PtrNode r) {

	if (r == NULL) return 0;
	else
		return (1 + TreeSize(r->leftTree) + TreeSize(r->rightTree));
}

/**
*	@brief Balanceia os ramos da arvore
*
*	@param [in] root	Node da arvore
* 	@return		Primeiro node da arvore	
*/
PtrNode Balance(PtrNode root) {
	PtrNode newRoot = NULL;
	if (root == NULL) return NULL;

	int tot = TreeSize(root); //quantos nodos tem a arvore?
	int count = 0;

	//criar estrutura "dinâmica" auxiliar
	Node* listNode;
	if ((listNode = (Node*)malloc(sizeof(Node) * tot)) == NULL) return NULL;
	//preenche "lista" a partir da arvore
	BST2List(root, &count, listNode);
	//balanceia arvore
	newRoot = BSTBalance(newRoot, listNode, 0, tot - 1);
	free(listNode);
	return newRoot;
}

/*
Balanceia árvore. Travessia Binária de um array!
*/
PtrNode BSTBalance(PtrNode root, Node* list, int ini, int end) {
	unsigned int m;

	if (ini <= end) {
		m = (ini + end) / 2;
		root = AddNode(root, &list[m].job);
		root = BSTBalance(root, list, ini, m - 1);
		root = BSTBalance(root, list, m + 1, end);
	}
	return root;
}

/*
Cria uma "Lista" a partir dos elementos de uma arvore
*/
void BST2List(PtrNode root, unsigned int* count, Node* list) {
	if (root != NULL) {
		BST2List(root->leftTree, count, list);
		list[(*count)++].job = root->job;
		BST2List(root->rightTree, count, list);
	}
}

/**
*	@brief Grava arvore em ficheiro binario
*
*	Grava em cada linha o codigo do Job, codigo da operacao e cada maquina de forma individual
* 
*	@param [in] h	Node da arvore
*	@param [in] fp	Apontador do ficheiro
* 	@return	 TRUE - gravado com sucesso | FALSE - erro na gravacao
*/
bool SaveAll(Node* h, FILE* fp) {
	if (h == NULL) return false;
	else{
		SaveAll(h->leftTree, fp); //grava ramos a esquerda
		Job* auxJob = &h->job;	//grava ramo atual
		OperationsList* auxOperations = auxJob->operations;
		NodeInfo auxFile = { 0, 0, NULL };
		auxFile.codJob = auxJob->cod;
		while (auxOperations)
		{
			auxFile.codOperation = auxOperations->operation.cod;
			MachinesList* auxMachine = auxOperations->operation.machines;
			while (auxMachine) {
				auxFile.machine.cod = auxMachine->machine.cod;
				auxFile.machine.time = auxMachine->machine.time;
				fwrite(&auxFile, sizeof(auxFile), 1, fp);
				auxMachine = auxMachine->nextMachine;
			}
			auxOperations = auxOperations->nextOperation;
		}
		SaveAll(h->rightTree, fp); //grava ramos a direita
	}
	
	return true;
}

/**
*	@brief Le arvore guardada em ficheiro binario
*
*	Le cada linha com o codigo do Job, codigo da operacao e cada maquina de forma individual
*
*	@param [in] h			Node da arvore
*	@param [in] fileName	Nome do ficheiro
* 	@return	 Primeiro Node da arvore
*/
Node* GetAll(Node* h, char* fileName) {
	FILE* fp;
	
	if ((fp = fopen(fileName, "rb")) == NULL) 
		return NULL;

	NodeInfo auxFile;
	Job* auxJob = NULL;

	while (fread(&auxFile, sizeof(auxFile), 1, fp)) {
		MachinesList* auxMachinesList = NULL;
		if (!CheckJobExists(h, auxFile.codJob)) { //se o job nao existir, cria um novo
			OperationsList* auxOperationList = NULL;
			Machine* auxMachine = CreateMachine(auxFile.machine.cod, auxFile.machine.time);
			auxMachinesList = InsertMachineInMachinesList(auxMachinesList, auxMachine);
			Operation* auxOperation = CreateOperation(auxFile.codOperation, auxMachinesList);
			auxOperationList = InsertOperationInOperationsList(auxOperationList, auxOperation);
			Job* auxJob = CreateJob(auxFile.codJob, auxOperationList);
			h = AddNode(h, auxJob);
		}else {
			Machine* auxMachine = CreateMachine(auxFile.machine.cod, auxFile.machine.time);
			Job* auxJob = SearchJob(h, auxFile.codJob);
			Operation* auxOperation = SearchOperation(auxJob->operations, auxFile.codOperation);
			if (auxOperation) { //se a opercao existir, adiciona maquina
				auxOperation->machines = InsertMachineInMachinesList(auxOperation->machines, auxMachine);
			}else {				//senao cria operacao
				Machine* auxMachine = CreateMachine(auxFile.machine.cod, auxFile.machine.time);
				auxMachinesList = InsertMachineInMachinesList(auxMachinesList, auxMachine);
				Operation* auxOperation = CreateOperation(auxFile.codOperation, auxMachinesList);
				auxJob->operations = InsertOperationInOperationsList(auxJob->operations, auxOperation);
			}
		}
	}
	fclose(fp);
	return h;
}