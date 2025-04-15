#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME15.h"

//メインループ側でESCキーの判定をするしないの状態を保持するグローバル変数
extern bool EscapeKeyValid;

namespace GAME15
{
	int GAME::create()
	{
		//メインループ側でのESCキーでの終了判定を無効化する
		EscapeKeyValid = false;

		//ここにはゲーム開始時に1回だけ行うものを記述する



		return 0;
	}

	void GAME::destroy()
	{
		//ここにはゲーム終了時に1回だけ行うものを記述する



		//メインループ側でのESCキーでの終了判定を有効化する
		EscapeKeyValid = true;
	}

	void GAME::proc()
	{
		clear(0, 0, 64);

		print(delta);

		fill(255);
		text("ESCキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ESCAPE)) {
			main()->backToMenu();
		}
	}
}
