module;
export module renderer;

namespace Lys
{
    export class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void init() = 0;
        virtual void begin_frame() = 0;
        virtual void draw() = 0;
        virtual void end_frame() = 0;
        virtual void resize(int width, int height) = 0;
        virtual void shutdown() = 0;
    };
}