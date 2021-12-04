//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996) 
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
typedef struct node { //описание элемента структуры item
	char type[100]; //численность населения
	char name[100]; //название города
	char coordinats[100]; //площадь города
	char description[100]; //главная достопримечательность
	struct node* next; //указатель на следующий элемент списка
}item;
typedef struct { //описание головного элемента структуры item
	int num; //количество элементов в списке
	item* first; //указатель на первый элемент списка
}hitem;
static int sort = 0; //глобальная переменная определяющая тип сортировки
void fon(int pos, int now) { //функция меняющая цвет написания текста и фона
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //извлечение дескриптора устройства стандартного вывода
	if (pos == now) {
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE |
			FOREGROUND_RED); //при совпадении входных данных цвет фона и текста меняется, что создает эффект выделения
	}
	else {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); //при несовпадении фон черный, текст белый, т.е.невыделенный
	}
}
void wait() { //функция ожидания нажатия клавиши Enter
	char key;
	fon(0, 1); //для обеспечения однородности фона будем использовать черный фон и белый цвет
	printf("\n\t\t\t\t*       -|Нажмите Enter для продолжения|-       *\t\t\t\t\n");
	printf("\t\t\t\t*                                               *\t\t\t\n");
	printf("\t\t\t\t*************************************************\t\t\t");
	do
		key = getch();
	while (key != 13); //ожидание нажатия Enter
}
void help() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);//функция вызова справки
	FILE* f;
	char p;
	fon(0, 1); //однородность фона
	if ((f = fopen("d://help.txt", "r")) == NULL) { //проверка на возможность открытия файла
		printf("\t\t\t\tСправка не готова"); //в случае невозможности вывод соответствующих сообщений
		wait();
		return;
	}
	while ((p = fgetc(f)) != EOF) { //посимвольное считывание из файла помощи
		printf("%c", p); //посимвольный вывод на экран
	}
	wait();
}
int convertation() { //функция конвертации для значений переменной типа int
	char* uk, input[15];

	int i, num;
	float check;
	gets(input); //ввод строки типа char
	fflush(stdin);
	if (strcmp(input, "exit") == 0) //если была введения строка exit
		return INT_MIN; //возвращаем минимальное значение типа int
	for (i = 0; i < strlen(input); i++) {
		if ((input[i] < '0' || input[i] > '9') && (input[i] != ' ')) //если хотя бы один элемент строки не является числом или пробелом
			return -1; //возврашаем -1
	}
	uk = strtok(input, " "); //делим строку на лексемы
	if (strtok(NULL, " ") != NULL) //если существуют две лексемы,
		return -1; //возвращаем -1
	check = (float)atof(uk); //переводим строку к типу float
	if (check > INT_MAX) //если вещественное число больше чем масимальное значение типа int
		return -1; //возвращаем -1
	num = (int)check; //приведением типов получаем число типа int
	return num; //возвращаем полученное число типа int
}
void welcome() { //Функция вывода приветственного сообщения
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	fon(0, 1);
	printf("\t\t\t\t*************************************************\n");
	printf("\t\t\t\t*---------Информационно-поисковая система-------*\t\t\t\t\n");
	printf("\t\t\t\t*             <<Города Беларуси>>               *\t\t\t\t\n");
	printf("\t\t\t\t*                 Lopukh V.A.                   *\t\t\t\n");
	printf("\t\t\t\t*                                               *\t\t\t");
	wait();
}
int menu(hitem* head) { //функция вывода меню
	char key;
	int i = 1;

	while (1) {
		system("cls");
		fon(0, 1); //однородность фона
		printf("\t\t\t\t*************************************************\n");
		printf("\t\t\t\t*---------Информационно-поисковая система-------*\t\t\t\t\n");
		printf("\t\t\t\t*             <<Города Беларуси>>               *\t\t\t\t\n");
		printf("\t\t\t\t*                                               *\t\t\t\n");
		fon(1, i); //если i равно значению передаваемому перед i выделяем следующую введенную строку, иначе не выделяем
		printf("\t\t\t\t*              ~Добавить город~                 *\n");
		fon(2, i);
		printf("\t\t\t\t*              ~Удалить  город~                 *\n");
		fon(3, i);
		printf("\t\t\t\t*               ~Найти город~                   *\n");
		fon(4, i);
		printf("\t\t\t\t*           ~Редактировать города~              *\n");
		fon(5, i);
		printf("\t\t\t\t*            ~Показать все города~              *\n");
		fon(6, i);
		//printf("\t\t\t\t*              Сортировка:                      *\n");
		(sort == 1); //Вывод типа сортировки: 0 - по типу, 1 - по имени

		//fon(7, i);
		printf("\t\t\t\t*                  Помощь                       *\n");
		fon(7, i);
		printf("\t\t\t\t*                  Выход                        *");
		fon(0, 1); //для того, чтобы количество элементов не закрашивалось
		printf("\n\n\t\t\t\t*         [База содержит %d элементов]           *\n", head->num); //вывод количества элементов в списке
		printf("\t\t\t\t*************************************************\n");
		do
			key = getch();
		while (key != 72 && key != 80 && key != 13); //ожидание клавиши Enter или стрелок Вверх или Вниз

		if (key == 72) { //если нажата стрелка Вверх
			i--;
			if (i == 0) //если i = 0
				i = 8; //переносим выделение на последний элемент
		}
		if (key == 80) { //если нажата стрелка вниз
			i++; //увеличиваем значение i
			if (i == 9) //если i = 9
				i = 1; //переносим выделение на первый элемент
		}
		if (key == 13) //если нажата клавиша Enter
			return i; //возвращаем i
	}
}
hitem* initialize() { //инициализация головного элемента
	hitem* head;
	if ((head = (hitem*)malloc(sizeof(hitem))) == NULL) { //выделение памяти для головного элемента
		printf("Недостаточно памяти");
		wait();
		return 0;
	}
	head->first = NULL; //указатель на первый элемент указывает в NULL
	head->num = 0; //количество элементов равно 0
	return head;
}
hitem* sorting(hitem* head) { //функция сортировки
	item* now, * prevnow, * first, * sorted, * prevsorted;
	int swap, i, stop;
	if (head->num < 2) //если элементов всего 0 или 1 значит отсортировано
		return head;

	now = head->first->next;
	first = head->first;
	prevnow = head->first;
	if (sort == 1) //если сортировка осуществляется по названию
		while (now != NULL) { //метод вставок
			swap = 0;
			stop = 0;
			sorted = first;
			prevsorted = NULL;
			while (sorted != now) {
				for (i = 0; i < strlen(now->name); i++) {
					if (now->name[i] < sorted->name[i]) {
						prevnow->next = now->next;
						now->next = sorted;
						if (prevsorted != NULL)
							prevsorted->next = now;
						else
							first = now;
						now = prevnow->next;
						prevsorted = NULL;
						swap = 1;
						stop = 2;
						break;
					}
					if (now->name[i] > sorted->name[i]) {
						prevsorted = sorted;
						sorted = sorted->next;
						stop = 1;
						break;
					}
				}
				if (stop == 1) {
					stop = 0;
					continue;
				}
				if (stop == 2)
					break;
				if (strlen(now->name) <= strlen(sorted->name)) {
					prevnow->next = now->next;
					now->next = sorted;
					if (prevsorted != NULL)
						prevsorted->next = now;
					else
						first = now;
					now = prevnow->next;
					prevsorted = NULL;
					swap = 1;
					break;
				}
				else {
					prevsorted = sorted;
					sorted = sorted->next;
				}
			}
			if (swap == 0) {
				prevnow = now;
				now = now->next;
			}
		}
	//if (sort == 0) //если сортировка осуществляется по численности
//		while (now != NULL) { //метод вставок
//			swap = 0;
	//		stop = 0;
		//	sorted = first;
			//prevsorted = NULL;
			//while (sorted != now) {
		//			for (i = 0; i < strlen(now->type); i++) {
			//			if (now->type[i] < sorted->type[i]) {
			//				prevnow->next = now->next;
				//			now->next = sorted;
					//		if (prevsorted != NULL)
						//		prevsorted->next = now;
							//else
							//	first = now;
							//now = prevnow->next;
				//			prevsorted = NULL;
					//		swap = 1;
						//	stop = 2;
							//break;
			//			}
				//		if (now->type[i] > sorted->type[i]) {
					//		prevsorted = sorted;
						//	sorted = sorted->next;
							//stop = 1;
						//	break;
						//}
					//}
	//			if (stop == 1) {
		//			stop = 0;
			//		continue;
				//}
	//			if (stop == 2)
		//			break;
			//	if (strlen(now->type) < strlen(sorted->type)) {
				//	prevnow->next = now->next;
					//now->next = sorted;
//					if (prevsorted != NULL)
	//					prevsorted->next = now;
		//			else
			//			first = now;
				//	now = prevnow->next;
					//prevsorted = NULL;
//					swap = 1;
	//				break;
		//		}
			//	else {
				//	prevsorted = sorted;
					//sorted = sorted->next;
//				}
	//		}
		//	if (swap == 0) {
			//	prevnow = now;
				//now = now->next;
		//	}
		//}
	head->first = first; //меняем указатель на первый элемент
	return head;
}
void algser(char crit[4], hitem* head) { //функция алгоритма поиска
	item* now;
	int i, stop = 0, num = 0;
	char word[50];
	system("cls");
	now = head->first;
	if ((strcmp(crit, "Численность")) == 0) { //если поиск по численности
		printf("Поиск: ");
		gets(word); //вводим искомое слово
		fflush(stdin);
		if (word[0] >= 'а' && word[0] <= 'а') //если вводимое имеет первую букву в нижнем регистре
			word[0] -= 32; //переводим её в верхний
		do {
			stop = 0;
			for (i = 0; i < strlen(word); i++)
				if (word[i] != now->type[i]) { //сравнение каждого элемента массива на равенство
					stop++; //если не равны то увеличиваем переменную stop
					break;
				}
			if (stop != 0) { //если не равны
				now = now->next; //переходим к следующему элементу
			}
			else { //иначе выводим элемент
				num++;
				printf("%d.\nЧисленность: ", num);
				for (i = 0; i <= strlen(now->type); i++) {
					printf("%c", now->type[i]);
				}
				printf("\n");
				printf("Название: ");
				for (i = 0; i <= strlen(now->name); i++) {
					printf("%c", now->name[i]);
				}
				printf("\n");
				printf("Площадь: ");
				for (i = 0; i <= strlen(now->coordinats); i++) {
					printf("%c", now->coordinats[i]);
				}
				printf("\n--------------------\n");
				now = now->next;
			}
		} while (now); //проделываем операции до тех пор пока now не равен NULL
	}


	if (num == 0) { //вывод сообщения, если элементы не были найдены
		printf("Город не найден.");
	}
	wait();
}
void treasure(hitem* head) { //функция поиска
	int i = 1;
	char key;
	if (head->num == 0) { //если нет элементов вывод соответствующего сообщения
		system("cls");
		fon(0, 1);
		printf("Empty base");
		wait();
		return;
	}
	while (1) { //вывод меню поиска, в котором выбирается критерия поиска
		system("cls");
		fon(0, i);
		printf("Категория поиска:\n\n");
		fon(1, i);
		printf("По численности\n");
		fon(3, i);
		printf("Назад\n");
		fon(4, i);
		do
			key = getch();
		while (key != 13 && key != 80 && key != 72); //ожидание клавиш Enter, стреки Вверх или Вниз
		if (key == 72) { //если стрелка вверх
			i--; //уменьшение i
			if (i == 0) //если i = 0
				i = 3; //переносим выделение в конец
		}
		if (key == 80) { //если стрелка вниз
			i++; //увеличение i
			if (i == 4) //если i = 4
				i = 1; //переносим выделение в начало
		}
		if (key == 13) //если Enter
			switch (i) { //В зависимости от текущего значения i
			case 1: { //Если i = 1
				algser("Численность", head); //Вызов алгоритма поиска по типу
				return; //Выходим из функции
			}
			case 2: { //Если i = 2
				algser("Название города", head); //Вызов алгоритма поиска по имени
				return; //Выходим из функции
			}
			case 3: //Если i = 3
				return; //Выходим из функции
			}
	}
}
hitem* add(hitem* head) { //функция добавления в список
	char name[100];
	char coordinats[100];
	char type[100];
	char description[100];
	int i, retry;
	item* newitem, * prev;
	system("cls");
	if ((newitem = (item*)malloc(sizeof(item))) == NULL) { //выделение памяти под новый элемент
		printf("Не достаточно памяти");
		wait();
		return head;
	}
	fon(0, 1);

	printf("Введите название города: ");
	fgets(name, 100, stdin); //ввод названия
	if (name[0] == '\n')
		while (name[0] == '\n') {
			printf("Введите корректное название города: ");
			fgets(name, 100, stdin);
		}
	name[strlen(name) - 1] = '\0';
	fflush(stdin);
	if (name[0] >= 'а' && name[0] <= 'я') //если первая буква нижнего регистра переводим к верхнему
		name[0] -= 32;
	printf("Введите численность населения: ");
	fgets(type, 100, stdin); //ввод численности
	if (type[0] == '\n')
		while (type[0] == '\n') {
			printf("Введите корректную численность населения: ");
			fgets(type, 100, stdin);
		}
	type[strlen(type) - 1] = '\0';
	fflush(stdin);
	printf("Введите площадь города: ");
	fgets(coordinats, 100, stdin); //ввод площади
	if (coordinats[0] == '\n')
		while (coordinats[0] == '\n') {
			printf("Введите корректную площадь города: ");
			fgets(coordinats, 100, stdin);
		}
	coordinats[strlen(coordinats) - 2] = '\0';
	fflush(stdin);
	printf("Введите главную достопримечательность: ");
	fgets(description, 100, stdin); //ввод главной достопримечательности
	if (description[0] == '\n')
		while (description[0] == '\n') {
			printf("Введите корректную достопримечательность\n");
			fgets(description, 100, stdin);
		}
	if (name[0] >= 'а' && name[0] <= 'я') //если первая буква нижнего регистра переводим к верхнему
		name[0] -= 32;
	fflush(stdin);
	for (i = 0; i <= strlen(name); i++) { //запись в поля элементов списка
		newitem->name[i] = name[i];
	}
	for (i = 0; i <= strlen(coordinats); i++) {
		newitem->coordinats[i] = coordinats[i];
	}
	for (i = 0; i <= strlen(type); i++) {
		newitem->type[i] = type[i];
	}
	for (i = 0; i <= strlen(description); i++) {
		newitem->description[i] = description[i];
	}
	newitem->next = NULL; //указатаель на следующий элемент указывает на NULL
	if (head->first == NULL) { //если добавляемый элемент первый
		head->first = newitem; //переводим головной указатель на добавляемый
		head->num++; //увеличение количества элементов
		return head;
	}
	prev = head->first;
	while (prev->next != NULL) //указатель prev на последний элемент
		prev = prev->next;
	prev->next = newitem; //вставляем добавляемый элемент последним
	head->num++; //увеличение количества элементов
	return head;
}
void show(hitem* head) { //функция вывода всех элементов
	item* now;
	int i = 1;
	system("cls");
	fon(0, 1);
	now = head->first;
	if (now == NULL) {
		printf("Нету списка городов"); //Если нет элементов выводим сообщение
		return;
	}
	if (sort == 0) { //если сортировка по типам
		while (now) { //выводим все элементы, начиная с названия
			printf("%d.\n", i);
			printf("Название: ");
			puts(now->name);
			printf("Численность: ");
			puts(now->type);
			printf("Площадь: ");
			puts(now->coordinats);
			printf("Достопримечательность: ");
			puts(now->description);
			puts("------------------------");
			now = now->next;
			i++;
		}
	}
	else { //если сортировка по именам
		while (now) { //выводим все элементы начиная с имени
			printf("%d.\n", i);
			printf("Название: ");
			puts(now->name);
			printf("Численность: ");
			puts(now->type);
			printf("Площадь: ");
			puts(now->coordinats);
			printf("Достопримечательность: ");
			puts(now->description);
			puts("------------------------");
			now = now->next;
			i++;
		}
	}
	return;
}
hitem* delete(hitem* head) { //функция удаления
	item* now, * buf = NULL;
	int i;
	now = head->first;
	if (head->num == 0) { //если нет элементов
		fon(0, 1);
		printf("Нет элементов\n");
		wait();
		return head; //выходим из функции, возвращаем head
	}
	show(head); //вывод всех элементов
	fon(0, 1);
	printf("Введите элемент, который вы хотите удалить (если хотите выйти нажмите \"exit\"): ");
	i = convertation(); //функция выводит номер, -1, или минимальное значение int
	while ((i <= 0 && i != INT_MIN) || i > head->num) { //ввод номера удаляемого значения или слова exit
		printf("Неисправный номер\nВведите правильный: ");
		i = convertation();
	}
	if (i == INT_MIN) { //значение указывает на то, что было введено exit
		return head; //выходим из функции, возвращаем head
	}
	if (head->num == 1) { //если в списке всего 1 элемент
		head->first = NULL; //зануляем указатель в голове
		head->num--; //уменьшаем количество элементов головы
		free(now); //освобождаем память под удаляемый элемент
		return head;
	}
	if (i == 1) { //если удаляется первый элемент
		head->first = now->next; //перемещаем указатель головы на второй элемент
		head->num--; //уменьшаем количество элементов головы
		free(now); //освобождаем память под удаляемый элемент
		return head;
	}
	while (i != 1) { //если удаляется не первый элемент, то двигаясь по списку ищем удаляемый элемент
		buf = now; //элемент перед удаляемым
		now = now->next; //удаляемый элемент
		i--;
	}
	buf->next = now->next; //элемент перед удаляемым указывает на элемент после удаляемого
	head->num--; //уменьшаем количество элементов
	free(now); //освобождаем память под удаляемый элемент
	return head;
}
hitem* edit(hitem* head) { //функция редактирования элемента
	item* prev, * change, * buf;
	int i, retry;
	char name[100], type[100], coordinats[100], description[100];
	change = head->first; //изменяемый элемент
	prev = NULL;
	buf = NULL;
	if (head->num == 0) { //если список пуст
		fon(0, 1);
		printf("Empty list\n");
		wait();
		return head; //выходим из функции
	}
	show(head); //выводим все элементы
	printf("Введите пункт, который вы хотите изменить (если хотите выйти нажмите \"exit\"): ");
	i = convertation(); //функция выводит номер, -1, или минимальное значение int
	while ((i <= 0 && i != INT_MIN) || i > head->num) { //ввод номера удаляемого значения или слова exit
		printf("Неисправный номер\nВведите правильный: ");
		i = convertation();
	}
	if (i == INT_MIN) { //значение указывает на то, что было введено exit
		return head; //выходим из функции, возвращаем head
	}
	system("cls");
	if (i == 1) { //если запрос на изменение 1 элемента
		if (head->num == 1) { //если в списке всего 1 элемент
			free(change); //освобождаем память под change
		}
		else { //если в списке не 1 элемент
			buf = change->next; //указываем buf на элемент после первого
			free(change); //освобождаем память под change
		}
	}
	else { //если запрос на изменение не первого элемента
		while (i != 1) { //пока не дойдём до нужных элементов
			prev = change; //элемент перед изменяемым
			change = change->next; //изменяемый элемент
			buf = change->next; //элемент после изменяемого
			i--;
		}
		free(change); //освобождаем память под изменяемый
	}
	if ((change = (item*)malloc(sizeof(item))) == NULL) { //выделение памяти под изменяемый элемент
		printf("Нету памяти");
		wait();
		return head;
	}
	fon(0, 1);
	printf("Введите численность населения: ");
	fgets(type, 10, stdin); //ввод численности
	if (type[0] == '\n')
		while (type[0] == '\n') {
			printf("Введит корректную численность: ");
			fgets(type, 100, stdin);
		}
	type[strlen(type) - 1] = '\0';
	fflush(stdin);
	if (type[0] >= 'a' && type[0] <= 'z') //если первая буква нижнего регистра переводим к верхнему
		type[0] -= 32;

	printf("Введите площадь города: ");
	fgets(coordinats, 100, stdin); //ввод площади
	if (type[0] == '\n')
		while (type[0] == '\n') {
			printf("Введите корректную площадь: ");
			fgets(type, 100, stdin);
		}
	type[strlen(type) - 1] = '\0';
	fflush(stdin);
	if (type[0] >= 'a' && type[0] <= 'z') //если первая буква нижнего регистра переводим к верхнему
		type[0] -= 32;
	printf("Введите главную достопримечательность: ");
	fgets(description, 100, stdin); //ввод достопримечательности
	if (description[0] == '\n')
		while (description[0] == '\n') {
			printf("Введите корректную достопримечательность\n");
			fgets(description, 100, stdin);
		}
	description[strlen(description) - 1] = '\0';
	fflush(stdin);
	for (i = 0; i <= strlen(type); i++) { //ввод значений в поля элемента списка
		change->type[i] = type[i];
	}
	for (i = 0; i <= strlen(name); i++) {
		change->name[i] = name[i];
	}
	for (i = 0; i <= strlen(coordinats); i++) {
		change->coordinats[i] = coordinats[i];
	}
	for (i = 0; i <= strlen(description); i++) {
		change->description[i] = description[i];
	}
	if (prev == NULL) { //если первый элемент
		if (buf == NULL) { //если первый элемент - единственный
			head->first = change; //указатель на первый элемент указывает на change
			change->next = NULL;
		}
		else { //если элементов > 1
			head->first = change; //в головном элементе первым становится изменяемый
			change->next = buf; //указатель в изменяемом переводим на следующий
		}
	}
	else { //если не первый элемент
		prev->next = change; //указатель в элементе перед изменяемым переводим на изменяемыйй
		change->next = buf; //указатель в изменяемом переводим на следующий
	}
	return head;
}
hitem* addfromfile(hitem* head, char type[51], char name[51],
	char coordinats[51], char description[51]) { //функция записи передаваемых данных в структуру
	item* newitem, * prev;
	int i;
	prev = head->first;
	if ((newitem = (item*)malloc(sizeof(item))) == NULL) { //выделение памяти под новый элемент
		printf("Ошибка выделенной памяти");
		wait();
		return head;
	}
	for (i = 0; i < strlen(type) - 1; i++) { //запись массива в поля элементов
		newitem->type[i] = type[i];
	}
	newitem->type[i] = '\0';
	for (i = 0; i < strlen(name) - 1; i++) {
		newitem->name[i] = name[i];
	}
	newitem->name[i] = '\0';
	for (i = 0; i < strlen(coordinats) - 1; i++) {
		newitem->coordinats[i] = coordinats[i];
	}
	newitem->coordinats[i] = '\0';
	for (i = 0; i < strlen(description) - 1; i++) {
		newitem->description[i] = description[i];
	}
	newitem->description[i] = '\0';
	newitem->next = NULL;
	if (prev == NULL) { //если новый элемент первый
		head->first = newitem; //указатель в голове переводим на новый элемент
	}
	else { //если новый элемент не первый
		while (prev->next != NULL) //переводим указатель в конец списка
			prev = prev->next;
		prev->next = newitem; //вставляем новый элемент в конец списка
	}
	head->num++; //увеличиваем количество элементов
	return head;
}
hitem* read(hitem* head) { //функция чтения из файла
	FILE* f;
	//item* now;
	int i = 0;
	char* check, srt, type[51], name[51], coordinats[51], description[301];
	if ((f = fopen("d://data.txt", "r")) == NULL) { //открытие файла
		return head; //если файла нет, то выходим из функции
	}
	srt = fgetc(f); //ввод значения переменной сортировки sort
	if (srt == '\n') { //если файл создан, но полностью пуст
		fclose(f);
		return head; //выходим из функции
	}
	if (srt == '0') //Определение последней сортировки в списке
		sort = 0;
	else
		sort = 1;
	fseek(f, 2, SEEK_CUR); //перенос курсора на следующий абзац
	while (1) { //проход по всем строкам
		check = fgets(type, sizeof(type), f); //получение типа из файла
		if (check == NULL) //если указатель на массив указывает на NULL
			if (feof(f) != 0) //Если достигнут конец файла
				break; //выходим из цикла
		fgets(name, sizeof(name), f); //построчное получение полей элементов
		fgets(coordinats, sizeof(coordinats), f);
		fgets(description, sizeof(description), f);
		head = addfromfile(head, type, name, coordinats, description);
		//добавление нового элемента списка из файла
		for (i = 0; i < sizeof(name); i++) //замещение всей длины массива пробелами
			name[i] = ' ';
		for (i = 0; i < sizeof(type); i++) //замещение всей длины массива пробелами
			type[i] = '	';
		for (i = 0; i < sizeof(coordinats); i++) //замещение всей длины массива пробелами
			coordinats[i] = ' ';
		for (i = 0; i < sizeof(description); i++) //замещение всей длины массива пробелами
			description[i] = ' ';
	}
	fclose(f); //закрытие файла
	return head;
}
void save(hitem* head) {
	FILE* f;
	item* now;
	now = head->first;
	if ((f = fopen("d://data.txt", "w+")) == NULL) { //открытие файла для редактирования
		printf("Error of writting file\n");
		wait();
		return;
	}
	fprintf(f, "%d", sort); //вставка в файл текущей сортировка
	fputs("\n", f); //вставка Enter
	while (now != NULL) {
		fputs(now->name, f); //вставка названия города
		fputs("\n", f); //вставка Enter
		fputs(now->type, f); //вставка численности населения
		fputs("\n", f); //вставка Enter
		fputs(now->coordinats, f); //вставка площади города
		fputs("\n", f); //вставка Enter
		fputs(now->description, f); //вставка достопримечательности
		fputs("\n", f); //вставка Enter
		now = now->next;
	}
	fclose(f); //закрытие файла
	return;
}
int action(hitem* head) { //функция, производящая действие при выборе элемента меню
	int i;
	i = menu(head);
	switch (i) { //в зависимости от i
	case 1: {
		head = add(head); //добавить элемент
		head = sorting(head); //отсортировать список
		save(head); //сохранить в файл
		break;
	}
	case 2: {
		head = delete(head); //удалить элемент
		save(head); //сохранить в файл
		break;
	}
	case 3: {
		treasure(head); //найти элемент
		break;
	}
	case 4: {
		head = edit(head); //редактировать элемент
		head = sorting(head); //отсортировать список
		save(head); //сохранить в файл
		break;
	}
	case 5: {
		show(head); //вывести все элементы
		wait();
		break;
	}
	case 6: {
		if (sort == 0) //изменение критерия сортировки
			sort = 1;
		else
			sort = 0;
		head = sorting(head); //отсортировать список
		save(head); //сохранить в файл
		break;
	}
	case 7: {
		system("cls"); //очистка экрана
		help(); //вывод помощи
		break;
	}
	case 8:
		return 0; //выход из функции и возврат 0
	}
	return 1; //выход из функции и возврат 1
}
void program() { //функция основного состава программы
	hitem* head;
	head = initialize(); //инициализация головы
	head = read(head); //чтение элементов списка из файла
	welcome(); //вывод приветствия
	system("cls");
	help(); //вывод помощи
	system("cls");
	while (action(head)); //повторять вызов функции до тех пор, пока функция не вернёт 0
}
int main()
{
	program();
	return 0;
}
