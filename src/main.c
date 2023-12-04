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

float camera_speed = 0.1f;
float camera_rot_speed = 0.02f;
float cube_rot_speed = 0.5f;

vec3 camera_pos = { 0.f, 0.f, 10.f };
vec3 camera_front = { 0.f, 0.f, -1.f };
vec3 camera_up = { 0.f, 1.f, 0.f };

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // position movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_muladds(camera_front, camera_speed, camera_pos);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_muladds(camera_front, -camera_speed, camera_pos);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 temp;
        glm_vec3_cross(camera_front, camera_up, temp);
        glm_vec3_normalize(temp);
        glm_vec3_muladds(temp, -camera_speed, camera_pos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 temp;
        glm_vec3_cross(camera_front, camera_up, temp);
        glm_vec3_normalize(temp);
        glm_vec3_muladds(temp, camera_speed, camera_pos);
    }

    // rotation
    // yaw
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        versor rotation_quaternion;
        glm_quatv(rotation_quaternion, camera_rot_speed, camera_up);
        glm_quat_rotatev(rotation_quaternion, camera_front, camera_front);
    } 
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        versor rotation_quaternion;
        glm_quatv(rotation_quaternion, -camera_rot_speed, camera_up);
        glm_quat_rotatev(rotation_quaternion, camera_front, camera_front);
    }

    // roll
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        versor rotation_quaternion;
        glm_quatv(rotation_quaternion, camera_rot_speed, camera_front);
        glm_quat_rotatev(rotation_quaternion, camera_up, camera_up);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        versor rotation_quaternion;
        glm_quatv(rotation_quaternion, -camera_rot_speed, camera_front);
        glm_quat_rotatev(rotation_quaternion, camera_up, camera_up);
    }

    // pitch
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        vec3 camera_right;
        glm_vec3_cross(camera_front, camera_up, camera_right);
        versor rotation_quaternion;
        glm_quatv(rotation_quaternion, camera_rot_speed, camera_right);
        glm_quat_rotatev(rotation_quaternion, camera_front, camera_front);
        glm_quat_rotatev(rotation_quaternion, camera_up, camera_up);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        vec3 camera_right;
        glm_vec3_cross(camera_front, camera_up, camera_right);
        versor rotation_quaternion;
        glm_quatv(rotation_quaternion, -camera_rot_speed, camera_right);
        glm_quat_rotatev(rotation_quaternion, camera_front, camera_front);
        glm_quat_rotatev(rotation_quaternion, camera_up, camera_up);
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
    glm_look(camera_pos, camera_front, camera_up, view);

    mat4 model = GLM_MAT4_IDENTITY_INIT;

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
        glm_look(camera_pos, camera_front, camera_up, view);


        // cube rotation
        //glm_rotate(model, glm_rad(cube_rot_speed), (vec3){0.f, 1.f, 0.f});
        //glm_rotate(model, glm_rad(cube_rot_speed), (vec3){1.f, 0.f, 0.f});

        glm_mat4_mul(projection, view, mvp);
        glm_mat4_mul(mvp, model, mvp);

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
