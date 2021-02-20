#pragma once

#include "CScene.h"
#include "ImageSpriteStudio.h"

namespace Opening {
class SSLogo   final : public CScene {
#pragma region ŠO•”ŒöŠJ
public:
	std::shared_ptr<ITransStart> getTransStart() const override;
	virtual void                 update() override;

public:
	SSLogo(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region ”ñŒöŠJ
private:
	int mCounter           = 0;
	int mSpriteStudioIndex = 0;

	const std::shared_ptr<ImageSpriteStudio> mSS;
#pragma endregion
};
} // namespace Opening
