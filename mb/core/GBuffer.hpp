class GBuffer
{
public:
  enum class TextureType
  {
    Position = 0, Normal, Diffuse, TexCoord
  };
private:
  Framebuffer* _fbo;
  Texture2D* _textures[4];  // TODO Move to std::array
  DepthTexture *_depthTex;
  unsigned int _width, _height;

public:
  GBuffer(unsigned int width, unsigned int height);
  ~GBuffer();

  void bind( unsigned int mode )
  {
    bindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    bindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
  }
  //void setReadBuffer();

  inline unsigned int width( ) const { return _width; }
  inline unsigned int height( ) const { return _height; }

  inline unsigned int texture( unsigned int index ) { return _textures[index]; }

private:
  void init( );
  {
    others -> GL_RGBA, GL_RGBA, GL_UNSIGNED BYTE
    depth -> GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT
  }
};
