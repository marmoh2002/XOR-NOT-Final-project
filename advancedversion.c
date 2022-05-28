
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define OFF_BOARD -2
#define EMPTY -1
#define LOOK_AHEAD 5
#define TABLE_SIZE 32000
#define TABLE_BIN_SIZE 10
typedef struct {
	int width;
	int height;
	int* board;
	int last_move;
	int weight;
	int refs;
} GameState;

/*@null@*/
GameState* newGameState(int width, int height) {
	int i;
	GameState* toR = (GameState*) malloc(sizeof(GameState));

	if (toR == NULL)
		return NULL;


	toR->width = width;
	toR->height = height;
	toR->board = (int*) malloc(sizeof(int) * width * height);

	toR->weight = 0;
	toR->refs = 1;
	toR->last_move = 0;

	for (int i = 0; i < width * height; i++) {

	toR->board = (int*) malloc(sizeof(int) * width * height);
	if (toR->board == NULL) {
		free(toR);
		return NULL;
	}


	/*@+forloopexec@*/
	for (i = 0; i < width * height; i++) {
		toR->board[i] = EMPTY;
	}
	/*@=forloopexec@*/

	return toR;
}

void freeGameState(GameState* gs) {
void freeGameState(/*@owned@*/ GameState* gs) {
	gs->refs--;
	if (gs->refs <= 0) {
		free(gs->board);
@@ -78,7 +96,8 @@ int at(GameState* gs, int x, int y) {
}

void drop(GameState* gs, int column, int player) {
	for (int i = 0; i < gs->height; i++) {
	int i;
	for (i = 0; i < gs->height; i++) {
		if (at(gs, column, i) == EMPTY) {
			gs->board[column * gs->height + i] = player;
			gs->last_move = column;
@@ -91,11 +110,12 @@ void drop(GameState* gs, int column, int player) {

int checkAt(GameState* gs, int x, int y) {
	// check across
	int found = 1;
	bool found = true;
	int curr = at(gs, x, y);
	for (int i = 0; i < 4; i++) {
	int i;
	for (i = 0; i < 4; i++) {
		if (at(gs, x + i, y) != curr) {
			found = 0;
			found = false;
			break;
		}
	}
@@ -104,10 +124,10 @@ int checkAt(GameState* gs, int x, int y) {
		return curr;

	// check down
	found = 1;
	for (int i = 0; i < 4; i++) {
	found = true;
	for (i = 0; i < 4; i++) {
		if (at(gs, x, y + i) != curr) {
			found = 0;
			found = false;
			break;
		}
	}
@@ -116,10 +136,10 @@ int checkAt(GameState* gs, int x, int y) {
		return curr;

	// check diag +/+
	found = 1;
	for (int i = 0; i < 4; i++) {
	found = true;
	for (i = 0; i < 4; i++) {
		if (at(gs, x + i, y + i) != curr) {
			found = 0;
			found = false;
			break;
		}
	}
@@ -128,10 +148,10 @@ int checkAt(GameState* gs, int x, int y) {
		return curr;

	// check diag -/+
	found = 1;
	for (int i = 0; i < 4; i++) {
	found = true;
	for (i = 0; i < 4; i++) {
		if (at(gs, x - i, y + i) != curr) {
			found = 0;
			found = false;
			break;
		}
	}
@@ -144,7 +164,8 @@ int checkAt(GameState* gs, int x, int y) {

int getIncrementForArray(int* arr, int player) {
	int toR = 0;
	for (int i = 0; i < 4; i++) {
	int i;
	for (i = 0; i < 4; i++) {
		if (arr[i] == player) {
			toR = 1;
			continue;
@@ -163,38 +184,41 @@ int countAt(GameState* gs, int x, int y, int player) {
	// check across
	int found = 0;
	int buf[4];
	int i;

	for (int i = 0; i < 4; i++) {
	for (i = 0; i < 4; i++) {
		buf[i] = at(gs, x + i, y);
	}

	found += getIncrementForArray(buf, player);

	// check down
	for (int i = 0; i < 4; i++) {
	for (i = 0; i < 4; i++) {
		buf[i] = at(gs, x, y + i);
	}
	found += getIncrementForArray(buf, player);

	// check diag +/+
	for (int i = 0; i < 4; i++) {
	for (i = 0; i < 4; i++) {
		buf[i] = at(gs, x + i, y + i);
	}
	found += getIncrementForArray(buf, player);

	// check diag -/+
	for (int i = 0; i < 4; i++) {
	for (i = 0; i < 4; i++) {
		buf[i] = at(gs, x - i, y + i);
	}
	found += getIncrementForArray(buf, player);

	return found;
}

int getWinner(GameState* gs) {
	for (int x = 0; x < gs->width; x++) {
		for (int y = 0; y < gs->height; y++) {
			int res = checkAt(gs, x, y);
bool getWinner(GameState* gs) {
	int x, y;
	bool res;
	for (x = 0; x < gs->width; x++) {
		for (y = 0; y < gs->height; y++) {
			res = (bool) checkAt(gs, x, y);
			if (res)
				return res;
		}
@@ -204,8 +228,9 @@ int getWinner(GameState* gs) {
}

int isDraw(GameState* gs) {
	for (int x = 0; x < gs->width; x++) {
		for (int y = 0; y < gs->height; y++) {
	int x, y;
	for (x = 0; x < gs->width; x++) {
		for (y = 0; y < gs->height; y++) {
			if (at(gs, x, y) == EMPTY)
				return 0;
		}
@@ -216,8 +241,9 @@ int isDraw(GameState* gs) {

int getHeuristic(GameState* gs, int player, int other_player) {
	int toR = 0;
	for (int x = 0; x < gs->width; x++) {
		for (int y = 0; y < gs->height; y++) {
	int x, y;
	for (x = 0; x < gs->width; x++) {
		for (y = 0; y < gs->height; y++) {
			toR += countAt(gs, x, y, player);
			toR -= countAt(gs, x, y, other_player);
		}
@@ -227,31 +253,44 @@ int getHeuristic(GameState* gs, int player, int other_player) {
}

int canMove(GameState* gs, int column) {
	for (int y = 0; y < gs->height; y++) {
	int y;
	for (y = 0; y < gs->height; y++) {
		if (at(gs, column, y) == EMPTY)
			return 1;
	}

	return 0;
}

/*@null@*/
GameState* stateForMove(GameState* orig, int column, int player) {
	GameState* toR = newGameState(orig->width, orig->height);
	GameState* toR;
	if (orig == NULL || orig->board == NULL)
		return NULL;



	toR = newGameState(orig->width, orig->height);
	if (toR == NULL)
		return NULL;


	memcpy(toR->board, orig->board, sizeof(int) * orig->width * orig->height);
	drop(toR, column, player);
	return toR;
}

void printGameState(GameState* gs) {
	for (int i = 0; i < gs->width; i++) {
	int i, x, y, toP;
	for (i = 0; i < gs->width; i++) {
		printf("%d ", i);
	}

	printf("\n");

	for (int y = gs->height - 1; y >= 0 ; y--) {
		for (int x = 0; x < gs->width; x++) {
			int toP = at(gs, x, y);
	for (y = gs->height - 1; y >= 0 ; y--) {
		for (x = 0; x < gs->width; x++) {
			toP = at(gs, x, y);
			if (toP == EMPTY) {
				printf("  ");
			} else {
@@ -261,27 +300,29 @@ void printGameState(GameState* gs) {
		printf("\n");
	}

	for (int i = 0; i < gs->width; i++) {
	for (i = 0; i < gs->width; i++) {
		printf("%d ", i);
	}

	printf("\n\n");
}

unsigned long hashGameState(GameState* gs) {
unsigned long long hashGameState(GameState* gs) {
	unsigned long long hash = 14695981039346656037Lu;
	for (int i = 0; i < gs->width * gs->height; i++) {
	int i;
	for (i = 0; i < gs->width * gs->height; i++) {
		hash ^= gs->board[i];
		hash *= 1099511628211Lu;
	}
	return hash;
}

int isGameStateEqual(GameState* gs1, GameState* gs2) {
	int i;
	if (gs1->width != gs2->width || gs1->height != gs2->height)
		return 0;

	for (int i = 0; i < gs1->width * gs1->height; i++) {
	for (i = 0; i < gs1->width * gs1->height; i++) {
		if (gs1->board[i] == gs2->board[i])
			continue;
		return 0;
@@ -296,11 +337,12 @@ typedef struct {


TranspositionTable* newTable() {
	int i, j;
	TranspositionTable* toR = (TranspositionTable*) malloc(sizeof(TranspositionTable));
	toR->bins = (GameState***) malloc(sizeof(GameState**) * TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++) {
	for (i = 0; i < TABLE_SIZE; i++) {
		toR->bins[i] = (GameState**) malloc(sizeof(GameState*) * TABLE_BIN_SIZE);
		for (int j = 0; j < TABLE_BIN_SIZE; j++) {
		for (j = 0; j < TABLE_BIN_SIZE; j++) {
			toR->bins[i][j] = NULL;
		}
	}
@@ -310,8 +352,9 @@ TranspositionTable* newTable() {

GameState* lookupInTable(TranspositionTable* t, GameState* k) {
	int hv = hashGameState(k) % TABLE_SIZE;
	int i;
	GameState** bin = t->bins[hv];
	for (int i = 0; i < TABLE_BIN_SIZE; i++) {
	for (i = 0; i < TABLE_BIN_SIZE; i++) {
		if (bin[i] == NULL) {
			return NULL;
		}
@@ -325,8 +368,9 @@ GameState* lookupInTable(TranspositionTable* t, GameState* k) {

void addToTable(TranspositionTable* t, GameState* k) {
	int hv = hashGameState(k) % TABLE_SIZE;
	int i;
	GameState** bin = t->bins[hv];
	for (int i = 0; i < TABLE_BIN_SIZE; i++) {
	for (i = 0; i < TABLE_BIN_SIZE; i++) {
		if (bin[i] == NULL) {
			bin[i] = k;
			retainGameState(k);
@@ -338,8 +382,9 @@ void addToTable(TranspositionTable* t, GameState* k) {
}

void freeTranspositionTable(TranspositionTable* t) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < TABLE_BIN_SIZE; j++) {
	int i, j;
	for (i = 0; i < TABLE_SIZE; i++) {
		for (j = 0; j < TABLE_BIN_SIZE; j++) {
			if (t->bins[i][j] != NULL)
				freeGameState(t->bins[i][j]);
		}
@@ -414,7 +459,7 @@ int desComp(const void* a, const void* b) {
}

int getWeight(GameTreeNode* node, int movesLeft) {
	int toR;
	int toR, move, best_weight;
	if (getWinner(node->gs) || isDraw(node->gs) || movesLeft == 0)
		return heuristicForState(node->gs, node->player, node->other_player);

@@ -438,9 +483,9 @@ int getWeight(GameTreeNode* node, int movesLeft) {
		qsort(possibleMoves, validMoves, sizeof(GameState*), desComp);
	}

	int best_weight = (node->turn ? INT_MIN : INT_MAX);
	best_weight = (node->turn ? INT_MIN : INT_MAX);

	for (int move = 0; move < validMoves; move++) {
	for (move = 0; move < validMoves; move++) {
		// see if the game state is already in the hash table
		GameState* inTable = lookupInTable(node->ht, possibleMoves[move]);
		int child_weight;
