#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO 50
#define Maqs 8
#define Tempos 10

typedef struct ListaJobNode
{
    struct Job *job;
    struct ListaJobNode *leftNode;
    struct ListaJobNode *rightNode;
} ListaJobNode;

typedef struct Job
{
    int id;
    char nome[TAMANHO];
    struct Operacao *operacao;
} Job;

typedef struct JobFile
{
    int id;
    char nome[TAMANHO];
} JobFile;

typedef struct ListaMaquinas
{
    int id;
    struct Maquina *proximaMaq;
} ListaMaquinas;

typedef struct Maquina
{
    int id;
    char nome[TAMANHO];
    struct Maquina *proximaMaq;
} Maquina;

typedef struct MaquinaFile
{
    int id;
    char nome[TAMANHO];
} MaquinaFile;

typedef struct TempoMaquina
{
    int tempo;
    struct Maquina *maquina;
    struct TempoMaquina *nextTempMaq;
} TempoMaquina;

typedef struct Operacao
{
    int id;
    struct Operacao *proxOperacao;
    struct TempoMaquina *nextTempMaq;
} Operacao;

typedef struct CelPlano
{
    int idJob;
    int idOper;
} CelPlano;