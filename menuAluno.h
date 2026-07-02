#pragma once
#include "menu.h"

void alunoVerNotas(int id, char materia[4]);
void alunoVerMedias(int id);
void mostrarMenuAluno();

int alunoPreencherNotas(int id, char *materia, Nota *notas);