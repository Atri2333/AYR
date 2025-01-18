#include"gl.h"
#include"Core.h"
#include"utils.h"
#include<cmath>
#include<vector>
namespace AYR
{
    //TODO(1/16): adjust the view port
    Renderer::Renderer(int width, int height) : width(width), height(height)
    {
        model = Matrix4x4::get_model_matrix(0);
        view = Matrix4x4::get_view_matrix(eye_pos, LookAt, Up);
        projection = Matrix4x4::get_projection_matrix(45.0, 1, -0.1, -50);

        lights.clear();

        for(int i = 0; i < width * height; ++i)
        {
            frame_buffer.push_back(Vector3f(0, 0, 0));
            z_buffer.push_back(std::numeric_limits<float>::lowest());
        }
    }

    void Renderer::setEyePos(const Vector3f& eye_pos)
    {
        this->eye_pos = eye_pos;
        view = Matrix4x4::get_view_matrix(eye_pos, LookAt, Up);
    }

    void Renderer::setLookAt(const Vector3f& look_at)
    {
        this->LookAt = look_at;
        view = Matrix4x4::get_view_matrix(eye_pos, LookAt, Up);
    }

    void Renderer::setUp(const Vector3f& up)
    {
        this->Up = up;
        view = Matrix4x4::get_view_matrix(eye_pos, LookAt, Up);
    }

    void Renderer::addLight(const light& light)
    {
        this->lights.push_back(light);
    }

    void Renderer::clearLight()
    {
        this->lights.clear();
    }

    void Renderer::drawLine(const Vector2i& p1, const Vector2i& p2, const Vector3f& col, img *image)
    {
        int x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;
        const bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);
        if (steep)
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const int dx = x2 - x1;
        const int dy = std::abs(y2 - y1);


        int error = dx;
        const int ystep = (y1 < y2) ? 1 : -1;
        int y = y1;


