#pragma once

#include "CScene.h"
#include "GraphicLogo.h"

namespace Opening {
class MyLogo final : public CScene {
private:
	int                                mCounter = 0;
	const std::shared_ptr<GraphicLogo> mMyLogo;

public:
	MyLogo(std::weak_ptr<ISceneChanger> sceneChanger);

	virtual void update() override;
};
} // namespace Opening
