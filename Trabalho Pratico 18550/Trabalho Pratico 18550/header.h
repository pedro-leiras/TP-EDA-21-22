#ifndef HEADER_H
#define HEADER_H 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Machine {
	int cod;
	int time;
}Machine;

typedef struct MachinesList {
	struct Machine machine;
	struct MachinesList* nextMachine;
}MachinesList;

typedef struct Operation {
	int cod;
	struct MachinesList* machines;

}Operation;

typedef struct OperationsList {
	struct Operation operation;
	struct OperationsList* nextOperation;
}OperationsList;

typedef struct Job {
	int cod;
	struct OperationsList* operations;
}Job;

typedef struct ProcessPlan {
	struct Job job;
	struct ProcessPlan* nextJob;
}ProcessPlan;

typedef struct OperationsMath {
	int res;
	struct OperationsList* operations;
}OperationsMath;


Machine* CreateMachine(int cod, int time);
MachinesList* CreateMachineListNode(Machine* m);
MachinesList* InsertMachineInMachinesList(MachinesList* h, Machine* newMachine);
bool CheckMachineExists(MachinesList* h, int cod);
Machine* SearchMachine(MachinesList* h, int cod);
int SumMachineTime(MachinesList* h);
int CountMachines(MachinesList* h);
Machine* ChangeMachineTime(Machine* h, int newTime);
int GetMinMachineTime(MachinesList* h);
int GetMaxMachineTime(MachinesList* h);

Operation* CreateOperation(int cod, MachinesList* m);
OperationsList* CreateOperationListNode(Operation* o);
OperationsList* InsertOperationInOperationsList(OperationsList* h, Operation* newOperation);
bool CheckOperationExists(OperationsList* h, int cod);
Operation* SearchOperation(OperationsList* h, int cod);
float GetAverageOperationTime(ProcessPlan* h, int jobCod, int opCod);
ProcessPlan* ChangeOperationInJob(ProcessPlan* h, int jobCod, int opCod, int macCod, int newTime);
int GetMinTimeToCompleteOperation(Operation h);
int GetMaxTimeToCompleteOperation(Operation h);
int GetMinTimeToCompleteOperations(OperationsList* h);
int GetMaxTimeToCompleteOperations(OperationsList* h);

Job* CreateJob(int cod, OperationsList* o);
ProcessPlan* CreateJobNode(Job* j);
ProcessPlan* InsertJobInProcessPlan(ProcessPlan* h, Job* newJob);
bool CheckJobExists(ProcessPlan* h, int cod);
ProcessPlan* AddNewOperationToJob(ProcessPlan* h, int jobCod, Operation* o);
ProcessPlan* RemoveOperationFromJob(ProcessPlan* h, int jobCod, int opCod);
Job* SearchJob(ProcessPlan* h, int cod);
OperationsMath GetMinTimeToCompleteJob(ProcessPlan* h, int jobCod);
OperationsMath GetMaxTimeToCompleteJob(ProcessPlan* h, int jobCod);


ProcessPlan* ReadProcessPlanFile(char* path, ProcessPlan* p);
#endif