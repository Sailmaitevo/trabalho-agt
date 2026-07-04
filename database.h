#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PASS_SIZE 16 // Esse e o tamanho maximo que uma senha pode ter (em caracteres)
#define NAME_SIZE 21 // Esse e o tamanho maximo de um nome (de usuario ou de prova)
#define MAXN 2048 // Esse e o tamanho maximo dos vetores
#define TIPO_ADMIN 1
#define TIPO_PROF 2
#define TIPO_ALUNO 3
#define TURMA_SIZE 40
#define MATERIA_SIZE 4

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

typedef struct {
	int idProfessor;
	int idAluno;
	int numero;
} Faltas;

// "Criptografia" (e so um djb2)
unsigned criptografar(const unsigned char *str);

// Funcoes para cadastrar usuarios e provas no banco de dados, retorna o id
int cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]);
int cadastrarAluno(char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma);
int cadastrarProva(char nome[NAME_SIZE], int idProfessor, int ano, char turma);
int cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]);

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

// Funcao para incrementar (ou decrementar) o numero de faltas de um aluno
void incrementarFaltas(int idProfessor, int idAluno, int incremento);

// Conferem se a senha bate para o usuario
int validarSenha(int id, int tipo, char senha[PASS_SIZE]);

// Busca usuarios e provas pelo nome
int buscarProfessor(char nome[NAME_SIZE], int capializacaoImporta);
int buscarAluno(char nome[NAME_SIZE], int capializacaoImporta);
int buscarAdmin(char nome[NAME_SIZE], int capializacaoImporta);
int buscarProva(char nome[NAME_SIZE], int ano, char turma);
int compararNomes(char nome1[NAME_SIZE], char nome2[NAME_SIZE], int capializacaoImporta);
char fazerMinusculo(char c);
char fazerMaiusculo(char c);
char ehLetra(char c);
void acharNome(int id, int tipo, char nome[NAME_SIZE]);
int acharIdTipo(int *id, int *tipo, char nome[NAME_SIZE]);

int alunoPreencherNotas(int id, int idProfessor, Nota *notas);
int alunoPreencherFaltas(int id, Faltas *faltas);
float alunoMedia(int id, int idProfessor);
float alunoNota(int idProva, int idAluno);
int alunoFaltas(int idProfessor, int idAluno);

int preencherTurma(int ano, char turma, Aluno alunos[TURMA_SIZE]); // Preenche um vetor de alunos com todos os alunos de uma mesma turma
int preencherProvas(int id, int ano, char turma, Prova *provas); // Preenche um vetor de provas com todas as provas aplicadas para uma turma

extern Professor PROFESSORES[MAXN];
extern Aluno ALUNOS[MAXN];
extern Prova PROVAS[MAXN];
extern Nota NOTAS[MAXN];
extern Admin ADMINS[MAXN];
extern Faltas FALTAS[MAXN];