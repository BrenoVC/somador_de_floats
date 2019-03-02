/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>

/* Maquina de estados:
 * Detecta se existe ao menos um numero inteiro na linha inserida */

int eh_digito(char c)
{
  if ((c >= '0') && (c <= '9')) return 1;
  else return 0;
}

typedef struct {
  int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */

int opera_fsm(void *this_fsm, char entrada) {
  Fsm maquina = (Fsm) this_fsm;

  switch (maquina->estado_atual) {
    case 0:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 3;
      } else if (entrada == '-') {
        maquina->estado_atual = 2;
      } else if (entrada != ' ') {
        maquina->estado_atual = 1;
      }
      break;

    case 1:
      if (entrada == ' ') {
        maquina->estado_atual = 0;
      }
      break;
    
    case 2:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 2;
      } else {
        maquina->estado_atual = 1;
      }
      break;
      
    case 3:
      if (entrada == ' ' || entrada == '\n') {
        maquina->estado_atual = 6;
      } else if(entrada == '.') {
        maquina->estado_atual = 4;
      } else if(!eh_digito(entrada)) {
        maquina->estado_atual = 1;
      }
      break;

    case 4:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 5;
      } else if (entrada == ' ') {
        maquina->estado_atual = 0;
      } else {
        maquina->estado_atual = 1;
      }
      break;
    
    case 5:
      if (!eh_digito(entrada) && entrada != ' ' && entrada != '\n') {
        maquina->estado_atual = 0;
      } else if(entrada == ' ' || entrada == '\n'){
        maquina->estado_atual = 6;
      }
      break;

    case 6:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 3;
      } else if (entrada == '-') {
        maquina->estado_atual = 2;
      } else if (entrada != ' ') {
        maquina->estado_atual = 1;
      } else {
        maquina->estado_atual = 0;
      }
      break;
  }
  return (maquina->estado_atual);
}

int main() {
  char buffer_in[100];
  char number_found[100];
  int pointer;
  int ind_number_found;
  char c;
  float floats_sum;

  for (int i=0; i<100; i++) buffer_in[i] = '\0';
  for (int i=0; i<100; i++) number_found[i] = '\0';

  pointer = 0;
  do {
    c=getchar();
    buffer_in[pointer++] = c;
  } while (c != '\n');

  fsm maquina;
  maquina.estado_atual = 0;

  pointer = 0;
  ind_number_found = 0;
  floats_sum = 0;

  while (buffer_in[pointer] != '\0') {
    opera_fsm((void*) (&maquina), buffer_in[pointer]);
    if (maquina.estado_atual != 0 && maquina.estado_atual != 1) {
      if (maquina.estado_atual == 6) {
        char number[ind_number_found];
        for (int i=0; i<ind_number_found; i++) {
          number[i] = number_found[i];
        }
        float fnumber = atof(number);
        floats_sum += fnumber;
        for (int i=0; i<100; i++) number_found[i] = '\0';
        ind_number_found = 0;
      } else {
        number_found[ind_number_found] =  buffer_in[pointer];
        ind_number_found++;
      }
    } else {
      for (int i=0; i<100; i++) number_found[i] = '\0';
      ind_number_found = 0;
    }
    pointer++;
  }

  printf("%.6g\n", floats_sum);
  return 0;
}
