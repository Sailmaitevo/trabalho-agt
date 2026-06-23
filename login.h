#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "menu.h"

void login(void (*existe)(char*), void (*buscarID)(char*), void (*validar)(int, char*), void (*mostrarMenu)());
void loginAluno();
void loginPai();
void loginProfessor();
void loginAdmin();