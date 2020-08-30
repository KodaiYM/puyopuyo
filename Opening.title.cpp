#include "Opening.Title.h"
#include "CTransDarkness.h"
#include "CTransFadein.h"
#include "CTransFadeout.h"
#include "Menu.h"
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
	// まだムービーが終了していなければ
	if (!mMovieFinished) {
		// 再生する。
		// ムービー終了なら
		if (mTitleMovie->update()) {
			// ムービー終了とする
			mMovieFinished = true;
		}
	}

	switch (mCounter) {
	case 0: // まだエンターを押していない
		if (mMovieFinished) {
			// ムービー終了
			mSceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransDarkness>(60, CTransDarkness::Mode::Fix),
			    std::make_shared<CTransFadein>(30, CTransFadein::Mode::Fix),
			    std::make_shared<Opening::MyLogo>(mSceneChanger));
		} else if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			mSceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransFadeout>(60, CTransFadeout::Mode::Update),
			    std::make_shared<CTransFadein>(60, CTransFadein::Mode::Update),
			    std::make_shared<Menu::SceneMenu>(mSceneChanger));
			++mCounter;
		}
		break;
	case 1: // エンターを押して、遷移中
		break;
	default:
		assert(false);
		break;
	}
}
