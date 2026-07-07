#include "database.h"
#include "menuAdmin.h"
#include "menuProfessor.h"
#include "menuAluno.h"

extern int SESSION_ID;

// Exibe o menu de login, autentica o usuário e redireciona para o menu certo
void menuLogin();

void cabecalho(); // Limpa a tela e printa o cabeçalho
void esperar(); // Espera até o usuário pressionar ENTER

// Funções de input
void mostrarAreaInput();
void consumirInput();
void digitaString(int tamanho, char str[tamanho]);
int  inputSimNao();
void digitaNomeValido(char nome[NAME_SIZE], int capitalizacaoImporta);
void digitaTurmaValida(int *ano, char *turma);
void digitaMateriaValida(char materia[MATERIA_SIZE]);
int  digitaOpcao(int min, int max);
int  inputTurma(int *ano, char *turma);

// Pede a senha atual e permite ao usuário mudá-la
void mudarSenha(int tipo);

// Deixa uma string num tamanho fixo, alinhando à esquerda, ao centro ou à direita
void padString(char *string, int tamanho, char alinhamento);