/**
 * @file machines.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pratico da UC EDA (versao 1)
 * Metodos para manipular as Structs Machine e MachinesList
 *
 * @bug bugs desconhecidos.
*/
#include "header.h"

/**
*	@brief Cria nova Machine.
*
*	Aloca memoria necessaria para armazenar uma Machine em memoria
*
*	@param [in] cod		Codigo da Machine
*	@param [in] time	Tempo para realizar tarefa
*
*/
Machine* CreateMachine(int cod, int time) {
	Machine* aux = (Machine*)calloc(1, sizeof(Machine));
	if (aux == NULL) {
		return NULL;
	}

	aux->cod = cod;
	aux->time = time;

	return aux;
}

/**
* @brief Cria novo nodo para a Lista de Maquinas
* Copia para o nodo da lista a informacao de uma Machine
* @param [in] m		Nova Machine
* @return	Apontador para nodo criado
*/
MachinesList* CreateMachineListNode(Machine* m) {
	MachinesList* newNode = (MachinesList*)calloc(1, sizeof(MachinesList));
	if (newNode == NULL) {
		return NULL;
	}

	newNode->machine.cod = m->cod;
	newNode->machine.time = m->time;
	newNode->nextMachine = NULL;

	return newNode;
}

/**
* @brief Insere uma nova Machine na lista
* @param [in] h				Inicio da Lista de Maquinas
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
* @brief Verifica se uma Machine existe a Lista de Maquinas
* Procura se a Machine esta presente na Lista de Maquinas, atraves do codigo
* @param [in] h		Inicio da Lista do MachinesList
* @param [in] cod	Codigo da Machine a procurar
* @return	true - Machine existe na lista; false - Machine nao esta presente na lista
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
* @brief Verifica se a Machine existe. Se existir devolve endereco da Machine!
* @param [in] h		Inicio da Lista do MachinesList
* @param [in] cod	Codigo da Machine a procurar
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
* @brief Soma todos os tempos das maquinas presentes numa Lista de Maquinas
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
* @brief Conta todas as maquinas presentes numa Lista de Maquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Total de maquinas
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
* @brief Altera os dados de uma maquina
* @param [in] h				Apontador da Machine
* @param [in] newMacCod		Novo codigo para a maquina
* @param [in] newTime		Novo tempo para a maquina
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
* @brief Determinar a maquina com menor tempo numa Lista de Maquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Apontador da copia da Machine
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
* @brief Determinar a maquina com maior tempo numa Lista de Maquinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Apontador da copia da Machine
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
* @brief Lista todas as maquinas de uma Lista de Maquinas
* @param [in] h		Inicio da Lista de Maquinas
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