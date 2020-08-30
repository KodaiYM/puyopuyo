#pragma once

#include "CScene.h"
#include "ImageLogo.h"

namespace Opening {
class MyLogo final : public CScene {
private:
	int                              mCounter = 0;
	const std::shared_ptr<ImageLogo> mMyLogo;

public:
	MyLogo(std::weak_ptr<ISceneChanger> sceneChanger);

	virtual void update() override;
};
} // namespace Opening
