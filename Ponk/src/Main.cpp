#include "Game.h"
#include <memory>

int main(int argc, char* argv[]) {
	std::shared_ptr<Game> Ponk = std::make_shared<Game>();
	Ponk->Init();
	Ponk->Run();
	return 0;
}