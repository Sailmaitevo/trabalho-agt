#include "menu.h"

void limpar() {
  printf("\x1b[2J\x1b[H");
}

void cabecalho(){
  limpar();
  printf("==== SIGEC (Sistema Integrado de Gestao Escolar em C) ====\n");
}

void menuLogin(){
  cabecalho();
  int opcao;
  printf("Bem-vindo, escolha uma forma de login:\n1- Aluno\n2- Professor\n3- Pai\n4- Administrador\n");
  scanf("%d", &opcao);
  switch(opcao){
    case 1:
      loginAluno();
      break;
    case 2:
      loginProfessor();
      break;
    case 3:
      loginPai();
      break;
    case 4:
      loginAdmin();
      break;
    default:
      menuLogin();
      return;
  }
}