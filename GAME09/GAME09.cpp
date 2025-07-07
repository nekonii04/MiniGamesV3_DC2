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

		// �n�C�X�R�A�ǂݍ���
		std::ifstream in("../MAIN/assets/GAME09/highscore.txt");
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

		// �X�R�A�@�n�C�X�R�A�\��
		fill(255);
		textSize(40);
		text(("SCORE: " + std::to_string(score)).c_str(), 1600, 50);
		text(("HIGHSCORE: " + std::to_string(highScore)).c_str(), 1600, 100);

		// �Q�[���I�����Ƀn�C�X�R�A�ۑ�
		static bool saved = false;
		if ((gameOver || gameClear) && !saved) {
			if (score > highScore) {
				highScore = score;
				std::ofstream out("../MAIN/assets/GAME09/highscore.txt");
				if (out.is_open()) {
					out << highScore;
					out.close();
				}
			saved = true;
			}
		}

		// �Q�[���I�[�o�[�E�N���A�\��
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

		//�������
		textSize(50);
		fill(255);
		text("[��][��]�F�ړ�", 0, 50);
		text("[SPACE]�F�e�𔭎�", 0, 100);
		text("ENTER�L�[�Ń��j���[�ɖ߂�", 0, 1080);

		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
