#include "database.h"

unsigned long criptografar(const unsigned char *str) {
    unsigned long hash = 7723;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void cadastrarProfessor(char nome[NAME_SIZE], char senha[PASS_SIZE], char materia[4]){
    for(int i = 0; i < MAXN; i++){
        if(PROFESSORES[i].id == 0){
            PROFESSORES[i] = {i+1, nome, criptografar(senha), materia};
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}

void cadastrarAluno(int id, char nome[NAME_SIZE], char senha[PASS_SIZE], int ano, int turma, int idPai){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].id == 0){
            ALUNOS[i] = {i+1, nome, criptografar(senha), ano, turma, idPai};
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase(); 
}

void cadastrarProva(int idProfessor, int ano, int turma){
    for(int i = 0; i < MAXN; i++){
        if(PROVAS[i].id == 0){
            PROVAS[i] = {i+1, ano, turma};
            criarNotas(i);
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}

void cadastrarPai(char nome[NAME_SIZE], char senha[PASS_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(PAIS[i].id == 0){
            PAIS[i] = {i+1, nome, criptografar(senha)};
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}

void cadastrarAdmin(char nome[NAME_SIZE], char senha[PASS_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ADMINS[i].id == 0){
            ADMINS[i] = {i+1, nome, criptografar(senha)};
            return;
        }
    }
    limpar();
    printf("Erro! O banco de dados esta cheio!");
    sobrescreverDatabase();
}

void zerarNotas(int idProva){
    Prova prova = PROVAS[idProva-1];
    unsigned long ultimoIndex = 0;

    for(int i = 0; i < MAXN; i++){
        if (ultimoIndex == MAXN << 2){
            printf("Erro, o banco de dados esta cheio!");
            deletarProva(idProva);
            sobrescreverDatabase();
        }

        if(ALUNOS[i].ano == prova.ano && ALUNOS[i].turma == prova.turma){
            for(ultimoIndex; ultimoIndex < MAXN; ultimoIndex++){
                if(NOTAS[ultimoIndex].idProva == 0){
                    NOTAS[ultimoIndex] = {idProva, i+1, 0.0};
                    break;
                }
            }
        }
    }
}

void deletarProfessor(int id){
    PROFESSORES[id-1] = {0, "\0", 0, "---"};
}
void deletarAluno(int id){
    ALUNOS[id-1] = {0, "\0", 0, 0, 0, 0};
}
void deletarProva(int id){
    for(int i = 0; i < (MAXN << 2); i++){
        if(NOTAS[i].idProva == id) NOTAS[i] = {0, 0, 0.0};
    }
    PROVA[id-1] = {0, ano, turma};
}
void deletarPai(int id){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].idPai == id) ALUNOS[i].idPai = 0;
    }
    PAIS[id-1] = {0, "", 0};
}
void deletarAdmin(int id){
    ADMINS[id-1] = {0, "", 0}
}

int validarProfessor(int id, char senha[PASS_SIZE]){
    unsigned long senhaCriptografada = criptografar(senha);
    return PROFESSORES[id-1].senha == senhaCriptografada;
}
int validarAluno(int id, char senha[PASS_SIZE]){
    unsigned long senhaCriptografada = criptografar(senha);
    return ALUNOS[id-1].senha == senhaCriptografada;
}
int validarPai(int id, char senha[PASS_SIZE]){
    unsigned long senhaCriptografada = criptografar(senha);
    return PAIS[id-1].senha == senhaCriptografada;
}
int validarAdmin(int id, char senha[PASS_SIZE]){
    unsigned long senhaCriptografada = criptografar(senha);
    return ADMINS[id-1].senh senhaCriptografada;
}

int buscarProfessor(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(PROFESSORES[i].nome == nome) return i+1;
    }
    return 0;
}
int buscarAluno(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ALUNOS[i].nome == nome) return i+1;
    }
    return 0;
}
int buscarPai(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(PAIS[i].nome == nome) return i+1;
    }
    return 0;
}
int buscarAdmin(char nome[NAME_SIZE]){
    for(int i = 0; i < MAXN; i++){
        if(ADMINS[i].nome == nome) return i+1;
    }
    return 0;
}

