#pragma once
#include "CObj.h"
#include "ResMgr.h"
#include <DxLib.h>

namespace Object {
	class CStaticObj : public CObj {
	private:
		const GrName mGrName;

	protected:
		int x, y;
		int TransFlag;

		CStaticObj(GrName grName);

	public:
		virtual void draw() const override final;
	};
	class CFlipObj : public CObj {
	private:
		const GrName mGrName;
		const unsigned int mMaxCount;
		unsigned int mCounter;

	protected:
		int x, y;
		int TransFlag;

		CFlipObj(GrName grName, unsigned int maxCount);

	public:
		enum class STATUS {
			NOT_STARTED,
			BEGINNING,
			MIDDLE,
			END
		};
		STATUS update();
		virtual void draw() const override final;
	};
	class CMovieObj :public CObj {
	private:
		const GrName mGrName;

	public:
		enum class STATUS {
			NOT_STARTED,
			BEGINNING,
			MIDDLE,
			END
		};

	private:
		STATUS mStatus;

	public:
		CMovieObj(GrName grName);
		void init();
		void deinit();
		STATUS update();
		virtual void draw() const override final;
	};

	class MyLogo final :public CStaticObj {
	private:
		const std::unordered_set<GrName> ResInfo = { GrName::Logo };

	public:
		MyLogo() :CStaticObj(GrName::Logo) {
			x = y = 0;
			TransFlag = FALSE;
			ResMgr::getInstance().push_profile(ResInfo);
		}
		~MyLogo() {
			ResMgr::getInstance().pop_profile(ResInfo);
		}
	};

	class SpriteStudio final :public CObj {
	private:
		int x, y;
		int TransFlag;
		class SpriteStudioFlip final :public CFlipObj {
		public:
			SpriteStudioFlip() :CFlipObj(GrName::SpriteStudio, 119) {}
		} mSpriteStudioFlip;
		const std::unordered_set<GrName> ResInfo = { GrName::SpriteStudio };

	public:
		SpriteStudio() {
			x = y = 0;
			TransFlag = TRUE;
			ResMgr::getInstance().push_profile(ResInfo);
		}
		~SpriteStudio() {
			ResMgr::getInstance().pop_profile(ResInfo);
		}
		SpriteStudioFlip::STATUS update() {
			return mSpriteStudioFlip.update();
		}
		virtual void draw() const override final {
			DrawBox(x, y, 640, 480, GetColor(96, 96, 96), TRUE);
			mSpriteStudioFlip.draw();
		}
	};

	class TitleMovie final :public CMovieObj {
	private:
		const std::unordered_set<GrName> ResInfo = { GrName::Title };

	public:
		TitleMovie() :CMovieObj(GrName::Title) {
			ResMgr::getInstance().push_profile(ResInfo);
		}
		~TitleMovie() {
			ResMgr::getInstance().pop_profile(ResInfo);
		}
	};
}
