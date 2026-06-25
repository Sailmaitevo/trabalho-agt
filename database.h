#pragma once
#include <stdio.h>
#include <stdlib.h>

#define PASS_SIZE 16
#define NAME_SIZE 20
const unsigned MAXN = 1 << 16;

void importarDatabase();
void sobrescreverDatabase();

typedef struct {
  unsigned id;
  char nome[NAME_SIZE];
  unsigned long senha;
  char materia[3];
} Professor;

typedef struct {
  unsigned id;
  char nome[NAME_SIZE];
  unsigned long senha;
  int ano;
  int turma;
  unsigned idPai;
} Aluno;

typedef struct {
  unsigned id;
  unsigned idProfessor;
  int ano;
  int turma;
} Prova;

typedef struct {
  unsigned idProva;
  unsigned idAluno;
  float nota;
} Nota;

typedef struct {
  int id;
  char nome[NAME_SIZE];
  unsigned long senha;
} Pai;

typedef struct {
  int id;
  char nome[NAME_SIZE];
  unsigned long senha;
} Admin;

unsigned long criptografar(const unsigned char *str); // criptografa uma senha

void cadastrarProfessor(char nome[NAME_SIZE], char senha[33], char materia[4]);
void cadastrarAluno(int id, char nome[NAME_SIZE], char senha[33], int ano, int turma, int idPai);
void cadastrarProva(int idProfessor, int ano, int turma);
void cadastrarPai(char nome[NAME_SIZE], char senha[PASS_SIZE]);
void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]);

void deletarProfessor(int id);
void deletarAluno(int id);
void deletarProva(int id);
void deletarPai(int id);
void deletarAdmin(int id);

void editarProfessor(int id, char nome[NAME_SIZE], char senha[33], char materia[4]);
void editarAluno(int id, char nome[NAME_SIZE], char senha[33], int ano, int turma, int idPai);
void editarProva(int id, int idProfessor, int ano, int turma);
void editarNota(int idAluno, int idProva, int nota);
void editarPai(int id, char nome[NAME_SIZE], char senha[PASS_SIZE]);
void editarAdmin(int id, int nome[NAME_SIZE], char senha[PASS_SIZE]);

int validarProfessor(int id, char senha[PASS_SIZE]);
int validarAluno(int id, char senha[PASS_SIZE]);
int validarPai(int id, char senha[PASS_SIZE]);
int validarAdmin(int id, char senha[PASS_SIZE]);

int buscarProfessor(char nome[NAME_SIZE]);
int buscarAluno(char nome[NAME_SIZE]);
int buscarPai(char nome[NAME_SIZE]);
int buscarAdmin(char nome[NAME_SIZE]);

Professor PROFESSORES[MAXN];
Aluno ALUNOS[MAXN];
Prova PROVAS[MAXN];
Nota NOTAS[MAXN << 2];
Pai PAIS[MAXN];
Admin ADMINS[MAXN];