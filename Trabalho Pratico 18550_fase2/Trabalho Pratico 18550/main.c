/**
 * @file main.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 2)
 * @bug bugs desconhecidos.
*/

#include "header.h";

int main() {
	FILE* fp;
	Node* p = InitTree();
	Machine* auxMachine = NULL,* auxMachine2 = NULL;
	MachinesList* auxMachineList = NULL;
	OperationsMath x;
	float y;

	p = GetAll(p, "data.dat");

	p = Balance(p);

	p = RemoveJob(p, 1);

	auxMachine = CreateMachine(1, 3);
	auxMachine2 = CreateMachine(3, 7);
	auxMachineList = InsertMachineInMachinesList(auxMachineList, auxMachine);
	auxMachineList = InsertMachineInMachinesList(auxMachineList, auxMachine2);
	Operation* auxOperation = CreateOperation(5, auxMachineList);
	p = AddNewOperationToJob(p, 4, auxOperation);

	auxMachineList = NULL;
	auxMachine = CreateMachine(6, 3);
	auxMachineList = InsertMachineInMachinesList(auxMachineList, auxMachine);
	auxOperation = CreateOperation(5, auxMachineList);
	p = AddNewOperationToJob(p, 6, auxOperation);

	p = RemoveOperationFromJob(p, 3, 1);
	p = ChangeOperationInJob(p, 8, 3, 3, 5, 10);

	x = GetMinTimeToCompleteJob(p, 6);
	ListOperations(x.operations);
	puts(" ");
	x = GetMaxTimeToCompleteJob(p, 6);
	ListOperations(x.operations);

	y = GetAverageOperationTime(p, 6, 3);

	if ((fp = fopen("data2.dat", "wb")) != NULL) {
		SaveAll(p, fp);
		fclose(fp);
	}
	return 0;
}