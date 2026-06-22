#include "login.h"
#define USER_PASS_SIZE 16

void mostrarLogin() {
  char nome[NAME_SIZE];
  char senha[USER_PASS_SIZE];

  printf("Digite o nome do usuario (maximo de %d caracteres): ", NAME_SIZE);
  scanf("%s", nome);

  printf("Digite a senha do usuario (maximo de %d caracteres): ", USER_PASS_SIZE);
  scanf("%s", senha);

  // funcao para checar se o usuario existe na database
  if (0) {
    printf("Usuario nao encontrado!");
  }
  // e para checar se a senha esta correta
  else if (0) {
    printf("Senha nao esta correta!");
  } else {
    printf("Seja bem-vindo, %s", nome);
  }

}