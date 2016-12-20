namespace mb
{
  template <typename T>
  T* Node::componentInParent( )
  {
    auto parent = this->parent( );
    return parent->getComponent<T>( );
  }
  /*template <typename T>
  std::vector<T*> Node::componentsInParent( )
  {

  }
  template <typename T>
  T* Node::componentInChildren( )
  {

  }
  template <typename T>
  std::vector<T*> Node::componentsInChildren( )
  {

  }*/

  template <typename T>
  void Node::toggleComponent( )
  {
    for ( auto comp : _components )
    {
      if ( typeid( *comp.get( ) ) == typeid( T ) )
      {
        comp.get( )->toggle( );
      }
    }
  }
  template <typename T>
  void Node::enableComponent( )
  {
    for ( auto comp : _components )
    {
      if ( typeid( *comp.get( ) ) == typeid( T ) )
      {
        comp.get( )->enable( );
      }
    }
  }
  template <class T>
  void Node::disableComponent( )
  {
    for ( auto comp : _components )
    {
      if ( typeid( *comp.get( ) ) == typeid( T ) )
      {
        comp.get( )->disable( );
      }
    }
  }
  template <class T>
  bool Node::hasComponent( ) const
  {
    for ( auto comp : _components )
    {
      if ( typeid( *comp.get( ) ) == typeid( T ) )
      {
        return true;
      }
    }
    return false;
  }
  template<class T>
  T * Node::getComponent( )
  {
    {
      for ( auto comp : _components )
      {
        // std::cout << typeid(*comp).name() << std::endl;
        // std::cout << typeid(T).name() << std::endl;
        if ( typeid( *comp.get( ) ) == typeid( T ) )
        {
          return static_cast<T*>( comp.get( ) );
        }
      }
      return nullptr;
    }
  }
  /*template<typename C, typename .. T>
  inline std::shared_ptr<C> Node::addComp( T ..t )
  {
    auto res = std::make_shared<C>( this, t... );
    mComponents.push_back( res );

    return res;
  }

  template<typename C>
  inline std::shared_ptr<C> Node::comp( )
  {
    for ( auto c : mComponents )
    {
      auto comp = std::dynamic_pointer_cast< C >( c );
      if ( comp )
      {
        return comp;
      }
    }
    return nullptr;
  }*/
}
