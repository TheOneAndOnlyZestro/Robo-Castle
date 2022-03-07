#pragma once

namespace GFX_Engine {
	class LogItem {
	public:
		LogItem() {}
		virtual ~LogItem() {}

		virtual void Log() const {}
	};
}
