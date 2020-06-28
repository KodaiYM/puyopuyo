#pragma once

#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "Objects.h"

namespace Opening {
	class MyLogo;
	class SSLogo;

	class LogoMgr final : public CSceneMgr {
	private:
		std::shared_ptr<MyLogo> mMyLogo;
		std::shared_ptr<SSLogo> mSSLogo;

	public:
		LogoMgr(std::weak_ptr<ISceneChanger> sceneChanger);

		virtual void init() override;
		virtual void deinit() override;
		virtual void update() override;
		virtual void ChangeScene(const std::type_info& nextScene) override;
	};

	class MyLogo final : public CObjMgr {
	private:
		int mCounter;
		int mWaitCounter;

		std::shared_ptr<Object::MyLogo> mMyLogo;

	public:
		MyLogo(std::weak_ptr<ISceneChanger> sceneChanger);

		virtual void init() override;
		virtual void deinit() override;
		virtual void update() override;
	};
	class SSLogo final : public CObjMgr {
	private:
		int mCounter;
		int mSpriteStudioIndex;

		std::shared_ptr<Object::SpriteStudio> mSS;

	public:
		SSLogo(std::weak_ptr<ISceneChanger> sceneChanger);

		virtual void init() override;
		virtual void deinit() override;
		virtual void update() override;
	};
}
