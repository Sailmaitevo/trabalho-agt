#pragma once
#include "menu.h"

void alunoVerNotas(int id, int idProfessor);
void alunoVerMedias(int id);
void mostrarMenuAluno();

int alunoPreencherNotas(int id, int idProfessor, Nota *notas);
float alunoMedia(int id, int idProfessor);
float alunoNota(int idProva, int idAluno);