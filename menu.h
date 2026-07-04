#include "database.h"
#include "login.h"
#include "menuAdmin.h"
#include "menuProfessor.h"
#include "menuAluno.h"

extern int SESSION_ID;

void limpar();
void menuLogin();
void cabecalho();
void padString(char *string, int padding);
void esperar();
void mostrarAreaInput();
void consumirInput();
int inputSimNao();