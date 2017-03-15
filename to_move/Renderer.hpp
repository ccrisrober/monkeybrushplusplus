class Renderer
{
protected:
	Renderer( void );
public:
	virtual void setViewport( const Rect& viewport) {}
	virtual void beginRender( void )
	{
		static const Rect viewport;
		setViewport( viewport );
	}
	virtual void render( RenderQueue* renderQueue, RenderPass* renderPass )
	{
		renderPass->render( this, renderQueue, renderQueue->getCamera( ) );
	}
	virtual void endRender( void );
}

class RendererQueue
{
	struct Renderable
	{
		Geometry* geometry;
		Material* material;
		mb::Mat4 transform;
		double distFromCamera;
	}

	enum RenderableType
	{
		OPAQUE,
		TRANSPARENT
	}

public:
	RenderQueue( void );
	{
    	setTimestamp( ( unsigned long ) 
    		std::chrono::duration_cast< std::chrono::milliseconds >( 
    			std::chrono::system_clock::now().time_since_epoch() )
    				.count() );
	}
	~RenderQueue( void )
	{
		reset( );
	}
public:
	void reset( void )
	{
		setCamera( nullptr );
		_lights.clear( );
		for ( auto &it: _renderables ) 
		{
			it.second.clear( );
		}
		_renderables.clear( );
	}
	void setCamera( CameraPtr c )
	{
		if ( c->get( ) != nullptr )
		{
			_camera = c;
			_viewMatrix = _camera->getViewMatrix( );
			_projectionMatrix = _camera->getProjectionMatrix( );
			return;
		}
		throw;
	}
	Camera* getCamera( void ) {
		 return _camera;
	}

	const mb::Mat4& getViewMatrix( void ) const { return _viewMatrix; }
	const mb::Mat4& getProjectionMatrix( void ) const { return _projectionMatrix; }
	void push( Geometry* g )
	{
		auto rs = geometry->getComponent< MeshRenderer > ( );
		if ( rs == nullptr )
		{
			return;
		}
		auto material = rs->getMaterial( );
		auto renderableType = RenderQueue::RenderableType::OPAQUE;

		auto renderable = RenderQuee::Renderable {
			g,
			material,
			g->getWorld( ).computeModelMatrix( ),
			0.0f // TODO
		}
		auto queue = &_renderables[ renderableType ];

		if ( renderableType == RenderQueue::RenderableType::TRANSPARENT )
		{
			// BACK TO FRONT
			// TODO: Order for camera distance
		} else 
		{
			// FRONT TO BACK
			queue->insert( renderable );
		}
	}
	void push( LightPtr l )
	{
		_lights.push_back( l );
	}
public:
    unsigned long getTimestamp( void ) const { return _timestamp; }
    void setTimestamp( unsigned long value ) { _timestamp = value; }
protected:
    std::chrono::microseconds::rep _timestamp;

private:
	Camera* _camera;
	mb::Mat4 _viewMatrix;
	mb::Mat4 _projectionMatrix;

	std::vector< LightPtr > _lights;
	std::map< RenderableType, Renderables > _renderables;
}

class RenderPass
{
public:
	RenderPass( void );
	virtual ~RenderPass( void );

	virtual void render( Renderer* renderer, RenderQueue* renderQueue, Camera* camera) {};
}

class StandardRenderPass: public RenderPass
{
public:
	StandardRenderPass( void );
	virtual ~StandardRenderPass( void );

	virtual void render( Renderer* renderer, RenderQueue* queue, Camera* camera ) override
	{
		renderOpaqueObjects( renderer, queue, camera );
		renderTransparentObjects( renderer, queue, camera );
	}

protected:
	virtual void renderOpaqueObjects( Renderer* renderer, RenderQueue* queue, Camera* camera )
	{
		auto renderables = renderQueue->getRenderables( RenderQueue::RenderableType::OPAQUE );
		it ( renderables.empty( ) )
		{
			return;
		}
		queue->each( renderables, [ this, renderer, queue ] (RendererQueue::Renderable *r )
		{
			auto material = r->material;
			auto program = r->getProgram( );

			auto proj = r->getProjectionMatrix( );
			auto view = r->getViewMatrix( );
		});
	}
	virtual void renderTransparentObjects( Renderer* renderer, RenderQueue* queue, Camera* camera )
	{
		
	}
}