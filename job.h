#pragma once

#include "./structs.h"

/**
 * @brief
 * Função para criar uma lista de jobs.
 * Retorna a head da lista.
 * @return ListaJobNode*
 */
ListaJobNode *criarListaJobs();

/**
 * @brief
 * Função para inserir um job dentro da lista de jobs.
 * Recebe a head da lista de job e o job a ser colocado lá.
 * Retorna o node na qual se encontra.
 * @param raiz
 * @param job
 * @return ListaJobNode*
 */
ListaJobNode *inserirJobLista(ListaJobNode *raiz, Job *job);

/**
 * @brief
 * Função para criar um node de um novo job.
 * Recebe o job a ser colocado no node.
 * Retorna esse node.
 * @param job
 * @return ListaJobNode*
 */
ListaJobNode *criarNodeJob(Job *job);

/**
 * @brief
 * Função para carregar a lista de jobs do ficheiro jobs.txt
 * Recebe a head da lista de jobs
 * Retorna essa lista.
 * @param raiz
 * @return ListaJobNode*
 */
ListaJobNode *carregarJobs(ListaJobNode *raiz);

/**
 * @brief
 * Função para procurar um job especifico dentro da árvore de Jobs
 * Recebe o topo da árvore onde vai ser pesquisado o job.
 * Recebe um id que é a propriedade sobre a qual a pesquisa vai ser efetuada.
 * Devolve por fim o node da árvore na qual o job se encontra
 * @param raiz ListaJobNode *
 * @param id int
 * @return ListaJobNode*
 */
ListaJobNode *procuraJobNaLista(ListaJobNode *raiz, int id);

/**
 * @brief
 * Função para criar e inserir um job dentro da lista de jobs.
 * Recebe um id e o nome a colocar no job.
 * @param raiz
 * @param idJob
 * @param nomeJob
 * @return Job*
 */
Job *criarInserirJob(ListaJobNode *raiz, int idJob, char *nomeJob);

/**
 * @brief
 * Função para criar um job.
 * Recebe o id e o nome a colocar no job.
 * Retorna esse job.
 * @param idJob
 * @param nomeJob
 * @return Job*
 */
Job *criarJob(int idJob, char *nomeJob);

/**
 * @brief
 * Função para apagar e libertar um job da lista.
 * Recebe a head da lista de jobs e o job.
 * Retorna o node na qual se encontra
 * @param raiz
 * @param job
 * @return ListaJobNode*
 */
ListaJobNode *apagarNodeJob(ListaJobNode *raiz, Job *job);

/**
 * @brief
 * Função para apagar um job da lista de jobs.
 * Recebe o node do job a apagar.
 * @param raiz
 * @return ListaJobNode*
 */
ListaJobNode *apagarJobActual(ListaJobNode *raiz);

/**
 * @brief
 * Função para apagar um job através do seu id
 * Recebe a head da lista de jobs e o id do job a apagar.
 * @param raiz
 * @param id
 */
void apagaJobPorId(ListaJobNode *raiz, int id);

/**
 * @brief
 * Função para remover todas as Operações dentro de um node de um job e libertar o job..
 * Recebe a head do node do job.
 * @param raiz
 */
void apagarOperacoesLiberataJob(ListaJobNode *raiz);

/**
 * @brief
 * Função para remover todas as Operações dentro de um job e libertar essas operações
 * Recebe a head do node do job.
 * @param raiz
 */
void removerOperacoesRecursivo(Job *job);

/**
 * @brief
 * Função para remover uma operação através do seu id.
 * Recebe a head do job o id da operação que deseja remover
 * @param job
 * @param id
 */
void removerOperacao(Job *job, int id);

/**
 * @brief
 * Função para remover uma operação dentro de um job.
 * Recebe a head da lista de job, o id do job e da operação na qual a remoção vai ser efetuada.
 * @param raiz ListaJobNode *
 * @param idJob int
 * @param idOperacao int
 */
void removerOperacaoNaJob(ListaJobNode *raiz, int idJob, int idOperacao);

/**
 * @brief
 * Função para editar uma operação dentro de um job.
 * Recebe a head da lista de job, o id do job e da operação na qual a remoção vai ser efetuada.
 * Recebe tambem o novo id a atribuir à operação
 * @param raiz ListaJobNode *
 * @param idJob int
 * @param idOperacao int
 * @param idNovoOperacao int
 */
void editarOperacaoNaJob(ListaJobNode *raiz, int idJob, int idOperacao, int idNovoOperacao);

/**
 * @brief
 * Função para obter o tempo mínimo que um job demora a efetuar.
 * Recebe o job na qual se pretende saber o tempo.
 * @param job Job *
 * @return int
 */
int ObterMinimo(Job *job);

/**
 * @brief
 * Função para obter o tempo máximo que um job demora a efetuar.
 * Recebe o job na qual se pretende saber o tempo.
 * @param job Job *
 * @return int
 */
int ObterMaximo(Job *job);

/**
 * @brief
 * Função para obter o tempo médio que um job demora a efetuar.
 * Recebe o job na qual se pretende saber o tempo.
 * @param job Job *
 * @return int
 */
float ObterMedio(Job *job);

/**
 * @brief
 * Função para listar a árvore de jobs.
 * Recebe a head da árvore
 * @param raiz
 */
void listarArvore(ListaJobNode *raiz);

/**
 * @brief
 * Função para listar um job e as suas operações.
 * Recebe um job.
 * @param job
 */
void ListarJob(Job *job);

/**
 * @brief
 * Função para guardar os estado atual dos jobs num ficheiro binário.
 * Recebe a head da árvore de jobs.
 * @param raiz
 * @return true
 * @return false
 */
bool guardaJobs(ListaJobNode *raiz);

/**
 * @brief
 * Função para guardar cada node do job no ficheiro binário.
 * Recebe a head da árvore de jobs.
 * @param fp
 * @param raiz
 */
void guardarNode(FILE *fp, ListaJobNode *raiz);