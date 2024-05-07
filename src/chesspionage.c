#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#include "chess.h"

#define MAX_MOVES 256

int moveCount = 0;

void capture(struct Board *board, struct Move *move)
{
    if (board->board[move->y1 - 1][move->x1 - 1]->piece != board->board[move->y0 - 1][move->x0 - 1]->piece)
    {
        printf("capture!");
    }
}

bool isPromotion(struct Board *board)
{
    for (int i = 0; i < 8; i++)
    {
        if (board->board[7][i]->piece == PAWN)
        {
            return true;
        }
        
        else if (board->board[0][i]->piece == PAWN)
        {
            return true;
        }
    }
    return false;
}


void promotePawn(struct Board *board, int promoteChoice)
{
    for (int i = 0; i < 8; i++)
    {
        if (board->board[7][i]->piece == PAWN)
        {
            if (promoteChoice == 1)
            {
                setPiece(board, i+1, 8, EMPTY, NONE);
                setPiece(board, i+1, 8, QUEEN, WHITE);
            }
            
            else if (promoteChoice == 2)
            {
                setPiece(board, i+1, 8, EMPTY, NONE);
                setPiece(board, i+1, 8, ROOK, WHITE);
            }
            
            else if (promoteChoice == 3)
            {
                setPiece(board, i+1, 8, EMPTY, NONE);
                setPiece(board, i+1, 8, BISHOP, WHITE);
            }
            
            else if (promoteChoice == 4)
            {
                setPiece(board, i+1, 8, EMPTY, NONE);
                setPiece(board, i+1, 8, KNIGHT, WHITE);
            }
        }
        
        else if (board->board[0][i]->piece == PAWN)
        {
            if (promoteChoice == 1)
            {
                setPiece(board, i+1, 1, EMPTY, NONE);
                setPiece(board, i+1, 1, QUEEN, BLACK);
            }
            
            else if (promoteChoice == 2)
            {
                setPiece(board, i+1, 1, EMPTY, NONE);
                setPiece(board, i+1, 1, ROOK, BLACK);
            }
            
            else if (promoteChoice == 3)
            {
                setPiece(board, i+1, 1, EMPTY, NONE);
                setPiece(board, i+1, 1, BISHOP, BLACK);
            }
            
            else if (promoteChoice == 4)
            {
                setPiece(board, i+1, 1, EMPTY, NONE);
                setPiece(board, i+1, 1, KNIGHT, BLACK);
            }
        }
    }
}

bool hasWKingMoved(struct Board *board)
{
    if (board->board[0][4]->piece == EMPTY)
    {
        return true;
    }
    return false;
}

bool hasBKingMoved(struct Board *board)
{
    if (board->board[7][4]->piece == EMPTY)
    {
        return true;
    }
    return false;
}

bool hasWLRookMoved(struct Board *board)
{
    if (board->board[0][0]->piece == EMPTY)
    {
        return true;
    }
    return false;
}

bool hasWRRookMoved(struct Board *board)
{
    if (board->board[0][7]->piece == EMPTY)
    {
        return true;
    }
    return false;
}

bool hasBLRookMoved(struct Board *board)
{
    if (board->board[7][0]->piece == EMPTY)
    {
        return true;
    }
    return false;
}

bool hasBRRookMoved(struct Board *board)
{
    if (board->board[7][7]->piece == EMPTY)
    {
        return true;
    }
    return false;
}

void castleWQueenside(struct Board *board)
{
    setPiece(board, 1, 1, EMPTY, NONE);
    setPiece(board, 4, 1, ROOK, WHITE);
}

void castleWKingside(struct Board *board)
{
    setPiece(board, 8, 1, EMPTY, NONE);
    setPiece(board, 6, 1, ROOK, WHITE);
}

void castleBQueenside(struct Board *board)
{
    setPiece(board, 1, 8, EMPTY, NONE);
    setPiece(board, 4, 8, ROOK, BLACK);
}

