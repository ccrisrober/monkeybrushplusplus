#include <boost/python.hpp>

namespace mb
{
	class ScriptComponent: public Component
	{
		public:
		MB_API
		ScripComponent( const std::string &scriptFile );
		MB_API
		virtual void onAttach( void ) override;

	protected:
		std::string _scriptFile;
	}
}

namespace mb
{
	ScriptComponent::ScriptComponent( const std::string& scriptFile )
		: Component( )
	{

	}
	void ScriptComponent::onAttach( void )
	{

	}
}