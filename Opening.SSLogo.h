#pragma once

#include "CScene.h"
#include "ImageSpriteStudio.h"

namespace Opening {
class SSLogo   final : public CScene {
#pragma region ŠO•”ŒöŠJ
public:
	std::shared_ptr<ITransStart> getTransStart() const noexcept override;
	void                         update() override;

public:
	SSLogo(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region ”ñŒöŠJ
private:
	int m_counter           = 0;
	int m_SpriteStudioIndex = 0;

	const std::shared_ptr<ImageSpriteStudio> m_SpriteStudio;
#pragma endregion
};
} // namespace Opening