void castleBKingside(struct Board *board)
{
    setPiece(board, 8, 8, EMPTY, NONE);
    setPiece(board, 6, 8, ROOK, BLACK);
}

bool pawnMove(struct Board *board, struct Move *move, pieceColor color)
{
  // Determine the valid direction based on color
  int direction = (color == WHITE) ? 1 : -1;
  bool enPassant;
  int startingRow = (color == WHITE) ? 2 : 7;

  if (move->x0 == move->x1 && move->y1 == move->y0 + direction)
  {
    if (board->board[move->y1 - 1][move->x1 - 1]->color != NONE)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  // double step pawn move
  if (move->x0 == move->x1 && move->y0 == startingRow && move->y1 == move->y0 + 2 * direction)
  {
    // is the path clear?
    if (board->board[move->y1 - 1][move->x1 - 1]->piece == EMPTY &&
        board->board[move->y0 + direction - 1][move->x1 - 1]->piece == EMPTY)
    {
      return true;
    }
  }

  struct Piece *leftPiece = (move->x1 > 1) ? board->board[move->y1 - 1][move->x1 - 2] : NULL;
  struct Piece *rightPiece = (move->x1 < 8) ? board->board[move->y1 - 1][move->x1] : NULL;

  if (move->y1 == move->y0 + direction &&
      (move->x1 == move->x0 + 1 || move->x1 == move->x0 - 1))
  {
    // is there an enemy piece at the destination?
    if (board->board[move->y1 - 1][move->x1 - 1]->color != color &&
        board->board[move->y1 - 1][move->x1 - 1]->color != NONE)
    {
      if (leftPiece && (leftPiece->piece == PAWN && leftPiece->color != NONE && leftPiece->color != color))
      {
        enPassant = true;
      }
      else if (rightPiece && (rightPiece->piece == PAWN && rightPiece->color != NONE && rightPiece->color != color))
      {
        enPassant = true;
      }
      else
      {
        enPassant = false;
      }

      if (enPassant)
      {
        printf("You can en passant!");
      }

      return true;
    }
  }

  return false;
}

bool rookMove(struct Board *board, struct Move *move)
{

    int start = (move->y1 < move->y0) ? move->y1 : move->y0;
    int end = (move->y1 > move->y0) ? move->y1 : move->y0;

    if (move->x0 == move->x1)
    {

        // Check for pieces in between
        for (int y = start + 1; y < end; y++)
        {
            if (board->board[y - 1][move->x0 - 1]->piece != EMPTY)
            {
                return false; // There's a piece blocking the path
            }
        }

        return true;
    }

    else if (move->y0 == move->y1)
    {

        int start = (move->x1 < move->x0) ? move->x1 : move->x0;
        int end = (move->x1 > move->x0) ? move->x1 : move->x0;

        for (int x = start + 1; x < end; x++)
        {
            if (board->board[move->y0 - 1][x - 1]->piece != EMPTY)
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool knightMove(struct Board *board, struct Move *move)
{

    if ((move->y1 == move->y0 + 2 || move->y1 == move->y0 - 2) && (move->x1 == move->x0 + 1 || move->x1 == move->x0 - 1))
    {
        return true;
    }
    else if ((move->x1 == move->x0 + 2 || move->x1 == move->x0 - 2) && (move->y1 == move->y0 + 1 || move->y1 == move->y0 - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool bishopMove(struct Board *board, struct Move *move)
{
    int yDistance = move->y1 - move->y0;
    int xDistance = move->x1 - move->x0;

    if (abs(xDistance) != abs(yDistance))
    {
        return false; // The move isn't diagonal
    }

    int yDirection = (yDistance > 0) ? 1 : -1;
    int xDirection = (xDistance > 0) ? 1 : -1;

    int steps = abs(xDistance); // Number of steps to move diagonally

    for (int i = 1; i < steps; i++)
    {
        int y = move->y0 - 1 + i * yDirection;
        int x = move->x0 - 1 + i * xDirection;
        if (board->board[y][x]->piece != EMPTY)
        {
            return false; // There's a piece blocking the path
        }
    }

    return true;
}

bool kingMove(struct Board *board, struct Move *move)
{
    int xDistance = abs(move->x1 - move->x0);
    int yDistance = abs(move->y1 - move->y0);
    
    // Special case: castling
    if (((move->x0 == 5) && (move->y0 == 1) && (move->x1 == 3) && (move->y1 == 1)) || ((move->x0 == 5) && (move->y0 == 1) && (move->x1 == 7) && (move->y1 == 1)) || ((move->x0 == 5) && (move->y0 == 8) && (move->x1 == 3) && (move->y1 == 8)) || ((move->x0 == 5) && (move->y0 == 8) && (move->x1 == 7) && (move->y1 == 8)))
    {
        if ((xDistance <= 2) && (yDistance <= 1))
        {
            // Ensure that the move does not place the king on a square with a piece of the same color
            if (board->board[move->y1 - 1][move->x1 - 1]->color != board->board[move->y0 - 1][move->x0 - 1]->color)
            {
                return true;
            }
        }        
    }

    // The king can move one square in any direction: horizontally, vertically, or diagonally
    if ((xDistance <= 1) && (yDistance <= 1))
    {
        // Ensure that the move does not place the king on a square with a piece of the same color
        if (board->board[move->y1 - 1][move->x1 - 1]->color != board->board[move->y0 - 1][move->x0 - 1]->color)
        {
            return true;
        }
    }

    // isCastle - move rook first and then return true

    return false; // If the move is not one square away or it's onto a square with a piece of the same color
}

bool queenMove(struct Board *board, struct Move *move)
{
    int yDistance = move->y1 - move->y0;
    int xDistance = move->x1 - move->x0;

    if (abs(xDistance) == abs(yDistance))
    {
        // Diagonal movement
        int yDirection = (yDistance > 0) ? 1 : -1;
        int xDirection = (xDistance > 0) ? 1 : -1;

        int steps = abs(xDistance); // Number of steps to move diagonally

        for (int i = 1; i < steps; i++)
        {
            int y = move->y0 - 1 + i * yDirection;
            int x = move->x0 - 1 + i * xDirection;
            if (board->board[y][x]->piece != EMPTY)
            {
                return false; // There's a piece blocking the path
            }
        }

        return true;
    }
    else if (move->x0 == move->x1)
    {
        // Vertical movement
        int start = (move->y1 < move->y0) ? move->y1 : move->y0;
        int end = (move->y1 > move->y0) ? move->y1 : move->y0;

        for (int y = start + 1; y < end; y++)
        {
            if (board->board[y - 1][move->x0 - 1]->piece != EMPTY)
            {
                return false; // There's a piece blocking the path
            }
        }

        return true;
    }
    else if (move->y0 == move->y1)
    {
        // Horizontal movement
        int start = (move->x1 < move->x0) ? move->x1 : move->x0;
        int end = (move->x1 > move->x0) ? move->x1 : move->x0;

        for (int x = start + 1; x < end; x++)
        {
            if (board->board[move->y0 - 1][x - 1]->piece != EMPTY)
            {
                return false;
            }
        }

        return true;
    }

    return false; // If it's not a valid queen move
}

bool isValid(struct Board *board, struct Move *move, pieceColor color)
{   
  struct Piece *startPiece = board->board[move->y0 - 1][move->x0 - 1];
  struct Piece *endPiece = board->board[move->y1 - 1][move->x1 - 1];

   if (endPiece->color != EMPTY && endPiece->color == startPiece->color)
   {
     //printf("There is a piece of your own color at that destination.\n");
     return false;
   }

  if (move->x0 < 0 || move->x0 > 8 || move->y0 < 0 || move->y0 > 8 || move->x1 < 0 || move->x1 > 8 || move->y1 < 0 || move->y1 > 8) {
    return false;  // Prevent out-of-bounds access
}

  
  
  switch (startPiece->piece)
  {
  case PAWN:
    return pawnMove(board, move, color);
  case ROOK:
    return rookMove(board, move);
  case KNIGHT:
    return knightMove(board, move);
  case KING:
    return kingMove(board, move);
  case BISHOP:
    return bishopMove(board, move);
  case QUEEN:
    return queenMove(board, move);
  default:
    printf("Invalid piece type.\n");
    return false;
  }

}


bool isCheck(struct Board *board, struct Move *move, pieceColor color)
{
  int kingPosX = -1;
  int kingPosY = -1;

    //find king on board
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board->board[i][j]->piece == KING && board->board[i][j]->color == color)
      {
        kingPosX = j + 1;
        kingPosY = i + 1;
        break;
      }
    }
    if (kingPosX != -1)
      break; 
  }

  
  if (kingPosX == -1 || kingPosY == -1)
  {
    printf("King not found.\n");
    return false;
  }

  struct Move m;
  m.x1 = kingPosX;
  m.y1 = kingPosY;

  // check if every piece can move to king 
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board->board[i][j]->color != NONE && board->board[i][j]->color != color)
      {
        m.x0 = j + 1;
        m.y0 = i + 1;
        struct Piece *attackingPiece = board->board[i][j];

        //is move valid? And does it move to king?
        if (isValid(board, &m, attackingPiece->color)&& 
                    board->board[m.y1 - 1][m.x1 - 1]->piece == KING &&
                    board->board[m.y0 - 1][m.x0 - 1]->color != color) 
        {
          
          
            
          return true;
        }
      }
    }
  }

  return false;
}


void generateLegalMoves(struct Board *board, pieceColor color, Move moves[], int *moveCount) {
    *moveCount = 0;  // Reset move count

    for (int y0 = 0; y0 < 8; y0++) {
        for (int x0 = 0; x0 < 8; x0++) {
            if (board->board[y0][x0] && board->board[y0][x0]->color == color) {
                for (int y1 = 0; y1 < 8; y1++) {
                    for (int x1 = 0; x1 < 8; x1++) {
                        Move move = {x0 + 1, y0 + 1, x1 + 1, y1 + 1}; // Adjust for 1-based index
                        if (isValid(board, &move, color)) {
                            if (*moveCount < MAX_MOVES) {
                                moves[*moveCount] = move;
                                (*moveCount)++;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool isCheckmate(struct Board* board, pieceColor color) {
    // Check if the king is in check
    Move dummyMove = {0, 0, 0, 0}; // Dummy move to check the current state
    if (!isCheck(board, &dummyMove, color)) {
        return false; // If not in check, it's not checkmate
    }

    // Generate all possible moves for this color
    Move moves[MAX_MOVES];
    int moveCount = 0;
    generateLegalMoves(board, color, moves, &moveCount);

    // Simulate each move to see if it removes the check
    for (int i = 0; i < moveCount; i++) {
        Move move = moves[i];

        // Save the original state
        struct Piece* originalStartPiece = board->board[move.y0 - 1][move.x0 - 1];
        struct Piece* originalEndPiece = board->board[move.y1 - 1][move.x1 - 1];

        // Simulate the move
        board->board[move.y1 - 1][move.x1 - 1] = board->board[move.y0 - 1][move.x0 - 1];
        board->board[move.y0 - 1][move.x0 - 1] = malloc(sizeof(Piece));
        board->board[move.y0 - 1][move.x0 - 1]->piece = EMPTY;
        board->board[move.y0 - 1][move.x0 - 1]->color = NONE;
        board->board[move.y0 - 1][move.x0 - 1] = NULL; // Clear the start square
        board->board[move.y1 - 1][move.x1 - 1] = originalStartPiece; // Move piece to the end square

        // Check if the king is still in check
        bool stillInCheck = isCheck(board, &dummyMove, color);

        // Restore the original state
        board->board[move.y0 - 1][move.x0 - 1] = originalStartPiece;
        board->board[move.y1 - 1][move.x1 - 1] = originalEndPiece;

        if (!stillInCheck) {
            // If any move removes the check, it's not checkmate
            return false;
        }
    }

    // If every move still results in check, it's checkmate
    return true;
}

void aiTurn(struct Board *board, pieceColor color)
{
    Move moves[MAX_MOVES];
    int moveCount = 0;

    generateLegalMoves(board, color, moves, &moveCount);

    if (moveCount > 0)
    {
        srand(time(NULL));
        int randomIndex = rand() % moveCount;

        printf("Computer moves: %d %d -> %d %d\n",
               moves[randomIndex].x0, moves[randomIndex].y0,
               moves[randomIndex].x1, moves[randomIndex].y1);
        movePiece(&moves[randomIndex], board);
    } else {
        printf("Computer cannot move.\n");
    
    }
}

int main()
{

    /* Structs, Variables & strings */
    struct Board b;
    struct Move m;
    struct Game *game;

    int gameMode; // 1 is pvp, 2 is pve
    int playerColor;

    int turn = 1;
    int status = 1;
    pieceColor currentMove;
    bool validInput;
    bool gameActive = true;
    bool check;
    int promoteChoice;
    bool wkingMoved = false;
    bool bkingMoved = false;
    bool wlrookMoved = false;
    bool wrrookMoved = false;
    bool blrookMoved = false;
    bool brrookMoved = false;
    /* Initialize Board */
    initializeBoard(&b);

    printf("Welcome to Chesspionage!\nPlease select from the following options:\n1. Player vs Player\n2. Player vs Computer\n");
    scanf("%d", &gameMode);

    if (gameMode == 1)
    {
        printf("\nWhite goes first. Let the games begin!\n");
    }
    if (gameMode == 2)
    {
        printf("Select Your Team Color:\n1. White\n2. Black\n");
        scanf("%d", &playerColor);
        if(playerColor == 1)
        {
            status = 1;
        }
        else if (playerColor == 2)
        {
            status = 2;
        }
    }

    while (gameActive)
    {
        if (status == 1)
        {
            if (gameMode == 2 && playerColor == 2)
            {
                printf("\nIt's the Black Player's turn\n");
                currentMove = BLACK;
            }
            else
            {
                printf("\nIt's the White Player's turn\n");
                currentMove = WHITE;
            }
        }

        else if (status == 2)
        {
            if (gameMode == 2)
            {
                printf("\nIt's the Computer's turn\n");
                currentMove = (playerColor == 1) ? BLACK : WHITE;
                aiTurn(&b, currentMove);
                status = 1;
                continue;
            }

            else if (gameMode == 1)
            {
                printf("\nIt's the Black Player's turn\n");
                currentMove = BLACK;
            }
        }

        check = isCheck(&b, &m, currentMove);

        if (check)
        {
            printf("%s is in check!\n", (currentMove == BLACK) ? "Black" : "White");
        }

        validInput = false;

        while (!validInput)
        {
            printf("\n");

            printBoard(&b);

            printf("Enter the coordinates of the piece to move (x0 y0): ");
            scanf("%d %d", &m.x0, &m.y0);

            struct Piece *piece = b.board[m.y0 - 1][m.x0 - 1];

            if (m.x0 < 1 || m.x0 > 8 || m.y0 < 1 || m.y0 > 8)
            {
                printf("\nInvalid coordinates.\n");
                continue;
            }

            if (piece->color == NONE && piece->piece == EMPTY)
            {
                printf("No piece at that square\n");
                continue;
            }

            if (status == 1 && playerColor == 1 && piece->color == BLACK)
            {
                printf("Not your piece!\n");
                continue;
            }

            if (status == 2 && playerColor == 2 && piece->color == WHITE)
            {
                printf("Not your piece!\n");
                continue;
            }

            printf("Piece at square [%d, %d]: ", m.x0, m.y0);
            getPiece(&m, &b, piece);

            printf("Enter the coordinates of the destination (x1 y1): ");
            scanf("%d %d", &m.x1, &m.y1);

            if (m.x1 < 1 || m.x1 > 8 || m.y1 < 1 || m.y1 > 8)
            {
                printf("Can't put a piece there.\n");
                continue;
            }
            
            if (hasWKingMoved(&b) == true)
            {
                wkingMoved = true;
            }
            
            if (hasBKingMoved(&b) == true)
            {
                bkingMoved = true;
            }
            
            if (hasWLRookMoved(&b) == true)
            {
                wlrookMoved = true;
            }
            
            if (hasWRRookMoved(&b) == true)
            {
                wrrookMoved = true;
            }
            
            if (hasBLRookMoved(&b) == true)
            {
                blrookMoved = true;
            }
            
            if (hasBRRookMoved(&b) == true)
            {
                brrookMoved = true;
            }
            
            if ((m.x0 == 5 && m.y0 == 1 && m.x1 == 3 && m.y1 == 1 && piece->piece == KING && piece->color == WHITE && (wkingMoved == true || wlrookMoved == true) && check == false) || (m.x0 == 5 && m.y0 == 1 && m.x1 == 7 && m.y1 == 1 && piece->piece == KING && piece->color == WHITE && (wkingMoved == true || wrrookMoved == true) && check == false))
            {
                printf("Either King or Rook has already moved. Cannot castle.\n");
                continue;
            }
            
            if ((m.x0 == 5 && m.y0 == 8 && m.x1 == 3 && m.y1 == 8 && piece->piece == KING && piece->color == BLACK && (bkingMoved == true || blrookMoved == true) && check == false) || (m.x0 == 5 && m.y0 == 8 && m.x1 == 7 && m.y1 == 8 && piece->piece == KING && piece->color == BLACK && (bkingMoved == true || brrookMoved == true) && check == false))
            {
                printf("Either King or Rook has already moved. Cannot castle.\n");
                continue;
            }

            if (isValid(&b, &m, currentMove))
            {
                movePiece(&m, &b);
                
                if (m.x0 == 5 && m.y0 == 1 && m.x1 == 3 && m.y1 == 1 && piece->piece == KING && piece->color == WHITE)
                {
                    castleWQueenside(&b);
                    printf("White King has been castled queenside!");
                }
                
                if (m.x0 == 5 && m.y0 == 1 && m.x1 == 7 && m.y1 == 1 && piece->piece == KING && piece->color == WHITE)
                {
                    castleWKingside(&b);
                    printf("White King has been castled kingside!");
                }
                
                if (m.x0 == 5 && m.y0 == 8 && m.x1 == 3 && m.y1 == 8 && piece->piece == KING && piece->color == BLACK)
                {
                    castleBQueenside(&b);
                    printf("Black King has been castled queenside!");
                }
                
                if (m.x0 == 5 && m.y0 == 8 && m.x1 == 7 && m.y1 == 8 && piece->piece == KING && piece->color == BLACK)
                {
                    castleBKingside(&b);
                    printf("Black King has been castled kingside!");
                }

                if (isCheckmate(&b, currentMove == BLACK ? WHITE : BLACK))
                {
                    printf("Checkmate! %s wins!\n", (currentMove == BLACK) ? "Black" : "White");
                    gameActive = false;
                    break;
                }
                
                if (isPromotion(&b) == true)
                {
                    printf("Pawn detected at end of board! Choose which piece to promote the pawn to:\n1. Queen\n2. Rook\n3. Bishop\n4. Knight\nChoice: ");
                    scanf("%d", &promoteChoice);
                    
                    promotePawn(&b, promoteChoice);
                }

                if(check){
                    printf("%s King is in check!\n", (currentMove == BLACK) ? "Black" : "White");
                }

                status = (status == 1) ? 2 : 1;
                validInput = true;
            }

            else
            {
                printf("Invalid move.\n");
                continue;
            }
        }
    }

    return 0;
}