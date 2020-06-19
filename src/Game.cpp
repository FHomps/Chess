#include "Game.hpp"

Game::Game() {}

Game::Game(std::string const& filename) {
	loadFromFile(filename);
}

Game::~Game() {
	for (size_t row = 0; row < boardHeight; row++)
		delete[] board[row];
	delete[] board;
}

bool Game::loadFromFile(std::string const& filename) {
	for (size_t row = 0; row < boardHeight; row++)
		delete[] board[row];
	delete[] board;
	boardHeight = 0;
	boardWidth = 0;

	std::ifstream fs(filename);
	if (!fs.is_open())
		return false;
	std::deque<std::vector<Square>> vboard;
	bool whiteKing = false;
	bool blackKing = false;
	
	while (!fs.eof()) {
		std::string line;
		std::getline(fs, line);
		std::stringstream ss(line);
		
		std::vector<Square>& row = vboard.emplace_back();

		char c;
		ss >> c;

		while (!ss.eof()) {
			switch (c) {
			case '_': row.emplace_back(Square::VOID); break;
			case '.': row.emplace_back(Square::EMPTY); break;
			case 'K':
				if (!whiteKing) {
					row.emplace_back(Square::W_KING);
					whiteKing = true;
				}
				else
					row.emplace_back(Square::EMPTY);
				break;
			case 'Q': row.emplace_back(Square::W_QUEEN); break;
			case 'B': row.emplace_back(Square::W_BISHOP); break;
			case 'N': row.emplace_back(Square::W_KNIGHT); break;
			case 'R': row.emplace_back(Square::W_ROOK); break;
			case 'P': row.emplace_back(Square::W_PAWN); break;
			case 'k':
				if (!blackKing) {
					row.emplace_back(Square::B_KING);
					blackKing = true;
				}
				else
					row.emplace_back(Square::EMPTY);
				break;
			case 'q': row.emplace_back(Square::B_QUEEN); break;
			case 'b': row.emplace_back(Square::B_BISHOP); break;
			case 'n': row.emplace_back(Square::B_KNIGHT); break;
			case 'r': row.emplace_back(Square::B_ROOK); break;
			case 'p': row.emplace_back(Square::B_PAWN); break;
			default: break;
			}

			ss >> c;
		}

		if (row.size() > boardWidth)
			boardWidth = row.size();
	}

	if (!whiteKing || !blackKing)
		return false;

	while (!vboard.empty() && vboard.begin()->empty())
		vboard.pop_front();
	while (!vboard.empty() && vboard.rbegin()->empty())
		vboard.pop_back();
	if (vboard.empty())
		return false;	

	boardHeight = vboard.size();
	board = new Square*[boardHeight];
	for (size_t row = 0; row < boardHeight; row++) {
		board[row] = new Square[boardWidth];
		size_t col = 0;
		while (col < vboard[row].size()) {
			board[row][col] = vboard[row][col];
			col++;
		}
		while (col < boardWidth) {
			board[row][col] = Square::VOID;
			col++;
		}
	}

	return true;

}

char Game::squareToChar(Game::Square s) {
	switch (s) {
		case Square::VOID: return '_'; break;
		case Square::EMPTY: return '.'; break;
		case Square::W_KING: return 'K'; break;
		case Square::W_QUEEN: return 'Q'; break;
		case Square::W_BISHOP: return 'B'; break;
		case Square::W_KNIGHT: return 'N'; break;
		case Square::W_ROOK: return 'R'; break;
		case Square::W_PAWN: return 'P'; break;
		case Square::B_KING: return 'k'; break;
		case Square::B_QUEEN: return 'q'; break;
		case Square::B_BISHOP: return 'b'; break;
		case Square::B_KNIGHT: return 'n'; break;
		case Square::B_ROOK: return 'r'; break;
		case Square::B_PAWN: return 'p'; break;
		default: return '?'; break;
	}
}

void Game::printWhite() const {
	for (size_t row = 0; row < boardHeight; row++) {
		for (size_t col = 0; col < boardWidth; col++) {	
			std::cout << squareToChar(board[row][col]) << ' ';
		}
		std::cout << std::endl;;
	}
}

void Game::printBlack() const {
	for (size_t row = 0; row < boardHeight; row++) {
		for (size_t col = 0; col < boardWidth; col++) {	
			std::cout << squareToChar(board[boardHeight-row-1][boardWidth-col-1]) << ' ';
		}
		std::cout << std::endl;;
	}
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}