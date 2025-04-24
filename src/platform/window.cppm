module;
export module window;

import rendering;

#ifdef USE_VULKAN
import :vk_window;
export using Window = Lys::VkWindow;
#else
import :gl_window;
export using Window = Lys::GLWindow;
#endif
