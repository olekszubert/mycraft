#include "Paths.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders/BasicShader.h"
#include "Camera.h"

#include <iostream>

#include "Texture/BasicTexture.h"
#include "Model.h"
#include "Mesh.h"
#include "Renderer/CubeRenderer.h"

#if 0
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
#endif

//Resolution
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//Camera Init
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Timing between current frame and last frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    //glfw: initialize and configure------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mycraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

#if 0
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
#endif

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // ---------------------------------------------------------------------------------------------









    // build and compile our shader program
    BasicShader ourShader(vertexShaderPath.c_str(), fragShaderPath.c_str());


#if 0
    Mesh CubeMesh;
    CubeMesh.vertexPositions;
    CubeMesh.textureCoords;
    CubeMesh.indices;

    Model SimpleCube;
    SimpleCube.AddData(CubeMesh);
#endif



    //Grass texture
    BasicTexture GrassTexture;
    GrassTexture.LoadFromFile(grassTexPath);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    //ourShader.use();
    //ourShader.setInt("texture1", 0);
    //ourShader.setInt("texture2", 1);

    CubeRenderer Cube;

    //Rendering loop--------------------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

#if 0
        // input
        processInput(window);
#endif 
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture1);
        GrassTexture.BindTexture();

        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.useProgram();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //ourShader.setMat4("projection", projection);
        ourShader.loadModelMatrix(projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //ourShader.setMat4("view", view);
        ourShader.loadModelMatrix(view);

        // render boxes
        //glBindVertexArray(VAO);
        //Cube.BindVAO();
        Cube.render(camera);

        // calculate the model matrix for each object and pass it to shader before drawing
         // make sure to initialize matrix to identity matrix first
        glm::mat4 model = glm::mat4(1.0f);
        float angle = 0;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //ourShader.setMat4("model", model);
        ourShader.loadModelMatrix(model);

        //Render primitives from array data(what kind of primitives to render, starting index, num of indices)
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //--------------------------------------------------------------------------------------------------------------
#if 0
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
#endif
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

#if 0

void Application::runLoop()
{
    sf::Clock dtTimer;

    while (m_context.window.isOpen() && !m_states.empty())
    {
        auto deltaTime = dtTimer.restart();
        auto& state = *m_states.back();

        state.handleInput();
        state.update(deltaTime.asSeconds());
        m_camera.update();

        state.render(m_masterRenderer);
        m_masterRenderer.finishRender(m_context.window, m_camera);

        handleEvents();
        if (m_isPopState)
        {
            m_isPopState = false;
            m_states.pop_back();
        }
    }
}
#endif



#if 0
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

#endif