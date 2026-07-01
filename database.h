#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PASS_SIZE 16
#define NAME_SIZE 21
#define MAXN 1024

void importarDatabase();
void sobrescreverDatabase();

typedef struct {
  int id;
  char nome[NAME_SIZE];
  unsigned senha;
  char materia[4];
} Professor;

typedef struct {
  int id;
  char nome[NAME_SIZE];
  unsigned senha;
  int ano;
  char turma;
} Aluno;

typedef struct {
  int id;
  int idProfessor;
  int ano;
  char turma;
} Prova;

typedef struct {
  int idProva;
  int idAluno;
  float nota;
} Nota;

typedef struct {
  int id;
  char nome[NAME_SIZE];
  unsigned senha;
} Admin;

unsigned criptografar(const unsigned char *str); // criptografa uma senha

void cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]);
void cadastrarAluno(char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma);
void cadastrarProva(int idProfessor, int ano, char turma);
void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]);

void deletarProfessor(int id);
void deletarAluno(int id);
void deletarProva(int id);
void deletarAdmin(int id);
void zerarNotas(int id, int delete);

int validarProfessor(int id, char senha[PASS_SIZE]);
int validarAluno(int id, char senha[PASS_SIZE]);
int validarAdmin(int id, char senha[PASS_SIZE]);

int buscarProfessor(char nome[NAME_SIZE]);
int buscarAluno(char nome[NAME_SIZE]);
int buscarAdmin(char nome[NAME_SIZE]);
int buscarProfessorPorMateria(char materia[4]);

Professor PROFESSORES[MAXN];
Aluno ALUNOS[MAXN];
Prova PROVAS[MAXN];
Nota NOTAS[MAXN];
Admin ADMINS[MAXN];