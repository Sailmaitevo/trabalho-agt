#pragma once
#include "menu.h"

void admListarProfessores();
void admListarAlunos();
void admListarTurmas();

void admCadastrar();
void admDeletar();
void admEditar();

int admPedirNivelDePermissao(int admin);

void mostrarMenuAdmin();