#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OPCAO_MIN 1
#define OPCAO_MAX 8
#define ALUNOS_MAX 50
#define NOME_MAX 21
#define DADOS_Q 3
#define AULAS_NUM 72
#define MEDIA_MIN 7
#define EXAME_MIN 3
#define ALUNOS_CSV "Alunos.csv"
#define DADOS_CSV "Resultados.csv"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

char estudantes[ALUNOS_MAX][NOME_MAX];
float escores[ALUNOS_MAX];
float dados[ALUNOS_MAX][DADOS_Q];
int dadosQuantia;
int estudanteQuantia;

void consumirInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarAreaInput() {
  printf("\n>");
}

void limparTela() {
  printf("\e[1;1H\e[2J");
  fflush(stdout); 
  printf("==== SIGA (Sistema Integrado de Gestao Algoritmica) ====\n\n");
}

void esperarInput() {
  // essa função por si só não garante que o programa vai esperar, é preciso que
  // não haja um \n no buffer
  printf("\nPressione enter para prosseguir...");
  consumirInput();
}

void printHiphensNome() {
  for (int i = 0; i < NOME_MAX; i++) {
    printf("-");
  }
}

int obterOpcao() {
  int opcao;
  int valido = 0;
  printf("  Opcoes\n");

  printf("------------------------------------------------------\n");
  printf("  1 - %-46s  \n", "Inserir um novo estudante");

  printf("------------------------------------------------------\n");
  printf("  2 - %-46s  \n", "Remover um estudante existente");
  
  printf("------------------------------------------------------\n");
  printf("  3 - %-46s  \n", "Ver a listagem de todos os estudantes");
  
  printf("------------------------------------------------------\n");
  printf("  4 - %-46s  \n", "Consultar os dados de um estudante");
  
  printf("------------------------------------------------------\n");
  printf("  5 - %-46s  \n", "Cadastrar resultado semetral de um estudante");
  
  printf("------------------------------------------------------\n");
  printf("  6 - %-46s  \n", "Listar os resultados semestrais dos estudantes");
  
  printf("------------------------------------------------------\n");
  printf("  7 - %-46s  \n", "Sair");
  
  printf("------------------------------------------------------\n");
  printf("  8 - %-46s  \n", "Apagar database");
  printf("------------------------------------------------------\n");

  printf("\nDigite uma das opcoes:");
  mostrarAreaInput();

  while (!valido) {
    int resultado = scanf("%d", &opcao);
    consumirInput();
    if (!resultado) {
      printf("Input invalido! Escreva um digito:\n>");
    } else {
      if (opcao < OPCAO_MIN || opcao > OPCAO_MAX) {
        printf("Input invalido! Escreva um valor de %d a %d:", OPCAO_MIN, OPCAO_MAX);
        mostrarAreaInput();
      } else {
        valido = 1;
      }
    }
  }

  return opcao;
}

void digitaString(int tamanho, char str[tamanho]) {
  mostrarAreaInput();
  fgets(str, tamanho, stdin);

	// ver se o newline foi lido ou nao
	if (strchr(str, '\n') != NULL) {
		str[strcspn(str, "\n")] = '\0';
	} else {
		consumirInput();
	}
}

void inputNome(char nome[NOME_MAX]) {
  printf("Escreva o nome do estudante, maximo de %d caracteres (digite nada para cancelar):", NOME_MAX - 1);

  digitaString(NOME_MAX, nome);
}

char fazerMinusculo(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 'a';
  } else {
    return c;
  }
}

int compararNomes(char nome1[NOME_MAX], char nome2[NOME_MAX]) {
  for (int i = 0; i < NOME_MAX - 1; i++) {
    char c1 = nome1[i];
    char c2 = nome2[i];
    if (c1 == '\0' && c2 == '\0') {
      return 1;
    }
    if (fazerMinusculo(c1) != fazerMinusculo(c2)) {
      return 0;
    }
  }

  return 1;
}

int acharIndexEstudante(char nome[NOME_MAX]) {
  int index = -1;
  for (int i = 0; i < estudanteQuantia; i++) {
    if (compararNomes(estudantes[i], nome)) {
      index = i;
      break;
    }
  }
  return index;
}

int acharIndexDados(int index) {
  for (int i = 0; i < dadosQuantia; i++) {
    if (dados[i][0] == index) {
      return i;
    }
  }

  return -1;
}

int nomeEhValido(char nome[NOME_MAX]) {
  for (int i = 0; nome[i] != '\0'; i++) {
    int ehLetraMaiscula = nome[i] >= 'A' && nome[i] <= 'Z';
    int ehLetraMinuscula = nome[i] >= 'a' && nome[i] <= 'z';
    if (!ehLetraMaiscula && !ehLetraMinuscula && nome[i] != ' ' && nome[i] != '-') {
      return 0;
    }
  }

  return 1;
}

