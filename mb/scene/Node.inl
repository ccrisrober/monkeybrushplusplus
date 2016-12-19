namespace mb
{
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
