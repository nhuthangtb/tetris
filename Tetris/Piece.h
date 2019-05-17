#pragma once
class Piece {
public:
	//Piece(int type, int angle);
	int getBlock(int type, int angle, int px, int py);
	

private:
	int px, py, type, angle;
};
