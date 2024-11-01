#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, int data) {
	// Если дерево пустое, создаем новый узел
	if (root == NULL) {
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		if (newNode == NULL) {
			printf("Ошибка выделения памяти");
			exit(0);
		}
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}

	// Если дерево не пустое, рекурсивно добавляем узел
	if (data < root->data) {
		root->left = CreateTree(root->left, data);
	}
	else {
		root->right = CreateTree(root->right, data);
	}

	return root;
}

void print_tree(struct Node* r, int l) {
	if (r == NULL) {
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++) {
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

struct Node* SearchTree(struct Node* r, int data) {
	if (r == NULL || r->data == data) {
		return r;
	}

	if (data < r->data) {
		return SearchTree(r->left, data);
	}
	else {
		return SearchTree(r->right, data);
	}
}

// Обновленная функция для подсчета вхождений и определения их уровня
int CountOccurrences(struct Node* r, int data, int level, int* lastLevel) {
	if (r == NULL) {
		return 0; // Базовый случай: если узел пустой, возвращаем 0
	}

	int count = (r->data == data) ? 1 : 0; // Если узел равен искомому значению, увеличиваем счетчик

	// Если мы нашли совпадение, обновляем уровень
	if (count == 1) {
		*lastLevel = level;
	}

	// Рекурсивно считаем вхождения в левом и правом поддеревьях
	count += CountOccurrences(r->left, data, level + 1, lastLevel);
	count += CountOccurrences(r->right, data, level + 1, lastLevel);

	return count; // Возвращаем общее количество вхождений
}

int main() {
	setlocale(LC_ALL, "");
	int D, start = 1;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start) {
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1) {
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else {
			root = CreateTree(root, D);
		}
	}

	print_tree(root, 0);

	printf("\nВведите число для поиска: ");
	scanf_s("%d", &D);

	struct Node* result = SearchTree(root, D);
	if (result != NULL) {
		printf("Значение %d найдено в дереве.\n", result->data);
	}
	else {
		printf("Значение %d не найдено в дереве.\n", D);
	}

	// Подсчёт вхождений заданного числа и уровня последнего вхождения
	int occurrences, lastLevel = -1;
	occurrences = CountOccurrences(root, D, 0, &lastLevel);
	printf("Количество вхождений значения %d в дереве: %d\n", D, occurrences);

	if (occurrences > 0) {
		printf("Последнее вхождение значения %d находится на уровне: %d\n", D, lastLevel);
	}
	else {
		printf("Значение %d не встречается в дереве.\n", D);
	}

	return 0;
}