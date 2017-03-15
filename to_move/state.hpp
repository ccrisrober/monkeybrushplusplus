namespace mb 
{
	class StateMachine;
	class State
	{
	public:
		State(std::shared_ptr<StateMachine> owner);
		virtual ~State( void );

		virtual void Enter( void ) = 0;
		virtual void Exit( void ) = 0;
		virtual void Update( void ) = 0;
		std::shared_ptr< StateMachine > owner;
	}

	class StateMachine:
		public Node
	{
	public:
		StateMachine( void );
		virtual ~StateMachine( void );
		
		std::shared_ptr< State > currentState;
		virtual void Update( const float& dt ) override;
		void SwitchState( std::shared_ptr< State > newState );
	}
}

namespace mb
{
	State::State( std::shared_ptr< StateMachine > o )
	: owner( o ) 
	{
	}
	State::~State( void )
	{
	}
	StateMachine::StateMachine( void )
		: Component( )
		, currentState( nullptr )
	{
	}
	void StateMachine::SwitchState( std::shared_ptr< State > newState )
	{
		if ( currentState != nullptr )
		{
			currentState->Exit( );
		}
		currentState = newState;
		if ( newState != nullptr )
		{
			currentState->Enter( );
		}
	}
	void StateMachine::Update( )
	{
		if( currentState != nullptr )
		{
			currentState->Update( );
		}
		// TODO (Neccesary?) Component::Update( );
	}
}

// Code example
class AttackingState: public State
{
public:
	AttackingState( std::shared_ptr< StateMachine > owner )
	: State( owner ) { }
	virtual void Enter( void ) { }
	virtual void Exit( void ) { }
	virtual void Update( void )
	{
		owner->SwitchState( std::make_shared< IdleState > ( owner ) );
	}
}
class IddleState: public State
{
public:
	IddleState( std::shared_ptr< StateMachine > owner )
	: State( owner ) { }
	virtual void Enter( void ) { }
	virtual void Exit( void ) { }
	virtual void Update( void )
	{
		owner->SwitchState( std::make_shared< AttackingState > ( owner ) );
	}
}