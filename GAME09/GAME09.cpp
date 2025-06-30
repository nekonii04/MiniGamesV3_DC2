#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME09.h"
#include <string>
#include <fstream>

namespace GAME09
{
	int GAME::create()
	{
		rectMode(CENTER);
		player.load();
		invaderManager.load();
		barrierManager.create();
		hideCursor();

		backImg = loadImage("../MAIN/assets/GAME09/backImg.png");

		// ハイスコア読み込み
		std::ifstream in("highscore.txt");
		if (in.is_open()) {
			in >> highScore;
			in.close();
		}
		else {
			highScore = 0;
		}
		return 0;
	}

	void GAME::destroy()
	{
	}

	void GAME::proc()
	{
		clear(0, 0, 64);

		image(backImg, VECTOR(0,0),0.0f,1.0f);

		textSize(50);

		if (!gameOver && !gameClear) {
			player.update();
			invaderManager.update(player.getBullets(), player.getX(), player.getY(), gameOver, gameClear, score);
			barrierManager.update(invaderManager.getEnemyBullets());
		}

		player.draw();
		invaderManager.draw();
		barrierManager.draw();

		// スコア　ハイスコア表示
		fill(255);
		textSize(40);
		text(("SCORE: " + std::to_string(score)).c_str(), 1600, 50);
		text(("HIGHSCORE: " + std::to_string(highScore)).c_str(), 1600, 100);

		// ゲーム終了時にハイスコア保存
		static bool saved = false;
		if ((gameOver || gameClear) && !saved) {
			if (score > highScore) {
				highScore = score;
				std::ofstream out("highscore.txt");
				if (out.is_open()) {
					out << highScore;
					out.close();
				}
			saved = true;
			}
		}

		// ゲームオーバー・クリア表示
		if (gameOver) {
			fill(255, 0, 0);
			textSize(200);
			text("GAME OVER", 480, 540);
		}
		else if (gameClear) {
			fill(0, 255, 0);
			textSize(200);
			text("GAME CLEAR!", 480, 540);
		}

		//操作説明
		textSize(50);
		fill(255);
		text("[←][→]：移動", 0, 50);
		text("[SPACE]：弾を発射", 0, 100);
		text("ENTERキーでメニューに戻る", 0, 1080);

		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
