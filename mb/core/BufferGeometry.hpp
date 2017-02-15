class BufferGeometry
{
public:
  std::vector< unsigned int >& index( ) const
  {
    return _index;
  }
  void index( const std::vector<unsigned int>& index )
  {
    _index = index;
  }
  void addAttribute( const std::string& name, BufferAttribute* attr )
  {

  }
  BufferAttribute* attribute( const std::string& name )
  {

  }
  BufferAttribute* removeAttribute( const std::string& name )
  {

  }
protected:
  std::vector< BufferAttribute* > _attributes;
}
