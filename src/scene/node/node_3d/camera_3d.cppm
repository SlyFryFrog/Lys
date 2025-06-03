module;
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
export module lys.scene.camera_3d;

import lys.scene.node_3d;

namespace Lys
{
	export class Camera3D final : Node3D
	{
		glm::mat4 m_modelMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		glm::vec3 m_position;
		glm::vec3 m_right;	 // Right component <- X
		glm::vec3 m_up;		 // Up component <- Y
		glm::vec3 m_forward; // Forward component <- -Z

		float m_fov;		 // vertical field of view (radians or degrees)
		float m_aspectRatio; // width / height
		float m_nearPlane;	 // near clipping plane
		float m_farPlane;	 // far clipping plane

		float m_yaw;   // horizontal rotation (left/right)
		float m_pitch; // vertical rotation (up/down)

	public:
		Camera3D() = default;
		~Camera3D() override = default;

		void _process(double delta) override
		{
			m_viewMatrix = look_at(m_position, m_forward, m_up);
		}

		void set_position_to_origin()
		{
			m_position = rotate_to_align() * translate_to_origin() * glm::vec4(m_position, 1.0f);
		}

		[[nodiscard]] glm::mat4 get_view_matrix() const
		{
			return m_viewMatrix;
		}

		[[nodiscard]] glm::mat4 get_projection_matrix() const
		{
			return m_projectionMatrix;
		}

		[[nodiscard]] glm::mat4 get_model_matrix() const
		{
			return m_modelMatrix;
		}

		[[nodiscard]] glm::mat4 get_view_projection_matrix() const
		{
			return m_viewMatrix * m_projectionMatrix;
		}

		[[nodiscard]] glm::vec3 get_position() const
		{
			return m_position;
		}

		void set_position(const glm::vec3& position)
		{
			m_position = position;
		}

	private:
		[[nodiscard]] glm::mat4 rotate_to_align() const
		{
			// clang-format off
			return glm::mat4{
				glm::vec4(m_right,    0.0f),
				glm::vec4(m_up,       0.0f),
				glm::vec4(-m_forward, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
			};
			// clang-format on
		}

		[[nodiscard]] glm::mat4 translate_to_origin()
		{
			m_position = glm::vec3(0.0f, 0.0f, 0.0f);

			// clang-format off
    		return {
				1.0f, 0.0f, 0.0f, -m_position.x,
    			0.0f, 1.0f, 0.0f, -m_position.y,
    			0.0f, 0.0f, 1.0f, -m_position.z,
    			0.0f, 0.0f, 0.0f, 1.0f
    		};
			// clang-format on
		}

		/**
		 * @brief Constructs a view matrix that transforms world coordinates to camera space.
		 *
		 * @param position The position of the camera in world space.
		 * @param target   The point the camera is looking at.
		 * @param up       The up direction vector (usually {0, 1, 0}).
		 * @return glm::mat4 The resulting view matrix.
		 *
		 * @note Uses column-major order.
		 */
		static glm::mat4 look_at(const glm::vec3 position, const glm::vec3 target,
								 const glm::vec3 up)
		{
			const glm::vec3 n = glm::normalize(position - target);
			const glm::vec3 u = glm::normalize(glm::cross(up, n));
			const glm::vec3 v = glm::cross(n, u);

			// clang-format off
			return {
				glm::vec4(u, 0.0f),
				glm::vec4(v, 0.0f),
				glm::vec4(n, 0.0f),
				glm::vec4(-glm::dot(u, position), -glm::dot(v, position), -glm::dot(n, position), 1.0f)
			};
			// clang-format on
		}
	};
} // namespace Lys
