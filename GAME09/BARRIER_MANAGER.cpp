#include "BARRIER_MANAGER.h"

void BARRIER_MANAGER::create() {
    barriers.clear();
    const int numBarriers = 4;           
    const float spacing = 300.0f;        
    const float barrierWidth = 4 * 20.0f;  
    const float totalWidth = numBarriers * barrierWidth + (numBarriers - 1) * spacing;
    const float startX = (1920 - totalWidth) / 2.0f;  
    const float y = 800.0f;

    for (int i = 0; i < numBarriers; i++) {
        float baseX = startX + i * (barrierWidth + spacing);
        for (int bx = 0; bx < 4; ++bx) {
            for (int by = 0; by < 3; ++by) {
                BARRIER b;
                b.set(baseX + bx * 20, y + by * 20);
                barriers.push_back(b);
            }
        }
    }
}

void BARRIER_MANAGER::update(std::vector<ENEMY_BULLET>& enemyBullets) {
	for (auto& b : enemyBullets) {
		if (b.isDead()) continue;
		for (auto& barrier : barriers) {
			if (barrier.checkHit(b.getX(), b.getY())) {
				b.setDead();
				break;
			}
		}
	}
}

void BARRIER_MANAGER::draw() {
	for (auto& barrier : barriers) {
		barrier.draw();
	}
}
