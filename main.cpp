#include <iostream>
#include <cctype>
using namespace std;

class ChessGame {
private:
    char board[8][8];
    bool whiteTurn;

public:
    ChessGame() {
        whiteTurn = true;
        initializeBoard();
    }

    void initializeBoard() {
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                board[i][j] = '.';

        // Pawns
        for(int i=0;i<8;i++){
            board[1][i] = 'P';
            board[6][i] = 'p';
        }

        // Rooks
        board[0][0] = board[0][7] = 'R';
        board[7][0] = board[7][7] = 'r';

        // Knights
        board[0][1] = board[0][6] = 'N';
        board[7][1] = board[7][6] = 'n';

        // Bishops
        board[0][2] = board[0][5] = 'B';
        board[7][2] = board[7][5] = 'b';

        // Queens
        board[0][3] = 'Q';
        board[7][3] = 'q';

        // Kings
        board[0][4] = 'K';
        board[7][4] = 'k';
    }

    void displayBoard() {
        cout << "\n   0 1 2 3 4 5 6 7\n";
        for(int i=0;i<8;i++){
            cout << i << "  ";
            for(int j=0;j<8;j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    bool isValidMove(int fr, int fc, int tr, int tc) {

        if(fr<0||fr>7||fc<0||fc>7||tr<0||tr>7||tc<0||tc>7)
            return false;

        char piece = board[fr][fc];
        char destination = board[tr][tc];

        if(piece == '.')
            return false;

        // Turn validation
        if(whiteTurn && islower(piece)) return false;
        if(!whiteTurn && isupper(piece)) return false;

        int dr = tr - fr;
        int dc = tc - fc;

        switch(tolower(piece)) {

            case 'p': // Pawn
                if(isupper(piece)) { // White
                    if(dc==0 && dr==1 && destination=='.')
                        return true;
                } else { // Black
                    if(dc==0 && dr==-1 && destination=='.')
                        return true;
                }
                break;

            case 'r': // Rook
                if(fr==tr || fc==tc)
                    return true;
                break;

            case 'n': // Knight
                if((abs(dr)==2 && abs(dc)==1) ||
                   (abs(dr)==1 && abs(dc)==2))
                    return true;
                break;

            case 'b': // Bishop
                if(abs(dr)==abs(dc))
                    return true;
                break;

            case 'q': // Queen
                if(fr==tr || fc==tc || abs(dr)==abs(dc))
                    return true;
                break;

            case 'k': // King
                if(abs(dr)<=1 && abs(dc)<=1)
                    return true;
                break;
        }

        return false;
    }

    bool isKingAlive(char kingSymbol) {
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(board[i][j] == kingSymbol)
                    return true;
        return false;
    }

    void movePiece(int fr, int fc, int tr, int tc) {
        board[tr][tc] = board[fr][fc];
        board[fr][fc] = '.';
        whiteTurn = !whiteTurn;
    }

    void startGame() {
        int fr, fc, tr, tc;

        while(true) {
            displayBoard();
            cout << (whiteTurn ? "White" : "Black") << " Turn\n";
            cout << "Enter move (fromRow fromCol toRow toCol): ";
            cin >> fr >> fc >> tr >> tc;

            if(isValidMove(fr,fc,tr,tc)) {
                movePiece(fr,fc,tr,tc);

                // Game State Evaluation
                if(!isKingAlive('K')) {
                    cout << "Black Wins! White King Captured.\n";
                    break;
                }
                if(!isKingAlive('k')) {
                    cout << "White Wins! Black King Captured.\n";
                    break;
                }
            }
            else {
                cout << "Invalid Move!\n";
            }
        }
    }
};

int main() {
    ChessGame game;
    game.startGame();
    return 0;
}