#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "chess.h"

//                                     x         y
void setPiece(struct Board *board, int file, int rank, pieceType piece, pieceColor color)
{
    struct Piece *newPiece = malloc(sizeof(struct Piece));
    newPiece->color = color;
    newPiece->piece = piece;
    newPiece->file = file;
    newPiece->rank = rank;

    board->board[rank - 1][file - 1] = newPiece;
}

void getPiece(struct Move *move, struct Board *board, struct Piece *piece)
{

    switch (piece->piece)
    {
    case PAWN:

        switch (piece->color)
        {
        case WHITE:
            printf("WHITE ");
            break;
        case BLACK:
            printf("BLACK ");
            break;
        case NONE:
            printf("NONE");
            break;
        }
        printf("PAWN\n");
        break;
    case ROOK:

        switch (piece->color)
        {
        case WHITE:
            printf("WHITE ");
            break;
        case BLACK:
            printf("BLACK ");
            break;
        case NONE:
            printf("NONE\n");
            break;
        }
        printf("ROOK\n");
        break;
    case KNIGHT:

        switch (piece->color)
        {
        case WHITE:
            printf("WHITE ");
            break;
        case BLACK:
            printf("BLACK ");
            break;
        case NONE:
            printf("NONE\n");
            break;
        }
        printf("KNIGHT\n");
        break;
    case BISHOP:

        switch (piece->color)
        {
        case WHITE:
            printf("WHITE ");
            break;
        case BLACK:
            printf("BLACK ");
            break;
        case NONE:
            printf("NONE\n");
            break;
        }
        printf("BISHOP\n");
        break;
    case QUEEN:

        switch (piece->color)
        {
        case WHITE:
            printf("WHITE ");
            break;
        case BLACK:
            printf("BLACK ");
            break;
        case NONE:
            printf("NONE\n");
            break;
        }
        printf("QUEEN\n");
        break;
    case KING:

        switch (piece->color)
        {
        case WHITE:
            printf("WHITE ");
            break;
        case BLACK:
            printf("BLACK ");
            break;
        case NONE:
            printf("NONE\n");
            break;
        }
        printf("KING\n");
        break;
    case EMPTY:
        printf("EMPTY\n");
        break;
    default:
        printf("UNKNOWN\n");
        break;
    }
    printf("\n");
}

void movePiece(struct Move *move, struct Board *board)
{

    // struct Piece *startPiece = board->board[move->y0 - 1][move->x0 - 1];
    // struct Piece *endPiece = board->board[move->y1 - 1][move->x1 - 1];
    struct Piece *inputPiece = board->board[move->y0 - 1][move->x0 - 1];
    //struct Piece inputPiece;

    inputPiece->piece = board->board[move->y0 - 1][move->x0 - 1]->piece;
    inputPiece->color = board->board[move->y0 - 1][move->x0 - 1]->color;

    setPiece(board, move->x1, move->y1, inputPiece->piece, inputPiece->color);
    setPiece(board, move->x0, move->y0, EMPTY, NONE);
}

void initializeBoard(struct Board *board)
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board->board[i][j] = malloc(sizeof(struct Piece));
            board->board[i][j]->piece = EMPTY;
            board->board[i][j]->color = NONE;
        }
    }

    for (int j = 1; j < 9; j++)
    {
        setPiece(board, j, 7, PAWN, BLACK);
        setPiece(board, j, 2, PAWN, WHITE);
    }

    setPiece(board, 1, 1, ROOK, WHITE);
    setPiece(board, 8, 1, ROOK, WHITE);
    setPiece(board, 2, 1, KNIGHT, WHITE);
    setPiece(board, 7, 1, KNIGHT, WHITE);
    setPiece(board, 3, 1, BISHOP, WHITE);
    setPiece(board, 6, 1, BISHOP, WHITE);
    setPiece(board, 4, 1, QUEEN, WHITE);
    setPiece(board, 5, 1, KING, WHITE);

    setPiece(board, 1, 8, ROOK, BLACK);
    setPiece(board, 8, 8, ROOK, BLACK);
    setPiece(board, 2, 8, KNIGHT, BLACK);
    setPiece(board, 7, 8, KNIGHT, BLACK);
    setPiece(board, 3, 8, BISHOP, BLACK);
    setPiece(board, 6, 8, BISHOP, BLACK);
    setPiece(board, 5, 8, KING, BLACK);
    setPiece(board, 4, 8, QUEEN, BLACK);
}

void printBoard(struct Board *board)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d | ", i + 1);
        for (int j = 0; j < 8; j++)
        {
            if (board->board[i][j]->color != NONE && board->board[i][j]->piece != EMPTY)
            {
                switch (board->board[i][j]->piece)
                {
                case PAWN:
                    switch (board->board[i][j]->color)
                    {
                    case WHITE:
                        printf("wP ");
                        break;
                    case BLACK:
                        printf("bP ");
                        break;
                    }
                    break;
                case ROOK:
                    switch (board->board[i][j]->color)
                    {
                    case WHITE:
                        printf("wR ");
                        break;
                    case BLACK:
                        printf("bR ");
                        break;
                    }
                    break;
                case KNIGHT:
                    switch (board->board[i][j]->color)
                    {
                    case WHITE:
                        printf("wN ");
                        break;
                    case BLACK:
                        printf("bN ");
                        break;
                    }
                    break;
                case BISHOP:
                    switch (board->board[i][j]->color)
                    {
                    case WHITE:
                        printf("wB ");
                        break;
                    case BLACK:
                        printf("bB ");
                        break;
                    }
                    break;
                case KING:
                    switch (board->board[i][j]->color)
                    {
                    case WHITE:
                        printf("wK ");
                        break;
                    case BLACK:
                        printf("bK ");
                        break;
                    }
                    break;
                case QUEEN:
                    switch (board->board[i][j]->color)
                    {
                    case WHITE:
                        printf("wQ ");
                        break;
                    case BLACK:
                        printf("bQ ");
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {

                printf(" 0 ");
            }
        }
        printf("\n");
    }
    printf("   ------------------------\n");
    printf("    1  2  3  4  5  6  7  8\n");
}
