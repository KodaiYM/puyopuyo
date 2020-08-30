#pragma once

#include "CScene.h"
#include "GraphicSpriteStudio.h"

namespace Opening {
class SSLogo final : public CScene {
private:
	int mCounter           = 0;
	int mSpriteStudioIndex = 0;

	const std::shared_ptr<GraphicSpriteStudio> mSS;

public:
	SSLogo(std::weak_ptr<ISceneChanger> sceneChanger);

	virtual void update() override;
};
} // namespace Opening
