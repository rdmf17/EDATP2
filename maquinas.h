#pragma once

#include "./structs.h"

/**
 * @brief
 * Função para obter uma máquina através do id.
 * Recebe o id da máquina que queremos procurar.
 * Devolve a máquina em questão.
 * @param lista
 * @param id
 * @return Maquina*
 */
Maquina *obterMaquina(ListaMaquinas *lista, int id);

/**
 * @brief
 * Função para ler máquinas gravadas num ficheiro e criar-las na lista de máquinas.
 * Recebe como parametros a head da lista.
 * Retorna a head da lista após a inserção.
 * @param list
 * @return ListaMaquinas*
 */
ListaMaquinas *lerMaquinas(ListaMaquinas *list);

/**
 * @brief
 * Função para inicializar e criar uma lista de máquinas.
 * Recebe um id.
 * Retorna a lista.
 * @param id
 * @return ListaMaquinas*
 */
ListaMaquinas *criarListaMaquina(int id);

/**
 * @brief
 * Função para criar e inserir uma máquina na lista de máquina
 * Recebe um id e um nome para atribuir á máquina.
 * Recebe também a head da lista onde as vai colocar.
 * Retorna a head da lista.
 * @param id
 * @param nome
 * @param lista
 * @return ListaMaquinas*
 */
ListaMaquinas *criarMaquina(int id, char *nome, ListaMaquinas *lista);

/**
 * @brief
 * Função para inserir uma máquina numa lista.
 * Essa inserção é feita no fim da lista.
 * Recebe a head da lista e a máquina.
 * @param list
 * @param mq
 */
void inserirMaquina(ListaMaquinas *list, Maquina *mq);

/**
 * @brief
 * Função para gravar o estado atual das máquinas no ficheiro binário para ser usado mais tarde.
 * Recebe a head da lista de máquinas.
 * @param lista
 * @return true
 * @return false
 */
bool guardaMaquinas(ListaMaquinas *lista);

/**
 * @brief
 * Função para destruir a lista de máquinas.
 * Recebe a head da lista de máquinas.
 * @param lista
 */
void DestroiMaquina(ListaMaquinas *lista);