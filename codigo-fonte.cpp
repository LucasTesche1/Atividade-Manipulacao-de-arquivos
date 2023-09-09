#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Calculando a media do aluno

float MediaAluno(float *notas, int numNotasAluno) {
    float soma = 0.0;
    for (int i = 0; i < numNotasAluno; i++) {
        soma += notas[i];
    }
    return soma / numNotasAluno;
}

int main() {
	
	//Abrindo um arquivo para Ler e o outro para Escrever
	
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
    	printf("-----------------------------\n");
        printf("Erro ao abrir arquivos, tente novamente.\n");
        printf("-----------------------------");
        
        return 1;
    }


	printf("--------------------------------------------------------------\n");
    printf("Estrutura dos dados do arquivo:\n");
    printf("Exemplo: 'Nome do Aluno' , 'Telefone' , 'Curso' , 'Notas'\n");
    printf("--------------------------------------------------------------\n");



    char linha[600];
    
	//Aqui separa os dados

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
    	
        char *nome, *telefone, *curso, *nota_str; 
        
        float notas[10]; 

        nome = strtok(linha, ",");
        telefone = strtok(NULL, ",");
        curso = strtok(NULL, ",");
        
        int numNotasAluno = 0;
        float nota;
        
        nota_str = strtok(NULL, ",");
        
        while (nota_str != NULL) {
            nota = atof(nota_str);
            notas[numNotasAluno++] = nota;
            nota_str = strtok(NULL, ",");
        }

		//Imprime no Terminal os dados dos alunos
	
        printf("\n-%s , %s , %s ", nome, telefone, curso);
        for (int i = 0; i < numNotasAluno; i++) {
            printf(" %.1f", notas[i]);
        }
        
        printf("\n");

        
        float media = MediaAluno(notas, numNotasAluno);

        
        const char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO";

        
        fprintf(saida, "%s, %.2f, %s\n", nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);
	
	//Imprimindo o laço for com resultados
	
	printf("\n---------------------------------------------------");
    printf("\nResultados finais em 'SituacaoFinal.csv':\n");
    printf("\nNome do Aluno , Media , Situacao\n");
    printf("---------------------------------------------------\n");

    saida = fopen("SituacaoFinal.csv", "r");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo, por favor, tente novamente.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), saida) != NULL) {
        printf("%s\n", linha);
    }

	printf("---------------------------------\n");
	printf("Arquivo 'SituacaoFinal.csv' criado! Por favor cheque sua pasta.\n");
	
    fclose(saida);

    return 0;
}
