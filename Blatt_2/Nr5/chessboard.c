#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"

//struct board_t {
//	int **fields;
//	int curX;
//	int curY;
//	int n;
//	int iteration;
//};

void set_cur_field(struct board_t* b, int value) {
	b->fields[b->curX][b->curY] = value;
}

int init_board(struct board_t* b, int n, int x, int y) {
	int **f = malloc(sizeof(int*) * n);
	if (!f) return 1;
	for (int i = 0; i < n; i++) {
		int *fInner = malloc(sizeof(int) * n);
		if (!fInner) return 1;
		for (int j = 0; j < n; j++) {
			fInner[j] = -1;
		}
		f[i] = fInner;
	}
	b->fields = f;
	b->n = n;
	b->curX = x;
	b->curY = y;
	b->iteration = 1;
	set_cur_field(b, b->iteration);
	return 0;
}

void free_board(struct board_t *b) {
	for (int i = 0; i < b->n; i++) {
		free(b->fields[i]);
	}
	free(b->fields);
}

void new_jump(struct board_t* b, int x, int y) {
	b->iteration++;
	b->curX += x;
	b->curY += y;
	set_cur_field(b, b->iteration);
}

void remove_jump(struct board_t* b, int x, int y) {
	set_cur_field(b, -1);
	b->iteration--;
	b->curX -= x;
	b->curY -= y;
}

int isfree(struct board_t* b, int x, int y) {
	int newX = b->curX + x;
	int newY = b->curY + y;
	if (newX >= b->n || newY >= b->n || newX < 0 || newY < 0) return 0;
	return b->fields[newX][newY] == -1;
}

int visited_fields(struct board_t* b) {
	return b->iteration;
}

void print_horizontal_line(int n) {
	for (int i = 0; i < n; i++) {
		printf("+---");
	}
	printf("+\n");
}

void print_board(struct board_t* b) {
	if (b->n == 0) return;

	for (int i = 0; i < b->n; i++) {
		print_horizontal_line(b->n);
		for (int j = 0; j < b->n; j++) {
			printf("+%3i", b->fields[i][j]);
		}
		printf("+\n");
	}
	print_horizontal_line(b->n);
}