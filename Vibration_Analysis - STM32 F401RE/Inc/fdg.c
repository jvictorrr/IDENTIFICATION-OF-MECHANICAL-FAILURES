//Aluno: João Victor Rodrigues Ramalho
//Matrícula: 117100955
//Turma:
#include "biblioteca.h"
void ordem (uint8_t array[][SIZE], uint8_t i,uint16_t j);
void mostrar(uint8_t array[][SIZE], uint8_t i, uint16_t j);
void prencher_aleatoriamente(uint8_t array[][SIZE], uint8_t i, uint16_t j);
void func_central(uint8_t array[][SIZE], uint8_t i, uint16_t j);

int main()
{

uint8_t i;
uint16_t j;
uint8_t array[10][SIZE];
srand( (unsigned)time(NULL) );

func_central(array,i,j);







	return 0;
}
