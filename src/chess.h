#ifndef CHESS_H
#define CHESS_H

#define MAX_MOVES 256

typedef enum
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    EMPTY
} pieceType;

typedef enum
{
    BLACK,
    WHITE,
    NONE
} pieceColor;

typedef enum
{
    WIN_WHITE,
    WIN_BLACK,
    DRAW,
    CONTINUE
} stateOfGame;

typedef enum
{
    QUEEN_PROMOTION,
    ROOK_PROMOTION,
    BISHOP_PROMOTION,
    KNIGHT_PROMOTION,
    NO_PROMOTION
} promotionType;

typedef struct Piece
{
    pieceType piece;
    pieceColor color;
    int rank;
    int file;
}Piece;

struct Board
{
    struct Piece *board[8][8];
};

typedef struct Move
{
    int x0;
    int y0;
    int x1;
    int y1;
}Move;

struct Move moves[MAX_MOVES];

struct Game
{
    stateOfGame gameState;
};

void setPiece(struct Board *board, int file, int rank, pieceType piece, pieceColor color);

void getPiece(struct Move *move, struct Board *board, struct Piece *piece);

void movePiece(struct Move *move, struct Board *board);

void initializeBoard(struct Board *board);

void printBoard(struct Board *board);

#endif