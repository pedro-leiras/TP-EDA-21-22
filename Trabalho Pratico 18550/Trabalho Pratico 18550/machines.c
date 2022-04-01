/**
 * @file machines.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho prático da UC EDA (versão 1)
 * Métodos para manipular as Structs Machine e MachinesList
 *
 * @bug bugs desconhecidos.
*/
#include "header.h"

/**
*	@brief Cria nova Machine.
*
*	Aloca memória necessária para armazenar uma Machine em memória
*
*	@param [in] cod		Código da Machine
*	@param [in] time	Tempo para realizar tarefa
*
*/
Machine* CreateMachine(int cod, int time) {
	Machine* aux = (Machine*)calloc(1, sizeof(Machine));
	aux->cod = cod;
	aux->time = time;

	return aux;
}

/**
* @brief Cria novo nodo para a Lista de Máquinas
* Copia para o nodo da lista a informação de uma Machine
* @param [in] m		Nova Machine
* @return	Apontador para nodo criado
*/
MachinesList* CreateMachineListNode(Machine* m) {
	MachinesList* newNode = (MachinesList*)calloc(1, sizeof(MachinesList));
	newNode->machine.cod = m->cod;
	newNode->machine.time = m->time;
	newNode->nextMachine = NULL;

	return newNode;
}

/**
* @brief Insere uma nova Machine na lista
* @param [in] h				Inicio da Lista de Máquinas
* @param [in] newOperation	Apontador da Machine a adicionar
*/
MachinesList* InsertMachineInMachinesList(MachinesList* h, Machine* newMachine) {
	if (newMachine == NULL) {
		return h;
	}

	MachinesList* aux = CreateMachineListNode(newMachine);

	if (CheckMachineExists(h, aux->machine.cod)) {
		return h;
	}

	if (h == NULL) {
		h = aux;
	}else {
		MachinesList* tmp = h;
		while (tmp->nextMachine != NULL) {
			tmp = tmp->nextMachine;
		}
		tmp->nextMachine = aux;
	}

	return h;
}

/**
* @brief Verifica se uma Machine existe a Lista de Máquinas
* Procura se a Machine está presente na Lista de Máquinas, através do código
* @param [in] h		Inicio da Lista do MachinesList
* @param [in] cod	Código da Machine a procurar
* @return	true - Machine existe na lista; false - Machine não está presente na lista
*/
bool CheckMachineExists(MachinesList* h, int cod) {
	if (h != NULL) {
		MachinesList* aux = h;
		while (aux != NULL) {
			if (aux->machine.cod == cod) {
				return true;
			}
			aux = aux->nextMachine;
		}
	}

	return false;
}

/**
* @brief Verifica se a Machine existe. Se existir devolve endereço da Machine!
* @param [in] h		Inicio da Lista do MachinesList
* @param [in] cod	Código da Machine a procurar
* @return	Apontador para a Machine encontrada
*/
Machine* SearchMachine(MachinesList* h, int cod) {
	if (h != NULL) {
		MachinesList* aux = h;
		while (aux != NULL) {
			if (aux->machine.cod == cod) {
				return (aux);
			}
			aux = aux->nextMachine;
		}
	}

	return NULL;
}

/**
* @brief Soma todos os tempos das máquinas presentes numa Lista de Máquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Total da soma
*/
int SumMachineTime(MachinesList* h) {
	int sum = 0;
	while (h != NULL) {
		sum += h->machine.time;
		h = h->nextMachine;
	}

	return sum;
}

/**
* @brief Conta todas as máquinas presentes numa Lista de Máquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Total de máquinas
*/
int CountMachines(MachinesList* h) {
	int count = 0;
	while (h != NULL) {
		count++;
		h = h->nextMachine;
	}

	return count;
}

/**
* @brief Altera os dados de uma máquina
* @param [in] h				Apontador da Machine
* @param [in] newMacCod		Novo código para a máquina
* @param [in] newTime		Novo tempo para a máquina
* @return	Apontador da Machine
*/
Machine* ChangeMachine(Machine* h, int newMacCod, int newTime) {
	if (h != NULL) {
		h->cod = newMacCod;
		h->time = newTime;
	}
	return h;
}

/**
* @brief Determinar a máquina com menor tempo numa Lista de Máquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Apontador da cópia da Machine
*/
Machine* GetMachineWithLowerTime(MachinesList* h) {
	Machine* aux = NULL;
	int auxTime;

	if (h != NULL) {
		auxTime = h->machine.time;									//atribui à aux o tempo da primeira maquina
		aux = CreateMachine(h->machine.cod, auxTime);
		while (h != NULL) {											//percorrer todas as maquinas da operacao
			if (h->machine.time < auxTime) {						//comparar se o tempo da maquina e menor ao da aux
				auxTime = h->machine.time;
				aux = CreateMachine(h->machine.cod, auxTime);		
			}
			h = h->nextMachine;
		}
	}

	return aux;
}

/**
* @brief Determinar a máquina com maior tempo numa Lista de Máquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Apontador da cópia da Machine
*/
Machine* GetMachineWithHigherTime(MachinesList* h) {
	Machine* aux = NULL;
	int auxTime;

	if (h != NULL) {
		auxTime = h->machine.time;									//atribui à aux o tempo da primeira maquina
		aux = CreateMachine(h->machine.cod, auxTime);
		while (h != NULL) {											//percorrer todas as maquinas da operacao
			if (h->machine.time > auxTime) {						//comparar se o tempo da maquina e maior ao da aux
				auxTime = h->machine.time;
				aux = CreateMachine(h->machine.cod, auxTime);
			}
			h = h->nextMachine;
		}
	}

	return aux;
}

/**
* @brief Lista todas as máquinas de uma Lista de Máquinas
* @param [in] h		Inicio da Lista de Máquinas
*/
void ListMachines(MachinesList* h) {
	if (h != NULL) {
		printf("- Codigo Maquina: %d | Tempo: %d\n", h->machine.cod, h->machine.time);
		while (h->nextMachine != NULL) {
			h = h->nextMachine;
			printf("- Codigo Maquina: %d | Tempo: %d\n", h->machine.cod, h->machine.time);	
		};
	}
}