module;
#include <GLFW/glfw3.h>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include "vulkan/vulkan_core.h"
export module lys.vulkan.vk_renderer;

export import lys.rendering.renderer;
import vulkan_hpp;

// Enable Vulkan debugging while in Debug mode
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

namespace Lys
{
	export class VkRenderer final : public IRenderer
	{
		vk::Instance m_instance{};

	public:
		VkRenderer() = default;

		void init() override
		{
			create_vulkan_instance();
		}

		void begin_frame() override
		{
		}

		void draw() override
		{
		}

		void end_frame() override
		{
		}

		void update_viewport(int width, int height) override
		{
		}

		void shutdown() override
		{
		}

		void set_polygon_mode(PolygonMode mode) override
		{

		}

	private:
		void create_vulkan_instance()
		{
			// -- Vulkan Application Info --
			vk::ApplicationInfo appInfo{};
			appInfo.sType = vk::StructureType::eApplicationInfo;
			appInfo.pApplicationName = "Vulkan WIP";
			appInfo.applicationVersion = vk::makeApiVersion(1, 0, 0, 0);
			appInfo.pEngineName = "Lys Engine";
			appInfo.engineVersion = vk::makeApiVersion(1, 0, 0, 0);
			appInfo.apiVersion = vk::makeApiVersion(1, 0, 0, 0);

			std::vector<const char*> requiredExtensions = get_required_extensions();

			// Vulkan Instance Create Info
			vk::InstanceCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eInstanceCreateInfo;
			createInfo.pNext = nullptr;

#ifdef __APPLE__
			// Required on macOS
			createInfo.flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
#endif
			createInfo.pApplicationInfo = &appInfo;

			createInfo.enabledExtensionCount = static_cast<std::uint32_t>(requiredExtensions.size());
			createInfo.ppEnabledExtensionNames = requiredExtensions.data();

			createInfo.enabledLayerCount = 0;
			createInfo.ppEnabledLayerNames = nullptr;

			// Create the Vulkan Instance
			vk::Result result = vk::createInstance(&createInfo, nullptr, &m_instance);
			if (result != vk::Result::eSuccess)
			{
				throw std::runtime_error("Failed to create Vulkan instance!");
			}
		}

		/**
		 * @brief Get the required extensions object
		 *
		 * @throws std::runtime_error Failed to get required GLFW extensions.
		 *
		 * @return std::vector<const char*>
		 */
		static std::vector<const char*> get_required_extensions()
		{
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions,
												glfwExtensions + glfwExtensionCount);

			// Failed to get required extensions, stop
			if (!glfwExtensions)
			{
				throw std::runtime_error("Failed to get GLFW required instance extensions");
			}

			// Enable debugging if building in Debug mode
			if (enableValidationLayers)
			{
				extensions.push_back(vk::EXTDebugUtilsExtensionName);
			}

			// Since Vulkan 1.3 this is needed for Apple devices
#ifdef __APPLE__
			extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

			return extensions;
		}
	};
} // namespace Lys
