#include "CatanGui/CatanLauncher/CatanLauncher.h"

int main(int argc, char** argv) {

	/*
	* Inicializo allegro...
	*/
	WindowUI::InitAllegro();

	if (WindowUI::isAllegroInit()) {

		CatanLauncher launcher;

		launcher.getGame().getCatanMap()->generateLand();
		launcher.getGame().getCatanMap()->generateSea();
		launcher.getGame().getCatanMap()->generateTokens();

		/*
		* Verifico que no haya terminado y,
		* cerrado... y bueno, eso es todo!
		*/
		while (launcher.alive()) {
			launcher.run();
		}
	}
}