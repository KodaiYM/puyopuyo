#pragma once

#include "CScene.h"
#include "MovieTitle.h"

namespace Opening {
class Title    final : public CScene {
#pragma region ŠO•”ŒöŠJ
public:
	std::shared_ptr<ITransStart> getTransStart() const override;
	void                         update() final;

public:
	Title(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region ”ñŒöŠJ
private:
	bool                        mMovieFinished = false;
	int                         mCounter       = 0;
	std::shared_ptr<MovieTitle> mTitleMovie;
#pragma endregion
};
} // namespace Opening
