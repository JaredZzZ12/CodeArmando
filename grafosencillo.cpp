#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

int main()
{
int opcion;

cout << "1. Grafo 4x4" << endl;
cout << "2. Grafo 8x8" << endl;
cout << "3. Grafo 16x16" << endl;
cout << "Opcion: ";
cin >> opcion;

cout << endl;


string archivos[4] = {"", "grafo_4x4.txt", "grafo_8x8.txt", "grafo_16x16.txt"};
int tamanios[4] = {0, 4, 8, 16};


if (opcion < 1 || opcion > 3)
{
	cout << "ERROR: Opcion no valida." << endl;
	return 0;
}

int tamanio = tamanios[opcion];
string archivo_nombre = archivos[opcion];


int **grafo = new int*[tamanio];
for (int i = 0; i < tamanio; i++)
{
	grafo[i] = new int[tamanio];
}

ifstream archivo("/home/jared/programasc++/grafo8x8.txt");

if (!archivo.is_open())
{
	cout << "ERROR: No se pudo abrir " << archivo_nombre << endl;
	return 0;
}

cout << "Leyendo grafo desde: " << archivo_nombre << endl << endl;

for (int i = 0; i < tamanio; i++)
{
	for (int j = 0; j < tamanio; j++)
	{
		archivo >> grafo[i][j];
	}
}
archivo.close();


cout << "Grafo actual:" << endl;
for (int i = 0; i < tamanio; i++)
{
	for (int j = 0; j < tamanio; j++)
	{
		cout << grafo[i][j] << " ";
	}
	cout << endl;
}
cout << endl;


int fila, columna, valor;
int valido = 0;

while (valido == 0)
{
	cout << "Cambio de grafo: Escoja una posicion" << endl;
	cout << "Fila (0 a " << tamanio - 1 << "): ";
	cin >> fila;
	cout << "Columna (0 a " << tamanio - 1 << "): ";
	cin >> columna;
	cout << "Valor (0 o 1): ";
	cin >> valor;
	
	if (fila < 0 || fila >= tamanio || columna < 0 || columna >= tamanio)
	{
		cout << "ERROR: Fila o columna fuera de rango. Intente de nuevo." << endl << endl;
		continue;
	}
	
	if (valor != 0 && valor != 1)
	{
		cout << "ERROR: Ingrese solo 0 o 1. Intente de nuevo." << endl << endl;
		continue;
	}
	
	valido = 1;
}


grafo[fila][columna] = valor;

cout << endl;
cout << "Grafo modificado en posicion [" << fila << "][" << columna << "] = " << valor << endl << endl;

cout << "Grafo actualizado:" << endl;
for (int i = 0; i < tamanio; i++)
{
	for (int j = 0; j < tamanio; j++)
	{
		cout << grafo[i][j] << " ";
	}
	cout << endl;
}
cout << endl;


cout << "Matriz de adyacencia (conexiones):" << endl;
cout << "=================================" << endl;

for (int i = 0; i < tamanio; i++)
{
	for (int j = 0; j < tamanio; j++)
	{
		if (grafo[i][j] == 1)
		{
			char nodoA = 'A' + i;
			char nodoB = 'A' + j;
			cout << nodoA << " conectado con " << nodoB << endl;
		}
	}
}
cout << "=================================" << endl << endl;


char nodoPrimero = 'A';
char nodoUltimo = 'A' + (tamanio - 1);

cout << "Ruta del primer punto (" << nodoPrimero << ") al ultimo punto (" << nodoUltimo << "):" << endl;
cout << "=================================" << endl;

cout << nodoPrimero;

int nodoActual = 0;
int visitados[20] = {0};
visitados[0] = 1;

for (int paso = 0; paso < tamanio - 1; paso++)
{
	int siguienteNodo = -1;
	
	for (int j = nodoActual + 1; j < tamanio; j++)
	{
		if (grafo[nodoActual][j] == 1 && visitados[j] == 0)
		{
			siguienteNodo = j;
			break;
		}
	}
	
	if (siguienteNodo == -1)
	{
		for (int j = 0; j < nodoActual; j++)
		{
			if (grafo[nodoActual][j] == 1 && visitados[j] == 0)
			{
				siguienteNodo = j;
				break;
			}
		}
	}
	
	if (siguienteNodo != -1)
	{
		cout << " -> " << (char)('A' + siguienteNodo);
		visitados[siguienteNodo] = 1;
		nodoActual = siguienteNodo;
	}
}

cout << endl;
cout << "=================================" << endl << endl;

cout << "CAMINO MAS CORTO (Búsqueda en Amplitud):" << endl;
cout << "=================================" << endl;

int padre[20];
int distancia[20];
int visitadosBFS[20] = {0};

for (int i = 0; i < tamanio; i++)
{
	padre[i] = -1;
	distancia[i] = -1;
}


queue<int> cola;
cola.push(0);
visitadosBFS[0] = 1;
distancia[0] = 0;

while (!cola.empty())
{
	int nodo = cola.front();
	cola.pop();
	
	for (int j = 0; j < tamanio; j++)
	{
		if (grafo[nodo][j] == 1 && visitadosBFS[j] == 0)
		{
			visitadosBFS[j] = 1;
			distancia[j] = distancia[nodo] + 1;
			padre[j] = nodo;
			cola.push(j);
		}
	}
}


int caminoCorto[20];
int longitud = 0;

if (distancia[tamanio - 1] == -1)
{
	cout << "NO HAY CAMINO POSIBLE" << endl;
}
else
{
	int nodo = tamanio - 1;
	
	while (nodo != -1)
	{
		caminoCorto[longitud] = nodo;
		longitud++;
		nodo = padre[nodo];
	}
	
	
	for (int i = longitud - 1; i >= 0; i--)
	{
		cout << (char)('A' + caminoCorto[i]);
		if (i > 0) cout << " -> ";
	}
	cout << endl;
	cout << "Distancia: " << distancia[tamanio - 1] << " pasos" << endl;
}

cout << "=================================" << endl;


for (int i = 0; i < tamanio; i++)
{
	delete[] grafo[i];
}
delete[] grafo;

return 0;
}