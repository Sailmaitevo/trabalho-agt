#pragma once
#include "menu.h"
#include "database.h"

void cadastrar();
void deletar();

void listarProfessores();
void listarAlunos();
void listarTurmas();
void listarNotas(int idAluno);
void listarProvas(int idProfessor);

void mostrarMenuAdmin();