#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

using namespace std;

void limpiar();
int pideCantidad();
int pideFilas();
int pidePaginas();
int pideVariables(int [], int, int *);
void comprueba(int);
void compruebaEstandar();
int calculaFila(int [], int, int);
int calculaPagina(int, int);
int calculaBD(int, int);
void resultado(int, int, int, int);
void proceso();
void compruebaChar(char *);


int main()
{
		char op;
	do
	{
		proceso();
		fflush(stdin);
		printf("¿Desea realizar otro cálculo? (s/n): ");
		scanf("%c", &op);
		op = tolower(op);
		compruebaChar(&op);
	}
	while(op == 's');

	printf("Gracias por utilizar la herramienta de Alfredo\n"
		"¡Hasta pronto!\n");

	return 0;
}

void limpiar()
{
#ifdef WIN32
    std::system("cls");
#else
    std::system ("clear");
#endif
}

void comprueba(int x)
{
	if (x <= 0 || x > 50)
	{
		limpiar();
		printf("Error. Introduce un número válido.\n");
	}
}

void compruebaEstandar(int x)
{
	if (x <= 0)
	{
		limpiar();
		printf("Error. Introduce un número válido.\t");
	}
}

void compruebaChar(char *op)
{
	while(*op != 's' && *op != 'n')
	{
		fflush(stdin);
		printf("Error. Elija una opción válida:\t");
		scanf("%s", op);
		*op = tolower(*op);
		printf("%c\n", *op);
	}
	limpiar();
}

void proceso()
{
	int pg = 0, fila = 0, bd = 0, cantidad, filas, pgs, regs, btexto = 0, contador;
	cantidad = pideCantidad();
	int variables[cantidad];

	filas = pideFilas();
	regs = pidePaginas();
	pgs = regs / filas;
	contador = pideVariables(variables, cantidad, &btexto);
	cantidad -= contador;
	limpiar();
	fila = calculaFila(variables, cantidad, btexto);
	pg = calculaPagina(fila, filas);
	bd = calculaBD(pg, pgs);
	getchar();
	resultado(fila, pg, bd, pgs);

}

int pideCantidad()
{
	int cantidad;
	do
	{
		printf("¿Cuántas variables serán?\t");
		scanf("%d", &cantidad);
		comprueba(cantidad);
	}
	while(cantidad <= 0 || cantidad > 50);
	return cantidad;
}

int pideFilas()
{
	int filas;
	do
	{
		printf("¿Cuántas filas serán por página?\t");
		scanf("%d", &filas);
		compruebaEstandar(filas);
	}
	while(filas <= 0);

	return filas;
}

int pidePaginas()
{
	int pgs;
	do
	{
		printf("¿Cuántas registros serán en total?\t");
		scanf("%d", &pgs);
		compruebaEstandar(pgs);
	}
	while(pgs <= 0);

	return pgs;
}

int pideVariables(int variables[], int cantidad, int *btexto)
{
	int var, i, contador = 0, aux;
	printf("%d\n", *btexto);
	for(i = 0; i < cantidad; i++)
	{
		do
		{
			limpiar();
			printf("Tipos de variables:\n1.\tEntero (integer).\n2.\tBoolean (0/1).\n"
			"3.\tSerial (counter).\n4.\tFecha (date).\n5.\tDouble.\n6.\tTexto (string).\n"
			"Introduce el tipo de variable #%d:\t", i+1);
			scanf("%d", &var);
			while (var <= 0 || var > 7)
			{
				printf("Error. Introduce un número válido.\t");
				scanf("%d", &var);
			}
			if(var == 6)
			{
				printf("¿De qué tamaño será el arreglo?\t");
				scanf("%d", &aux);
				while(aux <= 0)
				{
					compruebaEstandar(aux);
					scanf("%d", &aux);
				}
				*btexto = *btexto + aux;
				contador += 1;
			}
			else
				variables[i] = var;
		}
		while (var <= 0 || var > 7);
	}
	return contador;
}

int calculaFila(int variables[], int cantidad, int btexto)
{
	int vars[] = {4, 1, 8, 8, 8}, acum = 0, i;
	for (i = 0; i < cantidad; i++)
		acum += vars[(variables[i] - 1)];
	acum += btexto;
	return acum;
}

int calculaPagina(int fila, int filas)
{
	return fila * filas;
}

int calculaBD(int pg, int pgs)
{
	return pg * pgs;
}

void resultado(int fila, int pg, int bd, int pgs)
{
	limpiar();
	printf("Según mis calculos, tu base de datos (en el peor de los casos) "
		"tendrá un almacenamiento de %d bytes.\n\n"
		"Los resultados generales:\n1\tFila:\t%d bytes.\n1\tPágina:\t%d bytes.\n"
		"%d\tPáginas:\t%d bytes.\n\n", bd, fila, pg, pgs, bd);

}
