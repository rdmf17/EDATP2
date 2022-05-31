#include "./job.h"
#include "./operacoes.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#define MAX 100

ListaJobNode *criarListaJobs()
{
	ListaJobNode *node = NULL;

	node = carregarJobs(node);

	return node;
}

ListaJobNode *carregarJobs(ListaJobNode *raiz)
{
	ListaJobNode *auxList = raiz;
	FILE *fp;
	Job aux;

	char linhaJob[MAX];

	if ((fp = fopen("jobs.txt", "r")) == NULL)
		return NULL;

	while (fgets(linhaJob, MAX, fp) != NULL)
	{
		sscanf(linhaJob, "%d;%s", &aux.id, &aux.nome);
		auxList = criarInserirJob(auxList, aux.id, aux.nome);
	}

	return auxList;
}

Job *criarInserirJob(ListaJobNode *raiz, int idJob, char *nomeJob)
{
	Job *novoJob = criarJob(idJob, nomeJob);
	inserirJobLista(raiz, novoJob);
}

Job *criarJob(int idJob, char *nomeJob)
{
	Job *novoJob = (Job *)malloc(sizeof(Job));
	if (novoJob == NULL)
		return NULL;
	novoJob->id = idJob;
	strcpy(novoJob->nome, nomeJob);
	novoJob->operacao = NULL;

	return novoJob;
}

ListaJobNode *inserirJobLista(ListaJobNode *raiz, Job *job)
{
	if (raiz == NULL)
	{
		raiz = criarNodeJob(job);
	}
	else
	{
		if (raiz->job->id > job->id)
		{
			raiz->leftNode = inserirJobLista(raiz->leftNode, job);
		}
		else
		{
			if (raiz->job->id < job->id)
			{
				raiz->rightNode = inserirJobLista(raiz->rightNode, job);
			}
			else
			{
				printf("Ja existe um job na lista com esse id");
			}
		}
	}

	return raiz;
}

ListaJobNode *criarNodeJob(Job *job)
{
	ListaJobNode *node = (ListaJobNode *)malloc(sizeof(ListaJobNode));
	if (node == NULL)
		return NULL;
	node->job = job;
	node->leftNode = NULL;
	node->rightNode = NULL;
	return node;
}

void apagaJobPorId(ListaJobNode *raiz, int id)
{
	ListaJobNode *aux = procuraJobNaLista(raiz, id);
	if (aux == NULL)
	{
		printf("O job com o id passado n�o existe (id: %d)", id);
		return;
	}
	else
	{
		apagarNodeJob(raiz, id);
		return;
	}
}

ListaJobNode *procuraJobNaLista(ListaJobNode *raiz, int id)
{
	if (raiz == NULL)
		return NULL;
	else
	{
		if (raiz->job->id > id)
		{
			raiz->leftNode = procuraJobNaLista(raiz->leftNode, id);
		}
		else
		{
			if (raiz->job->id < id)
			{
				raiz->rightNode = procuraJobNaLista(raiz->rightNode, id);
			}
			else
			{
				return raiz;
			}
		}
	}
}

ListaJobNode *apagarNodeJob(ListaJobNode *raiz, Job *job)
{
	if (raiz == NULL)
		return NULL;

	if (raiz->job->id > job->id)
	{
		raiz->leftNode = apagarNodeJob(raiz->leftNode, job);
	}
	else
	{
		if (raiz->job->id < job->id)
		{
			raiz->rightNode = apagarNodeJob(raiz->rightNode, job);
		}
		else
		{
			raiz = apagarJobActual(raiz);
		}
	}

	return raiz;
}

ListaJobNode *apagarJobActual(ListaJobNode *raiz)
{
	if (raiz == NULL)
		return NULL;

	if (raiz->leftNode == NULL && raiz->rightNode == NULL)
	{
		return NULL;
	}
	else
	{
		ListaJobNode *aux;
		if (raiz->leftNode == NULL)
		{
			aux = raiz;
			raiz = raiz->rightNode;
			apagarOperacoesLiberataJob(aux);
			free(aux);
		}
		else
		{
			aux = raiz;
			raiz = raiz->leftNode;
			apagarOperacoesLiberataJob(aux);
			free(aux);
		}
	}
}

