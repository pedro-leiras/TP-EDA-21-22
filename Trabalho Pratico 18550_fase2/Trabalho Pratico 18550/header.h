/**
 * @file header.h
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Definicoes Globais para o Trabalho pratico da UC EDA (versao 2)
 *
 *	Structs e Assinaturas de Funcoes
 * @bug bugs desconhecidos.
*/

#ifndef HEADER_H
#define HEADER_H 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura para armazenar uma maquina
 *
 * Uma maquina contem um codigo (@@cod) e tempo (@@time).
 */
typedef struct Machine {
	int cod;	/**< Codigo da Maquina*/
	int time;	/**< Tempo para executar a operacao*/
}Machine;

/**
 * @brief Estrutura para armazenar as maquinas
 *
 * Uma lista de maquinas contem a estrutura do tipo Machine (@@machine) e o apontador para a proxima maquina (@@nextMachine).
 */
typedef struct MachinesList {
	struct Machine machine;					/**< toda a informacao da Maquina */
	struct MachinesList* nextMachine;		/**< Ligacao a outra Maquina*/
}MachinesList;

/**
 * @brief Estrutura para armazenar uma operacao
 *
 * Uma operacao contem um codigo (@@cod) e uma lista de maquinas (@@machines).
 */
typedef struct Operation {
	int cod;							/**< Codigo da Operacao*/
	struct MachinesList* machines;		/**< Todas as Maquinas da Operacao*/
}Operation;

/**
 * @brief Estrutura para armazenar as operacoes
 *
 * Uma lista de operacoes contem a estrutura do tipo Operation (@@operation) e o apontador para a proxima operacao (@@nextOperation).
 */
typedef struct OperationsList {
	struct Operation operation;					/**< toda a informacao da Operacao */
	struct OperationsList* nextOperation;		/**< Ligacao a outra Operacao*/
}OperationsList;

/**
 * @brief Estrutura para armazenar um trabalho
 *
 * Um trabalho contem um codigo (@@cod) e uma lista de operacoes (@@operations).
 */
typedef struct Job {
	int cod;								/**< Codigo do Job*/
	struct OperationsList* operations;		/**< Todas as Operacoes do Job*/
}Job;

/**
 * @brief Estrutura para armazenar os trabalhos
 *
 * Uma arvore de trabalhos contem a estrutura do tipo Job (@@job), o apontador para o ramo a esquerda (@@leftTree) e o apontador para o ramo a direitoa (@@rightTree).
 */
typedef struct Node {
	Job job;					/**< toda a informacao do Job */
	struct Node* leftTree;		/**< Ligacao o Job a esquerda*/
	struct Node* rightTree;		/**< Ligacao o Job a direita*/
}Node, * PtrNode;

/**
 * @brief Estrutura para guardar a arvore num ficheiro binario
 *
 * Uma estrutura que contem o codigo do Job (@@codJob), o codigo da operacao (@@codOperation) e a estrutura da maquina (@@machine).
 */
typedef struct NodeInfo {
	int codJob;
	int codOperation;
	Machine machine;
}NodeInfo;

/**
 * @brief Estrutura utilizada para resultados em calculos com Operacoes
 *
 * Um OperationsMath contem o resultado dos calculos (@@res) e o apontador para o lista de operacoes utilizadas para obter o resultado (@@operations).
 */
typedef struct OperationsMath {
	int res;								/**< resultado dos calculos */
	struct OperationsList* operations;		/**< Todas as Operacoes utilizadas para obter o resultado*/
}OperationsMath;

//Assinaturas de funcoes
#pragma region Machine Functions
	Machine* CreateMachine(int cod, int time);
	MachinesList* CreateMachineListNode(Machine* m);
	MachinesList* InsertMachineInMachinesList(MachinesList* h, Machine* newMachine);
	bool CheckMachineExists(MachinesList* h, int cod);
	Machine* SearchMachine(MachinesList* h, int cod);
	int SumMachineTime(MachinesList* h);
	int CountMachines(MachinesList* h);
	Machine* ChangeMachine(Machine* h, int newMacCod, int newTime);
	Machine* GetMachineWithLowerTime(MachinesList* h);
	Machine* GetMachineWithHigherTime(MachinesList* h);
	void ListMachines(MachinesList* h);
#pragma endregion

#pragma region Operation Functions
	Operation* CreateOperation(int cod, MachinesList* m);
	OperationsList* CreateOperationListNode(Operation* o);
	OperationsList* InsertOperationInOperationsList(OperationsList* h, Operation* newOperation);
	bool CheckOperationExists(OperationsList* h, int cod);
	Operation* SearchOperation(OperationsList* h, int cod);
	float GetAverageOperationTime(Node* h, int jobCod, int opCod);
	Node* ChangeOperationInJob(Node* h, int jobCod, int opCod, int macCod, int newMacCod, int newTime);
	OperationsMath GetMinTimeToCompleteOperations(OperationsList* h);
	OperationsMath GetMaxTimeToCompleteOperations(OperationsList* h);
	void ListOperations(OperationsList* h);
#pragma endregion

#pragma region Job Functions
	Job* CreateJob(int cod, OperationsList* o);
	bool CheckJobExists(Node* h, int cod);
	Node* AddNewOperationToJob(Node* h, int jobCod, Operation* o);
	Node* RemoveOperationFromJob(Node* h, int jobCod, int opCod);
	Job* SearchJob(Node* h, int cod);
	OperationsMath GetMinTimeToCompleteJob(Node* h, int jobCod);
	OperationsMath GetMaxTimeToCompleteJob(Node* h, int jobCod);
#pragma endregion

#pragma region ProcessPlan Functions
	PtrNode InitTree();
	Node* NewNode(Job* j);
	Node* AddNode(Node* root, Job* j);
	int TreeSize(PtrNode r);
	PtrNode FindMin(PtrNode root);
	void DestroyNode(Node** p);
	PtrNode DeleteCurrentNode(PtrNode root);
	PtrNode RemoveJob(PtrNode root, int jobCod);
	PtrNode Balance(PtrNode root);
	PtrNode BSTBalance(PtrNode root, Node* list, int ini, int end);
	void BST2List(PtrNode root, unsigned int* count, Node* list);
#pragma endregion

#pragma region Files Functions
	bool SaveAll(Node* h, FILE* fp);
	Node* GetAll(Node* h, char* fileName);
#pragma endregion
#endif