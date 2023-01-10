/*
Author: Sushant Guha && Dinyar Islam
Class: ECE4122

Description: Final Project

What is the purpose of this file?
A custom class that defines a multi-threaded chess engine.
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "thc.h"
#include <float.h>
#include <thread>
#include <mutex>

// Length of the chess board.
#define DIMENSION 8

// Maximum values for chess evaluations.
#define MAX_VAL DBL_MAX
#define MIN_VAL -DBL_MAX

// mte - multi-threaded engine

// Defining the namespace used to access the Engine class.
namespace mte {

    /*
        The Engine class that contains all the variables and classes to run the chess engine.
    */
    class Engine {
    private:
        // Defining all the private data

        // Value of the pieces
        enum pieceValues { pawnVal = 10, bishopVal = 30, knightVal = 30, rookVal = 50, queenVal = 90, kingVal = 900 };

        /*
            Piece-square tables for each piece on the chess board.
            These well-known piece-square tables from the chess-programming-wiki contain double values that signifiy the 'value' of a particular piece at a particular position. Some pieces have the same position values regardless of their colour, whereas others depend on the colour (black/white).
        */
        double pawnEvalWhite[DIMENSION][DIMENSION] = {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} ,
            {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
            {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
            {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
            {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
            {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
            {0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
        };

        double pawnEvalBlack[DIMENSION][DIMENSION] = {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, // Eight
            {0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5}, // Seventh
            {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5}, // Sixth
            {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0}, // Fifth
            {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5}, // Fourth
            {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0}, // Third
            {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0}, // Second
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} // First
        };

        double knightEval[DIMENSION][DIMENSION] = {
            {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
            {-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
            {-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
            {-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
            {-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
            {-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
            {-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
            {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
        };

        double bishopEvalWhite[DIMENSION][DIMENSION] = {
            { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
            {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
            {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
            {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
            {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
            {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
            {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
            {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
        };

        double bishopEvalBlack[DIMENSION][DIMENSION] = {
            {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}, // 8
            {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0}, // 7
            {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0}, // 6
            {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0}, // 5
            {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0}, // 4
            {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0}, // 3
            {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0}, // 2
            { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0} // 1
        };

        double rookEvalWhite[DIMENSION][DIMENSION] = {
            { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, // 1
            {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5}, // 2
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 3
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 4
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 5
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 6
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 7
             {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0} // 8
        };

        double rookEvalBlack[DIMENSION][DIMENSION] = {
            {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}, // 8
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 7
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 6
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 5
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 4
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5}, // 3
            {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5}, // 2
            { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} // 1

        };

        double evalQueen[DIMENSION][DIMENSION] = {
            { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
            {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
            {-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
            {-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
            {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
            {-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
            {-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
            {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
        };

        double kingEvalWhite[DIMENSION][DIMENSION] = {

            { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
            {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
            {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
            {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}
        };

        double kingEvalBlack[DIMENSION][DIMENSION] = {
            {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}, // 8
            {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0}, // 7
            {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0}, // 6
            {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0}, // 5
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}, // 4
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}, // 3
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}, // 2
            { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},// 1

        };

        // Private function definitions - Comments that describe their purpose are written at their implementation.

        double getPieceValue(thc::ChessRules* inBoard, int x, int y);
        double minimax(thc::ChessRules inBoard, int currDep, bool white, std::mutex* mtx, double* bstVal, int* idx, int inIdx);
        void pretty_display(thc::ChessRules inBoard);

    public:

        // The Chess Rules class used to ensure the rules of chess are followed.
        thc::ChessRules cr;

        // The depth of the engine for the minimax function.
        int depth = 3; // This is the default value.


        // Public function definitions:

        // The default constructor:
        Engine() {}

        // Get best move function
        thc::Move getBestMove(thc::ChessRules inBoard);

        // Display the position to the console.
        void display_position(thc::ChessRules inBoard, const std::string& description);

        // Function to evaluate the current position.
        double evaluateBoard(thc::ChessRules* inBoard);

        // Function to make a move following the rules of Chess given an input.
        bool makeMove(char s[20]);

        // Function to determine whether the curent position is a check mate.
        int isMate(thc::ChessRules inBoard);

        // Function to determine whether a position is a draw.
        int isADraw(thc::ChessRules inBoard, bool whiteAsking);

    };

    // Function implementations.

    /*
        Private function to display the board in the console.
        Used primarily for debugging and testing the engine.
    */
    void Engine::pretty_display(thc::ChessRules inBoard) {

        for (int i = 0; i < DIMENSION; i++) {
            if (i == 0) {
                for (int j = 0; j < DIMENSION * 4; j++) {
                    printf("_");
                }
                printf("\n");
            }
            for (int j = 0; j < DIMENSION; j++) {
                if (j == 0) {
                    printf("|", DIMENSION - i);
                }
                printf(" %c |", inBoard.squares[i * DIMENSION + j]);
                if (j == DIMENSION - 1) {
                    printf(" %d", 8 - i);
                }
            }
            printf("\n");
            for (int j = 0; j < DIMENSION * 2; j++) {
                printf("--");
            }

            printf("\n");
            if (i == (DIMENSION - 1)) {
                char cOut = 'A';
                printf("  ");
                for (int j = 0; j < DIMENSION; j++) {
                    printf("%c   ", cOut);
                    cOut++;
                }
                printf("\n");
            }
        }
    }

    /*
        Public function to display the board and its fen in the console.
        Used primarily for debugging and testing.
    */
    void Engine::display_position(thc::ChessRules inBoard, const std::string& description)
    {
        std::string fen = inBoard.ForsythPublish();
        std::string s = inBoard.ToDebugStr();
        printf("%s\n", description.c_str());
        printf("FEN (Forsyth Edwards Notation) = %s\n", fen.c_str());
        // printf("Position = %s\n", s.c_str());
        this->pretty_display(inBoard);
    }


    /*
        Get the 'value' of the particular piece at that particular position
        Considers the colour of the piece, its position, and its inherent value.
        Uses the piece-square tables.
        If the piece is white, the returned value is positive. If black, it is negative.
    */
    double Engine::getPieceValue(thc::ChessRules* inBoard, int x, int y) {
        if (x < 0 || x >= DIMENSION || y < 0 || y >= DIMENSION) {
            // Out of bounds
            return 0.0;
        }
        char c = inBoard->squares[(x * DIMENSION) + y];

        if (c == 'r') {
            // black rook
            return -(rookEvalBlack[y][x] + (double) rookVal);
        }
        if (c == 'R') {
            return rookEvalWhite[y][x] + (double) rookVal;
        }
        if (c == 'n') {
            return -(knightEval[y][x] + (double) knightVal);
        }
        if (c == 'N') {
            return (knightEval[y][x] + (double) knightVal);
        }
        if (c == 'b') {
            return -(bishopEvalBlack[y][x] + (double) bishopVal);
        }
        if (c == 'B') {
            return bishopEvalWhite[y][x] + (double) bishopVal;
        }
        if (c == 'q') {
            return -(evalQueen[y][x] + (double) queenVal);
        }
        if (c == 'Q') {
            return (evalQueen[y][x] + (double) queenVal);
        }
        if (c == 'k') {
            return -(kingEvalBlack[y][x] + (double) kingVal);
        }
        if (c == 'K') {
            return kingEvalWhite[y][x] + (double) kingVal;
        }
        if (c == 'p') {
            return -(pawnEvalBlack[y][x] + (double) pawnVal);
        }
        if (c == 'P') {
            return pawnEvalWhite[y][x] + (double) pawnVal;
        }
        // This is an empty square.
        return 0.0;
    }

    /*
        Returns the value of white - value of black. (Black value sutracted from white value)
        If the value is positive, white is better off.
        Uses the getPieceValue function for individual pieces.
    */
    double Engine::evaluateBoard(thc::ChessRules* inBoard) {
        double value = 0.0;
        for (int i = 0; i < DIMENSION; i++) {
            for (int j = 0; j < DIMENSION; j++) {
                value += this->getPieceValue(inBoard, i, j);
            }
        }
        return value;
    }

    /*
        A public function to return the best move the player can play.
        Calls the minimax function on every legal move.
        Each instance of the minimax function is called on a different thread.
        Uses std::thread to implement this multithreading.
    */
    thc::Move Engine::getBestMove(thc::ChessRules inBoard) {
        std::vector<thc::Move> moves;
        std::vector<bool> check;
        std::vector<bool> mate;
        std::vector<bool> stalemate;
        inBoard.GenLegalMoveList(moves, check, mate, stalemate); // Uses the thc library.
        unsigned int len = moves.size();

        if (len == 0) {
            // NO possible moves. Means a stalemate.
            printf("NO LEGAL MOVES AVAILABLE\n");
            thc::Move mv;
            mv.NaturalIn(&cr, "e9");// Returning an illegal move.
            return mv;
        }

        bool white = inBoard.white;

        double best = MIN_VAL; // Set to -inf if player is white.
        thc::Move bestMove = moves[0];

        if (!white) {
            best = MAX_VAL; // to +inf if player is black.
        }

        // Using a mutex to lock access to the 'best' variable
        // The 'best' variable contains the best move for the player calling the getBestMove function.
        std::mutex bestMutex;
        int index = 0;
        unsigned int maxNThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;


        // Looping through every possible move.
        for (unsigned int i = 0; i < len; i++) {

            // Checking if checkmate is possible with this move.
            if (mate[i]) {
                // The current player can check mate with this move. 
                // This is the best possible outcome.
                for (auto& th : threads)
                {
                    th.join();
                }
                return moves[i];
            }
            // Not a checkmate (The most likely outcome)

            // Create a copy of the current board and make the new move.
            thc::ChessRules copy = thc::ChessRules(inBoard);
            copy.PlayMove(moves[i]);

            // Multi-threaded call to the minimax function.
            // std::thread td(&minimax, copy, depth - 1, !white, &bestMutex, &best, &index, i);
            threads.push_back(std::thread(&Engine::minimax, this, copy, depth - 1, !white, &bestMutex, &best, &index, i));
        }


        // Joining the threads.
        for (auto& th : threads)
        {
            th.join();
        }

        // Returning the best move.
        return moves[index];
    }

    /*
        Function to determine if the current position is a stale mate / check mate.
        Returns 0 if it is neither.
        Returns 1 if WHITE is stalemated.
        Returns 2 if BLACK is stalemated.
        Returns 3 if WHITE is checkmated.
        Returns 4 if BLACK is checkmated.
    */
    int Engine::isMate(thc::ChessRules inBoard) {
        thc::TERMINAL eval_final_position;
        // Uses the thc library.
        bool legal2 = cr.Evaluate(eval_final_position);
        if ((eval_final_position == thc::TERMINAL_WCHECKMATE)) {
            return 3;
        }
        if ((eval_final_position == thc::TERMINAL_BCHECKMATE)) {
            return 4;
        }
        if ((eval_final_position == thc::TERMINAL_WSTALEMATE)) {
            return 1;
        }
        if ((eval_final_position == thc::TERMINAL_BSTALEMATE)) {
            return 2;
        }
        return 0; // No special cases regarding this position.
    }


    /*
        Determines whether the current position is a draw according to the Chess Rules.
        Uses the thc library.
    */
    int Engine::isADraw(thc::ChessRules inBoard, bool whiteAsking) {
        thc::DRAWTYPE result;
        return inBoard.IsDraw(whiteAsking, result);
    }


    /*
        The minimax function - Recursively determines the best move.
        It returns the evaluation of the best position.
        If it is white's turn, then we're trying to find the maximum possible value.
        If it is black's position, we're trying to find the minimum possible value.
    */
    double Engine::minimax(thc::ChessRules inBoard, int currDep, bool white, std::mutex* mtx, double* bstVal, int* idx, int inIdx) {

        // The base case
        if (currDep == 0) {
            return this->evaluateBoard(&inBoard);
        }

        // Reduce the depth of the minimax search.
        currDep--;
        // Generate all the legal moves.
        std::vector<thc::Move> moves;
        std::vector<bool> check;
        std::vector<bool> mate;
        std::vector<bool> stalemate;
        inBoard.GenLegalMoveList(moves, check, mate, stalemate);

        // Iterate through the list of legal moves.
        unsigned int len = moves.size();

        // Initialise the best possible move value
        double best = MIN_VAL; // Set to -inf if player is white.
        if (!white) {
            best = MAX_VAL; // to -inf if player is black.
        }

        bool stMate = false;
        thc::Move stMateMove;
        int stMateIdx = 0;

        bool drawPossible = false;
        thc::Move drawMove;
        int drawIdx = 0;

        for (unsigned int i = 0; i < len; i++) {

            // Checking if checkmate is possible with this move.
            if (mate[i]) {
                // The current player can check mate with this move. 
                // This is the best possible outcome. 
                if (white) {
                    best = MAX_VAL;
                    break;
                }
                else {
                    best = MIN_VAL;
                    break;
                }
            }
            // Not a checkmate (The most likely outcome)



            // Create a copy of the current board and make the new move.
            thc::ChessRules copy = thc::ChessRules(inBoard);
            copy.PlayMove(moves[i]);

            // Check for stalemate.
            if (stalemate[i]) {
                stMate = true;
                stMateMove = moves[i];
                stMateIdx = i;
                // return evaluateBoard(&copy);
                continue;
            }

            // Check to see if the position is a draw if this move is played.
            if (isADraw(copy, white)) {
                drawPossible = true;
                drawMove = moves[i];
                drawIdx = i;
                continue;
            }

            // Recursive call to determine 
            double outcome = this->minimax(copy, currDep, !white, mtx, &best, idx, inIdx);

            if ((white && (outcome > best)) || (!white && (outcome < best))) {
                best = outcome;

                // Alpha-beta pruning
                if (currDep != depth + 2) {
                    // lock access not needed to access the parent's "best" variable.
                    // The parent's best variable is stored in *bstVal
                    if (!white && (best <= *bstVal)) {
                        return best;
                    }
                    else if (white && (best >= *bstVal)) {
                        return best;
                    }
                }
                else {
                    // Lock access IS needed to access the parent's "best" variables
                }
            }
        }

        // Could not checkmate. 
        // Then, if possible, stalemate the game current player is in worse position.
        // NOTE:
            // Handling stalemates in a unique way will reduce stalemates from good position.
            // And will cause stalemate when in a bad position.

        if (stMate) {
            double currEval = evaluateBoard(&inBoard);
            if ((white && currEval < -10.0) || (!white && currEval > 10.0)) {
                // If current player in a bad position, then choose stalemate option.
                inBoard.PlayMove(stMateMove);
                best = evaluateBoard(&inBoard);
            }
        }


        // Performing a similar calculationg for a draw rather than stalemate. 
        if (drawPossible) {
            double currEval = evaluateBoard(&inBoard);
            if ((white && currEval < -10.0) || (!white && currEval > 10.0)) {
                // If current player in a bad position, then choose stalemate option.
                inBoard.PlayMove(drawMove);
                best = evaluateBoard(&inBoard);
            }
        }

        // Checking if the best value at this stage is better than any of the other threads.
        // Using the lock to access the shared variable.
        if (currDep == depth - 2) {
            bool parentWhite = !white;
            // Rewrite the value to best var if necessary.
            while (mtx->try_lock()) {
                std::this_thread::yield();
            }

            if ((parentWhite && (best > *bstVal)) || (!parentWhite && (best < *bstVal))) {
                *bstVal = best;
                *idx = inIdx;
            }

            mtx->unlock();

        }
        return best;
    }

    bool Engine::makeMove(char s[20]) {

        // Making a move that conforms to the chess rules.
        // Done so that all legal moves can be generated later on.
        thc::Move mv;
        if (!mv.NaturalIn(&cr, s)) {
            printf("ERROR INVALID MOVE\n");
            return false;
        }
        cr.PushMove(mv);
        return true;
    }

}

