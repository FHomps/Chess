#pragma once

class Game : public sf::Drawable, public sf::Transformable {
public:
	Game();
	Game(std::string const& filename);
	~Game();

	void printWhite() const;
	void printBlack() const;

	bool loadFromFile(std::string const& filename);

private:
	enum Square : short {
		VOID, EMPTY,
		W_KING, W_QUEEN, W_BISHOP, W_KNIGHT, W_ROOK, W_PAWN,
		B_KING, B_QUEEN, B_BISHOP, B_KNIGHT, B_ROOK, B_PAWN
	};

	static char squareToChar(Square s);

	Square** board;
	size_t boardHeight;
	size_t boardWidth;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};