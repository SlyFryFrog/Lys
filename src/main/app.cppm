module;
export module app;

import rendering;
import window;

namespace Lys 
{
    export class App
    {
    public:
        virtual void _init()
        {
            Window::_init();
        }

        virtual void _destroy()
        {

        }

        virtual void _process()
        {

        }
    };
}