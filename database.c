#include <stdio.h>

unsigned long criptografar(const unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void cadastrarProfessor(char nome[NAME_SIZE], char senha[33], char materia[3]){}

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