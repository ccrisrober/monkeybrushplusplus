namespace MB
{
	struct WindowParams
	{
		std::string title;
		int x;
		int y;
		int width;
		int height;
		bool displayFPS;
		bool displayMouse;
		bool debugWindowEvents;

		WindowParams()
		{
			this->x = 0;
			this->y = 0;
			this->title = "MB++";
			this->displayFPS = true;
			this->displayMouse = true;
			this->debugWindowEvents = true;
		}
	};
	class IWindow
	{
	public:
		virtual ~IWindow()
		{
		}
		virtual bool initialize() = 0;
		virtual void* nativeWindowHandle() = 0;
		virtual void* nativeDisplayHandle() = 0;
		virtual bool isRunning() = 0;
		virtual void pollEvents() = 0;
		virtual void close() = 0;
		virtual void swapBuffers() = 0;

	protected:
		void *_nativeWindowHandle;
		void *_nativeDisplayHandle;
		WindowParams _params;
	};

	class SDLContext: public IWindow
	{
	public:
		SDLContext(const WindowParams& params)
		: GLContext()
		{
			_handle = nullptr;
			_nativeWindowHandle = nullptr;
            _nativeDisplayHandle = nullptr;

            _params = params;
		}

		virtual ~SDLContext()
		{
			SDL_Quit();
		}

		bool initialize() override
		{
			if (SDL_Init(SDL_INIT_TIMER) != 0)
			{
				return false;
			}

			_handle = SDL_CreateWindow(_params.title.c_str(),
                _params.x <= 0 ? SDL_WINDOWPOS_CENTERED : _params.x,
                _params.y <= 0 ? SDL_WINDOWPOS_CENTERED : _params.y,
                _params.width,
                _params.height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

			if (!_handle)
			{
				SDL_Quit();
				return false;
			}

			#ifdef WIN32
	            SDL_SysWMinfo info;
	            SDL_VERSION(&info.version);
	            if (SDL_GetWindowWMInfo(_handle, &info))
	            {
	                _nativeWindowHandle = info.info.win.window;
	                _nativeDisplayHandle = nullptr;
            }
			#else
	            SDL_SysWMinfo info;
	            SDL_VERSION(&info.version);
	            if (SDL_GetWindowWMInfo(_handle, &info))
	            {
	                _nativeWindowHandle = (void*)info.info.x11.window;
	                _nativeDisplayHandle = info.info.x11.display;
	            }
			#endif
            _running = true;

            return true;
		}
		void* nativeWindowHandle() override
		{
			return _nativeWindowHandle;
		}
		void* nativeDisplayHandle() override
		{
			return _nativeDisplayHandle;
		}
		bool isRunning() override
		{
            return _running;
		}
		void pollEvents() override
		{
			SDL_Event ev;
			while(SDL_PollEvent(&ev))
			{
				switch(ev.type)
				{
					case SDL_QUIT:
						close();
						break;
					case SDL_KEYDOWN:
						break;
					// ...
				}
			}

			// std::string title = _params.title 
		}
		void close() override
		{
			_running = false;
			SDL_Quit();
		}
		void swapBuffers() override
		{

		}
	protected:
		SDL_Window* _handle;
	};

	class GLFWContext: public IWindow
	{
	public:
		GLFWContext(const WindowParams& params)
		: GLContext()
		{
			_handle = nullptr;
			_nativeWindowHandle = nullptr;
            _nativeDisplayHandle = nullptr;

            _params = params;
		}
		virtual ~GLFWContext()
		{
            glfwTerminate();
		}
		bool initialize() override
		{
			if (!glfwInit())
			{
                return false;
            }
            _handle = glfwCreateWindow(_params.width, _params.height, _params.title.c_str(),
            	nullptr, nullptr);

        	#ifdef WIN32
            	_nativeWindowHandle = glfwGetWin32Window(_handle);
            	_nativeDisplayHandle = nullptr;
        	#else

            	_nativeDisplayHandle = glfwGetX11Display();
            	_nativeWindowHandle = (void*)glfwGetX11Window(_handle);
        	#endif

        	if (!_handle)
        	{
        		glfwTerminate();
        		return false;
        	}

        	return true;
		}
		void* nativeWindowHandle() override
		{
            return _nativeWindowHandle;
		}
		void* nativeDisplayHandle() override
		{
            return _nativeDisplayHandle;
		}
		bool isRunning() override
		{
			return glfwWindowShouldClose(_handle) == 0;
		}
		void pollEvents() override
		{
			glfwPollEvents();
		}
		void close() override
		{
			glfwTerminate();
		}
		void swapBuffers() override
		{
			glfwSwapBuffers();
		}
	protected:
		GLFWwindow* _handle;
		void* _nativeWindowHandle;
		void *_nativeDisplayHandle;
	};
}