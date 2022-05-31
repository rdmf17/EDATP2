#pragma once

#include "./operacoes.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#define MAX 100

ListaJobNode *carregarOperacoes(ListaJobNode *raiz, ListaMaquinas *raizmaq, CelPlano p[][Tempos])
{
	ListaJobNode *auxList = raiz;
	ListaMaquinas *auxMaq = raizmaq;
	ListaJobNode *auxJob = NULL;
	FILE *fp;
	int idOperacao;
	int idJob;
	int tempo;
	int idMaq;

	char linhaJob[MAX];

	if ((fp = fopen("operacoes.txt", "r")) == NULL)
		return NULL;

	while (fgets(linhaJob, MAX, fp) != NULL)
	{
		sscanf(linhaJob, "%d;%d;%d;%d", &idOperacao, &idJob, &tempo, &idMaq);
		auxJob = procuraJobNaLista(auxList, idJob);
		if (auxJob != NULL)
		{
			Operacao *op = procuraOperacao(auxJob, idOperacao, 1);
			if (op == NULL)
			{
				criarOperacao(idOperacao, auxJob, 1);
			}
			inserirOpTempoMaquina(tempo, idOperacao, idMaq, auxJob->job, raizmaq);
			preparaCelPlano(p, auxJob->job->id, idOperacao, idMaq, tempo);
		}
		else
		{
			printf("Este job não existe");
		}
	}
	free(auxMaq);
	free(auxJob);

	return auxList;
}

Operacao *procuraOperacao(Job *job, int id, int type)
{
	if (job == NULL)
		return NULL;
	Operacao *opAux = job->operacao;
	while (opAux != NULL)
	{
		if (type != 1)
		{
			if (type != 2)
			{
				printf("O tipo para obter a operacao nao existe");
				return NULL;
			}
		}
		if (type == 1)
		{
			if (opAux->id == id)
				return opAux;
		}
		else
		{
			if (opAux->proxOperacao->id == id)
				return opAux;
		}
		opAux = opAux->proxOperacao;
	}
	return NULL;
}

void criarOperacao(int id, Job *job, int type)
{
	Operacao *novaOperacao = (Operacao *)malloc(sizeof(Operacao));

	novaOperacao->id = id;
	novaOperacao->proxOperacao = NULL;
	novaOperacao->nextTempMaq = NULL;

	if (type == 1)
		inserirInicioLista(job, novaOperacao);
	else
	{
		if (type == 2)
		{
			inserirFimLista(job, novaOperacao);
		}
		else
		{
			printf("O tipo de inser��o n�o existe");
		}
	}
}

void alterarOperacao(Job *job, int id, int newid)
{
	Operacao *opaux = procuraOperacao(job, newid, 1);
	if (opaux != NULL)
	{
		printf("A operacao n %d h� existe no job %s \n ", newid, job->nome);
		return;
	}
	Operacao *op = procuraOperacao(job, id, 1);
	if (op == NULL)
	{
		printf("A operacao n %d no job %s n�o existe \n ", id, job->nome);
		return;
	}
	op->id = newid;

	return;
}

void inserirInicioLista(Job *job, Operacao *op)
{
	if (job == NULL)
		return;
	if (job->operacao == NULL)
	{
		job->operacao = op;
		return;
	};
	Operacao *aux = job->operacao;
	job->operacao = op;
	op->proxOperacao = aux;
	return;
}

void inserirFimLista(Job *job, Operacao *op)
{
	if (job == NULL)
		return;
	if (job->operacao == NULL)
	{
		job->operacao = op;
		return;
	}
	Operacao *aux = job->operacao;
	while (aux->proxOperacao != NULL)
	{
		aux = aux->proxOperacao;
	}
	if (aux->proxOperacao == NULL)
	{
		aux->proxOperacao = op;
		return;
	}
}

int ObterMinimo(Job *job)
{
	if (job == NULL)
		return -1;
	if (job->operacao == NULL)
		return -1;
	Operacao *auxOp = job->operacao;
	int tempmin = 0;
	while (auxOp != NULL)
	{
		int temp = ObterMinimoOperacao(auxOp);
		if (temp != -1)
		{
			tempmin = tempmin + temp;
		}
		printf("%d\n", temp);
		auxOp = auxOp->proxOperacao;
	}
	return tempmin;
}

