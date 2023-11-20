#include <iostream>
#include <list>
using namespace std;

struct Piece{
    int lenght;
    int width;
    int price;
};

// Recursive function that realizes the cut
int cut(Piece& piece, int X, int Y, list<Piece>& pieces);


// Function that verifies if there is a piece that can be cut
int verify_pieces(list<Piece>& pieces, int X, int Y) {
    list<Piece>::iterator iter = next(pieces.begin());

    while (iter != pieces.end()) {
        if (iter->lenght < X || iter->width < Y) {
            return cut(*iter, X, Y, pieces);
        }
        ++iter;
    }

    return 0;
}


int cut(Piece& piece, int X, int Y, list<Piece>& pieces){
    int a = piece.lenght;
    int b = piece.width;

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        return verify_pieces(pieces, X, Y);
    }

    // The plate is equal to the piece
    else if (X == a && Y == b) {
        return piece.price;
    }

    // Case where the plate is cut vertically
    else if (X > a && Y == b) {
        return piece.price + cut(piece, X - a, Y, pieces);
    }

    // Case where the plate is cut horizontally
    else if (Y > b && X == a) {
        return piece.price + cut(piece, X, Y - b, pieces);
    } 

    else {
        return cut(piece, X - a, Y, pieces) + cut(piece, a, Y, pieces);
    }
}

void insertSorted(std::list<Piece>& pieces, const Piece& newPiece) {
    list<Piece>::iterator iter = pieces.begin();

    // Encontrar a posição correta para inserção
    while (iter != pieces.end() && newPiece.price <= iter->price) {
        ++iter;
    }

    pieces.insert(iter, newPiece);
}

int main(){
    int X, Y, n;
    int result = 0;

    list <Piece> pieces;

    cin >> X >> Y;  // Plate dimensions
    cin >> n;       // Types of pieces

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;
        if (a > X && b > Y){      // Piece is bigger than the plate
            continue;
        }

        // Swap the dimensions to rotate the piece
        if ((a > X && b <= Y ) || (a <= X && b > Y)) {
            swap(a, b);
        }
        Piece newPiece = {a, b, price};
        insertSorted(pieces, newPiece);
    }

    for (Piece piece : pieces) {
        int temp = cut(piece, X, Y, pieces);
        if (temp > result) {
            result = temp;
        }
    }

    cout << result << endl;
    return 0;
}



