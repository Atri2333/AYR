#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"Core.h"
#include"Mesh.h"
#include"vector.h"
namespace AYR
{
    inline float Clamp(float min, float max, float value)
    {
        if (value > max)
            value = max;
        if (value < min)
            value = min;
        return value;
    }

    AYR_API inline void ReadObj(const std::string& path, Mesh& mesh)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v")  // 顶点位置
            {
                float x, y, z;
                iss >> x >> y >> z;
                mesh.vertices.push_back(Vector3f(x, y, z));
            }
            else if (prefix == "vn")  // 顶点法线
            {
                float x, y, z;
                iss >> x >> y >> z;
                mesh.normals.push_back(Vector3f(x, y, z));
            }
            else if (prefix == "vt")  // 纹理坐标
            {
                float u, v;
                iss >> u >> v;
                mesh.uvs.push_back(Vector2f(u, v));
            }
            else if (prefix == "f")  // 面
            {
                std::string vert;
                std::vector<Vector3i> faceIndices;  // 临时存储一个面的所有顶点索引

                while(iss >> vert)
                {
                    std::istringstream viss(vert);
                    std::string indexStr;
                    int vi = 0, ti = -1, ni = -1;  // 使用-1表示未指定的索引

                    // 读取顶点索引
                    std::getline(viss, indexStr, '/');
                    if(!indexStr.empty())
                        vi = std::stoi(indexStr) - 1;

                    // 读取纹理坐标索引
                    if(std::getline(viss, indexStr, '/'))
                    {
                        if(!indexStr.empty())
                            ti = std::stoi(indexStr) - 1;
                    }

                    // 读取法线索引
                    if(std::getline(viss, indexStr, '/'))
                    {
                        if(!indexStr.empty())
                            ni = std::stoi(indexStr) - 1;
                    }

                    // 验证索引有效性
                    if(vi < 0 || vi >= mesh.vertices.size())
                        continue;  // 或抛出异常
                    if(ti >= 0 && ti >= mesh.uvs.size())
                        continue;
                    if(ni >= 0 && ni >= mesh.normals.size())
                        continue;

                    faceIndices.push_back(Vector3i(vi, ti, ni));
                }

                // 如果面包含至少3个顶点
                if(faceIndices.size() >= 3)
                {
                    // 将多边形面转换为三角形（三角形扇形）
                    for(size_t i = 2; i < faceIndices.size(); i++)
                    {
                        // 添加三角形：v0-vi-1-vi
                        mesh.indexes.push_back(faceIndices[0]);      // 第一个顶点
                        mesh.indexes.push_back(faceIndices[i-1]);    // 前一个顶点
                        mesh.indexes.push_back(faceIndices[i]);      // 当前顶点
                    }
                }
            }
        }
    }
}