void apagarOperacoesLiberataJob(ListaJobNode *raiz)
{
	if (raiz == NULL)
		return;
	if (raiz != NULL)
	{
		Job *jobAux;
		jobAux = raiz->job;
		removerOperacoesRecursivo(jobAux);
		free(jobAux);
	}
}

void removerOperacoesRecursivo(Job *job)
{
	Operacao *aux;
	while (job != NULL)
	{
		aux = job;
		job = job->operacao;
		free(aux);
	}
}

void removerOperacao(Job *job, int id)
{
	Operacao *op = procuraOperacao(job, id, 1);
	if (op == NULL)
	{
		printf("A operacao n %d no job %s n�o existe \n ", id, job->nome);
		return;
	}
	Operacao *opAux = procuraOperacao(job, id, 2);

	if (op->proxOperacao != NULL)
	{
		opAux->proxOperacao = op->proxOperacao;
		free(op);
	}
	opAux->proxOperacao = NULL;

	return;
}

void removerOperacaoNaJob(ListaJobNode *raiz, int idJob, int idOperacao)
{
	if (raiz == NULL)
		return;
	ListaJobNode *aux = procuraJobNaLista(raiz, idJob);
	if (aux == NULL)
		return;
	removerOperacao(raiz->job, idOperacao);
}

void editarOperacaoNaJob(ListaJobNode *raiz, int idJob, int idOperacao, int idNovoOperacao)
{
	if (raiz == NULL)
		return;
	ListaJobNode *aux = procuraJobNaLista(raiz, idJob);
	if (aux == NULL)
		return;
	alterarOperacao(raiz->job, idOperacao, idNovoOperacao);
}

void listarArvore(ListaJobNode *raiz)
{
	if (raiz == NULL)
		return;
	printf("Val=%d\n", raiz->job->id);
	listarArvore(raiz->leftNode);
	listarArvore(raiz->rightNode);
}

void ListarJob(Job *job)
{
	Job *aux = job;
	Operacao *auxOp = aux->operacao;
	printf("Trabalho: %s (%d) \n", aux->nome, aux->id);
	if (auxOp != NULL)
	{
		while (auxOp)
		{
			printf("Operacao n %d \n", auxOp->id);
			auxOp = auxOp->proxOperacao;
		}
	}
	printf("\n\n");
}

ListaJobNode *getJobs(ListaJobNode *raiz)
{
	ListaJobNode *aux = raiz;
	FILE *fp;

	if (raiz == NULL)
		return NULL;

	if ((fp = fopen("jobs.dat", "rb")) == NULL)
		return NULL;
	JobFile auxFile;
	while (fread(&auxFile, sizeof(auxFile), 1, fp))
	{
		raiz = criarInserirJob(aux, auxFile.id, auxFile.nome);
	}
	fclose(fp);
	return raiz;
}

bool guardaJobs(ListaJobNode *raiz)
{
	if (raiz == NULL)
		return false;
	FILE *fp;

	if ((fp = fopen("jobs.dat", "wb")) == NULL)
		return false;

	guardarNode(fp, raiz);

	fclose(fp);
	return true;
}

void guardarNode(FILE *fp, ListaJobNode *raiz)
{
	if (raiz == NULL)
		return;
	ListaJobNode *aux = raiz;
	JobFile *auxFile = (JobFile *)malloc(sizeof(JobFile));

	if (raiz->job && raiz->job->id)
	{

		auxFile->id = raiz->job->id;
		strcpy(auxFile->nome, raiz->job->nome);
		fwrite(&auxFile, sizeof(auxFile), 1, fp);
	}

	if (raiz->leftNode != NULL)
		guardarNode(fp, raiz->leftNode);
	if (raiz->rightNode != NULL)
		guardarNode(fp, raiz->rightNode);
}
