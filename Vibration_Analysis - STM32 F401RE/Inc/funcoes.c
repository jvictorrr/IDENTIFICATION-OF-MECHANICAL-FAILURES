#include "biblioteca.h"

void ordem (uint8_t array[][SIZE], uint8_t i,uint16_t j)
{
	uint8_t aux;
	char bubble_fim = 'a';
	while(bubble_fim == 'a')
	{
		bubble_fim = ' b';
		for ( i = 0; i < COL; i++)
		{
			for( j = 0; j < SIZE - 1; j++)
			{

				if(array[i][j] > array[i][j + 1])
				{
					equal(aux, array[i][j]);
					equal(array[i][j], array[i][j + 1]);
					equal(array[i][j + 1] , aux);

					bubble_fim = 'a';
				}
			}
		}
	}
}
void mostrar(uint8_t array[][SIZE], uint8_t i, uint16_t j)
{
	for (i = 0; i < COL; i++)
	{
		for(j = 0; j <SIZE; j++)
		{
			printf("array[%d][%d]=%d\n", i,j, array[i][j]);
		}
	}
}
void prencher_aleatoriamente(uint8_t array[][SIZE], uint8_t i, uint16_t j)
{

	for (i = 0; i < COL; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			array[i][j] = (rand() % 100);

		}
	}
}
void func_central(uint8_t array[][SIZE], uint8_t i, uint16_t j){
	
	prencher_aleatoriamente(array, i, j);
	ordem (array, i,j);
	mostrar(array, i, j);

}