        for (int x = x1; x <= x2; x++) {
            if (steep) {
                image->setBuf(y, x, col);
            } else {
                image->setBuf(x, y, col);
            }

            error -= dy * 2;
            if (error < 0) {
                y += ystep;
                error += dx * 2;
            }
        }
    }

    // TODO(1/16): implement shader
    void Renderer::drawTriangle(const Triangle &tri, const std::vector<Vector3f>& view_poses, const Color& col, Shader* shader)
    {
        const Vector3f light_dir = Vector3f(0, 0, 1);

        Vector3f p1 = tri.v[0];
        Vector3f p2 = tri.v[1];
        Vector3f p3 = tri.v[2];
        Vector2i aabb_min = Vector2i(std::min(p1.x, std::min(p2.x, p3.x)), std::min(p1.y, std::min(p2.y, p3.y)));
        Vector2i aabb_max = Vector2i(std::max(p1.x, std::max(p2.x, p3.x)), std::max(p1.y, std::max(p2.y, p3.y)));

        for (int x = std::max(0, aabb_min.x); x <= std::min(width - 1, aabb_max.x); ++x)
            for (int y = std::max(0, aabb_min.y); y <= std::min(height - 1, aabb_max.y); ++y)
                {
                    Vector3f bc_coord = BaryCentric(Vector2f(x+0.5, y+0.5), Vector2f(p1), Vector2f(p2), Vector2f(p3));
                    if(bc_coord.x < 0 || bc_coord.y < 0 || bc_coord.z < 0)
                        continue;
                    float z = bc_coord.x * p1.z + bc_coord.y * p2.z + bc_coord.z * p3.z;
                    if(z > z_buffer[y * width + x])
                    {
                        z_buffer[y * width + x] = z;
                        
                        auto normal = interpolate(bc_coord.x, bc_coord.y, bc_coord.z, tri.normal[0], tri.normal[1], tri.normal[2], 1);
                        normal.normalized();
                        auto tex_coord = interpolate(bc_coord.x, bc_coord.y, bc_coord.z, tri.tex_coords[0], tri.tex_coords[1], tri.tex_coords[2], 1);
                        auto shader_coord = interpolate(bc_coord.x, bc_coord.y, bc_coord.z, view_poses[0], view_poses[1], view_poses[2], 1);

                        

                        // TextureShader shader(eye_pos, shader_coord, col, normal, tex_coord, tri.tex);
                        shader->eye_pos = eye_pos;
                        shader->view_pos = shader_coord;
                        shader->normal = normal;
                        shader->tex_coords = tex_coord;
                        shader->tex = tri.tex;
                        shader->color = col;

                        auto color = shader->shade(trans_lights);
                        frame_buffer[y * width + x] = color;
                        
                    }
                }
    }

    //TODO(1/15): this function is not complete, need to add MVP transformation
    void Renderer::draw(Mesh& mesh, Shader *shader)
    {
        const float f1 = (50 - 0.1) / 2.0;
        const float f2 = (50 + 0.1) / 2.0;
        // for(auto tri : mesh.TriangleList)
        // {
        //     AYR::Vector3f screen_cords[3];
        //     AYR::Vector3f world_cords[3];
        //     for(int i = 0; i < 3; ++i)
        //     {
        //         screen_cords[i] = AYR::Vector3f(
        //             (tri->v[i].y + 1) * image->getHeight() / 2,
        //             (tri->v[i].x + 1) * image->getWidth() / 2,
        //             tri->v[i].z
        //         );
        //         world_cords[i] = tri->v[i];
        //     }
        //     AYR::Vector3f n = AYR::crossProduct(world_cords[2] - world_cords[0], world_cords[1] - world_cords[0]);
        //     n.normalize();
        //     float intensity = AYR::dotProduct(n, light_dir);
        //     if(intensity > 0)
        //     {
        //         drawTriangle(Triangle(), Color::WHITE * intensity, image, zbuffer);
        //     }
        // }
        auto mvp = projection * view * model;
        /*Vector3f test1 = mvp * Vector4f(1, 1, 1, 1);
        std::cerr << "test1.x = " << test1.x << " test1.y = " << test1.y << " test1.z = " << test1.z << std::endl;
        Vector3f test2 = mvp * Vector4f(1, 1, -1, 1);
        std::cerr << "test2.x = " << test2.x << " test2.y = " << test2.y << " test2.z = " << test2.z << std::endl;
        Vector3f test3 = mvp * Vector4f(-1, 1, 1, 1);
        std::cerr << "test1.x = " << test3.x << " test1.y = " << test3.y << " test1.z = " << test3.z << std::endl;
        Vector3f test4 = mvp * Vector4f(-1, 1, -1, 1);
        std::cerr << "test2.x = " << test4.x << " test2.y = " << test4.y << " test2.z = " << test4.z << std::endl;*/

        trans_lights.clear();
        for (auto &l : lights)
        {
            trans_lights.push_back(light{ view * model * l.position, l.intensity });
        }
        for(auto tri : mesh.TriangleList)
        {
            Triangle new_tri = *tri;


            // vertex transformation
            new_tri.v[0] = mvp * new_tri.v[0];
            new_tri.v[1] = mvp * new_tri.v[1];
            new_tri.v[2] = mvp * new_tri.v[2];
            
            // copy from games101 hw3
            // normal transformation
            Matrix4x4 inv_trans = (view * model).inverse().transpose();
            Vector4f n[] = 
            {
                inv_trans * Vector4f(tri->normal[0], 0),
                inv_trans * Vector4f(tri->normal[1], 0),
                inv_trans * Vector4f(tri->normal[2], 0)
            };

            for(auto &vert: new_tri.v)
            {
                vert.x = 0.5 * width * (vert.x + 1);
                vert.y = 0.5 * height * (vert.y + 1);

                // Mention(1/16): minus f1?
                vert.z = f1 * vert.z + f2;
            }

            for(int i = 0; i < 3; ++i)
            {
                new_tri.setNormal(i, Vector3f(n[i].x, n[i].y, n[i].z).normalized());
            }

            new_tri.tex = mesh.tex;

            Vector3f mm1 = view * model * tri->v[0];
            Vector3f mm2 = view * model * tri->v[1];
            Vector3f mm3 = view * model * tri->v[2];

            drawTriangle(new_tri, {Vector3f(mm1.x, mm1.y, mm1.z), Vector3f(mm2.x, mm2.y, mm2.z), Vector3f(mm3.x, mm3.y, mm3.z)}, Color::WHITE, shader);
        }
    }

    void Renderer::toImage(img* image)
    {
        for(int i = 0; i < height; ++i)
            for(int j = 0; j < width; ++j)
                image->setBuf(i, j, frame_buffer[i * width + j]);
        image->flipVertical();
    }
}

