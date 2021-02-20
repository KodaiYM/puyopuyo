#pragma once

#include "CScene.h"
#include "ImageLogo.h"

namespace Opening {
class MyLogo   final : public CScene {
#pragma region ŠO•”ŒöŠJ
public:
	std::shared_ptr<ITransStart> getTransStart() const override;
	void                         update() override;

public:
	MyLogo(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region ”ñŒöŠJ
private:
	int                              m_counter = 0;
	const std::shared_ptr<ImageLogo> m_MyLogo;
#pragma endregion
};
} // namespace Opening
