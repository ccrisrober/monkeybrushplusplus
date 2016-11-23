
#define MOUSE_LEFTBUTTON 0
#define MOUSE_CENTERBUTTON 1
#define MOUSE_RIGHTBUTTON 2 

enum class MouseButton
{
	Left,
	Middle,
	Right
};

class IMouse 
{
	virtual ~IMouse() {}
	virtual int mouseX() = 0;
	virtual int mouseY() = 0;
    virtual int previousMouseX() = 0;
    virtual int previousMouseY() = 0;
    virtual int mouseWheelX() = 0;
    virtual int mouseWheelY() = 0;
    virtual int deltaX(int val) = 0;
    virtual int deltaY(int val) = 0;
    virtual bool buttonRelease(MouseButton button) = 0;
    virtual bool buttonPress(MouseButton button) = 0;
    virtual bool singleButtonPress(MouseButton button) = 0;
    virtual void update() = 0;
};

class SDLMouse: public IMouse
{
	SDLMouse()
        : _x(0), _y(0), _prevX(0), _prevY(0), _wheelx(0), _wheely(0),
          _prevWheelX(0), _prevWheelY(0)
    {
        m_current[MOUSE_LEFTBUTTON].state = SDL_RELEASED;
        m_current[MOUSE_CENTERBUTTON].state = SDL_RELEASED;
        m_current[MOUSE_RIGHTBUTTON].state = SDL_RELEASED;

        m_previous[MOUSE_LEFTBUTTON].state = SDL_RELEASED;
        m_previous[MOUSE_CENTERBUTTON].state = SDL_RELEASED;
        m_previous[MOUSE_RIGHTBUTTON].state = SDL_RELEASED;
    }

    int mouseX()
    {
        return _x;
    }

    int mouseY()
    {
        return _y;
    }

    int previousMouseX()
    {
        return _prevX;
    }

    int previousMouseY()
    {
        return _prevY;
    }

    int mouseWheelX()
    {
        return _wheelx;
    }

    int mouseWheelY()
    {
        return _wheely;
    }

    int deltaX(int val)
    {
        if (_x != _prevX)
        {
            return _x - val;
        }
        else
        {
            return 0;
        }
    }

    int deltaY(int val)
    {
        if (_y != _prevY)
        {
            return _y - val;
        }
        else
        {
            return 0;
        }
    }

    bool buttonPress(MouseButton button)
    {
        switch (button)
        {
	        case MouseButton::Left:
	            return m_current[MOUSE_LEFTBUTTON].state == SDL_PRESSED;
	        case MouseButton::Middle:
	            return m_current[MOUSE_CENTERBUTTON].state == SDL_PRESSED;
	        case MouseButton::Right:
	            return m_current[MOUSE_RIGHTBUTTON].state == SDL_PRESSED;
	        default:
	            return false;
        }
    }

    bool buttonRelease(MouseButton button)
    {
        switch (button)
        {
	        case MouseButton::Left:
	            return m_current[MOUSE_LEFTBUTTON].state == SDL_RELEASED && m_previous[MOUSE_LEFTBUTTON].state == SDL_PRESSED;
	        case MouseButton::Middle:
	            return m_current[MOUSE_CENTERBUTTON].state == SDL_RELEASED && m_previous[MOUSE_CENTERBUTTON].state == SDL_PRESSED;
	        case MouseButton::Right:
	            return m_current[MOUSE_RIGHTBUTTON].state == SDL_RELEASED && m_previous[MOUSE_RIGHTBUTTON].state == SDL_PRESSED;
	        default:
	            return false;
        }
    }

    bool singleButtonPress(MouseButton button)
    {
        switch (button)
        {
	        case MouseButton::Left:
	            return m_current[MOUSE_LEFTBUTTON].state == SDL_PRESSED && m_previous[MOUSE_LEFTBUTTON].state == SDL_RELEASED;
	        case MouseButton::Middle:
	            return m_current[MOUSE_CENTERBUTTON].state == SDL_PRESSED && m_previous[MOUSE_CENTERBUTTON].state == SDL_RELEASED;
	        case MouseButton::Right:
	            return m_current[MOUSE_RIGHTBUTTON].state == SDL_PRESSED && m_previous[MOUSE_RIGHTBUTTON].state == SDL_RELEASED;
	        default:
	            return false;
        }
    }

    void update()
    {
        _prevWheelX = _wheelx;
        _prevWheelY = _wheely;
        _prevX = _x;
        _prevY = _y;
        _wheely = 0;
        memcpy(m_previous, m_current, sizeof(m_current));
    }

    void onMouseMove(int x, int y)
    {
        _x = x;
        _y = y;
    }

    void onMouseButtonEvent(SDL_MouseButtonEvent e)
    {
        switch (e.button)
        {
            case SDL_BUTTON_LEFT:
            {
                m_current[MOUSE_LEFTBUTTON].state = e.state;
                m_current[MOUSE_LEFTBUTTON].clicks = e.clicks;
            } break;

            case SDL_BUTTON_MIDDLE:
            {
                m_current[MOUSE_CENTERBUTTON].state = e.state;
                m_current[MOUSE_CENTERBUTTON].clicks = e.state;
            } break;

            case SDL_BUTTON_RIGHT:
            {
                m_current[MOUSE_RIGHTBUTTON].state = e.state;
                m_current[MOUSE_RIGHTBUTTON].clicks = e.clicks;
            } break;
        }
    }

