#pragma once
#define PASS_SIZE 16
#define NAME_SIZE 20
const unsigned MAXN = 1 << 10;

Professor PROFESSORES[MAXN];
Aluno ALUNOS[MAXN];
Prova PROVAS[MAXN];
Nota NOTAS[MAXN << 2];
Pai PAIS[MAXN];
Admin ADMINS[MAXN];

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
  int idProva;
  int idAluno;
  int nota;
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

void cadastrarProfessor(char nome[NAME_SIZE], char senha[33], char materia[3]);
void cadastrarAluno(int id, char nome[NAME_SIZE], char senha[33], int ano, int turma, int idPai);
void cadastrarProva(int idProfessor, int ano, int turma);
void cadastrarPai(char nome[NAME_SIZE], char senha[PASS_SIZE]);
void cadastrarAdmin(int nome[NAME_SIZE], char senha[PASS_SIZE]);

void deletarProfessor(int id);
void deletarAluno(int id);
void deletarProva(int id);
void deletarPai(int id);
void deletarAdmin(int id);

void editarProfessor(int id, char nome[NAME_SIZE], char senha[33], char materia[3]);
void editarAluno(int id, char nome[NAME_SIZE], char senha[33], int ano, int turma, int idPai);
void editarProva(int id, int idProfessor, int ano, int turma);
void editarNota(int idAluno, int idProva, int nota);
void editarPai(int id, char nome[NAME_SIZE], char senha[PASS_SIZE]);
void editarAdmin(int id, int nome[NAME_SIZE], char senha[PASS_SIZE]);

void validarProfessor(int id, char senha[PASS_SIZE]);
void validarAluno(int id, char senha[PASS_SIZE]);
void validarProva(int id, char senha[PASS_SIZE]);
void validarPai(int id, char senha[PASS_SIZE]);
void validarAdmin(int id, char senha[PASS_SIZE]);

int existeProfessor(char nome[NAME_SIZE])
int existeAluno(char nome[NAME_SIZE])
int existeProva(char nome[NAME_SIZE])
int existePai(char nome[NAME_SIZE])
int existeAdmin(char nome[NAME_SIZE])

int idProfessor(char nome[NAME_SIZE]); // nome do professor -> id do professor com aquele nome
int idAluno(char nome[NAME_SIZE]); // nome do aluno -> id do aluno com aquele nome
int idPai(char nome[NAME_SIZE]); // nome do pai -> id do pai com aquele nome
int idAdmin(char nome[NAME_SIZE]); // nome do admin -> id do admin com aquele nome
