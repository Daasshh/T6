// TASK_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

struct supermarket
{
	int flag; //что лежит в структуре, если =0 то десерты, если=1 то напитки
	union { // Объединения также хранят набор элементов, но что разные элементы занимают в памяти один и тот же участок.
		struct //определена структура, которая имеет два элемента
		{
			char* desserts = NULL;
			char* data = NULL;
		} desserts; //набор переменных
		struct
		{
			char* drinks = NULL;
			char* capacityOfDrink = NULL;
		} drinks;
	};supermarket() {};// конструктор для структуры
};

char* input(char* obj) { //нужен, чтобы вводить в конструктор массив char
	char c;
	char b;
	int len = 1;
	obj = (char*)malloc(sizeof(char));//malloc предоставляет ячейку памяти, создает указатель на нее и возвращает его
	while (((c = getchar()) != '\n')) //sizeof(char) – размер одного элемента массива. Считывает последовательно вводимые команды
	{
		obj[len - 1] = c;
		len++;
		obj = (char*)realloc(obj, len * sizeof(char));// динамически увеличивает массив
	}
	obj[len - 1] = '\0';// закрытие
	return obj;
}

void add(char* base, int* count, supermarket* sup) {//добавоение элементов в структуру, count- сколько эл-тов в структуре на данный момент
	if (strcmp(base, "desserts") == 0) // сравниввем на соответствие 
	{
		printf("Какой десерт вы хотите добавить?\n");
		sup[*count].desserts.desserts = input(sup[*count].desserts.desserts); //чтобы обратиться к полям вложенной структуры, обращаемся к самой этой структуре
		printf("Введите срок годности без пробелов: ");
		sup[*count].desserts.data = input(sup[*count].desserts.data);
		sup[*count].flag = 0;
		(*count)++;
	}
	else if (strcmp(base, "drinks") == 0)
	{
		printf("Какой напиток вы хотите доабавить?\n");
		sup[*count].drinks.drinks = input(sup[*count].drinks.drinks);
		printf("Введите ёмкость напитка без пробелов: ");
		sup[*count].drinks.capacityOfDrink = input(sup[*count].drinks.capacityOfDrink);
		sup[*count].flag = 1;
		(*count)++;
	}
}

void del(char* base, char* obj, supermarket* sup, int* count) {// удаление объектов, count передает указатель
	for (int i = 0; i < *count; i++) {
		if (sup[i].flag == 0 && strcmp(base, "desserts") == 0 && strcmp(obj, sup[i].desserts.desserts) == 0) {// сравниваем на соответствие строк
			for (int j = i; j < *count - 1; j++) { //ищем введеный объект 
				strcpy_s(sup[j].desserts.desserts, strlen(sup[j + 1].desserts.desserts) + 1, sup[j + 1].desserts.desserts); //Функция копирует содержимое в адрес str. возвращает длину строки, оканчивающейся нулевым символом, на которую указывает str.
				strcpy_s(sup[j].desserts.data, strlen(sup[j + 1].desserts.data) + 1, sup[j + 1].desserts.data);
				if (sup[j + 1].flag == 0) { //проверка на flag, который стоит в последующих эл-тах
					sup[j].flag = 0;
				}
				else {
					sup[j].flag = 1;
				}
			}
			delete sup[(*count) - 1].desserts.desserts;
			delete sup[(*count) - 1].desserts.data;
			(*count)--; // сдвигаем для удаления
			break;
		}
		else if (sup[i].flag == 1 && strcmp(base, "drinks") == 0 && strcmp(obj, sup[i].drinks.drinks) == 0) {
			for (int j = i; j < *count - 1; j++) {
				strcpy_s(sup[j].drinks.drinks, strlen(sup[j + 1].drinks.drinks) + 1, sup[j + 1].drinks.drinks);
				strcpy_s(sup[j].drinks.capacityOfDrink, strlen(sup[j + 1].drinks.capacityOfDrink) + 1, sup[j + 1].drinks.capacityOfDrink);
				if (sup[j + 1].flag == 1) {
					sup[j].flag = 1;
				}
				else {
					sup[j].flag = 0;
				}
			}
			delete sup[(*count) - 1].drinks.drinks;
			delete sup[(*count) - 1].drinks.capacityOfDrink;
			(*count)--;
			break;
		}
	}
}

void print(supermarket* sup, char* base, int count) {
	int counter = 0;
	for (int i = 0; i < count; i++) {
		if (sup[i].flag == 0 && strcmp(base, "desserts") == 0) {
			printf("Название десерта[%d]: %s \n", counter, sup[i].desserts.desserts);
			printf("Срок годности: %s \n", sup[i].desserts.data);
			counter++;
		}
		else if (sup[i].flag == 1 && strcmp(base, "drinks") == 0) {
			printf("Название напитка[%d] %s \n", counter, sup[i].drinks.drinks);
			printf("Ёмкость: %s \n", sup[i].drinks.capacityOfDrink);
			counter++;
		}
	}
	if (counter == 0) {
		printf("База данных пуста. \n");
	}
}

void main()
{
	setlocale(LC_ALL, "Rus");
	supermarket* mySup = (supermarket*)malloc(sizeof(supermarket));
	int i = 0;
	int count = 0;
	while (i == 0)
	{
		printf("Что вы хотите сделать: add, del, print или end работу?\n");
		char* act = NULL;
		act = input(act);
		char* base = NULL;
		if (strcmp(act, "add") == 0)
		{
			printf("В какую базу данных вы хотите добавить: desserts, drinks\n");
			base = input(base);
			mySup = (supermarket*)realloc(mySup, sizeof(supermarket) * (count + 1));
			add(base, &count, mySup);
			delete[] act;
			delete[] base;
		}
		else if (strcmp(act, "del") == 0)
		{
			printf("Из какой базы данных вы хотите удалить: desserts, drinks\n");
			base = input(base);
			printf("Введите объект, который вы хотите удалить: ");
			char* object = NULL;
			object = input(object);
			del(base, object, mySup, &count);
			delete[] act;
			delete[] object;
			delete[] base;
		}
		else if (strcmp(act, "print") == 0)
		{
			printf("Из какой базы данных вы хотите вывести: desserts, drinks\n");
			base = input(base);
			print(mySup, base, count);
			delete[] act;
			delete[] base;
		}
		else if (strcmp(act, "end") == 0)
		{
			delete[] act;
			delete[] base;
			delete[] mySup;
			i = -1;
		}
		else {
			printf("Такой команды не существует.\n");
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
