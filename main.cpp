#include <iostream>
#include <array>
#include <random>

enum class Colours {
	RED,
	LIME,
	ORANGE,
	YELLOW,
	RESET
};

class Game {
	private:
	static std::random_device rd;
	static std::mt19937 gen;

	int attempts{ 10 };

	static int guess, random_number;
	static char does_user_want_to_play_again;

	std::array<std::string_view, 5> colours {
		"\033[31m",
		"\033[38;5;40m",
		"\033[38;5;208m",
		"\033[33m",
		"\033[0m"
	};

	public:

	void output_attempts(int attempts) {
		std::cout << colours[static_cast<int>(Colours::ORANGE)] << "ATTEMPTS: " << colours[static_cast<int>(Colours::RESET)];

		if(attempts >= 7) {
			std::cout << colours[static_cast<int>(Colours::LIME)] << attempts << "\n\n" << colours[static_cast<int>(Colours::RESET)];
		} else if(attempts >= 4) {
			std::cout << colours[static_cast<int>(Colours::YELLOW)] << attempts << "\n\n" << colours[static_cast<int>(Colours::RESET)];
		} else {
			std::cout << colours[static_cast<int>(Colours::RED)] << attempts << "\n\n" << colours[static_cast<int>(Colours::RESET)];
		}
	}

	void check() {
		if (guess > 100) {
			std::cout << colours[static_cast<int>(Colours::RED)] << "Out of range!\n" << colours[static_cast<int>(Colours::RESET)];
		}

		if (guess < random_number) {
			std::cout << colours[static_cast<int>(Colours::RED)] << "Too low!\n" << colours[static_cast<int>(Colours::RESET)];
			--attempts;
		}

		if (guess > random_number && guess < 100) {
			std::cout << colours[static_cast<int>(Colours::RED)] << "Too high!\n" << colours[static_cast<int>(Colours::RESET)];
			--attempts;
		} else if(guess == random_number) {  // Correct guess
			std::cout << colours[static_cast<int>(Colours::LIME)] << "CORRECT!!\n" << colours[static_cast<int>(Colours::RESET)];
			playAgain();
			return;
		}

		if(attempts <= 0) {
			std::cout << "\nYou have ran out of attempts!";
			playAgain();
		}

		output_attempts(attempts);

		std::cout << "Enter number (0-100): ";
		std::cin >> guess;

		check();
	}

	void playAgain() {
		std::cout << '\n' << "Do you want to play again? (y/n): ";
		std::cin >> does_user_want_to_play_again;

		if (does_user_want_to_play_again == 'y') {
			random_number = std::uniform_int_distribution<uint8_t>(0, 100)(gen);
			guess = 0;

			#ifdef __WIN32
			system("cls");
			#else
			system("clear");
			#endif

			greeting();
		} else {
			std::cout << "Goodbye!\n";
		}
	}

	void greeting() {
		random_number = std::uniform_int_distribution<uint8_t>(0, 100)(gen);

		std::cout << ":::::::::: Number Guessing Game ::::::::::\n"
											 << "Enter a number (0-100): ";
		std::cin >> guess;
		check();
	}
};

std::random_device Game::rd;
std::mt19937 Game::gen(Game::rd());
int Game::guess = 0;
int Game::random_number = 0;
char Game::does_user_want_to_play_again = 'n';

int main() {
	Game game;

	game.greeting();
	return 0;
}
