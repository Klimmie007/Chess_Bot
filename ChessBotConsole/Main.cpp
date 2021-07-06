#include <iostream>

struct Vector
{
	int X;
	int Y;
	Vector(int x, int y)
	{
		X = x;
		Y = y;
	}
};

enum class PieceType { Pawn = 1, Knight, Bishop, Rook, Queen, King };

class Piece
{
public:
	char Symbol;
	PieceType Type;
	Vector* Moves;
	int SizeMoves;
	bool bIsRepeatable;
	bool bMoveIsCapture;
	bool bIsRotateable;
	Vector* Captures;
	int SizeCaptures;
	bool bHasMoved;
	bool bIsWhite;
	Piece(PieceType type, bool isWhite)
	{
		bIsWhite = isWhite;
		Type = type;
		bHasMoved = false;
		switch (type)
		{
		case PieceType::Pawn:
			Symbol = isWhite ? 'P' : 'p';
			Moves = new Vector[1]{ Vector(0,1) };
			SizeMoves = 1;
			bIsRepeatable = false;
			bMoveIsCapture = false;
			bIsRotateable = false;
			Captures = new Vector[2]{ Vector(-1,1), Vector(1,1) };
			SizeCaptures = 2;
			break;
		case PieceType::Knight:
			Symbol = isWhite ? 'N' : 'n';
			Moves = new Vector[2]{ Vector(2,-1), Vector(2, 1) };
			SizeMoves = 2;
			bIsRepeatable = false;
			bMoveIsCapture = true;
			bIsRotateable = true;
			Captures = Moves;
			SizeCaptures = SizeMoves;
			break;
		case PieceType::Bishop:
			Symbol = isWhite ? 'B' : 'b';
			Moves = new Vector[1]{ Vector(1,1) };
			SizeMoves = 1;
			bIsRepeatable = true;
			bMoveIsCapture = true;
			bIsRotateable = true;
			Captures = Moves;
			SizeCaptures = SizeMoves;
			break;
		case PieceType::Rook:
			Symbol = isWhite ? 'R' : 'r';
			Moves = new Vector[1]{ Vector(0,1) };
			SizeMoves = 1;
			bIsRepeatable = true;
			bMoveIsCapture = true;
			bIsRotateable = true;
			Captures = Moves;
			SizeCaptures = SizeMoves;
			break;
		case PieceType::Queen:
			Symbol = isWhite ? 'Q' : 'q';
			Moves = new Vector[2]{ Vector(0,1), Vector(1,1) };
			SizeMoves = 2;
			bIsRepeatable = true;
			bMoveIsCapture = true;
			bIsRotateable = true;
			Captures = Moves;
			SizeCaptures = SizeMoves;
			break;
		case PieceType::King:
			Symbol = isWhite ? 'K' : 'k';
			Moves = new Vector[2]{ Vector(0,1), Vector(1,1) };
			SizeMoves = 2;
			bIsRepeatable = false;
			bMoveIsCapture = true;
			bIsRotateable = true;
			Captures = Moves;
			SizeCaptures = SizeMoves;
			break;
		default:
			throw(-1);
		}
	}
	~Piece()
	{
		if (Moves != nullptr)
			delete[] Moves;
		if (!bMoveIsCapture && Captures != nullptr)
			delete[] Captures;
	}
};

class Tile
{
public:
	Piece* HeldPiece;
	Tile()
	{};
	~Tile()
	{
		delete HeldPiece;
	}
};

class Board
{
public:
	Tile Tiles[8][8];
	enum Colour { White, Black };
	Board()
	{
		Init(White);
		Init(Black);
		for (int i = 2; i < 6; i++)
			for (int j = 0; j < 8; j++)
				Tiles[i][j].HeldPiece = nullptr;
	}
	void Init(Colour colour)
	{
		int Rows[2];
		bool bIsWhite;
		if (colour == White)
		{
			Rows[0] = 0;
			Rows[1] = 1;
			bIsWhite = true;
		}
		else
		{
			Rows[0] = 7;
			Rows[1] = 6;
			bIsWhite = false;
		}
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				Tiles[Rows[i]][0].HeldPiece = new Piece(PieceType::Rook, bIsWhite);
				Tiles[Rows[i]][7].HeldPiece = new Piece(PieceType::Rook, bIsWhite);
				Tiles[Rows[i]][1].HeldPiece = new Piece(PieceType::Knight, bIsWhite);
				Tiles[Rows[i]][6].HeldPiece = new Piece(PieceType::Knight, bIsWhite);
				Tiles[Rows[i]][2].HeldPiece = new Piece(PieceType::Bishop, bIsWhite);
				Tiles[Rows[i]][5].HeldPiece = new Piece(PieceType::Bishop, bIsWhite);
				Tiles[Rows[i]][3].HeldPiece = new Piece(PieceType::Queen, bIsWhite);
				Tiles[Rows[i]][4].HeldPiece = new Piece(PieceType::King, bIsWhite);
			}
			else
			{
				for (int j = 0; j < 8; j++)
					Tiles[Rows[i]][j].HeldPiece = new Piece(PieceType::Pawn, bIsWhite);
			}
		}
	}
};

int main()
{
	Board Board;
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << (Board.Tiles[i][j].HeldPiece != nullptr ? Board.Tiles[i][j].HeldPiece->Symbol : 'x') << ' ';
		}
		std::cout << '\n';
	}
	return 0;
}