    void onMouseWheelEvent(SDL_MouseWheelEvent e)
    {
        _wheelx = e.x;
        _wheely = e.y;
    }
}

class GLFWMouse: public IMouse
{
public:
	GLFWMouse()
        : _x(0), _y(0), _prevX(0), _prevY(0), _wheelX(0), _wheelY(0),
          _prevWheelX(0), _prevWheelY(0)
    {
        _current[MOUSE_LEFTBUTTON].state = GLFW_RELEASE;
        _current[MOUSE_CENTERBUTTON].state = GLFW_RELEASE;
        _current[MOUSE_RIGHTBUTTON].state = GLFW_RELEASE;

        _previous[MOUSE_LEFTBUTTON].state = GLFW_RELEASE;
        _previous[MOUSE_CENTERBUTTON].state = GLFW_RELEASE;
        _previous[MOUSE_RIGHTBUTTON].state = GLFW_RELEASE;
    }
	virtual ~GLFWMouse() {}
	virtual int mouseX()
	{
		return _x;
	}
	virtual int mouseY()
	{
		return _y;
	}
    virtual int previousMouseX()
    {
		return _prevX;
    }
    virtual int previousMouseY()
    {
		return _prevY;
    }
    virtual int mouseWheelX()
    {
		return _wheelX;
    }
    virtual int mouseWheelY()
    {
		return _wheelY;
    }
    virtual int deltaX(int val)
    {
        if (_x != _prevX)
        {
            return _x - val;
        }
        else
        {
            return 0;
        }
    }
    virtual int deltaY(int val)
    {
        if (_y != _prevY)
        {
            return _y - val;
        }
        else
        {
            return 0;
        }
    }
    virtual bool buttonRelease(MouseButton button)
    {
        switch (button)
        {
	        case MouseButton::Left:
	            return m_current[MOUSE_LEFTBUTTON].state == GLFW_RELEASE && m_previous[MOUSE_LEFTBUTTON].state == GLFW_PRESS;
	        case MouseButton::Middle:
	            return m_current[MOUSE_CENTERBUTTON].state == GLFW_RELEASE && m_previous[MOUSE_CENTERBUTTON].state == GLFW_PRESS;
	        case MouseButton::Right:
	            return m_current[MOUSE_RIGHTBUTTON].state == GLFW_RELEASE && m_previous[MOUSE_RIGHTBUTTON].state == GLFW_PRESS;
	        default:
	            return false;
        }
    }
    virtual bool buttonPress(MouseButton button)
    {
        switch (button)
        {
	        case MouseButton::Left:
	            return m_current[MOUSE_LEFTBUTTON].state == GLFW_PRESS;
	        case MouseButton::Middle:
	            return m_current[MOUSE_CENTERBUTTON].state == GLFW_PRESS;
	        case MouseButton::Right:
	            return m_current[MOUSE_RIGHTBUTTON].state == GLFW_PRESS;
	        default:
	            return false;
        }
    }
    virtual bool singleButtonPress(MouseButton button)
    {
        switch (button)
        {
	        case MouseButton::Left:
	            return m_current[MOUSE_LEFTBUTTON].state == GLFW_PRESS && m_previous[MOUSE_LEFTBUTTON].state == GLFW_RELEASE;
	        case MouseButton::Middle:
	            return m_current[MOUSE_CENTERBUTTON].state == GLFW_PRESS && m_previous[MOUSE_CENTERBUTTON].state == GLFW_RELEASE;
	        case MouseButton::Right:
	            return m_current[MOUSE_RIGHTBUTTON].state == GLFW_PRESS && m_previous[MOUSE_RIGHTBUTTON].state == GLFW_RELEASE;
	        default:
	            return false;
        }
    }
    virtual void update()
    {
        _prevWheelX = _wheelX;
        _prevWheelY = _wheelY;
        _prevX = _x;
        _prevY = _y;
        _wheelY = 0;
        memcpy(_previous, _current, sizeof(_current));
    }

    void onMouseMove(int x, int y)
    {
        _x = x;
        _y = y;
    }

    void onMouseButtonEvent(int e, int action)
    {
        switch (e)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
            {
                _current[MOUSE_LEFTBUTTON].state = static_cast<uint8_t>(action);
                _current[MOUSE_LEFTBUTTON].clicks = 1;
            } break;

            case GLFW_MOUSE_BUTTON_MIDDLE:
            {
                _current[MOUSE_CENTERBUTTON].state = static_cast<uint8_t>(action);
                _current[MOUSE_CENTERBUTTON].clicks = 1;
            } break;

            case GLFW_MOUSE_BUTTON_RIGHT:
            {
                _current[MOUSE_RIGHTBUTTON].state = static_cast<uint8_t>(action);
                _current[MOUSE_RIGHTBUTTON].clicks = 1;
            } break;
        }
    }

    void onMouseWheelEvent(int xoffset, int yoffset)
    {
        _wheelX = xoffset;
        _wheelY = yoffset;
    }
protected:
    int _x;
    int _y;
    int _prevX;
    int _prevY;
    int _wheelX;
    int _wheelY;
    int _prevWheelX;
    int _prevWheelY;
    GLFWMouseState _current[3];
    GLFWMouseState _previous[3];
};