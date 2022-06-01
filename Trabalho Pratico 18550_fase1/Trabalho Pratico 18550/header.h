/**
 * @file header.h
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Definicoes Globais para o Trabalho pratico da UC EDA (versao 1)
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
 * Uma lista de trabalhos contem a estrutura do tipo Job (@@job) e o apontador para o proximo trabalho (@@nextJob).
 */
typedef struct ProcessPlan {
	struct Job job;						/**< toda a informacao do Job */
	struct ProcessPlan* nextJob;		/**< Ligacao o outro Job*/
}ProcessPlan;

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
	float GetAverageOperationTime(ProcessPlan* h, int jobCod, int opCod);
	ProcessPlan* ChangeOperationInJob(ProcessPlan* h, int jobCod, int opCod, int macCod, int newMacCod, int newTime);
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