#pragma once
#include "menu.h"
#include "database.h"

void cadastrarAluno();
void cadastrarProfessor();
void cadastrarPai();
void cadastrarAdmin();

void deletarAluno(int id);
void deletarProfessor(int id);
void deletarPai(int id);
void deletarAdmin(int id);

void listarProfessores();
void listarMaterias();
void listarAlunos();
void listarTurmas();
void listarNotas(int idAluno);
void listarProvas(int idProfessor);

void mostrarMenuAdmin(int id);