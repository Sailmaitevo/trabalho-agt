#include "database.h"
#include "login.h"
#include "menuAdmin.h"
#include "menuProfessor.h"
#include "menuAluno.h"

int SESSION_ID;

void limpar();
void menuLogin();
void cabecalho();
void padString(char *string, int padding);
void esperar(char *msg);