#include "CSceneMgr.h"
#include "CBright.h"
#include "ITrans.h"
#include <cassert>

void CSceneMgr::update() {
	changed = false;

	/* 終了時処理 */
	if (mHowToEnd) {
		if (!lasted) {
			// mHowToEnd に値があり、直前が最後のフレームではない場合
			if (mHowToEnd->update(mCurrentScene)) {
				// 最後のフレームの時
				lasted = true;
			}
			return;
		} else {
			// 直前が最後のフレームだった
			assert(lasted);

			mHowToEnd.reset();
			mCurrentScene.reset();
			lasted = false;
		}
	}

	/* 開始時処理 */
	if (mHowToStart) {
		if (!lasted) {
			// mHowToStart に値があり、直前が最後のフレームではない場合
			if (mHowToStart->update(mNextScene)) {
				// 最後のフレームの時
				lasted = true;
			}
			return;
		} else {
			// 直前が最後のフレームだった
			assert(lasted);

			mHowToStart.reset();
			lasted = false;
		}
	}

	/* next scene の移動 */
	if (mNextScene) {
		mCurrentScene = std::move(mNextScene);
		mNextScene.reset();
		CBright::getInstance().SetDrawBright(255, 255, 255);
	}

	mCurrentScene->update();
}
void CSceneMgr::draw() const {
	if (changed) {
		mCurrentScene->draw();
	} else {
		if (mHowToEnd) {
			mHowToEnd->draw(mCurrentScene);
		} else if (mHowToStart) {
			mHowToStart->draw(mNextScene);
		} else {
			mCurrentScene->draw();
		}
	}
}
void CSceneMgr::ChangeScene(std::shared_ptr<ITransEnd> howToEnd,
                            std::shared_ptr<CScene>    nextScene) {
	mHowToEnd   = std::move(howToEnd);
	mNextScene  = std::move(nextScene);
	mHowToStart = mNextScene->getTransStart();
	changed     = true;
	lasted      = false;
}
