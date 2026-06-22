#pragma once
#include "login.h"
#include "database.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

void login(void (*existe)(char*), void (*buscarID)(char*), void (*validar)(int, char*), void (*mostrarMenu)());
void loginAluno();
void loginPai();
void loginProfessor();
void loginAdmin();