#pragma once
#include <stdio.h>
#include <stdlib.h>

#define PASS_SIZE 16
#define NAME_SIZE 20
const int MAXN = 1 << 16;

void importarDatabase();
void sobrescreverDatabase();

typedef struct {
  int id;
  char nome[NAME_SIZE];
  unsigned senha;
  char materia[3];
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

void cadastrarProfessor(char nome[NAME_SIZE], char senha[33], char materia[4]);
void cadastrarAluno(int id, char nome[NAME_SIZE], char senha[33], int ano, char turma, int idPai);
void cadastrarProva(int idProfessor, int ano, char turma);
void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]);

void deletarProfessor(int id);
void deletarAluno(int id);
void deletarProva(int id);
void deletarAdmin(int id);

void editarProfessor(int id, char nome[NAME_SIZE], char senha[33], char materia[4]);
void editarAluno(int id, char nome[NAME_SIZE], char senha[33], int ano, char turma, int idPai);
void editarProva(int id, int idProfessor, int ano, char turma);
void editarNota(int idAluno, int idProva, int nota);
void editarAdmin(int id, int nome[NAME_SIZE], char senha[PASS_SIZE]);

int validarProfessor(int id, char senha[PASS_SIZE]);
int validarAluno(int id, char senha[PASS_SIZE]);
int validarAdmin(int id, char senha[PASS_SIZE]);

int buscarProfessor(char nome[NAME_SIZE]);
int buscarAluno(char nome[NAME_SIZE]);
int buscarAdmin(char nome[NAME_SIZE]);

Professor PROFESSORES[MAXN];
Aluno ALUNOS[MAXN];
Prova PROVAS[MAXN];
Nota NOTAS[MAXN << 2];
Admin ADMINS[MAXN];