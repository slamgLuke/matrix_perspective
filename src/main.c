#include "initWindow.h"
#include "shaderLoader.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>


#define SHADER_PATH "shaders/"
#define VERT_SHADER SHADER_PATH "vert.glsl"
#define FRAG_SHADER SHADER_PATH "frag.glsl"

#define WIDTH 600
#define HEIGHT 400


int auto_rotate = 0;

float speed = 0.1f;
float rot_speed = 0.5f;

float x_pos = 0.f;
float y_pos = 0.f;
float z_pos = 0.f;

float x_rot = 0.f;
float y_rot = 0.f;
float z_rot = 0.f;


void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // position movement
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        y_pos = speed;
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        y_pos = -speed;
    else y_pos = 0.f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        x_pos = -speed;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        x_pos = speed;
    else x_pos = 0.f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        z_pos = -speed;
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        z_pos = speed;
    else z_pos = 0.f;

    // rotation movement
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        x_rot = -rot_speed;
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        x_rot = rot_speed;
    else x_rot = 0.f;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        y_rot = -rot_speed;
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        y_rot = rot_speed;
    else y_rot = 0.f;

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        z_rot = rot_speed;
    else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        z_rot = -rot_speed;
    else z_rot = 0.f;

    // auto rotation
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        auto_rotate = !auto_rotate;

    if (auto_rotate) {
        x_rot = rot_speed;
        y_rot = rot_speed;
        z_rot = rot_speed;
    }
}

void draw_vao(GLuint vao)
{
    glBindVertexArray(vao);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}


int main()
{
    glewExperimental = 1;
    GLFWwindow* window = initWindow(WIDTH, HEIGHT, "Matrix test");
    if (window == NULL) return 1;
    printf("OpenGL: version supported by this platform (%s): \n", glGetString(GL_VERSION));

    static const GLfloat vertexData[] = {
        // 8 cube coords    // colors
        -1.f, -1.f, -1.f,   1.f, 0.f, 0.f,
        1.f, -1.f, -1.f,   1.f, 0.f, 0.f,
        1.f,  1.f, -1.f,   1.f, 0.f, 0.f,
        -1.f,  1.f, -1.f,   1.f, 0.f, 0.f,

        -1.f, -1.f,  1.f,   0.f, 1.f, 0.f,
        1.f, -1.f,  1.f,   0.f, 1.f, 0.f,
        1.f,  1.f,  1.f,   0.f, 1.f, 0.f,
        -1.f,  1.f,  1.f,   0.f, 1.f, 0.f,

        -1.f, -1.f, -1.f,   0.f, 0.f, 1.f,
        1.f, -1.f, -1.f,   0.f, 0.f, 1.f,
        1.f, -1.f,  1.f,   0.f, 0.f, 1.f,
        -1.f, -1.f,  1.f,   0.f, 0.f, 1.f,

        -1.f,  1.f, -1.f,   1.f, 1.f, 0.f,
        1.f,  1.f, -1.f,   1.f, 1.f, 0.f,
        1.f,  1.f,  1.f,   1.f, 1.f, 0.f,
        -1.f,  1.f,  1.f,   1.f, 1.f, 0.f,

        1.f, -1.f, -1.f,   1.f, 0.f, 1.f,
        1.f,  1.f, -1.f,   1.f, 0.f, 1.f,
        1.f,  1.f,  1.f,   1.f, 0.f, 1.f,
        1.f, -1.f,  1.f,   1.f, 0.f, 1.f,

        -1.f, -1.f, -1.f,   0.f, 1.f, 1.f,
        -1.f,  1.f, -1.f,   0.f, 1.f, 1.f,
        -1.f,  1.f,  1.f,   0.f, 1.f, 1.f,
        -1.f, -1.f,  1.f,   0.f, 1.f, 1.f
    };

    static const GLuint indices[] = {
        0, 1, 2, 2, 3, 0, // front
        4, 5, 6, 6, 7, 4, // back
        8, 9, 10, 10, 11, 8, // top
        12, 13, 14, 14, 15, 12, // bottom
        16, 17, 18, 18, 19, 16, // right
        20, 21, 22, 22, 23, 20 // left
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    GLuint programID = LoadShaders(VERT_SHADER, FRAG_SHADER);


    float fov = glm_rad(45.f);
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float near = 0.1f;
    float far = 100.f;



    mat4 projection;
    glm_perspective(fov, aspect_ratio, near, far, projection);
    mat4 view;
    glm_lookat((vec3){0.f, 0.f, 3.f}, (vec3){0.f, 0.f, 0.f}, (vec3){0.f, 1.f, 0.f}, view);
    glm_translate(view, (vec3){0.f, 0.f, -5.f});

    mat4 mvp;
    glm_mat4_mul(projection, view, mvp);

    GLint mvp_location = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);



    glEnable(GL_DEPTH_TEST);

    // Main loop
    do {
        process_input(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        

        glUseProgram(programID);


        // move camera
        glm_translate(view, (vec3){-x_pos, -y_pos, -z_pos});

        // rotate camera
        glm_rotate(view, glm_rad(x_rot), (vec3){1.f, 0.f, 0.f});
        glm_rotate(view, glm_rad(y_rot), (vec3){0.f, 1.f, 0.f});
        glm_rotate(view, glm_rad(z_rot), (vec3){0.f, 0.f, 1.f});

        glm_mat4_mul(projection, view, mvp);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);


        draw_vao(vao);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwWindowShouldClose(window) == GLFW_FALSE);
    

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(programID);


    glfwTerminate();
    return 0;
}
