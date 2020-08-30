#pragma once

#include "CScene.h"
#include "MovieTitle.h"

namespace Opening {
class Title final : public CScene {
private:
	bool                        mMovieFinished = false;
	int                         mCounter       = 0;
	std::shared_ptr<MovieTitle> mTitleMovie;

public:
	Title(std::weak_ptr<ISceneChanger> sceneChanger);

	virtual void update() override;
};
} // namespace Opening