void inserirItem() {
  limparTela();
  if (estudanteQuantia >= ALUNOS_MAX) {
    printf("Erro! O numero limite de estudantes foi alcancado. Impossivel adicionar um novo estudante.\n");
  } else {
    char nome[NOME_MAX];
    float escore;
  
    printf("Opcao 1 escolhida. Inserindo um novo estudante...\n\n");

    int valido = 0;
    while (!valido) {
      inputNome(nome);
  
      int indexNome = acharIndexEstudante(nome);
  
      if (strlen(nome) == 0) {
        printf("Cancelando a insercao.\n");
        return;
      } else if (indexNome != -1) {
        printf("Estudante ja existe! Cancelando a insercao...\n");
        return;
      } else if (!nomeEhValido(nome)) {
        printf("Nome invalido! Deve conter apenas letras, hifens e espacos.\n");
      } else if (strlen(nome) < 4) {
        printf("Nome invalido! Ele deve ter mais de 3 letras\n");
      } else {
        valido = 1;
      }
    }

    printf("Escreva o escore do estudante (digite -1 para cancelar):");
    mostrarAreaInput();

    int escoreValido = 0;
    int abortar = 0;
    while (!escoreValido) {
      int resultado = scanf("%f", &escore);
      consumirInput();

      if (!resultado) {
        consumirInput();
        printf("Escore invalido: Deve ser um numero.\nEscreva de novo:");
        mostrarAreaInput();
      } else {
        if (escore == -1) {
          abortar = 1;
          escoreValido = 1;
          printf("Cancelando...\n");
        } else if (escore < 0) {
          printf("Escore invalido: Nao pode ser negativo.\nEscreva de novo:");
          mostrarAreaInput();
        } else if (escore > 10) {
          if (escore > 8000) {
            printf("Eh de mais de 8000! ");
          }
          printf("Escore invalido: Nao pode ser maior que 10.\nEscreva de novo:");
          mostrarAreaInput();
        } else {
          escoreValido = 1;
        }
      }
    }
  
    if (!abortar) {
      strcpy(estudantes[estudanteQuantia], nome);
      escores[estudanteQuantia] = escore;
  
      estudanteQuantia++;
  
      printf("Estudante inserido com sucesso!\n");
    }
  }
}

void removerItem() {
  limparTela();
  printf("Opcao 2 escolhida, removendo um estudante (digite nada para cancelar)...\n\n");
  
  char nome[NOME_MAX];
  inputNome(nome);

  int index = acharIndexEstudante(nome);
  if (strlen(nome) == 0) {
    printf("Cancelando...\n");
    return;
  } else if (index == -1) {
    printf("Estudante nao encontrado! Nenhum item foi removido\n");
  } else {
    int dadoIndex = acharIndexDados(index);

    if (dadoIndex != -1) {
      printf("O estudante ja tem resultados semestrais. Nao eh possivel remove-lo\n");
      return;
    } else {
      for (int i = index; i < estudanteQuantia - 1; i++) {
        strcpy(estudantes[i], estudantes[i + 1]);
        escores[i] = escores[i + 1];
      }
      for (int i = 0; i < dadosQuantia; i++) {
        if (dados[i][0] > index) {
          dados[i][0]--;
        }
      }
      estudanteQuantia--;
      printf("Estudante removido com sucesso!\n");
    }
  }


}

float calcularMediaExame(float media) {
  return (50 - (media*6)) / 4;
}

void escreverResultado(char resultado[16], char nota[16], float media, float faltas) {
  if (faltas >= AULAS_NUM / 4) {
    strcpy(resultado, "Reprovad@ falta");
    strcpy(nota, "-");
  }
  else if (media >= MEDIA_MIN) {
    strcpy(resultado, "Aprovad@");
    strcpy(nota, "-");
  }
  else if (media >= EXAME_MIN) {
    strcpy(resultado, "Em exame");
    strcpy(nota, "");
    sprintf(nota, "%.1f", calcularMediaExame(media));
  } else {
    strcpy(resultado, "Reprovad@");
    strcpy(nota, "-");
  }
}

void listarEstudantes() {
  limparTela();

  if (estudanteQuantia == 0) {
    printf("Nao ha nenhum aluno cadastrado\n");
    return;
  }

  printf("Estudantes cadastrados:\n\n");

  printf("  %-" STR(NOME_MAX) "s | %-6s \n", "Estudante", "Escore");
  printHiphensNome();
  printf("-------------\n");

  for (int i = 0; i < estudanteQuantia; i++) {
    if (i > 0) {
      printf("|--------------------------------|\n");
    }
    printf("| %-" STR(NOME_MAX) "s | %-6.2f |\n", estudantes[i], escores[i]);
  }

  printHiphensNome();
  printf("-------------\n");
}

