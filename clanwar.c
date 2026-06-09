#include "clanwar.h"

int insideMap(int row, int col)
{
    return row >= 0 &&
           row < WAR_MAP &&
           col >= 0 &&
           col < WAR_MAP;
}

int isRedPiece(char piece)
{
    return piece == 'r' || piece == 'R';
}

int isBlackPiece(char piece)
{
    return piece == 'b' || piece == 'B';
}

int isKing(char piece)
{
    return piece == 'R' || piece == 'B';
}

int canCapture(Battlefield *arena,
               int row,
               int col)
{
    char piece = arena->troops[row][col];

    int directions[4][2] =
    {
        {-1,-1},
        {-1, 1},
        { 1,-1},
        { 1, 1}
    };

    for(int i=0;i<4;i++)
    {
        int dr = directions[i][0];
        int dc = directions[i][1];

        if(!isKing(piece))
        {
            if(piece == 'r' && dr > 0)
                continue;

            if(piece == 'b' && dr < 0)
                continue;
        }

        int middleRow = row + dr;
        int middleCol = col + dc;

        int landRow = row + 2*dr;
        int landCol = col + 2*dc;

        if(!insideMap(landRow, landCol))
            continue;

        char middle =
            arena->troops[middleRow][middleCol];

        if(piece == 'r' || piece == 'R')
        {
            if(isBlackPiece(middle) &&
               arena->troops[landRow][landCol] == '.')
            {
                return 1;
            }
        }

        if(piece == 'b' || piece == 'B')
        {
            if(isRedPiece(middle) &&
               arena->troops[landRow][landCol] == '.')
            {
                return 1;
            }
        }
    }

    return 0;
}
int playerHasCapture(Battlefield *arena,
                     char troop)
{
    for(int row=0; row<WAR_MAP; row++)
    {
        for(int col=0; col<WAR_MAP; col++)
        {
            char piece = arena->troops[row][col];

            if(troop == 'r' &&
               isRedPiece(piece) &&
               canCapture(arena,row,col))
            {
                return 1;
            }

            if(troop == 'b' &&
               isBlackPiece(piece) &&
               canCapture(arena,row,col))
            {
                return 1;
            }
        }
    }

    return 0;
}
int isLegalMove(Battlefield *arena,
                int fromRow,
                int fromCol,
                int toRow,
                int toCol,
                char troop)
{
    if (!insideMap(fromRow, fromCol) ||
        !insideMap(toRow, toCol))
    {
        return 0;
    }

    if (arena->troops[toRow][toCol] != '.')
    {
        return 0;
    }

    char piece = arena->troops[fromRow][fromCol];

    if (troop == 'r' && !isRedPiece(piece))
    {
        return 0;
    }

    if (troop == 'b' && !isBlackPiece(piece))
    {
        return 0;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (colDiff < 0)
        colDiff = -colDiff;

    int mustCapture = playerHasCapture(arena, troop);

    if (!isKing(piece))
    {
        if (piece == 'r')
        {
            if (!mustCapture &&
                rowDiff == -1 &&
                colDiff == 1)
            {
                return 1;
            }

            if (rowDiff == -2 &&
                colDiff == 2)
            {
                int midRow = (fromRow + toRow) / 2;
                int midCol = (fromCol + toCol) / 2;

                if (isBlackPiece(
                        arena->troops[midRow][midCol]))
                {
                    return 2;
                }
            }
        }

        if (piece == 'b')
        {
            if (!mustCapture &&
                rowDiff == 1 &&
                colDiff == 1)
            {
                return 1;
            }

            if (rowDiff == 2 &&
                colDiff == 2)
            {
                int midRow = (fromRow + toRow) / 2;
                int midCol = (fromCol + toCol) / 2;

                if (isRedPiece(
                        arena->troops[midRow][midCol]))
                {
                    return 2;
                }
            }
        }
    }
    else
    {
        if (!mustCapture &&
            (rowDiff == 1 || rowDiff == -1) &&
            colDiff == 1)
        {
            return 1;
        }

        if ((rowDiff == 2 || rowDiff == -2) &&
            colDiff == 2)
        {
            int midRow = (fromRow + toRow) / 2;
            int midCol = (fromCol + toCol) / 2;

            char middle =
                arena->troops[midRow][midCol];

            if ((piece == 'R' &&
                 isBlackPiece(middle)) ||
                (piece == 'B' &&
                 isRedPiece(middle)))
            {
                return 2;
            }
        }
    }

    return 0;
}

int makeMove(Battlefield *arena,
             int fromRow,
             int fromCol,
             int toRow,
             int toCol)
{
    char piece =
        arena->troops[fromRow][fromCol];

    int moveType =
        isLegalMove(arena,
                    fromRow,
                    fromCol,
                    toRow,
                    toCol,
                    (piece == 'r' || piece == 'R')
                        ? 'r'
                        : 'b');

    if (moveType == 0)
    {
        return 0;
    }

    arena->troops[toRow][toCol] = piece;
    arena->troops[fromRow][fromCol] = '.';

    if (moveType == 2)
    {
        int midRow = (fromRow + toRow) / 2;
        int midCol = (fromCol + toCol) / 2;

        arena->troops[midRow][midCol] = '.';
    }

    return moveType;
}
void promoteHeroes(Battlefield *arena)
{
    for (int col = 0; col < WAR_MAP; col++)
    {
        if (arena->troops[0][col] == 'r')
        {
            arena->troops[0][col] = 'R';
        }

        if (arena->troops[WAR_MAP - 1][col] == 'b')
        {
            arena->troops[WAR_MAP - 1][col] = 'B';
        }
    }
}

int playerHasMoves(Battlefield *arena,
                   char troop)
{
    for (int row = 0; row < WAR_MAP; row++)
    {
        for (int col = 0; col < WAR_MAP; col++)
        {
            char piece =
                arena->troops[row][col];

            if (troop == 'r' &&
                !isRedPiece(piece))
            {
                continue;
            }

            if (troop == 'b' &&
                !isBlackPiece(piece))
            {
                continue;
            }

            for (int dr = -2; dr <= 2; dr++)
            {
                for (int dc = -2; dc <= 2; dc++)
                {
                    if (isLegalMove(arena,
                                    row,
                                    col,
                                    row + dr,
                                    col + dc,
                                    troop))
                    {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int checkWinner(Battlefield *arena)
{
    int redCount = 0;
    int blackCount = 0;

    for (int row = 0; row < WAR_MAP; row++)
    {
        for (int col = 0; col < WAR_MAP; col++)
        {
            char piece =
                arena->troops[row][col];

            if (isRedPiece(piece))
            {
                redCount++;
            }

            if (isBlackPiece(piece))
            {
                blackCount++;
            }
        }
    }

    if (redCount == 0)
    {
        return 2;
    }

    if (blackCount == 0)
    {
        return 1;
    }

    if (!playerHasMoves(arena, 'r'))
    {
        return 2;
    }

    if (!playerHasMoves(arena, 'b'))
    {
        return 1;
    }

    return 0;
}