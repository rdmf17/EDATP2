#pragma once

#include "./structs.h"

/**
 * @brief
 * Função para iniciar um plano com o número de máquinas que o plano vai ter pelo número de tempos disponiveis.
 * Recebe o inicilizador da variavel de plano.
 * @param p
 */
void iniciaPlano(CelPlano p[][Tempos]);

/**
 * @brief
 * Função para prepar para a criação de uma variável do tipo CelPlano para inserir os dados no plano de trabalhos.
 * Recebe o plano, o id do job, o id da operação, o id da máquina, e o tempo de execução da operação.
 * @param p
 * @param idJob
 * @param idOp
 * @param idMaq
 * @param tempos
 */
void preparaCelPlano(CelPlano p[][Tempos], int idJob, int idOp, int idMaq, int tempos);

/**
 * @brief
 * Função para ocupar o plano de trabalho com os vários jobs e operações
 * @param p
 * @param idMaq
 * @param tempos
 * @param cel
 */
void ocupaPlano(CelPlano p[][Tempos], int idMaq, int tempos, CelPlano *cel);

/**
 * @brief
 * Função para lista um plano de trabalhos.
 * Recebe a variavel de plano.
 * @param p
 */
void listarPlano(CelPlano p[][Tempos]);

/**
 * @brief
 * Função para procurar uma operação em especifico dentro de um job.
 * Recebe a estrutura do job em questão.
 * Recebe o id de operação que é a propriedade sobre a qual a pesquisa vai ser efetuada
 * Recebe tambem um tipo de pesquisa que pode ser: 1 para retornar a operação atual, 2 para retornar a operção anterior à atual.
 * Retorna uma Operaçºao
 * @param job Job *
 * @param id int
 * @param type int
 * @return Operacao*
 */
Operacao *procuraOperacao(Job *job, int id, int type);

/**
 * @brief
 * Função para criar uma operação e a inserir na lista.
 * Recebe o id da operação, a head do job na qual a vamos inserir.
 * Recebe tambem o tipo de inserção que pode ser tipo 1 (inicio da Lista) ou tipo 2 (fim da lista)
 * @param id
 * @param job
 * @param type
 */
void criarOperacao(int id, Job *job, int type);

/**
 * @brief
 * Função para alterar o id de uma operação.
 * Recebe o id atual da operação e o novo id que ela irá ter.
 * @param job
 * @param id
 * @param novoId
 */
void alterarOperacao(Job *job, int id, int novoId);

/**
 * @brief
 * Função para inserir uma operação como a primeira de um job.
 * Recebe o job na qual a operação vai ser inserida e a própria operação
 * @param job Job *
 * @param op Operacao *
 */
void inserirInicioLista(Job *job, Operacao *op);

/**
 * @brief
 * Função para inserir uma operação como a última de um job.
 * Recebe o job na qual a operação vai ser inserida e a própria operação
 * @param job Job *
 * @param op Operacao *
 */
void inserirFimLista(Job *job, Operacao *op);

/**
 * @brief
 * Função para obter o mínimo que uma opereção demora a efetuar.
 * Verifica o tempo que demora a efetuar em cada máquina na qual é possivel fazer.
 * Recebe a operação na qual se pretende saber o tempo.
 * @param op
 * @return int
 */
int ObterMinimoOperacao(Operacao *op);

/**
 * @brief
 * Função para obter o máximo que uma opereção demora a efetuar.
 * Verifica o tempo que demora a efetuar em cada máquina na qual é possivel fazer.
 * Recebe a operação na qual se pretende saber o tempo.
 * @param op
 * @return int
 */
int ObterMaximoOperacao(Operacao *op);

/**
 * @brief
 * Função para obter o médio que uma opereção demora a efetuar.
 * Verifica o tempo que demora a efetuar em cada máquina na qual é possivel fazer.
 * Recebe a operação na qual se pretende saber o tempo.
 * @param op
 * @return int
 */
float ObterMedioOperacao(Operacao *op);

/**
 * @brief
 * Função para carregar uma lista de Operações através de um ficheiro txt.
 * Recebe a head da árvore de jobs e a head da lista de máquinas
 * Retorna a head da árvore de jobs.
 * @param raiz
 * @param raizmq
 * @return ListaJobNode*
 */
ListaJobNode *carregarOperacoes(ListaJobNode *raiz, ListaMaquinas *raizmq, CelPlano p[][Tempos]);

/**
 * @brief
 * Função para criar uma variavel com a estrutura do tipo tempo máquina.
 * Recebe um inteiro com o tempo, um com id de Operacao, um com id de Maquina.
 * Recebe tambem um job e a head da lista de máquinas.
 * @param tempo
 * @param idOp
 * @param idMaq
 * @param job
 * @param listamq
 */
void criarOpTempoMaquina(int tempo, int idOp, int idMaq, Job *job, ListaMaquinas *listamq);

/**
 * @brief
 * Função para inserir uma variável do tipo Tempo Máquina numa Operação.
 * Recebe a Operação onde vai ser inserida e a variavel Tempo Máquina.
 * @param op
 * @param tm
 */
void inserirTempoMaquinaLista(Operacao *op, TempoMaquina *tm);
