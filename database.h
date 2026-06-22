#pragma once
#define PASS_SIZE 33
#define NAME_SIZE 20


void importarDatabase();
void sobrescreverDatabase();

typedef struct {
  int id;
  char nome[NAME_SIZE];
  char senha[PASS_SIZE];
  char materia[3];
} Professor;

typedef struct {
  int matricula;
  char nome[20];
  char senha[PASS_SIZE];
  int ano;
  int turma;
  int idPai;
} Aluno;

typedef struct {
  int id;
  int idProfessor;
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
  char nome[20];
  char senha[PASS_SIZE];
} Pai;

typedef struct {
  int id;
  char nome[20];
  char senha[PASS_SIZE];
} Admin;

unsigned long criptografar(const unsigned char *str);

void cadastrarProfessor(char nome[20], char senha[33], char materia[3]);
void cadastrarAluno(int matricula, char nome[20], char senha[33], int ano, int turma, int idPai);
void cadastrarProva(int idProfessor, int ano, int turma);
void cadastrarNota(int matriculaAluno, int idProva, int nota);
void cadastrarPai(char nome[20], char senha[PASS_SIZE]);
void cadastrarAdmin(int nome[20], char senha[PASS_SIZE]);

void deletarProfessor(int id);
void deletarAluno(int matricula);
void deletarProva(int id);
void deletarPai(int id);
void deletarAdmin(int id);

void editarProfessor(int id, char nome[20], char senha[33], char materia[3]);
void editarAluno(int matricula, char nome[20], char senha[33], int ano, int turma, int idPai);
void editarProva(int id, int idProfessor, int ano, int turma);
void editarNota(int matriculaAluno, int idProva, int nota);
void editarPai(int id, char nome[20], char senha[PASS_SIZE]);
void editarAdmin(int id, int nome[20], char senha[PASS_SIZE]);

void validarProfessor(int id, char senha[PASS_SIZE]);
void validarAluno(int matricula, char senha[PASS_SIZE]);
void validarProva(int id, char senha[PASS_SIZE]);
void validarPai(int id, char senha[PASS_SIZE]);
void validarAdmin(int id, char senha[PASS_SIZE]);
