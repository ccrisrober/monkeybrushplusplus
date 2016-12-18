#include "Framebuffer2.hpp"

mb::Framebuffer2::Framebuffer2( )
{
  glGenFramebuffers( 1, &handle );
}

mb::Framebuffer2::~Framebuffer2( )
{
  glDeleteFramebuffers( 1, &handle );
}

void mb::Framebuffer2::attachDepth( mb::TexturePtr t )
{
  glBindFramebuffer( GL_FRAMEBUFFER, handle );
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, t->handler( ), 0 );
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void mb::Framebuffer2::attachStencil( mb::TexturePtr t )
{
  glBindFramebuffer( GL_FRAMEBUFFER, handle );
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, t->handler( ), 0 );
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void mb::Framebuffer2::attachDepthStencil( mb::TexturePtr t )
{
  glBindFramebuffer( GL_FRAMEBUFFER, handle );
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, t->handler( ), 0 );
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void mb::Framebuffer2::attachColor( mb::TexturePtr t, int i )
{
  glBindFramebuffer( GL_FRAMEBUFFER, handle );
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, t->handler( ), 0 );
  if ( find( color_attachments.begin( ), color_attachments.end( ),
    GL_COLOR_ATTACHMENT0 + i ) == color_attachments.end( ) )
  {
    color_attachments.push_back( GL_COLOR_ATTACHMENT0 + i );
  }
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void mb::Framebuffer2::use( )
{
  glBindFramebuffer( GL_FRAMEBUFFER, handle );
  glDrawBuffers( color_attachments.size( ), color_attachments.data( ) );
}

void mb::Framebuffer2::unuse( )
{
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}
