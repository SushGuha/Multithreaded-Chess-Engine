#Open Source C++ Multi-threaded Engine

**CONTRIBUTORS**:

DINYAR ISLAM

SUSHANT GUHA 

**Development information:**
Operating System: Windows-10
External library: Triple Happy Chess (https://github.com/billforsternz/thc-chess-library).

**Running information**
How to run on VSCode in Win-10:

1. Download the VSCode C/C++ Extension pack and the apprioriate version of SFML for your Operating system (Windows or MacOS).
2. Set the absolute path to the include folder in your SFML folder in c_cpp_properties under includePath. The path to my SFML folder is currently given (It is the second array element in includePath)
3. Set the absolute path to the include folder of your SFML in the makefile line 4 (under compile). Currently the path to my include folder is set as -IC://etc... replace the C://etc... with the correct path while keeping the -I.
4. Set the absolute path to the lib folder of your SFML in the makefile line 7 (under link). Currently the path to my lib folder is set as -LC://etc... replace the C://etc... with the correct path while keeping the -L.
5. Run make (or mingw32-make depending on your installation) to compile the code
6. Run ./frontend to run the program.

Here is the tutorial I used to setup SFML in VSCode: https://www.youtube.com/watch?v=rZE700aaT5I

Note: The above steps CAN also be used in MacOS, albeit with compiler warnings which can be ignored. These warnings do not appear in the windows Mingw compiler which was used throughout the project.

**Project implementation information**

The external library used has 2 files: thc.h and thc.cpp. These file were NOT written by us, and are from the external library linked above.

The file **MtEngine.h** contains a custom class for the engine. The frontend.cpp file contains the code for the SFML and creates an instantiation of the engine from MTEngine.h in order to generate the move for the opponent.

The project uses a minimax-style chess engine that determines the best move. The evaluation function is a heiristic function that takes in the current position of all the pieces on the chessboard and uses piece tables to determine the 'value' of a particular piece at a particular location. The minimax engine searches for the best move by looking for the opponent's best move and responding to that. It does this until a certain depth limit is reached. This depth limit is set when choosing the game difficulty.

Multithreading is used to run multiple minimax algorithms in parallel on the list of legal moves. A new thread is created for every legal move when the first instance of the minimax function is called. After this, the minimax function calls itself recursively until the depth limit is reached. The minimax calling itself is done in a singlethreaded manner and each thread in the system is running its own individual minimax function. This way, the computation time is vastly reduced. This made it difficult to run alpha-beta pruning to reduce the number of computations required. However, alpha-beta pruning is added on an individual thread basis.

The **frontend.cpp** file contains the SFML code to allow the user to play Chess. It contains the custom class "Tile" that represents an individual square on the chess board. The file allows the user to input moves, and the enigne to play its moves in response. The code uses the Engine class in MtEngine.h for move validation and for the engine's response. It also contains code that allows the user to customize the appearance of the board and their playing options. Multiple view windows are used for this purpose.

**Topics Used:**

1. Custom Class: The 'Engine' class in MtEngine.h is a custom class that encapuslates the functionality of the multi-threaded chess engine. The 'Tile' class in frontend.cpp is a custom class that represents a square in a chessboard. It encapsulates valuable data such as the colour of the piece residing in that square, the notation of that square (Eg: "a5"), and the piece currently residing on it.
2. Multithreading: std::thread is used the MtEngine.h class to efficiently determine the best move to play. The performance gain from using multithreading is huge, with single-threaded designs taking slightly longer at lower depths (<= 3), and considerably longer at higher depths (>= 4).
3. Simple Fast Media Library (SFML): SFML is used to create the 2-D Chess game. SFML allows the game to be played in a stable manner while also providing additional information such as timers, moves made, and possible moves.

