module;
export module lys.platform.window;

#ifdef USE_VULKAN
import lys.platform.vk_window;
export using Window = Lys::VkWindow;
#else
import lys.platform.gl_window;
export using Window = Lys::GLWindow;
#endif
