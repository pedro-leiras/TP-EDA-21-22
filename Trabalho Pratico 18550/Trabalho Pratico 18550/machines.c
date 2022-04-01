/**
 * @file machines.c
 * @author Pedro Leiras
 * @email a18550@alunos.ipca.pt
 * @date 2022
 * @brief Trabalho pr�tico da UC EDA (vers�o 1)
 * M�todos para manipular as Structs Machine e MachinesList
 *
 * @bug bugs desconhecidos.
*/
#include "header.h"

/**
*	@brief Cria nova Machine.
*
*	Aloca mem�ria necess�ria para armazenar uma Machine em mem�ria
*
*	@param [in] cod		C�digo da Machine
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
* @brief Cria novo nodo para a Lista de M�quinas
* Copia para o nodo da lista a informa��o de uma Machine
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
* @param [in] h				Inicio da Lista de M�quinas
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
* @brief Verifica se uma Machine existe a Lista de M�quinas
* Procura se a Machine est� presente na Lista de M�quinas, atrav�s do c�digo
* @param [in] h		Inicio da Lista do MachinesList
* @param [in] cod	C�digo da Machine a procurar
* @return	true - Machine existe na lista; false - Machine n�o est� presente na lista
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
* @brief Verifica se a Machine existe. Se existir devolve endere�o da Machine!
* @param [in] h		Inicio da Lista do MachinesList
* @param [in] cod	C�digo da Machine a procurar
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
* @brief Soma todos os tempos das m�quinas presentes numa Lista de M�quinas
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
* @brief Conta todas as m�quinas presentes numa Lista de M�quinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Total de m�quinas
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
* @brief Altera os dados de uma m�quina
* @param [in] h				Apontador da Machine
* @param [in] newMacCod		Novo c�digo para a m�quina
* @param [in] newTime		Novo tempo para a m�quina
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
* @brief Determinar a m�quina com menor tempo numa Lista de M�quinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Apontador da c�pia da Machine
*/
Machine* GetMachineWithLowerTime(MachinesList* h) {
	Machine* aux = NULL;
	int auxTime;

	if (h != NULL) {
		auxTime = h->machine.time;									//atribui � aux o tempo da primeira maquina
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
* @brief Determinar a m�quina com maior tempo numa Lista de M�quinas
* @param [in] h		Inicio da Lista do MachinesList
* @return	Apontador da c�pia da Machine
*/
Machine* GetMachineWithHigherTime(MachinesList* h) {
	Machine* aux = NULL;
	int auxTime;

	if (h != NULL) {
		auxTime = h->machine.time;									//atribui � aux o tempo da primeira maquina
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
* @brief Lista todas as m�quinas de uma Lista de M�quinas
* @param [in] h		Inicio da Lista de M�quinas
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