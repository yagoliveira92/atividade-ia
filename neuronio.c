/*
 * neuronio.c
 *
 * Copyright 2020 Yago Oliveira <yagoliveira92@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * Este programa apenas calcula os pesos para a atividade prática de IA
 * na UNINTER. Ele apenas treina para obtenção dos pesos e calcula a quantidade
 * de passos. Qualquer PR para inserção do RU em forma de matriz direto 
 * como arquivo será extremamente bem vindo.
 *
 *
 */

#include <stdio.h>

float defineIntermediario(float saidaI, int *amostra, float *pesos, int w0);
void defineDelta(float *delta, int *amostra, float taxaAprendizado, int *erro);
int defineErro(int fatorAtual, int objetivo);
int defineFatorAtual(float saidaIntermediaria);
float defineMediaDelta (float *delta);

int main(int argc, char **argv)
{
	/*
	 * Aqui temos os Xi citados na atividade. Cada coluna dessa matriz
	 * equivale a uma amostra, ou seja, um RU.
	 */
	int x1[7] = {3,1,3,3,3,9,3};
	int x2[7] = {0,2,0,0,0,0,0};
	int x3[7] = {0,3,0,7,0,9,0};
	int x4[7] = {7,4,7,5,7,7,7};
	int x5[7] = {5,5,5,7,5,9,5};
	int x6[7] = {9,6,9,9,9,5,9};
	int x7[7] = {0,7,0,7,0,9,0};
	
	/*
	 * Pesos utilizado nas amostras
	 */

	float pesos[7] = {1,1,1,1,1,1,1};
	
	/*
	 * Cada delta equivale a um Xi lá acima. Fiz isso pois:
	 * 1- Vacilita visualização
	 * 2- Melhora o Debug do que trabalhar com matriz
	 */

	float delta1[7];
	float delta2[7];
	float delta3[7];
	float delta4[7];
	float delta5[7];
	float delta6[7];
	float delta7[7];
	
	/*
	 * Variável que informa se há erro ainda ou não. Usado no laço
	 * de repetição do cálculo
	 */
	int temErro = 1;

	/*
	 * Constante do valor da taxa de aprendizado
	 */
	float taxaAprendizado = 0.01;
	
	/*
	 * Valor de ajuste fino 
	 */
	int w0 = -1;
	
	/*
	 * Saída intermediária usada no cálculo de Delta
	 */
	float saidaIntermediaria1 = 0;
	float saidaIntermediaria2 = 0;
	float saidaIntermediaria3 = 0;
	float saidaIntermediaria4 = 0;
	float saidaIntermediaria5 = 0;
	float saidaIntermediaria6 = 0;
	float saidaIntermediaria7 = 0;
	
	/*
	 * Variáveis que armazenam o valor das médias obtidas no delta
	 */
	float mediaDelta1 = 0;
	float mediaDelta2 = 0;
	float mediaDelta3 = 0;
	float mediaDelta4 = 0;
	float mediaDelta5 = 0;
	float mediaDelta6 = 0;
	float mediaDelta7 = 0;

	/*Contador de passos*/
	int passo = 1;

	int i1 = 0;
	int k = 0;

	/*Arrays que armazenam o estado atual do cálculo e o objetivo.*/
	int fatorAtual[7] = {1,1,1,1,1,1,1};
	int objetivo[7] = {1,-1,1,-1,1,-1,1};

	/*Array que armazena os erros*/
	int erro[7] = {0,0,0,0,0,0,0};
	
	/*Laço que calcula os pesos e compara. 
	 * Primeiro define os intermediários com a saída anterior,
	 * depois ele atribui os fatores fatores atuais em cada Xi e
	 * por fim calcula se esse fator atende a necessidade, caso sim ele 
	 * prossegue mas sai do laço, imprimindo o passo.
	 * Se não ele refaz os cálculos e retorna o laço
	 */
	do 
		{
			saidaIntermediaria1 = defineIntermediario(saidaIntermediaria1, x1, pesos, w0);
			saidaIntermediaria2 = defineIntermediario(saidaIntermediaria2, x2, pesos, w0);
			saidaIntermediaria3 = defineIntermediario(saidaIntermediaria3, x3, pesos, w0);
			saidaIntermediaria4 = defineIntermediario(saidaIntermediaria4, x4, pesos, w0);
			saidaIntermediaria5 = defineIntermediario(saidaIntermediaria5, x5, pesos, w0);
			saidaIntermediaria6 = defineIntermediario(saidaIntermediaria6, x6, pesos, w0);
			saidaIntermediaria7 = defineIntermediario(saidaIntermediaria7, x7, pesos, w0);
			
			fatorAtual[0] = defineFatorAtual(saidaIntermediaria1);
			fatorAtual[1] = defineFatorAtual(saidaIntermediaria2);
			fatorAtual[2] = defineFatorAtual(saidaIntermediaria3);
			fatorAtual[3] = defineFatorAtual(saidaIntermediaria4);
			fatorAtual[4] = defineFatorAtual(saidaIntermediaria5);
			fatorAtual[5] = defineFatorAtual(saidaIntermediaria6);
			fatorAtual[6] = defineFatorAtual(saidaIntermediaria7);
			
			for (i1 = 0; i1 < 7; i1++) {
				erro[i1] = defineErro(fatorAtual[i1], objetivo[i1]);
			};
			
			if (erro[0] == 0 && erro[1] == 0 && erro[2] == 0 && erro[3] == 0 && erro[4] == 0 && erro[5] == 0 && erro[6] == 0) {
				temErro = 0;
			}
			
			defineDelta(delta1, x1, taxaAprendizado, erro);
			defineDelta(delta2, x2, taxaAprendizado, erro);
			defineDelta(delta3, x3, taxaAprendizado, erro);
			defineDelta(delta4, x4, taxaAprendizado, erro);
			defineDelta(delta5, x5, taxaAprendizado, erro);
			defineDelta(delta6, x6, taxaAprendizado, erro);
			defineDelta(delta7, x7, taxaAprendizado, erro);
			
			mediaDelta1 = defineMediaDelta(delta1);
			mediaDelta2 = defineMediaDelta(delta2);
			mediaDelta3 = defineMediaDelta(delta3);
			mediaDelta4 = defineMediaDelta(delta4);
			mediaDelta5 = defineMediaDelta(delta5);
			mediaDelta6 = defineMediaDelta(delta6);
			mediaDelta7 = defineMediaDelta(delta7);
			
			pesos[0] = pesos[0] - mediaDelta1;
			pesos[1] = pesos[1] - mediaDelta2;
			pesos[2] = pesos[2] - mediaDelta3;
			pesos[3] = pesos[3] - mediaDelta4;
			pesos[4] = pesos[4] - mediaDelta5;
			pesos[5] = pesos[5] - mediaDelta6;
			pesos[6] = pesos[6] - mediaDelta7;
			
			passo = passo + 1;
			
			for (k = 0; k < 7; k++) {
				printf("Este aqui são os pesos calculados: %f", pesos[k]);
				printf("\n");
				printf("Este aqui é a quantidade de passos: %d", passo);
				printf("\n");
			};
		
		}while (temErro != 0);
}

float defineIntermediario(float saidaI, int *amostra, float *pesos, int w0) {

	int i = 0;
	float temporaria = saidaI;
	for (i = 0; i < 7; i++) {
		temporaria = temporaria + amostra[i]*pesos[i];
	};
	saidaI = temporaria+w0;
	return saidaI;

}

int defineFatorAtual(float saidaIntermediaria) {
	int retorno = 0;
	if (saidaIntermediaria > 0) {
		retorno = 1;		
	} else {
		retorno = -1;
	};
	return retorno;
}

int defineErro(int fatorAtual, int objetivo) {
	int erro = objetivo - fatorAtual;
	return erro*(-1);
}

void defineDelta(float *delta, int *amostra, float taxaAprendizado, int *erro) {
	
	int i;
	
	for (i=0; i<7; i++) {
		delta[i] = erro[i]*taxaAprendizado*amostra[i];
	};

}

float defineMediaDelta (float *delta) {
	float somaDelta = 0;
	float media = 0;
	float invertida = 0;
	int j;
	for(j = 0; j < 7; j++) {
		somaDelta = somaDelta + delta[j];
	}
	
	media = somaDelta / 7;
	invertida = media;
	return invertida;
}


