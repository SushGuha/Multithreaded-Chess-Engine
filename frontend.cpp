/*
Author: Dinyar Islam && Sushant Guha
Class: ECE4122

Description: Final Project

What is the purpose of this file?
Application that uses SFML to create a complex chess game.
*/

#include <sstream>
#include <SFML/Graphics.hpp>
#include "iostream"
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "MtEngine.h"

using namespace sf;
using namespace std;

/*
 *  Tile custom class
 *
 */
class Tile
{
public:
    Sprite tile; // tile sprite
    bool piecePresent = false; // does tile have a chess piece on it
    bool light; // type of tile light/dark
    std::string notation; // chess notation for tile
    bool whitePiece; // Indicates whether a white piece is sitting on the current tile.
    sf::Sprite currentPiece;
    bool isKing = false;
    bool isPawn = false;
    // constructor
    Tile() {
        Sprite tmp; // Setting the initial sprite to a dummy sprite.
        tmp.setScale(0.0, 0.0);
        tmp.setPosition(20020.0f, 20020.0f);
        this->currentPiece = tmp;
        this->isKing = false;
        this->isPawn = false;
    }
};

// void engineMove(mte::Engine* eng, bool* whiteTurn);

// The main function.
int main()
{

    // Variable to determine whose turn it is.
    bool whiteTurn = true;

    // Variable to indicate whether the human player is white or black
    bool playerColourWhite = false;

    // Create a video mode object
    VideoMode vm(1260, 1088);

    // Create and open a window for the game
    RenderWindow window(vm, "Chess");

    //ADD CODE
        // Create a video mode object for start menu
    VideoMode vm2(630, 544);

    // Create and open a window for the game start menu
    RenderWindow window2(vm2, "Start Menu");


    //ADD CODE
    // Create a video mode object for start menu
    // VideoMode vm3(630, 544);

    // Create and open a window for the game start menu
    // RenderWindow window3(vm3, "Piece Promotion");

    // Background for window2
    RectangleShape textureWindow2Background;
    textureWindow2Background.setFillColor(Color::Red);
    textureWindow2Background.setPosition(100, 100);
    textureWindow2Background.setSize(Vector2f(625, 540));

    // start flag
    bool startFlag = false;
    //

    // Make the light tile texture
    Texture textureLightTile;
    textureLightTile.loadFromFile("./resources1/blue_light.jpeg");

    // Make the dark tile texture
    Texture textureDarkTile;
    textureDarkTile.loadFromFile("./resources1/blue_dark.jpeg");

    // Make movement board
    Texture textureMoveBoard;
    textureMoveBoard.loadFromFile("./resources1/move_record_gray.png");

    Sprite spriteMoveBoard;
    spriteMoveBoard.setTexture(textureMoveBoard);
    spriteMoveBoard.setScale(0.9, 1);
    spriteMoveBoard.setPosition(1088, 5);

    // Setting the light and dark tile coordinates to map out the chess board.
    // tile coordinates
    int light_tile_x = 0;
    int light_tile_y = 0;
    int dark_tile_x = 128;
    int dark_tile_y = 0;

    // light tiles
    Sprite lightTiles[32];
    for (int i = 0; i < 32; i++)
    {
        if (!(i % 8) && i != 0)
        {
            light_tile_x = 0;
        }
        else if (!(i % 4) && i != 0)
        {
            light_tile_x = 128;
        }
        if (!(i % 4) && i != 0)
        {
            light_tile_y += 128;
        }
        lightTiles[i].setTexture(textureLightTile);
        lightTiles[i].setScale(0.5, 0.5);
        lightTiles[i].setPosition(light_tile_x, light_tile_y);
        light_tile_x += 256;
    }

    // dark tiles
    Sprite darkTiles[32];
    for (int i = 0; i < 32; i++)
    {
        if (!(i % 8) && i != 0)
        {
            dark_tile_x = 128;
        }
        else if (!(i % 4) && i != 0)
        {
            dark_tile_x = 0;
        }
        if (!(i % 4) && i != 0)
        {
            dark_tile_y += 128;
        }
        darkTiles[i].setTexture(textureDarkTile);
        darkTiles[i].setScale(0.5, 0.5);
        darkTiles[i].setPosition(dark_tile_x, dark_tile_y);
        dark_tile_x += 256;
    }

    // vector for storing all tiles
    vector<Sprite> tiles;
    int lightTileIdx = 0;
    int darkTileIdx = 0;

    // starting from top left corner
    for (int i = 0; i < 64; i++)
    {
        int numberIndex = 8 - (int) i / 8;
        if (numberIndex % 2 == 0) { // Even represents starting with a light tile.
            if (i % 2 == 1)
            {
                tiles.push_back(darkTiles[darkTileIdx]);
                darkTileIdx++;
            }
            else
            {
                tiles.push_back(lightTiles[lightTileIdx]);
                lightTileIdx++;
            }
        }
        else {
            if (i % 2 == 0)
            {
                tiles.push_back(darkTiles[darkTileIdx]);
                darkTileIdx++;
            }
            else
            {
                tiles.push_back(lightTiles[lightTileIdx]);
                lightTileIdx++;
            }
        }

    }

    // Make a white pieces
    Texture textureWhiteKing;
    Texture textureWhiteQueen;
    Texture textureWhiteRook;
    Texture textureWhiteBishop;
    Texture textureWhiteKnight;
    Texture textureWhitePawn;

    textureWhiteKing.loadFromFile("./resources2/WhiteKing.png");
    Sprite spriteWhiteKing;
    spriteWhiteKing.setTexture(textureWhiteKing);
    spriteWhiteKing.setScale(0.4, 0.4);
    spriteWhiteKing.setPosition(512, 896);

    textureWhiteQueen.loadFromFile("./resources2/WhiteQueen.png");
    Sprite spriteWhiteQueen;
    spriteWhiteQueen.setTexture(textureWhiteQueen);
    spriteWhiteQueen.setScale(0.4, 0.4);
    spriteWhiteQueen.setPosition(384, 896);

    textureWhiteRook.loadFromFile("./resources2/WhiteRook.png");
    Sprite spriteWhiteRookDark;
    spriteWhiteRookDark.setTexture(textureWhiteRook);
    spriteWhiteRookDark.setScale(0.4, 0.4);
    spriteWhiteRookDark.setPosition(0, 896);
    Sprite spriteWhiteRookLight;
    spriteWhiteRookLight.setTexture(textureWhiteRook);
    spriteWhiteRookLight.setScale(0.4, 0.4);
    spriteWhiteRookLight.setPosition(896, 896);

    textureWhiteBishop.loadFromFile("./resources2/WhiteBishop.png");
    Sprite spriteWhiteBishopDark;
    spriteWhiteBishopDark.setTexture(textureWhiteBishop);
    spriteWhiteBishopDark.setScale(0.4, 0.4);
    spriteWhiteBishopDark.setPosition(256, 896);
    Sprite spriteWhiteBishopLight;
    spriteWhiteBishopLight.setTexture(textureWhiteBishop);
    spriteWhiteBishopLight.setScale(0.4, 0.4);
    spriteWhiteBishopLight.setPosition(640, 896);

    textureWhiteKnight.loadFromFile("./resources2/WhiteKnight.png");
    Sprite spriteWhiteKnightDark;
    spriteWhiteKnightDark.setTexture(textureWhiteKnight);
    spriteWhiteKnightDark.setScale(0.4, 0.4);
    spriteWhiteKnightDark.setPosition(768, 896);
    Sprite spriteWhiteKnightLight;
    spriteWhiteKnightLight.setTexture(textureWhiteKnight);
    spriteWhiteKnightLight.setScale(0.4, 0.4);
    spriteWhiteKnightLight.setPosition(128, 896);

    textureWhitePawn.loadFromFile("./resources2/WhitePawn.png");
    Sprite spriteWhitePawn[8];
    int whitePawnX = 0;
    int whitePawnY = 0;
    for (int i = 0; i < 8; i++)
    {
        spriteWhitePawn[i].setTexture(textureWhitePawn);
        spriteWhitePawn[i].setScale(0.4, 0.4);
        spriteWhitePawn[i].setPosition(whitePawnX, 768);
        whitePawnX += 128;
    }

    // Make black pieces
    Texture textureBlackKing;
    Texture textureBlackQueen;
    Texture textureBlackRook;
    Texture textureBlackBishop;
    Texture textureBlackKnight;
    Texture textureBlackPawn;

    textureBlackKing.loadFromFile("./resources2/BlackKing.png");
    Sprite spriteBlackKing;
    spriteBlackKing.setTexture(textureBlackKing);
    spriteBlackKing.setScale(0.4, 0.4);
    spriteBlackKing.setPosition(512, 0);

    textureBlackQueen.loadFromFile("./resources2/BlackQueen.png");
    Sprite spriteBlackQueen;
    spriteBlackQueen.setTexture(textureBlackQueen);
    spriteBlackQueen.setScale(0.4, 0.4);
    spriteBlackQueen.setPosition(384, 0);

    textureBlackRook.loadFromFile("./resources2/BlackRook.png");
    Sprite spriteBlackRookDark;
    spriteBlackRookDark.setTexture(textureBlackRook);
    spriteBlackRookDark.setScale(0.4, 0.4);
    spriteBlackRookDark.setPosition(896, 0);
    Sprite spriteBlackRookLight;
    spriteBlackRookLight.setTexture(textureBlackRook);
    spriteBlackRookLight.setScale(0.4, 0.4);
    spriteBlackRookLight.setPosition(0, 0);


    textureBlackBishop.loadFromFile("./resources2/BlackBishop.png");
    Sprite spriteBlackBishopDark;
    spriteBlackBishopDark.setTexture(textureBlackBishop);
    spriteBlackBishopDark.setScale(0.4, 0.4);
    spriteBlackBishopDark.setPosition(640, 0);
    Sprite spriteBlackBishopLight;
    spriteBlackBishopLight.setTexture(textureBlackBishop);
    spriteBlackBishopLight.setScale(0.4, 0.4);
    spriteBlackBishopLight.setPosition(256, 0);

    textureBlackKnight.loadFromFile("./resources2/BlackKnight.png");
    Sprite spriteBlackKnightDark;
    spriteBlackKnightDark.setTexture(textureBlackKnight);
    spriteBlackKnightDark.setScale(0.4, 0.4);
    spriteBlackKnightDark.setPosition(128, 0);
    Sprite spriteBlackKnightLight;
    spriteBlackKnightLight.setTexture(textureBlackKnight);
    spriteBlackKnightLight.setScale(0.4, 0.4);
    spriteBlackKnightLight.setPosition(768, 0);

    textureBlackPawn.loadFromFile("./resources2/BlackPawn.png");
    Sprite spriteBlackPawn[8];
    int blackPawnX = 0;
    int blackPawnY = 0;
    for (int i = 0; i < 8; i++)
    {
        spriteBlackPawn[i].setTexture(textureBlackPawn);
        spriteBlackPawn[i].setScale(0.4, 0.4);
        spriteBlackPawn[i].setPosition(blackPawnX, 128);
        blackPawnX += 128;
    }


    // vector for storing and initializing tile objects
    vector<Tile> tileObjs;
    Tile tempTileObj;
    int letterIdx = 1; // A - H for notation
    int numIdx = 8; // 1 - 8 for notation

    // starting from top left corner
    for (int i = 0; i < 64; i++)
    {
        // set tile sprite
        tempTileObj.tile = tiles[i];

        tempTileObj.isKing = false;
        tempTileObj.isPawn = false;


        // does tile have a piece
        if (numIdx == 1 || numIdx == 2 || numIdx == 7 || numIdx == 8)
        {
            tempTileObj.piecePresent = true;
        }
        else {
            tempTileObj.piecePresent = false;
        }

        // set tile type
        if (numIdx % 2 == 0) {
            if (i % 2)
            {
                tempTileObj.light = false;
            }
            else
            {
                tempTileObj.light = true;
            }
        }
        else {
            if (i % 2)
            {
                tempTileObj.light = true;
            }
            else
            {
                tempTileObj.light = false;
            }
        }

        // set notation for the Tile object.
        if (letterIdx == 1)
        {
            tempTileObj.notation = "a" + to_string(numIdx);
        }
        else if (letterIdx == 2)
        {
            tempTileObj.notation = "b" + to_string(numIdx);
        }
        else if (letterIdx == 3)
        {
            tempTileObj.notation = "c" + to_string(numIdx);
        }
        else if (letterIdx == 4)
        {
            tempTileObj.notation = "d" + to_string(numIdx);
        }
        else if (letterIdx == 5)
        {
            tempTileObj.notation = "e" + to_string(numIdx);
        }
        else if (letterIdx == 6)
        {
            tempTileObj.notation = "f" + to_string(numIdx);
        }
        else if (letterIdx == 7)
        {
            tempTileObj.notation = "g" + to_string(numIdx);
        }
        else if (letterIdx == 8)
        {
            tempTileObj.notation = "h" + to_string(numIdx);
        }

        if (numIdx == 1 || numIdx == 2) {
            tempTileObj.whitePiece = true;
        }
        else if (numIdx == 8 || numIdx == 7) {
            tempTileObj.whitePiece = false;
        }


        // Mapping the pieces onto the correct tile to lay out the chess board.
        if (i == 0) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackRookLight;
        }

        else if (i == 1) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackKnightDark;
        }
        else if (i == 2) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackBishopLight;
        }
        else if (i == 3) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackQueen;
        }
        else if (i == 4) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackKing;
            tempTileObj.isKing = true;
        }
        else if (i == 5) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackBishopDark;
        }
        else if (i == 6) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackKnightLight;
        }
        else if (i == 7) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackRookDark;
        }
        if (i >= 8 && i < 16) {
            // Black Pawns
            tempTileObj.isPawn = true;
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteBlackPawn[i - 8];
        }


        // Laying out the board for white pieces.
        if (i == 56) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteRookDark;
        }
        else if (i == 57) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteKnightLight;
        }
        else if (i == 58) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteBishopDark;
        }
        else if (i == 59) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteQueen;
        }
        else if (i == 60) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteKing;
            tempTileObj.isKing = true;
        }
        else if (i == 61) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteBishopLight;
        }
        else if (i == 62) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteKnightDark;
        }
        else if (i == 63) {
            tempTileObj.piecePresent = true;
            tempTileObj.currentPiece = spriteWhiteRookLight;
            // cout << tempTileObj.notation << endl;
        }
        if (i >= 48 && i < 56) {
            tempTileObj.piecePresent = true;
            // White Pawns
            tempTileObj.isPawn = true;
            tempTileObj.currentPiece = spriteWhitePawn[i - 48];
        }

        // add to vector
        tileObjs.push_back(tempTileObj);

        // update notation indices
        if ((i % 8) == 7 && i != 0)
        {
            letterIdx = 1;
            numIdx--;
        }
        else
        {
            letterIdx++;
        }
    }

    // Make font
    Font font;
    font.loadFromFile("./fonts/Lekton-Bold.ttf");

    // ADD CODE
    // Make Title Text
    Text titleText;
    titleText.setString("Chess");
    titleText.setFont(font);
    titleText.setCharacterSize(100);
    titleText.setFillColor(Color::White);
    titleText.setOutlineColor(Color::Cyan);
    titleText.setOutlineThickness(4);
    titleText.setPosition(200, 0);

    // Make start difficulty text
    int difficultyLevel = 0;
    bool difficultySelected = false;
    Text difficultyLevelText;
    difficultyLevelText.setFont(font);
    difficultyLevelText.setCharacterSize(30);
    difficultyLevelText.setString("Enter Difficulty Level using number pad:"
        "\n\n     1      2      3      4      5"
        "\n    Easy         Medium         Hard");
    difficultyLevelText.setPosition(10, 400);
    difficultyLevelText.setFillColor(Color::White);

    // ADD CODE
    // Make board texture text
    bool textureSelected = false;
    std::string textureInputStr;
    Text textureChoiceText;
    textureChoiceText.setFont(font);
    textureChoiceText.setCharacterSize(30);
    textureChoiceText.setString("        Choose tile texture type:");
    textureChoiceText.setPosition(10, 200);
    textureChoiceText.setFillColor(Color::White);

    Text textureChoiceTextBlue;
    textureChoiceTextBlue.setFont(font);
    textureChoiceTextBlue.setCharacterSize(30);
    textureChoiceTextBlue.setString("       BLUE(b)");
    textureChoiceTextBlue.setPosition(10, 250);
    textureChoiceTextBlue.setFillColor(Color::Blue);


    Text textureChoiceTextBrown;
    textureChoiceTextBrown.setFont(font);
    textureChoiceTextBrown.setCharacterSize(30);
    textureChoiceTextBrown.setString("        RED(r)");
    textureChoiceTextBrown.setPosition(180, 250);
    textureChoiceTextBrown.setFillColor(Color::Red);

    Text textureChoiceTextGray;
    textureChoiceTextGray.setFont(font);
    textureChoiceTextGray.setCharacterSize(30);
    textureChoiceTextGray.setString("        GRAY(g)");
    textureChoiceTextGray.setPosition(320, 250);
    textureChoiceTextGray.setFillColor(Color::White);
    //

    // Make piece shadow text
    bool pieceShadowSelected = false;
    Text pieceShadowText;
    pieceShadowText.setFont(font);
    pieceShadowText.setCharacterSize(30);
    pieceShadowText.setString("        Choose piece texture type:"
        "\n        Shadow(s)     No Shadow(N)");
    pieceShadowText.setPosition(10, 310);
    pieceShadowText.setFillColor(Color::White);

    // Make piece color text
    bool pieceColorSelected = false;
    Text pieceColorText;
    pieceColorText.setFont(font);
    pieceColorText.setCharacterSize(30);
    pieceColorText.setString("               Choose color:"
        "\n            White(w)     Black(p)");
    pieceColorText.setPosition(10, 120);
    pieceColorText.setFillColor(Color::White);


    // board text
    Text boardText[16];

    int boardTextX = 1044;
    int boardTextY = 64;
    for (int i = 0; i < 8; i++)
    {
        boardText[i].setFont(font);
        if (i == 0)
        {
            boardText[i].setString("8");
        }
        else if (i == 1)
        {
            boardText[i].setString("7");
        }
        else if (i == 2)
        {
            boardText[i].setString("6");
        }
        else if (i == 3)
        {
            boardText[i].setString("5");
        }
        else if (i == 4)
        {
            boardText[i].setString("4");
        }
        else if (i == 5)
        {
            boardText[i].setString("3");
        }
        else if (i == 6)
        {
            boardText[i].setString("2");
        }
        else if (i == 7)
        {
            boardText[i].setString("1");
        }
        boardText[i].setCharacterSize(20);
        boardText[i].setPosition(boardTextX, boardTextY);
        boardTextY += 128;
    }
    boardTextX = 64;
    boardTextY = 1044;
    for (int i = 8; i < 16; i++)
    {
        boardText[i].setFont(font);
        if (i == 8)
        {
            boardText[i].setString("a");
        }
        else if (i == 9)
        {
            boardText[i].setString("b");
        }
        else if (i == 10)
        {
            boardText[i].setString("c");
        }
        else if (i == 11)
        {
            boardText[i].setString("d");
        }
        else if (i == 12)
        {
            boardText[i].setString("e");
        }
        else if (i == 13)
        {
            boardText[i].setString("f");
        }
        else if (i == 14)
        {
            boardText[i].setString("g");
        }
        else if (i == 15)
        {
            boardText[i].setString("h");
        }
        boardText[i].setCharacterSize(20);
        boardText[i].setPosition(boardTextX, boardTextY);
        boardTextX += 128;
    }

    //
    RectangleShape selectTile;
    selectTile.setFillColor(Color::Transparent);
    selectTile.setOutlineColor(Color::Red);
    selectTile.setOutlineThickness(5);
    selectTile.setPosition(2000, 2000);
    selectTile.setSize(Vector2f(128, 128));
    int offset = -8;
    if (playerColourWhite) {
        offset = 8;
    }

    // Prepare the sound
    SoundBuffer moveBuffer;
    moveBuffer.loadFromFile("./resources2/move.wav");
    Sound moveSound;
    moveSound.setBuffer(moveBuffer);

    // Capture
    SoundBuffer captureBuffer;
    captureBuffer.loadFromFile("./resources2/capture.wav");
    Sound captureSound;
    captureSound.setBuffer(captureBuffer);

    // Checkmate
    SoundBuffer checkMateBuffer;
    checkMateBuffer.loadFromFile("./resources2/check.wav");
    Sound checkMateSound;
    checkMateSound.setBuffer(checkMateBuffer);

    // Play the checkate sound when the game is opened.
    checkMateSound.play();

    // Defining the instance of the engine custom class in MtEngine.h
    mte::Engine eng;

    // Setting the depth of the engine - This will later be set by the user.
    eng.depth = 3;

    // Storing the number of moves played by the user.
    int numMoves = 0;

    // Defining the clock and the timer variables for the players.
    sf::Clock clock;
    double compTimer = 300; // 5 minutes - Blitz game.
    double playerTimer = 30000000;

    // Game variables to determine end of game.
    bool checkMated = false;
    bool staleMated = false;
    bool playerTimerUp = false;
    bool compTimerUp = false;

    // Vector to display the moves 
    std::vector<std::string> movesDisplayed;

    bool isPieceSelected = false; // Indicates whether the user has clicked a piece of their own colour.
    std::vector <std::string> highlight; // vector to highlight the tiles that user can move to.
    std::vector <sf::RectangleShape> tilesToHighlight;
    std::string selectedSquare; // Is the square that the user has clicked. This square has the piece of their own colour which the user intends to move.

    Tile* srcTile; // A pointer to the source tile.
    // when window is open
    while (window.isOpen())
    {
        // Checking whether the game is completed.
        if (checkMated || staleMated || compTimerUp || playerTimerUp) {
            checkMateSound.play();
            window.clear();

            // Draw board text
            for (int i = 0; i < 16; i++)
            {
                window.draw(boardText[i]);
            }
            // Draw Movement board
            window.draw(spriteMoveBoard);

            for (int x = 0; x < 64; x++) {
                window.draw(tileObjs[x].tile);
                if (tileObjs[x].piecePresent) {
                    window.draw(tileObjs[x].currentPiece);
                }
            }

            // Draw selection tile
            window.draw(selectTile);

            // Draw game over text depending on the result.
            window.display();
            sf::Text messageText;
            int matedOutput = eng.isMate(eng.cr);
            if (checkMated) {
                if (matedOutput == 3) {
                    messageText.setString("White Check Mated. Press Esc To Exit.");
                }
                else {
                    messageText.setString("Black Check Mated. Press Esc To Exit.");
                }
            }
            else if (eng.isADraw(eng.cr, !playerColourWhite)) {
                messageText.setString("Game Drawn. Press Esc To Exit.");
            }
            else if (staleMated) {
                if (matedOutput == 1) {
                    messageText.setString("White Stale Mated. Press Esc To Exit.");
                }
                else {
                    messageText.setString("Black Stale Mated. Press Esc To Exit.");
                }
            }
            else if (playerTimerUp) {
                messageText.setString("You lost on time. Press Esc To Exit.");
            }
            else if (compTimerUp) {
                messageText.setString("You Won on time. Press Esc To Exit.");
            }
            messageText.setFont(font);

            messageText.setCharacterSize(55);
            messageText.setFillColor(Color::Red);

            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);

            messageText.setPosition(1060 / 2.0f, 1088 / 2.0f);

            window.draw(messageText);
            window.display();
            // Waiting for user input to close the window.
            while (true)
            {
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    break;
                }
            }
            window.close();
            break;
        }

        // Determining if it is the computer's turn to play.
        sf::Event event;
        bool compJustPlayed = false;
        if (startFlag && (true || !((whiteTurn && playerColourWhite) || (!whiteTurn && !playerColourWhite)))) {
            // The computer's turn to play.
            thc::Move mv = eng.getBestMove(eng.cr); // Getting the best move from the engine
            std::string moveString = mv.NaturalOut(&eng.cr);
            eng.cr.PlayMove(mv); // Playing the move behind the scenes.
            numMoves += 1;
            // cout << "HERE CLOCK RESTART" << endl;
            sf::Time elapsed1 = clock.getElapsedTime();
            compTimer -= elapsed1.asSeconds();
            if (compTimer <= 0) {
                compTimerUp = true;
            }
            // cout << compTimer << endl;
            clock.restart(); // restaring the clock.
            // This if is unnecessary but was written before the new check detection mechanism.
            if (!checkMated) {
                std::string mv_txt = mv.TerseOut();// The string representation of the move the computer just played.
                bool shortCastle = false;
                bool longCastle = false;
                // Determining if the computer just castled.
                if (moveString == "O-O" || moveString == "O-O+" || moveString == "O-O#") {
                    shortCastle = true;
                }
                else if (moveString == "O-O-O" || moveString == "O-O-O+" || moveString == "O-O-O#") {
                    longCastle = true;
                }
                char srcTxt[3];
                srcTxt[0] = mv_txt[0];
                srcTxt[1] = mv_txt[1];
                srcTxt[2] = '\0';
                char dstTxt[3];
                dstTxt[0] = mv_txt[2];
                dstTxt[1] = mv_txt[3];
                dstTxt[2] = '\0';
                cout << "Computer move: " << srcTxt << "-" << dstTxt << " or " << moveString.c_str() << endl;

                // Adding the computer's move to the list of moves made.
                std::string displayStr;

                if (playerColourWhite) {
                    displayStr = "B: " + moveString;
                }
                else {
                    displayStr = "W: " + moveString;
                }

                movesDisplayed.push_back(displayStr);

                // Finding the destination and source of the computer's move.
                Tile* src;
                Tile* dstTile;
                for (int xx = 0; xx < 64; xx++) {
                    if (strcmp(srcTxt, tileObjs[xx].notation.c_str()) == 0) {
                        // The source tile.
                        src = &tileObjs[xx];
                    }
                    if (strcmp(dstTxt, tileObjs[xx].notation.c_str()) == 0) {
                        // The destination tile.
                        dstTile = &tileObjs[xx];
                    }
                }

                bool compColourWhite = !playerColourWhite;
                // Shifting the rook in case of a castle.
                if (shortCastle) {
                    Tile* rookTile;
                    Tile* rookDstTile;
                    if (compColourWhite) {
                        // The rook is at h1, which is position 63 in tileObjs
                        rookTile = &tileObjs[63];
                        rookDstTile = &tileObjs[61];
                    }
                    else {
                        // The rook is at h8, which is position 7 in tileObjs
                        rookTile = &tileObjs[7];
                        rookDstTile = &tileObjs[5];
                    }
                    Sprite* rook = &rookTile->currentPiece;
                    rook->setPosition((float) rookDstTile->tile.getPosition().x, (float) rookDstTile->tile.getPosition().y);
                    rookDstTile->piecePresent = true;
                    rookDstTile->currentPiece = *rook;
                    rookDstTile->isKing = false;
                    rookDstTile->whitePiece = !playerColourWhite;
                    Sprite tmp;
                    tmp.setTexture(textureBlackQueen);
                    tmp.setScale(0.0, 0.0);
                    tmp.setPosition(20020.0f, 20020.0f);
                    rookTile->currentPiece = tmp;
                    rookTile->piecePresent = false;

                }
                else if (longCastle) {
                    Tile* rookTile;
                    Tile* rookDstTile;
                    if (compColourWhite) {
                        // The rook is at a1, which is position 56 in tileObjs
                        rookTile = &tileObjs[56];
                        rookDstTile = &tileObjs[59];
                    }
                    else {
                        // The rook is at a8, which is position 0 in tileObjs
                        rookTile = &tileObjs[0];
                        rookDstTile = &tileObjs[3];
                    }
                    Sprite* rook = &rookTile->currentPiece;
                    rook->setPosition((float) rookDstTile->tile.getPosition().x, (float) rookDstTile->tile.getPosition().y);
                    rookDstTile->piecePresent = true;
                    rookDstTile->currentPiece = *rook;
                    rookDstTile->isKing = false;
                    rookDstTile->whitePiece = playerColourWhite;
                    Sprite tmp;
                    tmp.setTexture(textureBlackQueen);
                    tmp.setScale(0.0, 0.0);
                    tmp.setPosition(20020.0f, 20020.0f);
                    rookTile->currentPiece = tmp;
                    rookTile->piecePresent = false;
                }

                // Removing the piece that was previously occupying the destination square in case of a capture.
                Sprite* currPc = &src->currentPiece;
                bool isCapture = false;
                if (dstTile->piecePresent == false || dstTile->currentPiece.getPosition().x == 20020.0f || dstTile->currentPiece.getPosition().y == 20020.0f) {
                    //  No piece currently here.
                    moveSound.play();
                }
                else {
                    isCapture = true;
                    dstTile->currentPiece.setPosition(20020.0f, 20020.0f);
                    captureSound.play();
                    dstTile->piecePresent = false;
                }

                // Setting the position of the piece.
                currPc->setPosition((float) dstTile->tile.getPosition().x, (float) dstTile->tile.getPosition().y);
                // printf("%f and %f\n", currPc.getPosition().x, currPc.getPosition().y);// TODO: REMOVE

                // Highlighting the tile that the engine just moved to.
                selectTile.setPosition(dstTile->tile.getPosition().x, dstTile->tile.getPosition().y);

                dstTile->currentPiece = *currPc;
                dstTile->piecePresent = true;
                dstTile->whitePiece = !playerColourWhite;

                // Pawn promotion from the computer. Handling this case by removing the pawn and adding the correct pieve.
                bool isPromotion = false;
                char c = 'a'; // The piece being promoted to
                if (src->piecePresent && src->isPawn) {
                    std::string dstNotation = dstTile->notation;
                    if (dstNotation == "a8" || dstNotation == "b8" || dstNotation == "c8" || dstNotation == "d8" || dstNotation == "e8" || dstNotation == "f8" || dstNotation == "g8" || dstNotation == "h8" || dstNotation == "a1" || dstNotation == "b1" || dstNotation == "c1" || dstNotation == "d1" || dstNotation == "e1" || dstNotation == "f1" || dstNotation == "g1" || dstNotation == "h1") {
                        // Promoting a pawn.
                        isPromotion = true;
                        c = moveString[3];
                        if (c == 'q' || c == 'Q') {
                            // Queen promotion
                            if (compColourWhite) {
                                dstTile->currentPiece.setTexture(textureWhiteQueen);
                            }
                            else {
                                dstTile->currentPiece.setTexture(textureBlackQueen);
                            }
                        }
                        else if (c == 'r' || c == 'R') {
                            // Rook promotion
                            if (compColourWhite) {
                                dstTile->currentPiece.setTexture(textureWhiteRook);
                            }
                            else {
                                dstTile->currentPiece.setTexture(textureBlackRook);
                            }

                        }
                        else if (c == 'b' || c == 'B') {
                            // Bishop promotion
                            if (compColourWhite) {
                                dstTile->currentPiece.setTexture(textureWhiteBishop);
                            }
                            else {
                                dstTile->currentPiece.setTexture(textureBlackBishop);
                            }

                        }
                        else if (c == 'n' || c == 'N') {
                            // Night promotion
                            if (compColourWhite) {
                                dstTile->currentPiece.setTexture(textureWhiteKnight);
                            }
                            else {
                                dstTile->currentPiece.setTexture(textureBlackKnight);
                            }
                        }
                    }
                }

                // Handling en-passant manouver from the engine.
                if (!isPromotion) {
                    // COULD be an en-passant
                    if (src->piecePresent && src->isPawn) {
                        // If the player is white check the row directly behind it. 
                        // If the player is black check the row *ahead* of it on the board.

                        for (int xy = 8; xy < 56; xy++) {
                            if (tileObjs[xy].notation == dstTile->notation) {
                                // Check the tile *below* / *above* it on the board
                                if (!isCapture && tileObjs[xy - offset].piecePresent && tileObjs[xy - offset].isPawn && tileObjs[xy - offset].whitePiece == playerColourWhite) {
                                    // is an en-passant

                                    printf("IS AN EN PASSANT COMPUTER %d\n", offset);

                                    Sprite tmp;
                                    tmp.setTexture(textureBlackQueen);
                                    tmp.setScale(0.0, 0.0);
                                    tmp.setPosition(20020.0f, 20020.0f);
                                    tileObjs[xy - offset].currentPiece = tmp;
                                    tileObjs[xy - offset].piecePresent = false;
                                    tileObjs[xy - offset].isPawn = false;

                                }
                                break;
                            }
                        }
                        //
                    }
                }

                // Setting the tile variables according to the piece moved.
                if (src->isKing) {
                    src->isKing = false;
                    dstTile->isKing = true;
                }
                if (src->isPawn) {
                    src->isPawn = false;
                    if (!isPromotion) {
                        dstTile->isPawn = true;
                    }
                }
                Sprite tmp;
                tmp.setTexture(textureBlackQueen);
                tmp.setScale(0.0, 0.0);
                tmp.setPosition(20020.0f, 20020.0f);
                src->currentPiece = tmp;
                src->piecePresent = false;

            }
            else {
                for (int xy = 0; xy < 64; xy++) {
                    if ((tileObjs[xy].whitePiece == !playerColourWhite) && tileObjs[xy].isKing) {
                        selectTile.setPosition(tileObjs[xy].tile.getPosition().x, tileObjs[xy].tile.getPosition().y);
                        break;
                    }
                }
            }

            // Checking for check mate / stalamate / draw after the computer has moved.
            int matedOutput = eng.isMate(eng.cr);
            if (matedOutput == 3 || matedOutput == 4) {
                printf("CHECK MATED\n");
                checkMated = true;
            }
            else if (matedOutput == 1 || matedOutput == 2 || eng.isADraw(eng.cr, !playerColourWhite)) {
                staleMated = true;
                printf("STALE MATED\n");
            }


            compJustPlayed = true;
            whiteTurn = !whiteTurn;
        }

        // Checking if the computer just lost on time.
        if (compTimerUp) {
            continue;
        }

        // Checking for mouse click events.
        while (window.pollEvent(event))
        {
            if (compJustPlayed) {
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();

            // check which tile was clicked
            if (event.type == sf::Event::MouseButtonPressed)
            {
                std::string chosenSquare;
                // hihglights which square the user has selected.
                for (int i = 0; i < 64; i++)
                {
                    if (tileObjs[i].tile.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        selectTile.setPosition(tileObjs[i].tile.getPosition().x, tileObjs[i].tile.getPosition().y);
                        // i = 65;
                        chosenSquare = tileObjs[i].notation;
                        break;
                    }
                }

                // Determines whether it's the user's turn to play.
                bool passThrough = false;
                if (whiteTurn && playerColourWhite || (!whiteTurn && !playerColourWhite)) {
                    passThrough = true;
                }

                // Highlights all the possible moves the user can make.
                // Uses the thc library here.
                std::vector<thc::Move> moves;
                std::vector<bool> check;
                std::vector<bool> mate;
                std::vector<bool> stalemate;
                eng.cr.GenLegalMoveList(moves, check, mate, stalemate);
                unsigned int len = moves.size();

                // Empty highlight here.
                highlight.clear();
                // cout << "here" << endl;
                if (len != 0) {
                    for (int zz = 0; zz < len; zz++) {
                        std::string tersedMove = moves[zz].TerseOut();
                        char sourceTileNot[3];
                        sourceTileNot[0] = tersedMove[0];
                        sourceTileNot[1] = tersedMove[1];
                        sourceTileNot[2] = '\0';
                        if (strcmp(sourceTileNot, chosenSquare.c_str()) == 0) {
                            char destTileNot[3];
                            destTileNot[0] = tersedMove[2];
                            destTileNot[1] = tersedMove[3];
                            destTileNot[2] = '\0';
                            std::string sDestTile = destTileNot;
                            highlight.push_back(sDestTile);
                        }
                    }

                }

                // Highlight all the tiles in highlight.


                // Determines which piece the user is selecting.
                if (startFlag && !checkMated && passThrough && !isPieceSelected) {
                    // Check the colour of the piece the user has clicked.

                    for (int i = 0; i < 64; i++)
                    {
                        // Determines the tile the user has clicked.
                        if (tileObjs[i].tile.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (!tileObjs[i].piecePresent) {
                                // The user has clicked an empty tile.
                                i = 65;
                                break;
                            }
                            if (!(tileObjs[i].whitePiece == playerColourWhite)) {
                                // The piece the user has clicked is not his own.
                                i = 65;
                                break;
                            }
                            else {
                                // The user has clicked his own piece.
                                isPieceSelected = true;
                                selectedSquare = tileObjs[i].notation;
                                srcTile = &tileObjs[i];
                                break;
                            }
                        }
                    }


                    // If the user has clicked the white piece, then set isPieceSelected to true.
                    // (Assuming the user is white)
                    // Set the value of squareSelected
                }
                else {
                    // The user has clicked some square AFTER clicking their piece.
                    // Check whether the user has clicked a piece of the saem colour.
                    // If they have clicked their own colour DO NOT update isPieceSelected, but UPDATE squareSelected

                    bool isPlayerColourPieceSelected = false;
                    Tile* dstTile; // A pointer to the destination tile.
                    std::string destSq;
                    bool illegalMove = false;
                    for (int i = 0; startFlag && !checkMated && i < 64; i++)
                    {
                        if (tileObjs[i].tile.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (!tileObjs[i].piecePresent) {
                                // The user has clicked an empty tile.
                                destSq = tileObjs[i].notation;
                                dstTile = &tileObjs[i];
                                i = 65;
                                break;
                            }
                            else if (!(tileObjs[i].whitePiece == playerColourWhite)) {
                                // The piece the user has clicked is not their own.
                                destSq = tileObjs[i].notation;
                                dstTile = &tileObjs[i];
                                i = 65;
                                break;
                            }
                            else {
                                // The user has clicked their own piece.
                                isPlayerColourPieceSelected = true;
                                srcTile = &tileObjs[i];
                                selectedSquare = tileObjs[i].notation;
                                break;
                            }
                        }
                    }

                    if (startFlag && !checkMated && !isPlayerColourPieceSelected) {
                        // The user has officially made a move.
                        std::string moveNotation;

                        moveNotation = selectedSquare + "-" + destSq; // TODO: Manage promotion
                        char mvNot[7 + 1];
                        bool shortCastle = false;
                        bool longCastle = false;

                        // Castling logic.
                        std::string castleNotation;
                        // cout << moveNotation << srcTile->isKing << endl;
                        if (srcTile->isKing && selectedSquare == "e1") {
                            if (dstTile->notation == "g1") {
                                shortCastle = true;
                                // Short Castle-white
                                castleNotation = "O-O";
                            }
                            else if (dstTile->notation == "c1") {
                                // Long-castle-white
                                longCastle = true;
                                castleNotation = "O-O-O";

                            }
                        }
                        else if ((srcTile->isKing && selectedSquare == "e8")) {
                            if (dstTile->notation == "g8") {
                                // Short Castle-black
                                castleNotation = "O-O";
                                shortCastle = true;
                            }
                            else if (dstTile->notation == "c8") {
                                // Long-castle-black
                                castleNotation = "O-O-O";
                                longCastle = true;
                            }
                        }

                        if (shortCastle || longCastle) {
                            strcpy(mvNot, castleNotation.c_str());
                            cout << "Move made: " << castleNotation << endl;
                            std::string displayStr;
                            if (playerColourWhite) {
                                displayStr = "W: " + castleNotation;
                            }
                            else {
                                displayStr = "B: " + castleNotation;
                            }
                            movesDisplayed.push_back(displayStr);
                        }
                        else {
                            cout << "Move made: " << moveNotation << endl;
                            strcpy(mvNot, moveNotation.c_str());
                        }

                        // Handling pawn promotions from the user.
                        bool isPromotion = false;
                        // Promotion
                        if (srcTile->piecePresent && srcTile->isPawn && !srcTile->isKing) {
                            std::string dstNotation = dstTile->notation;
                            if (dstNotation == "a8" || dstNotation == "b8" || dstNotation == "c8" || dstNotation == "d8" || dstNotation == "e8" || dstNotation == "f8" || dstNotation == "g8" || dstNotation == "h8" || dstNotation == "a1" || dstNotation == "b1" || dstNotation == "c1" || dstNotation == "d1" || dstNotation == "e1" || dstNotation == "f1" || dstNotation == "g1" || dstNotation == "h1") {
                                // Promoting a pawn.
                                isPromotion = true;
                                std::string promotionStr = selectedSquare + destSq + "q";;
                                // Assume promotion is to a queen.
                                // For other pieces just append a different string to the end.
                                std::string displayStr;
                                if (playerColourWhite) {
                                    displayStr = "W: " + promotionStr;
                                }
                                else {
                                    displayStr = "B: " + promotionStr;
                                }
                                movesDisplayed.push_back(displayStr);

                                strcpy(mvNot, promotionStr.c_str());
                                thc::Move mvProm;

                                if (!mvProm.TerseIn(&eng.cr, mvNot)) {
                                    illegalMove = true;
                                    // Illegal Move
                                    // printf("Illegal MOVE!\n");
                                }
                                else {
                                    eng.cr.PlayMove(mvProm);
                                }
                            }
                        }

                        if (!isPromotion) {
                            std::string displayStr;
                            if (playerColourWhite) {
                                displayStr = "W: " + moveNotation;
                            }
                            else {
                                displayStr = "B: " + moveNotation;
                            }
                            movesDisplayed.push_back(displayStr);
                        }

                        bool isCapture = false;

                        if (dstTile->currentPiece.getPosition().x == 20020.0f && dstTile->currentPiece.getPosition().y == 20020.0f) {
                            //  No piece currently here.
                        }
                        else {
                            isCapture = true;
                            // dstTile->currentPiece.setPosition(20020.0f, 20020.0f);
                            // dstTile->piecePresent = false;
                        }
                        bool isEnPassant = false;

                        // Handling en passant from the user.
                        if (!isPromotion) {
                            // COULD be an en-passant
                            if (srcTile->piecePresent && srcTile->isPawn) {
                                // If the player is white check the row directly behind it. 
                                // If the player is black check the row *ahead* of it on the board.

                                for (int xy = 8; xy < 56; xy++) {
                                    if (tileObjs[xy].notation == dstTile->notation) {
                                        // Check the tile *below* / *above* it on the board
                                        if (!isCapture && tileObjs[xy + offset].piecePresent && tileObjs[xy + offset].isPawn && tileObjs[xy + offset].whitePiece != playerColourWhite) {
                                            // is an en-passant
                                            isEnPassant = true;
                                            printf("IS AN EN PASSANT PLAYER\n");
                                            //
                                            char enPassantMove[5];
                                            enPassantMove[0] = selectedSquare[0];
                                            enPassantMove[1] = 'x';
                                            enPassantMove[2] = destSq[0];
                                            enPassantMove[3] = destSq[1];
                                            enPassantMove[4] = '\0';
                                            if (!eng.makeMove(enPassantMove)) {
                                                illegalMove = true;
                                                // Illegal Move
                                                // printf("Illegal MOVE!\n");
                                            }
                                            else {
                                                Sprite tmp;
                                                tmp.setTexture(textureBlackQueen);
                                                tmp.setScale(0.0, 0.0);
                                                tmp.setPosition(20020.0f, 20020.0f);
                                                tileObjs[xy + offset].currentPiece = tmp;
                                                tileObjs[xy + offset].piecePresent = false;
                                                tileObjs[xy + offset].isPawn = false;
                                            }

                                        }
                                        break;
                                    }
                                }
                                //
                            }
                        }

                        // Making the move the user has chosen with their mouse.
                        if (!isPromotion && !isEnPassant) {
                            if (!eng.makeMove(mvNot)) {
                                illegalMove = true;
                                // Illegal Move
                            }
                        }

                        // Pausing the user's timer if the move is legal.
                        if (!illegalMove) {
                            whiteTurn = !whiteTurn;
                            isPieceSelected = false;
                            numMoves += 1;
                            if (numMoves > 1) {
                                sf::Time elapsed1 = clock.getElapsedTime();
                                playerTimer -= elapsed1.asSeconds();
                            }

                            clock.restart();
                            // cout << "HERE CLOCK RESTART" << endl;
                        }
                        // Remove the piece from the old square
                        // Add it to the new square
                        // And if we are capturing, we hve to remove the old piece
                        // Edge case: en-passant
                        // Edge case: Castle -- Done
                        // Edge case: Promotion -- Done
                        // Finding the destination and source tiles of the user.
                        for (int j = 0; !illegalMove && j < 64; j++) {
                            if (tileObjs[j].piecePresent && (tileObjs[j].notation == selectedSquare)) {
                                // This is the square where the piece is currently sitting.
                                Sprite* currPc = &tileObjs[j].currentPiece;
                                // If this is a capture, set the position of the piece at the dst tile to inf
                                if (dstTile->piecePresent == false || dstTile->currentPiece.getPosition().x == 20020.0f || dstTile->currentPiece.getPosition().y == 20020.0f) {
                                    //  No piece currently here.
                                    moveSound.play();
                                }
                                else {
                                    dstTile->currentPiece.setPosition(200020.0f, 200020.0f);
                                    captureSound.play();
                                    dstTile->piecePresent = false;
                                }

                                currPc->setPosition((float) dstTile->tile.getPosition().x, (float) dstTile->tile.getPosition().y);
                                // printf("%f and %f\n", currPc.getPosition().x, currPc.getPosition().y);// TODO: REMOVE

                                // Handling rook movement in castling. 
                                if (shortCastle) {
                                    Tile* rookTile;
                                    Tile* rookDstTile;
                                    if (playerColourWhite) {
                                        // The rook is at h1, which is position 63 in tileObjs
                                        rookTile = &tileObjs[63];
                                        rookDstTile = &tileObjs[61];
                                    }
                                    else {
                                        // The rook is at h8, which is position 7 in tileObjs
                                        rookTile = &tileObjs[7];
                                        rookDstTile = &tileObjs[5];
                                    }
                                    Sprite* rook = &rookTile->currentPiece;
                                    rook->setPosition((float) rookDstTile->tile.getPosition().x, (float) rookDstTile->tile.getPosition().y);
                                    rookDstTile->piecePresent = true;
                                    rookDstTile->currentPiece = *rook;
                                    rookDstTile->isKing = false;
                                    rookDstTile->whitePiece = playerColourWhite;
                                    Sprite tmp;
                                    tmp.setTexture(textureBlackQueen);
                                    tmp.setScale(0.0, 0.0);                                    tmp.setPosition(20020.0f, 20020.0f);
                                    rookTile->currentPiece = tmp;
                                    rookTile->piecePresent = false;

                                }
                                else if (longCastle) {
                                    Tile* rookTile;
                                    Tile* rookDstTile;
                                    if (playerColourWhite) {
                                        // The rook is at a1, which is position 56 in tileObjs
                                        rookTile = &tileObjs[56];
                                        rookDstTile = &tileObjs[59];
                                    }
                                    else {
                                        // The rook is at a8, which is position 0 in tileObjs
                                        rookTile = &tileObjs[0];
                                        rookDstTile = &tileObjs[3];
                                    }
                                    Sprite* rook = &rookTile->currentPiece;
                                    rook->setPosition((float) rookDstTile->tile.getPosition().x, (float) rookDstTile->tile.getPosition().y);
                                    rookDstTile->piecePresent = true;
                                    rookDstTile->currentPiece = *rook;
                                    rookDstTile->isKing = false;
                                    rookDstTile->whitePiece = playerColourWhite;
                                    Sprite tmp;
                                    tmp.setTexture(textureBlackQueen);
                                    tmp.setScale(0.0, 0.0);
                                    tmp.setPosition(20020.0f, 20020.0f);
                                    rookTile->currentPiece = tmp;
                                    rookTile->piecePresent = false;
                                }

                                // Handling texture of piece in promotion.
                                dstTile->currentPiece = *currPc;
                                if (isPromotion) {
                                    if (playerColourWhite) {
                                        dstTile->currentPiece.setTexture(textureWhiteQueen);
                                    }
                                    else {
                                        dstTile->currentPiece.setTexture(textureBlackQueen);
                                    }
                                }
                                else {
                                    // COULD be an en-passant
                                    if (isEnPassant) {
                                        // Handling en passant.
                                        for (int xy = 0; xy < 64; xy++) {
                                            if (tileObjs[xy].notation == dstTile->notation) {
                                                // Check the tile *below* / *above* it on the board
                                                if (!isCapture && tileObjs[xy + offset].piecePresent && tileObjs[xy + offset].isPawn && tileObjs[xy + offset].whitePiece != playerColourWhite) {
                                                    // is an en-passant
                                                    Sprite tmp;
                                                    tmp.setTexture(textureBlackQueen);
                                                    tmp.setScale(0.0, 0.0);
                                                    tmp.setPosition(20020.0f, 20020.0f);
                                                    tileObjs[xy + offset].currentPiece = tmp;
                                                    tileObjs[xy + offset].piecePresent = false;
                                                    tileObjs[xy + offset].isPawn = false;
                                                }
                                                break;
                                            }
                                        }
                                    }

                                }
                                // Setting the required tile variables.
                                dstTile->piecePresent = true;
                                dstTile->whitePiece = playerColourWhite;
                                if (srcTile->isKing) {
                                    dstTile->isKing = true;
                                    srcTile->isKing = false;
                                }
                                if (srcTile->isPawn) {
                                    dstTile->isPawn = true;
                                    srcTile->isPawn = false;
                                    if (isPromotion) {
                                        dstTile->isPawn = false;
                                    }
                                }

                                Sprite tmp;
                                tmp.setTexture(textureBlackQueen);
                                tmp.setScale(0.0, 0.0);
                                tmp.setPosition(20020.0f, 20020.0f);
                                tileObjs[j].currentPiece = tmp;
                                tileObjs[j].piecePresent = false;
                                // We need to coordinates of the dstSquare.
                                //
                                break;
                            }
                        }

                    }

                    // Checking for checkmate after the player has made their move.
                    int matedOutput = eng.isMate(eng.cr);
                    if (matedOutput == 3 || matedOutput == 4) {
                        printf("CHECK MATED\n");
                        checkMated = true;
                    }
                    else if (matedOutput == 1 || matedOutput == 2 || eng.isADraw(eng.cr, playerColourWhite)) {
                        staleMated = true;
                        printf("STALE MATED\n");
                    }

                }
            }
        }


        // Closing the second window.
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        window2.clear();
        //


        window.clear();

        // Draw board text
        for (int i = 0; i < 16; i++)
        {
            window.draw(boardText[i]);
        }
        // Draw Movement board
        window.draw(spriteMoveBoard);

        // Drawing out all the tiles and all the pieces.
        for (int x = 0; x < 64; x++) {
            window.draw(tileObjs[x].tile);
            if (tileObjs[x].piecePresent) {
                window.draw(tileObjs[x].currentPiece);
            }
        }

        // Drawing out the timer.
        if (startFlag && numMoves > 0) {
            sf::Time elapsed1 = clock.getElapsedTime();
            double tempCompTimer = compTimer;
            double tempPlayerTimer = playerTimer;
            if (numMoves == 1 && playerTimer <= 299.0 && !playerColourWhite) {
                playerTimer += 7.5;
            }
            else if (numMoves == 1 && playerTimer <= 299.0 && playerColourWhite) {
                playerTimer += 4.5;
            }
            // Determining if either player has exceeded their alloted time.
            if ((whiteTurn && playerColourWhite) || (!whiteTurn && !playerColourWhite)) {
                // The player is currently playing.
                tempPlayerTimer -= elapsed1.asSeconds();
                if (tempPlayerTimer <= 0.0) {
                    playerTimerUp = true;
                }
            }
            else if (!((whiteTurn && playerColourWhite) || (!whiteTurn && !playerColourWhite))) {
                tempCompTimer -= elapsed1.asSeconds();
                if (tempCompTimer <= 0.0) {
                    compTimerUp = true;
                }
            }
            sf::Text timerTextPlayer;
            char timerText[20];
            std::sprintf(timerText, "%.2f", tempPlayerTimer);
            std::string timerTextStr = timerText;
            timerTextStr = "P: " + timerTextStr;
            timerTextPlayer.setString(timerTextStr);
            timerTextPlayer.setFont(font);

            timerTextPlayer.setCharacterSize(35);
            timerTextPlayer.setFillColor(Color::White);

            FloatRect textRect = timerTextPlayer.getLocalBounds();
            timerTextPlayer.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);

            timerTextPlayer.setPosition(1170.0f, 30.0f);

            window.draw(timerTextPlayer);



            sf::Text timerTextComp;
            char timerTextComputer[10];
            std::sprintf(timerTextComputer, "%.2f", tempCompTimer);
            std::string timerTextStrComp = timerTextComputer;
            timerTextStrComp = "C: " + timerTextStrComp;
            timerTextComp.setString(timerTextStrComp);
            timerTextComp.setFont(font);

            timerTextComp.setCharacterSize(35);
            timerTextComp.setFillColor(Color::White);

            FloatRect textRectComp = timerTextComp.getLocalBounds();
            timerTextComp.setOrigin(textRectComp.left +
                textRectComp.width / 2.0f,
                textRectComp.top +
                textRectComp.height / 2.0f);

            timerTextComp.setPosition(1170.0f, 70.0f);

            window.draw(timerTextComp);

        }

        // Ensuring the displayed moves don't overshoot the window.
        while (movesDisplayed.size() > 40) {
            // Remove the first element of the vector
            movesDisplayed.erase(movesDisplayed.begin());
        }

        // Drawing out the moves.
        for (int xx = 0; xx < movesDisplayed.size(); xx++) {
            sf::Text moveText;
            moveText.setString(movesDisplayed[xx]);
            moveText.setFont(font);

            moveText.setCharacterSize(25);
            moveText.setFillColor(Color::White);

            FloatRect textRect = moveText.getLocalBounds();
            moveText.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);

            moveText.setPosition(1170.0f, (float) (120 + 22.5 * (xx)));

            window.draw(moveText);
        }

        // Draw selection tile
        window.draw(selectTile);

        tilesToHighlight.clear();
        // Highlighting all the tiles the user can move to with their chosen piece.
        for (int zz = 0; zz < highlight.size(); zz++) {
            for (int xx = 0; xx < 64; xx++) {
                if ((highlight[zz] == tileObjs[xx].notation)) {
                    RectangleShape sTile;
                    sTile.setFillColor(Color::Transparent);
                    sTile.setOutlineColor(Color::Yellow);
                    sTile.setOutlineThickness(5);
                    sTile.setPosition(tileObjs[xx].tile.getPosition().x, tileObjs[xx].tile.getPosition().y);
                    sTile.setSize(Vector2f(128, 128));
                    tilesToHighlight.push_back(sTile);
                    break;
                }
            }
            window.draw(tilesToHighlight[zz]);
        }

        // close start menu
        if (difficultySelected && Keyboard::isKeyPressed(Keyboard::Return))
        {
            startFlag = true;
            eng.depth = difficultyLevel;
            cout << "Difficulty level set to: " << eng.depth << endl;
            window2.close();
        }
        else {
            // Asking the user for input on the game's difficulty and appearance.
            window2.draw(difficultyLevelText);
            window2.draw(textureChoiceText);
            window2.draw(textureChoiceTextBlue);
            window2.draw(textureChoiceTextBrown);
            window2.draw(textureChoiceTextGray);
            window2.draw(pieceShadowText);
            window2.draw(pieceColorText);
            window2.draw(titleText);
            if (!pieceColorSelected)
            {
                if (Keyboard::isKeyPressed(Keyboard::P)) {
                    pieceColorSelected = true;
                    // Setting the player's colout.
                    playerColourWhite = false;
                    if (playerColourWhite) {
                        offset = 8;
                    }
                    else {
                        offset = -8;
                    }
                    pieceColorText.setString("               Choose color\n                   Black");
                }
                else if (Keyboard::isKeyPressed(Keyboard::W)) {
                    pieceColorSelected = true;
                    playerColourWhite = true;
                    if (playerColourWhite) {
                        offset = 8;
                    }
                    else {
                        offset = -8;
                    }
                    pieceColorText.setString("               Choose color\n                   White");
                }
            }
            if (!textureSelected)
            {
                // Setting the texture of the board.
                if (Keyboard::isKeyPressed(Keyboard::B)) {
                    textureInputStr = "blue";
                    textureSelected = true;
                    textureChoiceTextBrown.setFillColor(Color::Transparent);
                    textureChoiceTextGray.setFillColor(Color::Transparent);
                    difficultyLevelText.setOutlineColor(Color::Blue);
                }
                else if (Keyboard::isKeyPressed(Keyboard::R)) {
                    textureInputStr = "red";
                    textureSelected = true;
                    textureChoiceTextBlue.setFillColor(Color::Transparent);
                    textureChoiceTextGray.setFillColor(Color::Transparent);
                    difficultyLevelText.setOutlineColor(Color::Red);
                    textureLightTile.loadFromFile("./resources1/brown_light.jpeg");
                    textureDarkTile.loadFromFile("./resources1/brown_dark.jpeg");
                }
                else if (Keyboard::isKeyPressed(Keyboard::G)) {
                    textureInputStr = "gray";
                    textureSelected = true;
                    textureChoiceTextBrown.setFillColor(Color::Transparent);
                    textureChoiceTextBlue.setFillColor(Color::Transparent);
                    difficultyLevelText.setOutlineColor(Color::White);
                    textureLightTile.loadFromFile("./resources1/gray_light.jpeg");
                    textureDarkTile.loadFromFile("./resources1/gray_dark.jpeg");
                }
            }
            if (!pieceShadowSelected)
            {
                // Setting the texture of the pieces.
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    pieceShadowSelected = true;
                    pieceShadowText.setString("        Choose piece texture type:"
                        "\n                 Shadow(s)");
                    textureWhiteKing.loadFromFile("./resources2/w_king_png_shadow_256px.png");
                    spriteWhiteKing.setScale(0.5, 0.5);
                    textureWhiteQueen.loadFromFile("./resources2/w_queen_png_shadow_256px.png");
                    spriteWhiteQueen.setScale(0.5, 0.5);
                    textureWhiteBishop.loadFromFile("./resources2/w_bishop_png_shadow_256px.png");
                    spriteWhiteBishopLight.setScale(0.5, 0.5);
                    spriteWhiteBishopDark.setScale(0.5, 0.5);
                    textureWhiteRook.loadFromFile("./resources2/w_rook_png_shadow_256px.png");
                    spriteWhiteRookLight.setScale(0.5, 0.5);
                    spriteWhiteRookDark.setScale(0.5, 0.5);
                    textureWhiteKnight.loadFromFile("./resources2/w_knight_png_shadow_256px.png");
                    spriteWhiteKnightLight.setScale(0.5, 0.5);
                    spriteWhiteKnightDark.setScale(0.5, 0.5);
                    textureWhitePawn.loadFromFile("./resources2/w_pawn_png_shadow_256px.png");
                    for (int i = 0; i < 8; i++)
                    {
                        spriteWhitePawn[i].setScale(0.5, 0.5);
                    }

                    textureBlackKing.loadFromFile("./resources2/b_king_png_shadow_256px.png");
                    spriteBlackKing.setScale(0.5, 0.5);
                    textureBlackQueen.loadFromFile("./resources2/b_queen_png_shadow_256px.png");
                    spriteBlackQueen.setScale(0.5, 0.5);
                    textureBlackBishop.loadFromFile("./resources2/b_bishop_png_shadow_256px.png");
                    spriteBlackBishopLight.setScale(0.5, 0.5);
                    spriteBlackBishopDark.setScale(0.5, 0.5);
                    textureBlackRook.loadFromFile("./resources2/b_rook_png_shadow_256px.png");
                    spriteBlackRookLight.setScale(0.5, 0.5);
                    spriteBlackRookDark.setScale(0.5, 0.5);
                    textureBlackKnight.loadFromFile("./resources2/b_knight_png_shadow_256px.png");
                    spriteBlackKnightLight.setScale(0.5, 0.5);
                    spriteBlackKnightDark.setScale(0.5, 0.5);
                    textureBlackPawn.loadFromFile("./resources2/b_pawn_png_shadow_256px.png");
                    for (int i = 0; i < 8; i++)
                    {
                        spriteBlackPawn[i].setScale(0.5, 0.5);
                    }

                }
                else if (Keyboard::isKeyPressed(Keyboard::N)) {
                    pieceShadowSelected = true;
                    pieceShadowText.setString("        Choose piece texture type:"
                        "\n               No Shadow(s)");
                }
            }
            // Setting the difficulty of the game.
            if (Keyboard::isKeyPressed(Keyboard::Num1))
            {
                difficultyLevel = 1 + 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                difficultyLevel = 2 + 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                difficultyLevel = 3 + 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                difficultyLevel = 4 + 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Num5)) {
                difficultyLevel = 5 + 1;
            }
            if (pieceColorSelected && textureSelected && pieceShadowSelected && !difficultySelected && difficultyLevel > 0)
            {
                difficultySelected = true;
                textureChoiceText.setFillColor(Color::Transparent);
                textureChoiceTextBrown.setFillColor(Color::Transparent);
                textureChoiceTextBlue.setFillColor(Color::Transparent);
                textureChoiceTextGray.setFillColor(Color::Transparent);
                pieceShadowText.setFillColor(Color::Transparent);
                pieceColorText.setFillColor(Color::Transparent);
                difficultyLevelText.setString("PRESS ENTER TO START"
                    "\n\n     Color: " + textureInputStr + "\n    Difficulty: " + to_string(difficultyLevel - 1));
                difficultyLevelText.setCharacterSize(50);
                difficultyLevelText.setPosition(70, 200);
                difficultyLevelText.setOutlineThickness(2);
            }
        }        window2.display();


        window.display();
    }
}

