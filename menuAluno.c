#include "menuAluno.h"

void verNotas(int id, char *materia){
    Nota notas[MAXN];
    unsigned tamanho = preencherNotas(id, materia, notas);
    unsigned float soma = 0;
    
    for(int i = 0; i < tamanho; i++){
        soma += notas[i].nota;
    }

    printf("Notas em %s - Prof. %s", materia, professor);
    for(int i = 0; i <= index; i++){
        printf("Prova %d: %f\n", notas[i].prova, notas[i].nota);
    }
    printf("Media na materia: %f", soma/tamanho);
}

void verMedias(int id){
    struct Materia {
        char materia[4];
        float soma;
        unsigned int contador;
    }

    Nota notas[MAXN];
    Materia materias[MAXN];
    unsigned tamanho = preencherNotas(id, "***", notas);
    int maxIndex = 0;

    for(int i = 0; i < tamanho; i++){ // percorre todas as notas do aluno para separar por materia
        int flag = 1;
        for(int j = 0; j <= maxIndex; j++){ // percorre o array de notas vendo se ja existe um struct da materia em questao
            if(notas[i].materia == materias[j].materia){
                materias[j].soma += notas[i].nota;
                materia[j].contador++;
                flag = 0;
                break;
            }
        }
        if(!flag) continue;
        maxIndex++;
        materias[maxIndex] = {notas[i].materia, notas[i].nota, 1};
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

unsigned preencherNotas(int id, char materia*, Nota *notas){
    unsigned index;

    for(int i = 0; i < (MAXN << 2); i++){
        Nota nota = NOTAS[i];
        char materiaNota = PROFESSORES[PROVAS[nota.idProva - 1].idProfessor - 1].materia;
        if(nota.idAluno == id && materia == materiaNota){
            notas[index] = NOTAS[i];
            index++;
        }
    }

    return index;
}