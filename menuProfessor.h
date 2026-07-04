#pragma once
#include "menu.h"

void professorListarTurmas(int id); // Listar as turmas e medias das turmas do professor
int professorListarNotas(int id, int ano, char turma); // Listar as notas dos alunos de uma unica turma, retorna 1 se deu certo e 0 se nao achou alunos
void professorConsultarNotas(int id, int idAluno); // Listar as notas de um unico aluno com um professor

void professorCriarProva(int id); // Cadastra uma prova
void professorEditarNotas(int id, int unico); // Edita as notas de uma prova
void professorListarProvas(int id); // Lista as provas que o professor registrou
void professorIncrementarFaltas(int id); // Incrementa as faltas de um aluno
void professorDeletarProva(int id); // Deleta uma prova

void mostrarMenuProfessor();