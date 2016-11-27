#include "Texture.hpp"

namespace mb
{
    Texture::Texture( const TexOptions& options, unsigned int type )
    : _handler( -1 )
    {
        this->_target = type;
        this->_level = options.level;
        this->_border = options.border;
        this->_internalFormat = options.internalFormat;
        this->_format = options.format;
        this->_type = options.type;

        this->_wrapS = options.wrapS;
        this->_wrapT = options.wrapT;
        this->_wrapR = options.wrapR;

        this->_minFilter = options.minFilter;
        this->_magFilter = options.magFilter;
    }
    Texture::~Texture( )
    {
        glDeleteTextures( 1, &this->_handler );
        this->_handler = -1;
    }
    void Texture::bind( int slot )
    {
        this->load( );
        if ( slot >= 0 )
        {
            glActiveTexture( GL_TEXTURE0 + slot );
        }
        glBindTexture( this->_target, this->_handler );
    }
    void Texture::unbind( )
    {
        glBindTexture( this->_target, -1 );
    }
}
