#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PASS_SIZE 16 // O tamanho máximo de uma senha (em caracteres)
#define NAME_SIZE 21 // O tamanho máximo de um nome (de usuario ou de prova)
#define MATERIA_SIZE 4 // O tamanho máximo do nome da materia (contando o NULL)
#define TURMA_SIZE 40 // O tamanho máximo de uma turma
#define MAXN 2048 // O tamanho máximo dos vetores de dados

#define TIPO_ADMIN 1 // O nível de permissão de um admin
#define TIPO_PROF 2 // O nível de permissão de um professor
#define TIPO_ALUNO 3 // O nível de permissão de um aluno

#define AULAS_NUM 72 // O número de aulas de cada matéria
#define MEDIA_MIN 7 // A média mínima para passar direto
#define EXAME_MIN 5 // O mínimo necessário para passar em exame
#define PESO_EXAME 4 // O peso da nota do exame
#define PESO_MEDIA 6 // O peso da média original

void importarDatabase(); // Essa função importa o database, deve ser usada só no inicio da execução
void sobrescreverDatabase(); // Essa função sobrescreve o database com os vetores devidamente alterados e encerra a execução

// Definição dos structs que descrevem os dados
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

// Funções para cadastrar usuários e provas no banco de dados, retorna o id
int cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]);
int cadastrarAluno(char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, char turma);
int cadastrarProva(char nome[NAME_SIZE], int idProfessor, int ano, char turma);
int cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]);

// Funções para deletar dados do banco de dados
void deletarProfessor(int id);
void deletarAluno(int id);
void deletarProva(int id);
void deletarAdmin(int id);

// Função para zerar todas as notas de uma prova
// Se delete for verdadeiro, procura as notas da prova passada e exclui
// Se delete for falso, coloca uma nota 0 para cada aluno da turma
void zerarNotas(int id, int delete);
void editarNota(int idProva, int idAluno, float nota);

// Função para incrementar (ou decrementar) o número de faltas de um aluno
void incrementarFaltas(int idProfessor, int idAluno, int incremento);

// Confere se a senha bate para o usuário
int validarSenha(int id, int tipo, char senha[PASS_SIZE]);

// Buscam usuarios e provas pelo nome
int buscarProfessor(char nome[NAME_SIZE], int capializacaoImporta);
int buscarAluno(char nome[NAME_SIZE], int capializacaoImporta);
int buscarAdmin(char nome[NAME_SIZE], int capializacaoImporta);
int buscarProva(char nome[NAME_SIZE], int ano, char turma, int idProfessor);

int compararNomes(char nome1[NAME_SIZE], char nome2[NAME_SIZE], int capializacaoImporta); // Compara dois nomes considerando (ou não) a capitalização
char fazerMinusculo(char c); // Deixa um caractere minusculo
char fazerMaiusculo(char c); // Deixa um caractere minusculo
char ehLetra(char c); // Confere se um caractere e uma letra
void acharNome(int id, int tipo, char nome[NAME_SIZE]); // Retorna o nome do usuario com base na permissao e no id
int acharIdTipo(int *id, int *tipo, char nome[NAME_SIZE]); // Configura o id e o tipo do usuario com base no nome

int alunoPreencherNotas(int id, int idProfessor, Nota notas[MAXN]);
int alunoPreencherFaltas(int id, Faltas *faltas);
float alunoMedia(int id, int idProfessor);
float alunoNota(int idProva, int idAluno);
int alunoFaltas(int idProfessor, int idAluno);

int preencherTurma(int ano, char turma, Aluno alunos[TURMA_SIZE]); // Preenche um vetor de alunos com todos os alunos de uma mesma turma
int preencherProvas(int id, int ano, char turma, Prova *provas); // Preenche um vetor de provas com todas as provas aplicadas para uma turma

void pegarTempo(char *tempo, size_t tamanho); // Preenche a string com o tempo atual no formato DD/MM/AAAA hh:mm:ss
float calcularMediaExame(float media); // Calcula a nota necessaria para um aluno passar pelo exame considerando a media original

extern Professor PROFESSORES[MAXN];
extern Aluno ALUNOS[MAXN];
extern Prova PROVAS[MAXN];
extern Nota NOTAS[MAXN];
extern Admin ADMINS[MAXN];
extern Faltas FALTAS[MAXN];