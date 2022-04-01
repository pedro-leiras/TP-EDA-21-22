/**
 * @file header.h
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Definições Globais para o Trabalho prático da UC EDA (versão 1)
 *
 *	Structs e Assinaturas de Funções
 * @bug bugs desconhecidos.
*/

#ifndef HEADER_H
#define HEADER_H 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura para armazenar uma máquina
 *
 * Uma máquina contém um código (@@cod) e tempo (@@time).
 */
typedef struct Machine {
	int cod;	/**< Código da Máquina*/
	int time;	/**< Tempo para executar a operação*/
}Machine;

/**
 * @brief Estrutura para armazenar as máquinas
 *
 * Uma lista de máquinas contém a estrutura do tipo Machine (@@machine) e o apontador para a próxima máquina (@@nextMachine).
 */
typedef struct MachinesList {
	struct Machine machine;					/**< toda a informação da Máquina */
	struct MachinesList* nextMachine;		/**< Ligação a outra Máquina*/
}MachinesList;

/**
 * @brief Estrutura para armazenar uma operação
 *
 * Uma operação contém um código (@@cod) e uma lista de máquinas (@@machines).
 */
typedef struct Operation {
	int cod;							/**< Código da Operação*/
	struct MachinesList* machines;		/**< Todas as Máquinas da Operação*/
}Operation;

/**
 * @brief Estrutura para armazenar as operações
 *
 * Uma lista de operações contém a estrutura do tipo Operation (@@operation) e o apontador para a próxima operação (@@nextOperation).
 */
typedef struct OperationsList {
	struct Operation operation;					/**< toda a informação da Operação */
	struct OperationsList* nextOperation;		/**< Ligação a outra Operação*/
}OperationsList;

/**
 * @brief Estrutura para armazenar um trabalho
 *
 * Um trabalho contém um código (@@cod) e uma lista de operações (@@operations).
 */
typedef struct Job {
	int cod;								/**< Código do Job*/
	struct OperationsList* operations;		/**< Todas as Operações do Job*/
}Job;

/**
 * @brief Estrutura para armazenar os trabalhos
 *
 * Uma lista de trabalhos contém a estrutura do tipo Job (@@job) e o apontador para o próximo trabalho (@@nextJob).
 */
typedef struct ProcessPlan {
	struct Job job;						/**< toda a informação do Job */
	struct ProcessPlan* nextJob;		/**< Ligação o outro Job*/
}ProcessPlan;

/**
 * @brief Estrutura utilizada para resultados em calculos com Operações
 *
 * Um OperationsMath contém o resultado dos calculos (@@res) e o apontador para o lista de operações utilizadas para obter o resultado (@@operations).
 */
typedef struct OperationsMath {
	int res;								/**< resultado dos cálculos */
	struct OperationsList* operations;		/**< Todas as Operações utilizadas para obter o resultado*/
}OperationsMath;


//Assinaturas de funções
#pragma region Machine Functions
	Machine* CreateMachine(int cod, int time);
	MachinesList* CreateMachineListNode(Machine* m);
	MachinesList* InsertMachineInMachinesList(MachinesList* h, Machine* newMachine);
	bool CheckMachineExists(MachinesList* h, int cod);
	Machine* SearchMachine(MachinesList* h, int cod);
	int SumMachineTime(MachinesList* h);
	int CountMachines(MachinesList* h);
	Machine* ChangeMachineTime(Machine* h, int newTime);
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
	float GetAverageOperationTime(ProcessPlan* h, int jobCod, int opCod);
	ProcessPlan* ChangeOperationInJob(ProcessPlan* h, int jobCod, int opCod, int macCod, int newTime);
	OperationsMath GetMinTimeToCompleteOperations(OperationsList* h);
	OperationsMath GetMaxTimeToCompleteOperations(OperationsList* h);
	void ListOperations(OperationsList* h);
#pragma endregion

#pragma region Job Functions
	Job* CreateJob(int cod, OperationsList* o);
	ProcessPlan* CreateProcessPlanNode(Job* j);
	ProcessPlan* InsertJobInProcessPlan(ProcessPlan* h, Job* newJob);
	bool CheckJobExists(ProcessPlan* h, int cod);
	ProcessPlan* AddNewOperationToJob(ProcessPlan* h, int jobCod, Operation* o);
	ProcessPlan* RemoveOperationFromJob(ProcessPlan* h, int jobCod, int opCod);
	Job* SearchJob(ProcessPlan* h, int cod);
	OperationsMath GetMinTimeToCompleteJob(ProcessPlan* h, int jobCod);
	OperationsMath GetMaxTimeToCompleteJob(ProcessPlan* h, int jobCod);
#pragma endregion

ProcessPlan* ReadProcessPlanFile(char* path, ProcessPlan* p);
#endif