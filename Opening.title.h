#pragma once

#include "CScene.h"
#include "MovieTitle.h"

namespace Opening {
class Title    final : public CScene {
#pragma region ŠO•”ŒöŠJ
public:
	std::shared_ptr<ITransStart> getTransStart() const noexcept override;
	void                         update() final;

public:
	Title(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region ”ñŒöŠJ
private:
	bool                        m_movieFinished = false;
	int                         m_counter       = 0;
	std::shared_ptr<MovieTitle> m_TitleMovie;
#pragma endregion
};
} // namespace Opening
