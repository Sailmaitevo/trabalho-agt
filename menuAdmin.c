#include "menuAdmin.h"

void admListarProfessores(){
	cabecalho();
	printf("id - nome - materia");
	for(int i = 0; i < MAXN; i++){
		Professor professor = PROFESSORES[i-1];
		if(!professor.id) continue;
		
		printf("\n%d - %s - %s", professor.id, professor.nome, professor.materia);
	}
	esperar();
}
void admListarAlunos(){
	cabecalho();
	printf("id - nome - turma - media");
	for(int i = 0; i < MAXN; i++){
		Aluno aluno = ALUNOS[i-1];
		if(!aluno.id) continue;
		
		printf("\n%d - %s - %d%c - %.1f", aluno.id, aluno.nome, aluno.ano, aluno.turma, alunoMedia(aluno.id, 0));
	}
	esperar();
}
void admListarTurmas(){
	cabecalho();
	
	typedef struct {
		int ano; char turma;
	} Turma;
	Turma jaForam[MAXN] = {};
	int maiorIndex = -1;
	
	printf("turma - qtd - media");
	for(int i = 0; i < MAXN; i++){
		Turma turma = {ALUNOS[i].ano, ALUNOS[i].turma};
		
		int flag = 0;
		for(int j = 0; j <= maiorIndex; j++){
			if(turma.ano == jaForam[j].ano && turma.turma == jaForam[j].turma){
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		
		jaForam[maiorIndex] = turma;
		maiorIndex++;
	}
	
	for(int i = 0; i < maiorIndex; i++){
		int ano = jaForam[i].ano;
		char turma = jaForam[i].turma;
		
		float soma = 0;
		Aluno alunos[MAXN] = {};
		int tamanho = preencherTurma(ano, turma, alunos);
		
		for(int i = 0; i < tamanho; i++){
			soma += alunoMedia(alunos[i].id, 0);
		}
		float media = tamanho ? soma/tamanho : 0;
		
		printf("\n%d%c - %d - %.1f", ano, turma, tamanho, soma/tamanho);
	}
	
	esperar();
}

void admCadastrar(){
	int permissao = admPedirNivelDePermissao(1);
	if(!permissao) return;
	
	char nome[NAME_SIZE];
	printf("Digite o nome (ate 20 caracteres sem espaco): ");
	while(1){
		scanf("%s", nome);
		getchar();
		
		if(strlen(nome)) break;
		
		if(permissao == 1 && buscarAluno ||
			permissao == 2 && buscarProfessor ||
			permissao == 3 && buscarAdmin(nome)
		){
			printf("Esse nome ja foi cadastrado, tente novamente: ");
			continue;
		}
		
		printf("Nome invalido, tente novamente: ");
	}
	
	cabecalho();
	switch(permissao){
		int ano, id;
		char turma, materia[4];
		case 1:
			printf("Digite a turma d@ alun@ %s", nome);
			while(1){
				if(!scanf("%d%c", &ano, &turma)){
					printf("Input invalido, tente novamente: ");
					continue;
				};
				getchar();
				
				Aluno alunos[MAXN];
				int tamanho = preencherTurma(ano, turma, alunos);
				if(tamanho >= 40) printf("Turma %d%c cheia, escolha outra: ", ano, turma);
				if(!tamanho){
					printf("Turma %d%c inexistente, digite S para cria-la: ", ano, turma);
					if(getchar() == 'S') break;
					else printf("Digite outra turma: ");
					while(getchar() != '\n');
				}
			}
			
			id = cadastrarAluno(nome, "123456", ano, turma);
			printf("Alun@ %s criad@ com sucesso na turma %d%c com o id %d\nA senha padrao e 123456", nome, ano, turma, id);
			esperar();
			break;
		case 2:
			printf("Digite a materia d@ professor(a) (3 caracteres): ");
			while(1){
				scanf("%s", materia);
				getchar();
				if(strlen(materia) == 3 && !strchr(materia, ' ')) break;
				printf("Tente novamente: ");
			}
			id = cadastrarProfessor(nome, "123456", materia);
			printf("Professor %s criado sem sucesso para a materia %s com o id %d\nA senha padrao e 123456", nome, materia, id);
			esperar();
			break;
		case 3:
			id = cadastrarAdmin(nome, "123456");
			printf("Admin %s criado com sucesso com o id %d\nA senha padrao e 123456", nome, id);
			esperar();
			break;
	}
}
void admDeletar(){
	int permissao = admPedirNivelDePermissao(1);
	
	cabecalho();
	switch(permissao){
		Aluno aluno;
		Professor professor;
		Admin admin;
		int id;
		char confirma;
		case 1:
			for(int i = 0; i < MAXN; i++){
				aluno = ALUNOS[i];
				if(!aluno.id) continue;
				
				printf("\n%d - %s - %d%c", aluno.id, aluno.nome, aluno.ano, aluno.turma);
			}
			printf("\n\nEscolha um id para excluir (0 volta): ");
			while(1){
				scanf("%d", &id);
				getchar();
				if(!id) return;
				
				aluno = ALUNOS[id-1];
				if(!aluno.id) printf("Aluno inexistente, tente novamente: ");
				else break;
			}
			cabecalho();
			printf("Voce esta prestes a deletar %s, tem certeza?\nDigite S para confirmar: ", aluno.nome);
			scanf("%c", &confirma);
			if(confirma != 'S') return;
			
			deletarAluno(id);
			printf("Alun@ deletad@ com sucesso");
			esperar();
			break;
		case 2:
			for(int i = 0; i < MAXN; i++){
				professor = PROFESSORES[i];
				if(!professor.id) continue;
				
				printf("\n%d - %s - %s", professor.id, professor.nome, professor.materia);
			}
			printf("\n\nEscolha um id para excluir (0 volta): ");
			while(1){
				scanf("%d", &id);
				getchar();
				if(!id) return;
				
				professor = PROFESSORES[id-1];
				if(!professor.id) printf("Professor inexistente, tente novamente: ");
				else break;
			}
			cabecalho();
			printf("Voce esta prestes a deletar %s, tem certeza?\nDigite S para confirmar: ", professor.nome);
			scanf("%c", &confirma);
			if(confirma != 'S') return;
			
			deletarProfessor(id);
			printf("Professor deletado com sucesso");
			esperar();
			break;
		case 3:
			for(int i = 0; i < MAXN; i++){
				admin = ADMINS[i];
				if(!admin.id) continue;
				
				printf("\n%d - %s", admin.id, admin.nome);
			}
			printf("\n\nEscolha um id para excluir (0 volta): ");
			while(1){
				scanf("%d", &id);
				getchar();
				if(!id) return;
				
				admin = ADMINS[id-1];
				if(!admin.id) printf("Admin inexistente, tente novamente: ");
				else if(admin.id == 1) printf("Nao e possivel deletar o admin inicial, tente novamente: ");
				else if(admin.id == SESSION_ID) printf("Voce nao pode se deletar, tente novamente: ");
				else break;
			}
			cabecalho();
			printf("Voce esta prestes a deletar %s, tem certeza?\nDigite S para confirmar: ", admin.nome);
			scanf("%c", &confirma);
			if(confirma != 'S') return;
			
			deletarAdmin(id);
			printf("Professor deletado com sucesso");
			esperar();
			break;
	}
}
void admEditar(){
	int permissao = admPedirNivelDePermissao(0);
	
	switch(permissao){
		Aluno aluno;
		Professor professor;
		Admin admin;
		int id, opcao;
		case 1:
			for(int i = 0; i < MAXN; i++){
				aluno = ALUNOS[i];
				if(!aluno.id) continue;
				
				printf("\n%d - %s - %d%c", aluno.id, aluno.nome, aluno.ano, aluno.turma);
			}
			printf("\n\nEscolha um id para editar (0 volta): ");
			while(1){
				scanf("%d", &id);
				getchar();
				if(!id) return;
				
				aluno = ALUNOS[id-1];
				if(!aluno.id) printf("Alun@ inexistente, tente novamente: ");
				else break;
			}
			
			cabecalho();
			printf("\n1 - Nome: %s", aluno.nome);
			printf("\n2 - Turma: %d%c", aluno.ano, aluno.turma);
			printf("\nQual deseja alterar? ");
			while(1){
				scanf("%d", &opcao);
				getchar();
				if(opcao == 1 || opcao == 2) break;
				if(!opcao) return;
				printf("Tente novamente: ");
			}
			cabecalho();
			if(opcao == 1){
				char nomeNovo[NAME_SIZE];
				printf("Nome atual: %s\n", aluno.nome);
				printf("Nome novo: ");
				while(1){
					scanf("%s", nomeNovo);
					getchar();
					if(buscarAluno(nomeNovo)) printf("O nome inserido ja existe\n");
					else if(strlen(nomeNovo) >= 3) break;
					printf("Tente novamente: ");
				}
				
				strcpy(aluno.nome, nomeNovo);
			} else if(opcao == 2){
				int ano; char turma;
				printf("Turma atual: %d%c\n", aluno.ano, aluno.turma);
				printf("Turma nova: ");
				while(1){
					if(!scanf("%d%c", &ano, &turma)){
						printf("Input invalido, tente novamente: ");
						continue;
					};
					getchar();
					
					Aluno alunos[MAXN];
					int tamanho = preencherTurma(ano, turma, alunos);
					if(tamanho >= 40) printf("Turma %d%c cheia, escolha outra: ", ano, turma);
					if(!tamanho){
						printf("Turma %d%c inexistente, digite S para cria-la: ", ano, turma);
						if(getchar() == 'S') break;
						else printf("Digite outra turma: ");
						while(getchar() != '\n');
					}
				}
				
				aluno.ano = ano;
				aluno.turma = turma;
			}
			
			cabecalho();
			ALUNOS[id-1] = aluno;
			printf("Aluno alterado com sucesso");
			esperar();
			break;
		case 2:
			for(int i = 0; i < MAXN; i++){
				professor = PROFESSORES[i];
				if(!professor.id) continue;
				
				printf("\n%d - %s - %s", professor.id, professor.nome, professor.materia);
			}
			printf("\n\nEscolha um id para editar (0 volta): ");
			while(1){
				scanf("%d", &id);
				getchar();
				if(!id) return;
				
				professor = PROFESSORES[id-1];
				if(!professor.id) printf("Professor inexistente, tente novamente: ");
				else break;
			}
			
			cabecalho();
			printf("\n1 - Nome: %s", professor.nome);
			printf("\n2 - Materia: %s", professor.materia);
			printf("\nQual deseja alterar? ");
			while(1){
				scanf("%d", &opcao);
				getchar();
				if(opcao == 1 || opcao == 2) break;
				if(!opcao) return;
				printf("Tente novamente: ");
			}
			
			cabecalho();
			if(opcao == 1){
				char nomeNovo[NAME_SIZE];
				printf("Nome atual: %s\n", professor.nome);
				printf("Nome novo: ");
				while(1){
					scanf("%s", nomeNovo);
					getchar();
					if(buscarProfessor(nomeNovo)) printf("O nome inserido ja existe\n");
					else if(strlen(nomeNovo) >= 3) break;
					printf("Tente novamente: ");
				}
				
				strcpy(professor.nome, nomeNovo);
			} else if(opcao == 2){
				char materiaNova[4];
				printf("Materia atual: %s\n", professor.materia);
				printf("Materia nova: ");
				while(1){
					scanf("%s", materiaNova);
					getchar();
					if(strlen(materiaNova) == 3 && !strchr(materiaNova, ' ')) break;
					printf("Tente novamente: ");
				}
				
				strcpy(professor.materia, materiaNova);
			}
			
			cabecalho();
			PROFESSORES[id-1] = professor;
			printf("Professor alterado com sucesso");
			esperar();
			break;
	}
}

int admPedirNivelDePermissao(int admin){
	cabecalho();
	printf("Qual o nivel de permissao do usuario?\n");
	printf("0 - Voltar\n");
	printf("1 - Aluno\n");
	printf("2 - Professor\n");
	if(admin) printf("3 - Admin\n");
	
	int opcao;
	if(!scanf("%d", &opcao) || !(opcao >= 1 && opcao <= admin ? 3 : 2)) opcao = 0;
	return opcao;
}

void mostrarMenuAdmin(){
	Admin usuario = ADMINS[SESSION_ID - 1];
	
	int opcao = 1;
	
	do {
		cabecalho();
		printf("Bem-vindo, %s, o que você quer fazer hoje?\n", usuario.nome);
		printf("0 - sair\n");
		printf("1 - ver professores\n");
		printf("2 - ver alunos\n");
		printf("3 - ver turmas\n");
		printf("4 - cadastrar usuario\n");
		printf("5 - deletar usuario\n");
		printf("6 - editar dados de um usuario\n");
		printf("7 - alterar senha\n");
		
		scanf("%d", &opcao);
		getchar();
		
		switch(opcao){
			char senha[PASS_SIZE], senhaNova[PASS_SIZE], senhaNovaConfirmar[PASS_SIZE];
			case 0:
				cabecalho();
				printf("Saindo...");
				sobrescreverDatabase();
				break;
			case 1:
				admListarProfessores();
				break;
			case 2:
				admListarAlunos();
				break;
			case 3:
				admListarTurmas();
				break;
			case 4:
				admCadastrar();
				break;
			case 5:
				admDeletar();
				break;
			case 6:
				admEditar();
				break;
			case 7:
				printf("Digite sua senha atual: ");
				scanf("%s", senha);
				getchar();
				
				if(validarAdmin(SESSION_ID, senha)){
					cabecalho();
					while(1){
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
							ADMINS[SESSION_ID-1].senha = criptografar(senhaNova);
							printf("Senha alterada com sucesso");
							break;
						} else {
							cabecalho();
							printf("As duas senhas nao batem, tente novamente\n");
						}
					}
				}
				break;
		}
	} while(opcao);
	
	return;
}