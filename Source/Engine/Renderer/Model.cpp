#include "Model.h"
#include "Renderer.h"

namespace viper
{
	/// <summary>
	/// Draws the model by rendering lines between its points using the specified renderer.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	void Model::Draw(Renderer& renderer, const vec2& postion, float rotation, float scale)
	{
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);
		// iterate through the points and draw lines between them
		for (int i = 0; i < m_points.size() - 1; ++i)
		{
			vec2 p1 = (m_points[i].Rotate(rotation) * scale) + postion;
			vec2 p2 = (m_points[i + 1].Rotate(rotation) * scale) + postion;
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	/// <summary>
	/// Draws the model by rendering lines between its points using the specified renderer and transform.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	/// <param name="transform">The Transform object specifying position, rotation, and scale to apply to the model's points.</param>
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);
		// iterate through the points and draw lines between them
		for (int i = 0; i < m_points.size() - 1; ++i)
		{
			vec2 p1 = (m_points[i].Rotate(transform.rotation) * transform.scale) + transform.position;
			vec2 p2 = (m_points[i + 1].Rotate(transform.rotation) * transform.scale) + transform.position;
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}
