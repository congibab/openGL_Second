// Include standard headers
#include <iostream>
#include <glad/glad.h>

/* Include GLEW. Be sure to include GLAD before GLFW. The include file for GLAD contains
the correct OpenGL header includes (like GL/gl.h) so including GLAD before other header
files that require OpenGL does the trick.*/
//#include <GL/glew.h>

// Include GLFW. ������� Ű���带 ����� �� �ְ� �ϴ� include
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main(void)
{
    // Initialise GLFW. glfwInit()�� �ʱ�ȭ�� �����ϸ� return GLFW_TRUE,
    //�����ϸ� return GLFW_FALSE
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    /*
     �ݵ�� context�� �����ϱ� ���� ��Ʈ�� �־���մϴ�.
     ���� �ּ� ������ ��ǻ�Ϳ� ���� �ʴ´ٸ� window ������ ������ ���� �ֽ��ϴ�.
     glfwWindowHint���� ���޵Ǵ� �� ���ڴ� �츮�� configure�ϰ� ���� �ɼǿ� ���� ������ �����մϴ�.
     GLFW_COTEXT_VERSION_MAJOR��  glfw�ȿ��� ���ǵ� �� ���� enum�� ���� �����̰�
    �� ��°�� ���޵Ǵ� int�� �� enum �߿��� � ���� ������ �������� ��Ÿ���ϴ�.
    MAJOR ������ MINOR ������ 3�������� �����ϰ� �����ϴ� ���� �츮�� ����ϰ����ϴ� OpenGL��
    ���� subset�� ������ �� �ֵ����մϴ�. 1~3���� ��ü�� ������ �� �ִ� �ͺ��� ���� �� ������ ����� �� �ְڳ׿�.
    */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 �� �� �̴ϴ�
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS �� ��� ������; �� �ʿ��� �κ��� �ƴ�
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //���� OpenGL�� ������ �ʾƿ�

    /*
    ������� OpenGL�� context�� ���� �Լ��� ȣ���ϴ� ������ �����˴ϴ�.
    �� �Լ��� ���ؼ� window�� context object�� �����ǰ� ���յ˴ϴ�.
    �׸��� �̵��� �ٷ�� handle�� return �մϴ�.
    */
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "GLFW �����츦 ���µ� �����߽��ϴ�. Intel GPU �� ����Ѵٸ�, 3.3 ������ ���� �ʽ��ϴ�. 2.1 ������ Ʃ�丮���� �õ��ϼ���.\n");
        glfwTerminate();
        return -1;
    }
    /*
    openGL API��  ����ϱ� ����, �츮�� �ݵ�� ���� openGL�� context�� �����;��մϴ�.
    window�� openGL context�� ������ ���� handle�� �����ϴ� ������ ������ context�� ������ �� �ֽ��ϴ�.
    �̷��� ������ context�� ���� context�� ����� �װ��� ������ ������ �������ų�,
    ������ context�� ������ �ִ� window�� �ı��Ǿ��� ���� �����ϰ�� �׻� ������ �˴ϴ�.
    */
    glfwMakeContextCurrent(window);

    //glad �ʱ�ȭ
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //window�ȿ��� ������ �׸��� �׷��� ������ ����.
    //���ϴ��� x,y��ǥ�� ������ x,y��ǥ�� �ǹ���
    glViewport(0, 0, 800, 600);

    //������ � ������ ���� �����Ѵ�.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //ȭ���� ���� loop�� ���� ���ϰ� �ϴµ� ���
    float colorIndex = 0.1;

    /*
    ������ window���� flag�� ������ �ֽ��ϴ�. flag�� window�� ���������ϴ����� �Ǵ��ϴµ� ���˴ϴ�.
    ����ڰ� window�� �������� �� ��, window�� ���ܿ� �ִ� �ݱ� ��ư�� �������� ALT+F4�� ���� Ű ������ ����ϰų��� ��, �� flag�� 1�� �˴ϴ�.
    ������ ���� flag�� 1�� �Ǿ��ٰ� �ؼ�, window�� ������ �������� �ƴ϶�� ���Դϴ�.
    �� �ڵ忡�� glfwWindowShouldClose�Լ��� window�� �����ϰ�, �� window�� flag�� 1�̶�� �������ϴ� ��Ȳ���� �ǹ��մϴ�.
    ���� !�� �پ��ֹǸ��� {...}�ȿ��� window�� ������� �� ����Ǵ� �ڵ带 �ۼ��ϸ� �˴ϴ�.
    �� �Լ��� �����찡 �������ϴ� ��Ȳ���� �Ǵ��ϴ� ���� �����̶��,
    'glfwSetWindowCloseCallback'�� ����ڰ� �����츦 �������� �ϴ� ������ catch�ϴ� ���� �����̶�� �� �� �ֽ��ϴ�.
    */
    while (!glfwWindowShouldClose(window))
    {
        //������� �Է��� �޴´�. �Ʒ��� �Լ� ���� ����
        processInput(window);

        // rendering commands here
        glClearColor(0.2f + colorIndex, 0.3f + colorIndex, 0.3f + colorIndex, 1.0f + colorIndex);
        colorIndex += 0.0001;
        //������ �����Ѵ�.
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        event Polling�� ������ �޾Ҵ� �̺�Ʈ���� ���μ����ϰ� ��� return�մϴ�.
        �� ����� ����ؼ� rendering �ϴ� ��Ŀ� �־ �ְ��� �����Դϴ�.
        �ݸ鿡 ���� ����� ���ο� �Է��� ���ڸ��� rendering�� ���� ������Ʈ �ؾ��Ѵٸ�
        'glfwWaitEvents();'�� �ְ��� �����Դϴ�. �̰��� �̺�Ʈ�� �� �� ���� �������� ��ٸ���,
        thread�� ������ �ð����� �� �ڵ����մϴ�. �׸��� ���� ��� �̺�Ʈ���� ���μ����մϴ�.
        */
        glfwPollEvents();

        /*
        glfw window�� �⺻������ double buffering�� ����Ѵٰ� �մϴ�.
        �̰��� ������ window���� �� ���� rendering buffer�� �ִ� ���� �ǹ��մϴ�.
        a front buffer, a back buffer��� �θ��ϴ�.
        front buffer�� ����ڿ��� ���̰� �ִ� ���̰�, back buffer�� �츮�� rendering�ϰ� �ִ� buffer�Դϴ�.
        ���� ��ü frame�� �� rendering�� �Ǹ� �� ���� ���۴� swap�Ǿ�� �Ѵٰ� �մϴ�.
        ������ ������� ���� �����, ���� ������� ���� ��������� ���ϸ��̼��� �Ǵ� ���� ���ϳ� ���ϴ�.
        �׷��� back buffer�� front buffer�� �ǰ�, vice versa�� �̷�� ���ٰ� �մϴ�.
        �� ���� buffer�� swap�Ǵ� �ð� ������ �󸶳� ���� �����ӵ��� swap�Ǳ� ������ ��ٸ��� �ִ����� ��Ÿ���ϴ�.
        �׸��� �� ������ 'vsync'��� �θ��ٰ� �մϴ�.
        �⺻������ vsync�� 0�Դϴ�. �̰��� swap�� ��� �Ͼ�� ���� �ǹ��մϴ�. ���� ��ǻ�Ͱ� �����ٸ�,
        �����ӵ��� �ʹ� ������ �귯���� ��� �����ӵ��� ���� �������� ���� ���Դϴ�.
        1�ʿ� 60-75������ swap�� �Ͼ �� �����ϱ��. �̰��� CPU, GPU��ο��� �����Դϴ�.
        �츮�� ���� �� �����ӵ��� �� ���� ���ϴϱ��.
        �׷��� 'glfwSwapInterval(1);'�� ȣ���ؼ� �����ϰ� vsync�� �����մϴ�.
        */
        glfwSwapBuffers(window);
    }


    // Close OpenGL window and terminate GLFW.
    // glfw�� ����� ������ ���Ḧ �� ���ֱ�. 
    // glfw ���ο��� ������ �ڿ����� delete ����.
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}