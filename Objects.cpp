#include "Objects.h"
#include <cassert>

using namespace Object;

// CStaticObj
CStaticObj::CStaticObj(GrName grName) :mGrName(grName) {
	x = y = 0;
	TransFlag = TRUE;
}
void CStaticObj::draw() const {
	DrawGraph(x, y, ResMgr::getInstance().getHandle(mGrName), TransFlag);
}

// CFlipObj
CFlipObj::CFlipObj(GrName grName, unsigned int maxCount) :mGrName(grName), mMaxCount(maxCount) {
	x = y = 0;
	TransFlag = TRUE;
	mCounter = -1;
}
CFlipObj::STATUS CFlipObj::update() {
	mCounter++;

	if (mCounter >= mMaxCount) {
		return STATUS::END;
	}

	switch (mCounter) {
	case -1:
		return STATUS::NOT_STARTED;
		break;
	case 0:
		return STATUS::BEGINNING;
		break;
	default:
		return STATUS::MIDDLE;
		break;
	}
}
void CFlipObj::draw() const {
	if (mCounter == -1) {
		assert("Before draw(), update() at least once.");
	}
	DrawGraph(x, y, ResMgr::getInstance().getHandle(mGrName, mCounter >= mMaxCount ? mMaxCount : mCounter), TRUE);
}

// CMovieObj
CMovieObj::CMovieObj(GrName grName) :mGrName(grName) {
}
void CMovieObj::init() {
	mStatus = STATUS::NOT_STARTED;
}
void CMovieObj::deinit() {
	SeekMovieToGraph(ResMgr::getInstance().getHandle(mGrName), 0);
	PauseMovieToGraph(ResMgr::getInstance().getHandle(mGrName));
}
CMovieObj::STATUS CMovieObj::update() {
	switch (mStatus) {
	case STATUS::NOT_STARTED:
		SeekMovieToGraph(ResMgr::getInstance().getHandle(mGrName), 0);
		PlayMovieToGraph(ResMgr::getInstance().getHandle(mGrName));
		mStatus = STATUS::BEGINNING;
		break;
	case STATUS::BEGINNING:
		mStatus = STATUS::MIDDLE;
		break;
	case STATUS::MIDDLE:
		if (GetMovieStateToGraph(ResMgr::getInstance().getHandle(mGrName)) == 0) {
			mStatus = STATUS::END;
			PauseMovieToGraph(ResMgr::getInstance().getHandle(mGrName));
		}
		break;
	}
	return mStatus;
}
void CMovieObj::draw() const {
	DrawGraph(0, 0, ResMgr::getInstance().getHandle(mGrName), FALSE);
}
