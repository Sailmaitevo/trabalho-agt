#pragma once
#include "menu.h"

void professorListarTurmas(int id); // Listar as turmas e medias das turmas do professor
int professorListarNotas(int id, int ano, char turma); // Listar as notas dos alunos de uma unica turma, retorna 1 se deu certo e 0 se nao achou alunos
void professorConsultarNotas(int id, int idAluno); // Listar as notas de um unico aluno com um professor

void professorCriarProva(int id); // Cadastra uma prova
void professorEditarNotas(int id, int unico); // Edita as notas de uma prova
void professorListarProvas(int id); // Lista as provas que o professor registrou

void professorDeletarProva(int id);

int preencherTurma(int ano, char turma, Aluno *alunos); // Preenche um vetor de alunos com todos os alunos de uma mesma turma
int professorPreencherProvas(int id, int ano, char turma, Prova *provas); // Preenche um vetor de provas com todas as provas aplicadas para uma turma

void mostrarMenuProfessor();