void sobrescreverDatabase(){
	FILE *alunos = fopen(ALUNOS_CSV, "w");
	FILE *resultados = fopen(DADOS_CSV, "w");
	
  for (int i = 0; i < estudanteQuantia; i++) {
    fprintf(alunos, "%s,%f\n", estudantes[i], escores[i]);
  }
  for (int i = 0; i < dadosQuantia; i++) {
    fprintf(resultados, "%.0f,%f,%f\n", dados[i][0], dados[i][1], dados[i][2]);
  }

  fclose(alunos);
  fclose(resultados);
}

FILE *importarArquivo(char *caminho){
	FILE *arquivo = fopen(caminho, "r");
	if(arquivo == NULL){
		arquivo = fopen(caminho, "w");
		if(arquivo == NULL){
			printf("Erro fatal: não foi possível criar o arquivo %s", caminho);
			exit(1);
		}
	}
	fclose(arquivo);
	
	return fopen(caminho, "r");
}

void importarDatabase(){
	FILE *alunos = importarArquivo(ALUNOS_CSV);
  FILE *resultados = importarArquivo(DADOS_CSV);
	char linha[NOME_MAX+20];
	for(int i = 0; fgets(linha, sizeof(linha), alunos) != NULL; i++){
    char nome[NOME_MAX];
		sscanf(linha, "%[^,],%f", estudantes[i], &escores[i]);
    estudanteQuantia++;
	}

  for(int i = 0; fgets(linha, sizeof(linha), resultados) != NULL; i++){
    char nome[NOME_MAX];
		sscanf(linha, "%f,%f,%f", &dados[i][0], &dados[i][1], &dados[i][2]);
    dadosQuantia++;
	}
	
	fclose(alunos);
	fclose(resultados);
}

void listarDadosEspecificos() {
  limparTela();

  if (dadosQuantia == 0) {
    printf("Nenhum resultado de aluno foi cadastrado...\n");
    return;
  } else {
    printf("Resultado dos alunos no semestre:\n\n");
  }

  printf("  %-" STR(NOME_MAX) "s %-8s %-17s %-8s %-20s %-17s\n",
  "Estudante",
  "| Escore",
  "| Media Semestral",
  "| Faltas",
  "| Resultado",
  "| Nota Minima Exame");

  printHiphensNome();
  printf("--------------------------------------------------------------------------------\n");

  for (int i = 0; i < estudanteQuantia; i++) {
    int dadoIndex = acharIndexDados(i);

    if (dadoIndex != -1) {
      float media = dados[dadoIndex][1];
      float faltas = dados[dadoIndex][2];
      char resultado[16];
      char nota[16];
      escreverResultado(resultado, nota, media, faltas);

      if (i > 0) {
        printf("|---------------------------------------------------------------------------------------------------|\n");
      }

      printf("| %-" STR(NOME_MAX) "s | %-6.1f | %-15.1f | %-6.0f | %-18s | %-16s |\n",
        estudantes[i],
        escores[i],
        media,
        faltas,
        resultado,
        nota);
    }
  }

  printHiphensNome();
  printf("--------------------------------------------------------------------------------\n");
}

void listarDados() {
  char nome[NOME_MAX];
  
  limparTela();
  printf("Opcao 4 escolhida. Buscando os dados de um estudante...\n\n");
  
  inputNome(nome);

  int index = acharIndexEstudante(nome);
  if (strlen(nome) == 0) {
    printf("Cancelando...\n");
  } else if (index == -1) {
    printf("O estudante nao existe!\n");
  } else {
    int indexDado = acharIndexDados(index);
    limparTela();
    printf("Dados de %s:\n", estudantes[index]);
    printf("------------------------------------------\n");
    printf("| %-20s | %-15.1f |\n", "Escore", escores[index]);
    if (indexDado != -1) {
      char resultado[16];
      char nota[16];
      escreverResultado(resultado, nota, dados[indexDado][1], dados[indexDado][2]);
      printf("|----------------------------------------|\n");
      printf("| %-20s | %-15.1f |\n", "Media Semestral", dados[indexDado][1]);
      printf("|----------------------------------------|\n");
      printf("| %-20s | %-15.0f |\n", "Faltas", dados[indexDado][2]);
      printf("|----------------------------------------|\n");
      printf("| %-20s | %-15s |\n", "Resultado", resultado);
      printf("|----------------------------------------|\n");
      printf("| %-20s | %-15s |\n", "Nota minima exame", nota);      
    }
    printf("------------------------------------------\n");
    if (indexDado == -1) {
      printf("\nO estudante nao tem resultados semestrais cadastrados.\n");
    }
  }
}

