#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "frafment") << std::endl;
        std::cout <<message<< std::endl;
    
    

    
    }

    return id;

}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;

}
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        printf("Error\n");


    float positions[6]{
    -0.5f, -0.5f,//第一个vertex positions在屏幕上的Xpositions以及Ypositions坐标
    0.0f, 0.5f,
    0.5f, -0.5f,
    };//这里相当于有3个vertexs positions 
    
    unsigned int buffer;
    glGenBuffers(1, &buffer);//定义顶点缓冲区 参数1是你要定义多少个顶点缓冲区 参数2是生成的缓冲区的ID
    glBindBuffer(GL_ARRAY_BUFFER, buffer);//我生成了一个buffer 但是我要怎么使用他
    //GL_ARRAY_BUFFER只是一个数组 之后传入缓冲区的ID这就是我要绑定的缓冲区当然他就是刚刚生成的那个

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);//向缓冲区传入数据 STATIC代表不会每帧都渲染 
    //DYNAMIC  每帧渲染   这里只是给缓冲区传入了数据还没有告诉GPU该怎样使用

    glEnableVertexAttribArray(0);//传入一个index来启用这个布局
   //指定属性 这里只有position一个属性所以我们只调用这个函数一次
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);//相当于告诉GPU我们的顶点布局layout是怎么样的之后用shader来读取顶点数据
    //第一个参数为index索引0 因为他是第一个属性
    //第二个参数 代表他有多少个浮点数 
    //第三个参数 代表他的参数类型为浮点型
    //第四个参数 代表是否要将他标准化不需要就是 GL_FALSE 因为已经是浮点型了在我们的空间中
    //第五个参数 stride你需要移动到第二个顶点的长度
    //第六个参数 偏移量

   // glBindBuffer(GL_ARRAY_BUFFER, 0);


    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "gl_Position =position;\n"
        "}\n";

    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "color =vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
        glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);//第一个参数绘制什么东西  第二参数选择从哪个顶点（从0开始）开始绘制 第三个是count为要呈现的索引数量
        //每个顶点是两个浮点数这里是三个顶点所以传入三
        

        //glBegin(GL_TRIANGLES);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f(0.0f, 0.5f);
        //glVertex2f(0.5f, -0.5f);
        //glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}