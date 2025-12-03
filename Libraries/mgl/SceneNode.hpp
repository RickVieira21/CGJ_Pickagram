#pragma once
#include "../mgl/mgl.hpp"
#include <vector>
#include <glm/gtc/type_ptr.hpp>

class SceneNode {
public:
    mgl::Mesh* mesh = nullptr;
    mgl::ShaderProgram* shader = nullptr;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::vec3 color = glm::vec3(1.0f); // base color for this node
    std::vector<SceneNode*> children;

    SceneNode() = default;
    ~SceneNode() {
        for (auto child : children) delete child;
    }

    void addChild(SceneNode* child) { children.push_back(child); }

    void draw(const glm::mat4& parentMatrix) {
        glm::mat4 globalMatrix = parentMatrix * modelMatrix;
        if (mesh && shader) {
            shader->bind();
            // Model matrix (use convention constant)
            GLint modelId = shader->Uniforms[mgl::MODEL_MATRIX].index;
            if (modelId >= 0) {
                glUniformMatrix4fv(modelId, 1, GL_FALSE, glm::value_ptr(globalMatrix));
            }
            // baseColor uniform (optional)
            auto it = shader->Uniforms.find("baseColor");
            if (it != shader->Uniforms.end()) {
                GLint colorId = it->second.index;
                if (colorId >= 0) glUniform3fv(colorId, 1, glm::value_ptr(color));
            }
            mesh->draw();
            shader->unbind();
        }
        for (auto child : children) {
            child->draw(globalMatrix);
        }
    }
};
