#include "Shader.h"
#include "utils.h"
#include<cmath>
namespace AYR
{
    // Blinn-Phong Shading
	Color TextureShader::shade(std::vector<light> lights)
	{
		Color tex_color = tex->Sample(tex_coords.x, tex_coords.y);

		Vector3f color = Vector3f(tex_color.r, tex_color.g, tex_color.b);

        Vector3f ka = Vector3f(0.005, 0.005, 0.005);
        Vector3f kd = color;
        Vector3f ks = Vector3f(0.7937, 0.7937, 0.7937);

        Vector3f ambient_light = Vector3f(10, 10, 10);
        Vector3f ambient = ka * ambient_light;

        Color final_color = Color(ambient.x, ambient.y, ambient.z);

        for(auto& light : lights)
        {
            // std::cerr << "light position: " << light.position.x << " " << light.position.y << " " << light.position.z << std::endl;
            // std::cerr << "eye position: " << eye_pos.x << " " << eye_pos.y << " " << eye_pos.z << std::endl;
            Vector3f l = (light.position - view_pos).normalized();
            Vector3f v = (eye_pos - view_pos).normalized();
            Vector3f h = (l + v).normalized();

            float r2 = (light.position - view_pos).norm() * (light.position - view_pos).norm();

            Vector3f diffuse = kd * (light.intensity / r2) * std::max(0.0f, dotProduct(normal, l));

            Vector3f specular = ks * (light.intensity / r2) * std::pow(std::max(0.0f, dotProduct(normal, h)), 5);

            final_color += Color(diffuse.x, diffuse.y, diffuse.z) + Color(specular.x, specular.y, specular.z);
        }

        // Clamp the color to be between 0 and 1
        final_color.r = Clamp(0.0f, 1.0f, final_color.r);
        final_color.g = Clamp(0.0f, 1.0f, final_color.g);
        final_color.b = Clamp(0.0f, 1.0f, final_color.b);
        final_color.a = 1.0f;
        return final_color;
	}

    Color PureShader::shade(std::vector<light> lights)
    {

        Vector3f ka = Vector3f(0.005, 0.005, 0.005);
        Vector3f kd = color / 255;
        Vector3f ks = Vector3f(0.7937, 0.7937, 0.7937);

        Vector3f ambient_light = Vector3f(10, 10, 10);
        Vector3f ambient = ka * ambient_light;

        Color final_color = Color(ambient.x, ambient.y, ambient.z);

        for(auto& light : lights)
        {
            // std::cerr << "light position: " << light.position.x << " " << light.position.y << " " << light.position.z << std::endl;
            // std::cerr << "eye position: " << eye_pos.x << " " << eye_pos.y << " " << eye_pos.z << std::endl;
            Vector3f l = (light.position - view_pos).normalized();
            Vector3f v = (eye_pos - view_pos).normalized();
            Vector3f h = (l + v).normalized();

            float r2 = (light.position - view_pos).norm() * (light.position - view_pos).norm();

            Vector3f diffuse = kd * (light.intensity / r2) * std::max(0.0f, dotProduct(normal, l));

            Vector3f specular = ks * (light.intensity / r2) * std::pow(std::max(0.0f, dotProduct(normal, h)), 5);

            final_color += Color(diffuse.x, diffuse.y, diffuse.z) + Color(specular.x, specular.y, specular.z);
        }
        //std::cerr << "final_color: " << final_color.r << " " << final_color.g << " " << final_color.b << std::endl;
        // Clamp the color to be between 0 and 1
        final_color.r = Clamp(0.0f, 1.0f, final_color.r);
        final_color.g = Clamp(0.0f, 1.0f, final_color.g);
        final_color.b = Clamp(0.0f, 1.0f, final_color.b);
        final_color.a = 1.0f;
        return final_color;
    }
}