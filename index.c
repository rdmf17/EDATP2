#pragma warning(disable : 4996)

#include "./imports.h"

#define TAMANHO 50

int main()
{
	ListaJobNode *jobs = criarListaJobs();
	listarArvore(jobs);

	ListaMaquinas *lista = criarListaMaquina(2);
	lista = lerMaquinas(lista);

	CelPlano plano[Maqs][Tempos];
	iniciaPlano(plano);

	jobs = carregarOperacoes(jobs, lista, plano);

	listarPlano(plano);

	guardaJobs(jobs);
	guardaMaquinas(lista);

	// jobs = criarInserirJob(jobs, 12, "Job12");
	// jobs = criarInserirJob(jobs, 6, "Job6");
	// jobs = criarInserirJob(jobs, 22, "Job22");
	// jobs = criarInserirJob(jobs, 14, "Job14");
	// jobs = criarInserirJob(jobs, 2, "Job2");
	// jobs = criarInserirJob(jobs, 42, "Job42");
	// jobs = criarInserirJob(jobs, 13, "Job13");

	//// Aqui crio a lista de máquinas, introduzindo o id.
	// apagaJobPorId(jobs, 13);

	// jobs = criarInserirJob(jobs, 13, "Job13");

	//// Aqui leio as máquinas guardadas no ficheiro maquinas.bin, crio cada uma e guardo-as na lista.

	// criarMaquina(1, "m1", lista);
	// criarMaquina(2, "m2", lista);
	// criarMaquina(3, "m3", lista);
	// criarMaquina(4, "m4", lista);

	//// Crio aqui um "Job" e guardo-o numa variavel chamada de first
	// Job *first = criarJob(1, "job");

	//// Crio aqui 4 máquinas manualmente e associo-a ao Job.
	// criarOperacao(1, first, 1);
	// criarOperacao(6, first, 2);
	// criarOperacao(2, first, 2);
	// criarOperacao(22, first, 1);

	//// Insiro os tempos que cada operação demora executar em cada máquina.

	// inserirOpTempoMaquina(120, 1, 2, first, lista);
	// inserirOpTempoMaquina(20, 1, 4, first, lista);

	// inserirOpTempoMaquina(120, 22, 2, first, lista);
	// inserirOpTempoMaquina(20, 22, 4, first, lista);

	// inserirOpTempoMaquina(53, 6, 1, first, lista);
	// inserirOpTempoMaquina(180, 6, 4, first, lista);

	// inserirOpTempoMaquina(747, 2, 2, first, lista);
	// inserirOpTempoMaquina(564, 2, 3, first, lista);

	//// Remove operação de acordo com o id
	// removerOperacao(first, 6);
	// removerOperacao(first, 32);

	// alterarOperacao(first, 2, 3);
	// alterarOperacao(first, 2, 3);

	// ListarJob(first);

	// int min = ObterMinimo(first);

	// int max = ObterMaximo(first);

	// int media = ObterMedio(first);

	// DestroiMaquina(lista);

	return (0);
}
