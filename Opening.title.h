#pragma once

#include "CObjMgr.h"
#include "Objects.h"

namespace Opening {
	class TitleMgr final :public CObjMgr {
	private:
		int mCounter;
		std::shared_ptr<Object::TitleMovie> mTitleMovie;

	public:
		TitleMgr(std::weak_ptr<ISceneChanger> sceneChanger);

		virtual void init() override;
		virtual void deinit() override;
		virtual void update() override;
	};
}