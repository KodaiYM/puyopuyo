#include "Opening.Title.h"
#include "CTransDarkness.h"
#include "CTransFadein.h"
#include "Opening.MyLogo.h"
#include "key.h"
#include <DxLib.h>
#include <assert.h>

using namespace Opening;

Title::Title(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mTitleMovie(std::make_shared<MovieTitle>()) {
	addToDrawList(mTitleMovie);
}
void Title::update() {
	switch (mCounter) {
	case 0:
		if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			mCounter++;
		} else if (mTitleMovie->update()) {
			// ムービー終了
			mSceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransDarkness>(500, CTransDarkness::Mode::Fix),
			    std::make_shared<CTransFadein>(30, CTransFadein::Mode::Fix),
			    std::make_shared<Opening::MyLogo>(mSceneChanger));
		}
		break;
	case 1:
		if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			mCounter--;
		}
		break;
	}
}
