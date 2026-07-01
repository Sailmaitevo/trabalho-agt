#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "menu.h"

void login(int (*buscar)(char*), int (*validar)(int, char[PASS_SIZE]), void (*mostrarMenu)());
void loginAluno();
void loginProfessor();
void loginAdmin();