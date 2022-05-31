#include "./maquinas.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#define MAX 100

ListaMaquinas *lerMaquinas(ListaMaquinas *list)
{
	ListaMaquinas *auxList = list;
	FILE *fp;
	Maquina aux;

	char linhaMaq[MAX];

	if ((fp = fopen("maquinas.txt", "r")) == NULL)
		return NULL;

	while (fgets(linhaMaq, MAX, fp) != NULL)
	{
		sscanf(linhaMaq, "%d;%s", &aux.id, &aux.nome);
		auxList = criarMaquina(auxList, aux.id, aux.nome);
	}

	return auxList;
}

ListaMaquinas *criarListaMaquina(int id)
{
	ListaMaquinas *novaLista = (ListaMaquinas *)malloc(sizeof(ListaMaquinas));
	if (novaLista == NULL)
		return NULL;

	novaLista->id = id;
	novaLista->proximaMaq = NULL;

	return novaLista;
}

ListaMaquinas *criarMaquina(int id, char *nome, ListaMaquinas *lista)
{
	Maquina *novaMaq = (Maquina *)malloc(sizeof(Maquina));
	if (novaMaq == NULL)
		return;

	novaMaq->id = id;
	strcpy(novaMaq->nome, nome);

	novaMaq->proximaMaq = NULL;

	inserirMaquina(lista, novaMaq);

	return lista;
}

Maquina *obterMaquina(ListaMaquinas *listamq, int id)
{
	if (listamq == NULL)
		return NULL;
	Maquina *mqAux = listamq->proximaMaq;
	while (mqAux != NULL)
	{
		if (mqAux->id == id)
			return mqAux;

		mqAux = mqAux->proximaMaq;
	}
	return NULL;
}

void criarOpTempoMaquina(int tempo, int idOp, int idMaq, Job *job, ListaMaquinas *listamq)
{
	Operacao *op = procuraOperacao(job, idOp, 1);
	if (op == NULL)
	{
		printf("Inserir Operacao Tempo Maquina: A operacao com id: %d nao existe \n", idOp);
		return;
	}
	Maquina *mq = obterMaquina(listamq, idMaq);
	if (mq == NULL)
	{
		printf("Inserir Operacao Tempo Maquina: A maquina com id: %d nao existe \n", idMaq);
		return;
	}

	TempoMaquina *novoTemp = (TempoMaquina *)malloc(sizeof(TempoMaquina));
	if (novoTemp == NULL)
	{
		return;
	}
	novoTemp->tempo = tempo;
	novoTemp->maquina = mq;
	novoTemp->nextTempMaq = NULL;

	inserirTempoMaquinaLista(op, novoTemp);
}

void inserirTempoMaquinaLista(Operacao *op, TempoMaquina *tm)
{
	if (op == NULL)
		return;
	if (tm == NULL)
		return;
	if (op->nextTempMaq == NULL)
	{
		op->nextTempMaq = tm;
		return;
	}

	TempoMaquina *aux = op->nextTempMaq;

	while (aux->nextTempMaq != NULL)
	{
		aux = aux->nextTempMaq;
	}

	if (aux->nextTempMaq == NULL)
	{
		aux->nextTempMaq = tm;
		return;
	}
}

void inserirMaquina(ListaMaquinas *list, Maquina *mq)
{
	if (list == NULL)
		return;

	if (list->proximaMaq == NULL)
	{
		list->proximaMaq = mq;
		return;
	}

	Maquina *aux = list->proximaMaq;
	while (aux->proximaMaq != NULL)
	{
		aux = aux->proximaMaq;
	}

	if (aux->proximaMaq == NULL)
	{
		aux->proximaMaq = mq;
		return;
	}
}

bool guardaMaquinas(ListaMaquinas *lista)
{
	FILE *file;

	if (lista == NULL)
		return false;
	if ((file = fopen("maquinas.bin", "wb")) == NULL)
		return false;

	Maquina *aux = lista->proximaMaq;
	MaquinaFile auxMaq;
	while (aux)
	{
		auxMaq.id = aux->id;
		strcpy(auxMaq.nome, aux->nome);
		fwrite(&auxMaq, sizeof(MaquinaFile), 1, file);
		aux = aux->proximaMaq;
	}
	fclose(file);
	return true;
}

void DestroiMaquina(ListaMaquinas *lista)
{
	if (lista != NULL)
	{
		Maquina *aux = lista->proximaMaq;
		while (lista->proximaMaq != NULL)
		{
			aux = lista->proximaMaq;
			lista->proximaMaq = lista->proximaMaq->proximaMaq;
			free(aux);
		}
		if (lista->proximaMaq == NULL)
		{
			free(lista);
			return;
		}
	}
}