int inputSimNao() {
	char resposta[2];
	digitaString(2, resposta);
	return fazerMinusculo(resposta[0]) == 's';
}

void inserirDadosEstudante() {
  limparTela();
  printf("Opcao 5 escolhida, cadastrando resultados semestrais de um estudante...\n\n");
  
  char nome[NOME_MAX];
  inputNome(nome);
  int index = acharIndexEstudante(nome);
  if (strlen(nome) == 0) {
    printf("Cancelando...\n");
  } else if (index == -1) {
    printf("Estudante nao encontrado!\n");
  } else {
    int j = -1;
    for (int i = 0; i < dadosQuantia; i++) {
      if (dados[i][0] == index) {
        j = i;
        break;
      }
    }
    if (j != -1) {
      printf("Cadastro ja encontrado. Voce gostaria de sobreescrever? (S para sim):");
      if (!inputSimNao()) {
        printf("Cancelando cadastro...\n");
        return;
      }
    }
    // j sera o index a sobreescrever
    int incrementar = 0;
    if (j == -1) {
      j = dadosQuantia;
      incrementar = 1;
    }
    float media;
    float faltas;
    printf("Escreva a media semestral (digite -1 para cancelar):");
    mostrarAreaInput();

    int valido = 0;
    while (!valido) {
      int resultado = scanf("%f", &media);
      consumirInput();
      if (resultado) {
        if (media == -1) {
          printf("Cancelando...\n");
          return;
        } else if (media < 0) {
          printf("Valor invalido, deve ser maior que 0. Digite de novo:");
          mostrarAreaInput();
        } else if (media > 10) {
          printf("Valor invalido, deve ser menor que 10. Digite de novo:");
          mostrarAreaInput();
        } else {
          valido = 1;
        }
      } else {
        printf("Valor invalido, deve ser um numero. Digite de novo:");
        mostrarAreaInput();
      }
    }

    valido = 0;
    printf("Escreva o numero de faltas (digite -1 para cancelar):");
    while (!valido) {
      mostrarAreaInput();
      int resultado = scanf("%f", &faltas);
      consumirInput();
      if (resultado) {
        if (faltas == -1) {
          printf("Cancelando...\n");
          return;
        } else if (faltas < 0) {
          printf("Valor invalido de faltas, deve ser maior que 0. Digite de novo:");
        } else if (faltas > AULAS_NUM) {
          printf("Valor invalido de faltas, deve ser menor que o total de aulas (%d). Digite de novo:", AULAS_NUM);
        } else {
          valido = 1;
        }
      } else {
        printf("Valor invalido, deve ser um numero. Digite de novo:");
      }
    }
    if (incrementar) {
      dadosQuantia++;
    }
    dados[j][0] = index;
    dados[j][1] = media;
    dados[j][2] = faltas;
    printf("Cadastro feito com sucesso!\n");
  }
}

void limparDatabase() {
  limparTela();
  printf("Voce gostaria de limpar a database? (S para sim): \n");
  if (inputSimNao()) {
    printf("Voce REALMENTE quer APAGAR A DATABASE PARA SEMPRE? (Digite exatamente \"QUERO\"):");
    char quero[6];
    digitaString(6, quero);
    if (strcmp(quero, "QUERO") == 0) {
      printf("Apagando a database...\n");
      dadosQuantia = 0;
      estudanteQuantia = 0;
      sobrescreverDatabase();
      printf("Database apagada com exito.\n");
      return;
    }
  }

  printf("Cancelando...\n");  
}

void sair() {
  limparTela();
  printf("Obrigado por usar o nosso servico. Nos vemos em breve.\n\nTerminando o programa...");
}

int main() {
  limparTela();

  printf("Seja bem-vindo\n\n");

  estudanteQuantia = 0;
  dadosQuantia = 0;

  importarDatabase();

  int opcao = 0;

  while (1) {
    int opcao = obterOpcao();
  
    switch (opcao) {
      case 1:
        inserirItem();
        break;
      case 2:
        removerItem();
        break;
      case 3:
        listarEstudantes();
        break;
      case 4:
        listarDados();
        break;
      case 5:
        inserirDadosEstudante();
        break;
      case 6:
        listarDadosEspecificos();
        break;
      case 7:
        sair();
        sobrescreverDatabase();
        return 0;
      case 8:
        limparDatabase();
        break;
    }

    sobrescreverDatabase();
    esperarInput();
    limparTela();
  }
}