int ObterMinimoOperacao(Operacao *op)
{
	if (op == NULL)
		return -1;
	if (op->nextTempMaq == NULL)
		return -1;

	TempoMaquina *tempmaq = op->nextTempMaq;
	TempoMaquina *tempmaqmin = op->nextTempMaq;
	int temp = tempmaq->tempo;
	while (tempmaq->nextTempMaq != NULL)
	{
		printf("%d %d\n\n", tempmaq->tempo, temp);
		if (tempmaq->tempo < temp)
		{
			temp = tempmaq->tempo;
			tempmaqmin = tempmaq->nextTempMaq;
		}
		tempmaq = tempmaq->nextTempMaq;
	}
	return temp;
}

int ObterMaximo(Job *job)
{
	if (job == NULL)
		return -1;
	if (job->operacao == NULL)
		return -1;

	Operacao *auxOp = job->operacao;
	int tempmax = 0;
	while (auxOp != NULL)
	{
		int temp = ObterMaximoOperacao(auxOp);
		if (temp != -1)
		{
			tempmax = tempmax + temp;
		}
		printf("%d\n", temp);
		auxOp = auxOp->proxOperacao;
	}

	return tempmax;
}

int ObterMaximoOperacao(Operacao *op)
{
	if (op == NULL)
		return -1;
	if (op->nextTempMaq == NULL)
		return -1;

	TempoMaquina *tempmaq = op->nextTempMaq;
	TempoMaquina *tempmaqmax = op->nextTempMaq;
	int temp = tempmaq->tempo;
	while (tempmaq->nextTempMaq != NULL)
	{
		if (tempmaq->tempo > temp)
		{
			temp = tempmaq->tempo;
			tempmaqmax = tempmaq->nextTempMaq;
		}
		tempmaq = tempmaq->nextTempMaq;
	}
	return temp;
}

float ObterMedio(Job *job)
{
	if (job == NULL)
		return -1;
	if (job->operacao == NULL)
		return -1;

	Operacao *auxOp = job->operacao;
	float media = 0;
	float tempmedio = 0;
	int mainindex = 0;
	while (auxOp != NULL)
	{
		float temp = ObterMedioOperacao(auxOp);
		if (temp != -1)
		{
			tempmedio = tempmedio + temp;
			mainindex++;
		}
		auxOp = auxOp->proxOperacao;
	}
	media = tempmedio / mainindex;

	return tempmedio;
}

float ObterMedioOperacao(Operacao *op)
{
	if (op == NULL)
		return -1;
	if (op->nextTempMaq == NULL)
		return -1;

	TempoMaquina *tempmedio = op->nextTempMaq;
	int index = 0;
	int tempatual = 0;
	float media = 0;

	while (tempmedio->nextTempMaq != NULL)
	{
		tempatual = tempatual + tempmedio->tempo;
		index++;
		tempmedio = tempmedio->nextTempMaq;
	}
	media = tempatual / index;

	return media;
}

void iniciaPlano(CelPlano p[][Tempos])
{
	for (int l = 0; l < Maqs; l++)
		for (int col = 0; col < Tempos; col++)
		{
			p[l][col].idJob = -1;
			p[l][col].idOper = -1;
		}
}

void preparaCelPlano(CelPlano p[][Tempos], int idJob, int idOp, int idMaq, int tempos)
{
	CelPlano *aux = (CelPlano *)malloc(sizeof(CelPlano));
	aux->idJob = idJob;
	aux->idOper = idOp;

	ocupaPlano(p, idMaq, tempos, aux);
}

void ocupaPlano(CelPlano p[][Tempos], int idMaq, int tempos, CelPlano *cel)
{
	int col = 0;
	while (p[idMaq][col].idJob != -1)
		col++;

	if (col + tempos <= Tempos)
	{
		for (int i = col; i < col + tempos; i++)
		{
			printf("%d;%d;%d", i, cel->idJob, cel->idOper);
			p[idMaq][i].idJob = cel->idJob;
			p[idMaq][i].idOper = cel->idOper;
		}
		return;
	}
	else
	{
		if (idMaq + 1 > Maqs)
		{
			printf("Não existe mais nenhuma máquina para preencher");
			return;
		}
		ocupaPlano(p, idMaq + 1, tempos, cel);
	}
}

void listarPlano(CelPlano p[][Tempos])
{
	int i;
	int j;
	for (i = 0; i < Maqs; i++)
	{
		printf("Maq nº%d:\n", i);
		for (j = 0; j < Tempos; j++)
		{
			printf("	IdJob: %d;  IdOperação: %d", p[i][j].idJob, p[i][j].idOper);
		}
	}
}
