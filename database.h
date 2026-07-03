#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PASS_SIZE 16 // Esse e o tamanho maximo que uma senha pode ter (em caracteres)
#define NAME_SIZE 21 // Esse e o tamanho maximo de um nome (de usuario ou de prova)
#define MAXN 2048 // Esse e o tamanho maximo dos vetores

void importarDatabase(); // Essa funcao importa o database, deve ser usada so no inicio da execucao
void sobrescreverDatabase(); // Essa funcao sobrescreve o database com os vetores devidamente alterados, deve ser usada so ao fim das sessoes

// Definicao dos structs que descrevem os dados
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
  char nome[NAME_SIZE];
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

// "Criptografia" (e so um djb2)
unsigned criptografar(const unsigned char *str);

// Funcoes para cadastrar usuarios e provas no banco de dados
void cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]);
void cadastrarAluno(char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma);
void cadastrarProva(char nome[NAME_SIZE], int idProfessor, int ano, char turma);
void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]);

// Funcoes para deletar dados do banco de dados
void deletarProfessor(int id);
void deletarAluno(int id);
void deletarProva(int id);
void deletarAdmin(int id);

// Funcao para zerar todas as notas de uma prova
// Se delete for verdadeiro, procura as notas da prova passada e exclui
// Se delete for facil, coloca uma nota 0 para cada aluno da turma
void zerarNotas(int id, int delete);

void editarNota(int idProva, int idAluno, float nota);

// Conferem se a senha bate para o usuario
int validarProfessor(int id, char senha[PASS_SIZE]);
int validarAluno(int id, char senha[PASS_SIZE]);
int validarAdmin(int id, char senha[PASS_SIZE]);

// Busca usuarios e provas pelo nome
int buscarProfessor(char nome[NAME_SIZE]);
int buscarAluno(char nome[NAME_SIZE]);
int buscarAdmin(char nome[NAME_SIZE]);
int buscarProva(char nome[NAME_SIZE], int ano, char turma);

Professor PROFESSORES[MAXN];
Aluno ALUNOS[MAXN];
Prova PROVAS[MAXN];
Nota NOTAS[MAXN];
Admin ADMINS[MAXN];