#pragma once
#include <memory>
#include "ResMgr.h"

class CObj {
protected:
	CObj() {}

public:
	virtual ~CObj() {}
	virtual void draw() const = 0;
};
