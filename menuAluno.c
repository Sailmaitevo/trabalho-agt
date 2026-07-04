#include "menuAluno.h"

void alunoVerNotas(int id, int idProfessor){
    Nota notas[MAXN] = {};
	Professor professor = PROFESSORES[idProfessor - 1];
	
    int tamanho = alunoPreencherNotas(id, idProfessor, notas);
	
    float soma = 0;
    
    for(int i = 0; i < tamanho; i++){
        soma += notas[i].nota;
    }

	cabecalho();
    printf("Notas em %s - Prof. %s\n", professor.materia, professor.nome);
    for(int i = 0; i < tamanho; i++){
        printf("%s: %.1f\n", PROVAS[notas[i].idProva-1].nome, notas[i].nota);
    }
    printf("Media na materia: %.1f", soma/tamanho);
	
	esperar();
	
	alunoVerMedias(id);
}

void alunoVerMedias(int id){
	typedef struct {
		char materia[4];
        float soma;
        unsigned contador;
		int idProfessor;
    } Materia;
	
    Nota notas[MAXN] = {};
    Materia materias[MAXN] = {};
    int tamanho = alunoPreencherNotas(id, 0, notas);
    int maxIndex = 0;
	
    for(int i = 0; i < tamanho; i++){
        int flag = 1;
		int idProfessor = PROVAS[notas[i].idProva-1].idProfessor;
        for(int j = 0; j <= maxIndex; j++){ // percorre o array de notas vendo se ja existe um struct da materia em questao
            if(idProfessor == materias[j].idProfessor){
				materias[j].soma += notas[i].nota;
                materias[j].contador++;
                flag = 0;
                break;
            }
        }
        if(!flag) continue;
        
		Materia aux = {"", notas[i].nota, 1, idProfessor};
		strcpy(aux.materia, PROFESSORES[idProfessor-1].materia);
        materias[maxIndex] = aux;
		maxIndex++;
    }
	
	cabecalho();
    float soma = 0;
    int contador = 0;
	
	if(!tamanho){
		printf("\nNao foram encontradas notas");
		esperar();
		return;
	}
	
    for(int i = 0; i < maxIndex; i++){
		printf("%d - %s: %.1f\n", i+1, materias[i].materia, materias[i].soma/materias[i].contador);
        soma += materias[i].soma/materias[i].contador;
        contador++;
    }
    printf("Media geral: %.1f", soma/contador);
	
	int opcao;
	printf("\n\nInsira uma materia (utilize o numero) para ver detalhes ou 0 para voltar: ");
	scanf("%d", &opcao);
	if(opcao >= 1 && opcao <= maxIndex){
		alunoVerNotas(id, materias[opcao-1].idProfessor);
	}
}

void alunoVerFaltas(int id){
	Faltas faltas[MAXN] = {};
	int tamanho = alunoPreencherFaltas(id, faltas);
	
	cabecalho();
	printf("Suas faltas");
	if(!tamanho){
		printf("\nNao foram encontradas faltas");
	}
	for(int i = 0; i < tamanho; i++){
		printf("\n%s - %d", PROFESSORES[faltas[i].idProfessor-1].materia, faltas[i].numero);
	}
	
	esperar();
}

void mostrarMenuAluno(){
	
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que voce quer fazer hoje?\n", ALUNOS[SESSION_ID - 1].nome);
		printf("0 - sair\n");
		printf("1 - ver notas\n");
		printf("2 - ver faltas\n");
		printf("3 - alterar senha\n");
		
		scanf("%d", &opcao);
		
		switch(opcao){
			char senha[PASS_SIZE], senhaNova[PASS_SIZE], senhaNovaConfirmar[PASS_SIZE];
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
				break;
			case 1:
				alunoVerMedias(SESSION_ID);
				break;
			case 2:
				alunoVerFaltas(SESSION_ID);
				break;
			case 3:
				printf("Digite sua senha atual: ");
				scanf("%s", senha);
				getchar();
				if(validarAluno(SESSION_ID, senha)){
					while(1){
						cabecalho();
						printf("Digite sua nova senha (3 a %d caracteres): ", PASS_SIZE);
						while(1){
							scanf("%s", senhaNova);
							getchar();
							if(strlen(senha) > 2) break;
							printf("Input invalido, tente de novo: ");
						}
						printf("Digite a nova senha novamente: ");
						scanf("%s", senhaNovaConfirmar);
						if(!strcmp(senhaNova, senhaNovaConfirmar)){
							ALUNOS[SESSION_ID-1].senha = criptografar(senhaNova);
							printf("Senha alterada com sucesso");
							break;
						} else {
							printf("As duas senhas nao batem, tente novamente");
						}
					}
				}
				break;
		}
	} while(opcao);
}