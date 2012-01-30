/**
 * @file curses/Window.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::curses::Window                                                   */
/*************************************************************************/
inline Window::Window( int xpos, int ypos, int width, int height )
: mWindow( ::newwin( height, width, ypos, xpos ) )
{
}

inline Window::~Window()
{
    util::safeRelease( mWindow, ::delwin );
}

inline void Window::refresh() const
{
    ::wrefresh( mWindow );
}

inline void Window::move( int xpos, int ypos )
{
    ::wmove( mWindow, xpos, ypos );
}

inline void Window::attrOn( int attr )
{
    ::wattron( mWindow, attr );
}

inline void Window::attrOff( int attr )
{
    ::wattroff( mWindow, attr );
}

inline void Window::addStr( const char* str )
{
    ::waddstr( mWindow, str );
}

inline void Window::printw( const char* fmt, ... )
{
    // Start va_list
    va_list ap;
    va_start( ap, fmt );

    // Print the string
    vprintw( fmt, ap );

    // End va_list
    va_end( ap );
}

inline void Window::vprintw( const char* fmt, va_list ap )
{
    ::vwprintw( mWindow, fmt, ap );
}

inline void Window::clear()
{
    ::wclear( mWindow );
}
