#pragma once

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

enum class PieceType {Pawn = 1, Knight, Bishop, Rook, Queen, King};

class Piece
{
public:
	PieceType Type;
	Vector *Moves;
	int SizeMoves;
	bool bIsRepeatable;
	bool bMoveIsCapture;
	bool bIsRotateable;
	Vector *Captures;
	int SizeCaptures;
	bool bHasMoved;
	Piece(PieceType type)
	{
		Type = type;
		bHasMoved = false;
		switch (type) 
		{
			case PieceType::Pawn:
				Moves = new Vector[1]{ Vector(0,1) };
				SizeMoves = 1;
				bIsRepeatable = false;
				bMoveIsCapture = false;
				bIsRotateable = false;
				Captures = new Vector[2]{ Vector(-1,1), Vector(1,1) };
				SizeCaptures = 2;
				break;
			case PieceType::Knight:
				Moves = new Vector[2]{ Vector(2,-1), Vector(2, 1) };
				SizeMoves = 2;
				bIsRepeatable = false;
				bMoveIsCapture = true;
				bIsRotateable = true;
				Captures = Moves;
				SizeCaptures = SizeMoves;
				break;
			case PieceType::Bishop:
				Moves = new Vector[1]{ Vector(1,1) };
				SizeMoves = 1;
				bIsRepeatable = true;
				bMoveIsCapture = true;
				bIsRotateable = true;
				Captures = Moves;
				SizeCaptures = SizeMoves;
				break;
			case PieceType::Rook:
				Moves = new Vector[1]{ Vector(0,1) };
				SizeMoves = 1;
				bIsRepeatable = true;
				bMoveIsCapture = true;
				bIsRotateable = true;
				Captures = Moves;
				SizeCaptures = SizeMoves;
				break;
			case PieceType::Queen:
				Moves = new Vector[2]{ Vector(0,1), Vector(1,1) };
				SizeMoves = 2;
				bIsRepeatable = true;
				bMoveIsCapture = true;
				bIsRotateable = true;
				Captures = Moves;
				SizeCaptures = SizeMoves;
				break;
			case PieceType::King:
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
	Piece HeldPiece;
};

class Board
{

};