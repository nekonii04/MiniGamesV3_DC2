#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME11.h"
namespace GAME11
{
	int GAME::create()
	{
		return 0;
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		clear(0, 0, 64);
		textSize(50);
		fill(255, 255, 0);
		text("GAME11", 0, 100);
		fill(255);
		text("ENTERキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
