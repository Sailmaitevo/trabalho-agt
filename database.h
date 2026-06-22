#pragma once
#define passSize 33

void importarDatabase();
void sobrescreverDatabase();

typedef struct {
  int id;
  char nome[20];
  char senha[passSize];
  char materia[3];
} Professor;

typedef struct {
  int matricula;
  char nome[20];
  char senha[passSize];
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
  char senha[passSize];
} Pai;

typedef struct {
  int id;
  char nome[20];
  char senha[passSize];
} Admin;

unsigned long criptografar(const unsigned char *str);

void cadastrarProfessor(char nome[20], char senha[33], char materia[3]);
void cadastrarAluno(int matricula, char nome[20], char senha[33], int ano, int turma, int idPai);
void cadastrarProva(int idProfessor, int ano, int turma);
void cadastrarNota(int matriculaAluno, int idProva, int nota);
void cadastrarPai(char nome[20], char senha[passSize]);
void cadastrarAdmin(int nome[20], char senha[passSize]);

void deletarProfessor(int id);
void deletarAluno(int matricula);
void deletarProva(int id);
void deletarPai(int id);
void deletarAdmin(int id);

void editarProfessor(int id, char nome[20], char senha[33], char materia[3]);
void editarAluno(int matricula, char nome[20], char senha[33], int ano, int turma, int idPai);
void editarProva(int id, int idProfessor, int ano, int turma);
void editarNota(int matriculaAluno, int idProva, int nota);
void editarPai(int id, char nome[20], char senha[passSize]);
void editarAdmin(int id, int nome[20], char senha[passSize]);

void validarProfessor(int id, char senha[passSize]);
void validarAluno(int matricula, char senha[passSize]);
void validarProva(int id, char senha[passSize]);
void validarPai(int id, char senha[passSize]);
void validarAdmin(int id, char senha[passSize]);
