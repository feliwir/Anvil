#pragma once
#include <spark/scriptengine.hpp>

namespace anvil
{
	class ScriptEngine : public spark::IScriptEngine
	{
	public:
		ScriptEngine();
		void ExecuteString(const std::string& script);
		void ExecuteFile(const std::string& file);
	};
}