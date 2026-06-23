#include "login.h"

void login(void (*buscar)(char*), void (*validar)(int, char*), void (*mostrarMenu)()){
  char usuario[NAME_SIZE];
  char senha[PASS_SIZE];
  int id;
  
  int flag = 0;
  printf("Insira seu nome de usuario (0 para voltar): ");
  while(1){
    scanf("%s", usuario);
    
    if(usuario == "0"){
      menuLogin();
      return;
    }
    id = buscar(usuario);
    if(id) break;

    printf("Nome de usuario invalido!\nTente novamente (0 para voltar):");
  }
  limpar();

  printf("Ola, %s!\nInsira sua senha: ", usuario);

  int flag = 0;
  for(int i = 0; i < 5; i++){
    scanf("%s", senha);
    if(validar(id, senha)){
      flag = 1;
      break;
    }
  }
  if(!flag){
    printf("Senha errada inserida mais de 5 vezes, encerrando o programa");
    exit();
  }

  mostrarMenu();
  return;
}

void loginAluno(){
  login(&existeAluno, &buscarAluno, &validarAluno, &mostrarMenuAluno);
}
void loginPai(){
  login(&existePai, &buscarPai, &validarPai, &mostrarMenuPai);
}
void loginProfessor(){
  login(&existeProfessor, &buscarProfessor, &validarProfessor, &mostrarMenuProfessor);
}
void loginAdmin(){
  login(&existeAdmin, &buscarAdmin, &validarAdmin, &mostrarMenuAdmin);
}