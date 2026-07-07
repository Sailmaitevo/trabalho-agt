#include "database.h"
#include "menuAdmin.h"
#include "menuProfessor.h"
#include "menuAluno.h"

extern int SESSION_ID;

void login();

void digitaString(int tamanho, char str[tamanho]);
void limpar();
void menuLogin();
void cabecalho();
void padString(char *string, int padding);
void esperar();
void mostrarAreaInput();
void consumirInput();
int  inputSimNao();
void digitaNomeValido(char nome[NAME_SIZE], int capitalizacaoImporta);
void digitaTurmaValida(int *ano, char *turma);
void digitaMateriaValida(char materia[MATERIA_SIZE]);
int  digitaOpcao(int min, int max);
int  inputTurma(int *ano, char *turma);
void mudarSenha(int tipo);