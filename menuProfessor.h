#pragma once
#include "menu.h"

void professorListarTurmas(int id); // Listar as turmas e medias das turmas do professor
void professorListarNotas(int id, int ano, char turma); // Listar as notas dos alunos de uma unica turma
void professorConsultarNotas(int id, int idAluno); // Listar as notas de um unico aluno com um professor

void professorCriarProva(); // Cadastra uma prova
void professorEditarNotas(); // Edita as notas de uma prova

int preencherTurma(int ano, char turma, Aluno *alunos); // Preenche um vetor de alunos com todos os alunos de uma mesma turma
int professorPreencherProvas(int id, int ano, char turma, Prova *provas); // Preenche um vetor de provas com todas as provas aplicadas para uma turma

void mostrarMenuProfessor();