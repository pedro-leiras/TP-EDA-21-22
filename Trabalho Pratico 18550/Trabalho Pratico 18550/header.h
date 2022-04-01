/**
 * @file header.h
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Defini��es Globais para o Trabalho pr�tico da UC EDA (vers�o 1)
 *
 *	Structs e Assinaturas de Fun��es
 * @bug bugs desconhecidos.
*/

#ifndef HEADER_H
#define HEADER_H 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura para armazenar uma m�quina
 *
 * Uma m�quina cont�m um c�digo (@@cod) e tempo (@@time).
 */
typedef struct Machine {
	int cod;	/**< C�digo da M�quina*/
	int time;	/**< Tempo para executar a opera��o*/
}Machine;

/**
 * @brief Estrutura para armazenar as m�quinas
 *
 * Uma lista de m�quinas cont�m a estrutura do tipo Machine (@@machine) e o apontador para a pr�xima m�quina (@@nextMachine).
 */
typedef struct MachinesList {
	struct Machine machine;					/**< toda a informa��o da M�quina */
	struct MachinesList* nextMachine;		/**< Liga��o a outra M�quina*/
}MachinesList;

/**
 * @brief Estrutura para armazenar uma opera��o
 *
 * Uma opera��o cont�m um c�digo (@@cod) e uma lista de m�quinas (@@machines).
 */
typedef struct Operation {
	int cod;							/**< C�digo da Opera��o*/
	struct MachinesList* machines;		/**< Todas as M�quinas da Opera��o*/
}Operation;

/**
 * @brief Estrutura para armazenar as opera��es
 *
 * Uma lista de opera��es cont�m a estrutura do tipo Operation (@@operation) e o apontador para a pr�xima opera��o (@@nextOperation).
 */
typedef struct OperationsList {
	struct Operation operation;					/**< toda a informa��o da Opera��o */
	struct OperationsList* nextOperation;		/**< Liga��o a outra Opera��o*/
}OperationsList;

/**
 * @brief Estrutura para armazenar um trabalho
 *
 * Um trabalho cont�m um c�digo (@@cod) e uma lista de opera��es (@@operations).
 */
typedef struct Job {
	int cod;								/**< C�digo do Job*/
	struct OperationsList* operations;		/**< Todas as Opera��es do Job*/
}Job;

/**
 * @brief Estrutura para armazenar os trabalhos
 *
 * Uma lista de trabalhos cont�m a estrutura do tipo Job (@@job) e o apontador para o pr�ximo trabalho (@@nextJob).
 */
typedef struct ProcessPlan {
	struct Job job;						/**< toda a informa��o do Job */
	struct ProcessPlan* nextJob;		/**< Liga��o o outro Job*/
}ProcessPlan;

/**
 * @brief Estrutura utilizada para resultados em calculos com Opera��es
 *
 * Um OperationsMath cont�m o resultado dos calculos (@@res) e o apontador para o lista de opera��es utilizadas para obter o resultado (@@operations).
 */
typedef struct OperationsMath {
	int res;								/**< resultado dos c�lculos */
	struct OperationsList* operations;		/**< Todas as Opera��es utilizadas para obter o resultado*/
}OperationsMath;


//Assinaturas de fun��es
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