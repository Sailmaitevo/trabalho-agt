#include "menuAluno.h"

void alunoVerNotas(int id, char *materia){
    Nota notas[MAXN];
    int tamanho = alunoPreencherNotas(id, materia, notas);
    float soma = 0;
    
    for(int i = 0; i < tamanho; i++){
        soma += notas[i].nota;
    }

    printf("Notas em %s - Prof. %s", materia, PROFESSORES[buscarProfessorPorMateria(materia)].nome);
    for(int i = 0; i <= tamanho; i++){
        printf("Prova %d: %f\n", notas[i].idProva, notas[i].nota);
    }
    printf("Media na materia: %f", soma/tamanho);
}

void alunoVerMedias(int id){
    typedef struct {
        char *materia;
        float soma;
        unsigned int contador;
    } Materia;

    Nota notas[MAXN];
    Materia materias[MAXN];
    int tamanho = alunoPreencherNotas(id, "***", notas);
    int maxIndex = 0;

    for(int i = 0; i < tamanho; i++){ // percorre todas as notas do aluno para separar por materia
        int flag = 1;
		char *materia = PROFESSORES[PROVAS[notas[i].idProva-1].idProfessor-1].materia;
        for(int j = 0; j <= maxIndex; j++){ // percorre o array de notas vendo se ja existe um struct da materia em questao
            if(materia == materias[j].materia){
                materias[j].soma += notas[i].nota;
                materias[j].contador++;
                flag = 0;
                break;
            }
        }
        if(!flag) continue;
        maxIndex++;
		Materia a = {materia, notas[i].nota, 1};
        materias[maxIndex] = a;
    }

    float soma = 0;
    int contador = 0;
    for(int i = 0; i <= maxIndex; i++){
        printf("Media em %s: %f\n", materias[i].materia, materias[i].soma/materias[i].contador);
        soma += materias[i].soma/materias[i].contador;
        contador++;
    }
    printf("Media geral: %f", soma/contador);
}

int alunoPreencherNotas(int id, char *materia, Nota *notas){
    int index;

    for(int i = 0; i < (MAXN); i++){
        Nota nota = NOTAS[i];
        const char *materiaNota = PROFESSORES[PROVAS[nota.idProva - 1].idProfessor - 1].materia;
        if(nota.idAluno == id && !strcmp(materia, materiaNota)){
            notas[index] = NOTAS[i];
            index++;
        }
    }

    return index;
}

void mostrarMenuAluno(){
	Aluno usuario = ALUNOS[SESSION_ID - 1];
	
	int opcao;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que você quer fazer hoje?\n", usuario.nome);
		printf("0 - sair\n");
		printf("1 - ver notas\n");
		printf("2 - ver medias\n");
		
		scanf("%d", &opcao);
		
		printf("Opcao: %d", opcao);
		
		switch(opcao){
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
			default:
				printf("Ainda implementando...");
		}
	} while(opcao);
	
	return;
}