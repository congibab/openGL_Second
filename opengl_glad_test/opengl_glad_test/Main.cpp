// Include standard headers
#include <iostream>
#include <glad/glad.h>

/* Include GLEW. Be sure to include GLAD before GLFW. The include file for GLAD contains
the correct OpenGL header includes (like GL/gl.h) so including GLAD before other header
files that require OpenGL does the trick.*/
//#include <GL/glew.h>

// Include GLFW. 윈도우와 키보드를 사용할 수 있게 하는 include
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main(void)
{
    // Initialise GLFW. glfwInit()은 초기화가 성공하면 return GLFW_TRUE,
    //실패하면 return GLFW_FALSE
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    /*
     반드시 context를 생성하기 전에 힌트를 주어야합니다.
     만약 최소 버전이 컴퓨터에 맞지 않는다면 window 생성이 실패할 수도 있습니다.
     glfwWindowHint에게 전달되는 두 인자는 우리가 configure하고 싶은 옵션에 대한 정보를 전달합니다.
     GLFW_COTEXT_VERSION_MAJOR는  glfw안에서 정의된 수 많은 enum에 대한 정보이고
    두 번째로 전달되는 int는 이 enum 중에서 어떤 것을 선택할 것인지를 나타냅니다.
    MAJOR 버전과 MINOR 버전을 3버전으로 동일하게 적용하는 것은 우리가 사용하고자하는 OpenGL의
    작은 subset에 접근할 수 있도록합니다. 1~3버전 전체에 접근할 수 있는 것보다 조금 더 가볍게 사용할 수 있겠네요.
    */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 을 쓸 겁니다
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS 가 기분 좋아짐; 꼭 필요한 부분은 아님
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //옛날 OpenGL은 원하지 않아요

    /*
    윈도우와 OpenGL의 context는 위의 함수를 호출하는 것으로 생성됩니다.
    이 함수를 통해서 window와 context object는 생성되고 결합됩니다.
    그리고 이들을 다루는 handle을 return 합니다.
    */
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "GLFW 윈도우를 여는데 실패했습니다. Intel GPU 를 사용한다면, 3.3 지원을 하지 않습니다. 2.1 버전용 튜토리얼을 시도하세요.\n");
        glfwTerminate();
        return -1;
    }
    /*
    openGL API를  사용하기 전에, 우리는 반드시 현재 openGL의 context를 가져와야합니다.
    window와 openGL context의 묶음에 대한 handle을 전달하는 것으로 현재의 context를 가져올 수 있습니다.
    이렇게 가져온 context는 새로 context를 만들고 그것을 현재의 것으로 가져오거나,
    현재의 context를 가지고 있는 window가 파괴되었을 때를 제외하고는 항상 유지가 됩니다.
    */
    glfwMakeContextCurrent(window);

    //glad 초기화
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //window안에서 실제로 그림이 그려질 영역을 설정.
    //좌하단의 x,y좌표와 우상단의 x,y좌표를 의미함
    glViewport(0, 0, 800, 600);

    //배경색을 어떤 색으로 할지 결정한다.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //화면의 색을 loop에 따라 변하게 하는데 사용
    float colorIndex = 0.1;

    /*
    각각의 window들은 flag를 가지고 있습니다. flag는 window가 닫혀져야하는지를 판단하는데 사용됩니다.
    사용자가 window를 닫으려고 할 때, window의 우상단에 있는 닫기 버튼을 누르던가 ALT+F4와 같은 키 조합을 사용하거나할 때, 이 flag는 1이 됩니다.
    주의할 점은 flag가 1이 되었다고 해서, window가 정말로 닫힌것은 아니라는 점입니다.
    위 코드에서 glfwWindowShouldClose함수에 window를 전달하고, 이 window의 flag가 1이라면 닫혀야하는 상황임을 의미합니다.
    따라서 !이 붙어있므르로 {...}안에는 window가 살아있을 때 실행되는 코드를 작성하면 됩니다.
    위 함수는 윈도우가 닫혀야하는 상황인지 판단하는 것이 목적이라면,
    'glfwSetWindowCloseCallback'은 사용자가 윈도우를 닫으려고 하는 행위를 catch하는 것이 목적이라고 할 수 있습니다.
    */
    while (!glfwWindowShouldClose(window))
    {
        //사용자의 입력을 받는다. 아래에 함수 정의 있음
        processInput(window);

        // rendering commands here
        glClearColor(0.2f + colorIndex, 0.3f + colorIndex, 0.3f + colorIndex, 1.0f + colorIndex);
        colorIndex += 0.0001;
        //배경색을 적용한다.
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        event Polling은 이전에 받았던 이벤트들을 프로세싱하고 즉시 return합니다.
        이 방식은 계속해서 rendering 하는 방식에 있어서 최고의 선택입니다.
        반면에 만약 당신이 새로운 입력을 받자마자 rendering을 새로 업데이트 해야한다면
        'glfwWaitEvents();'가 최고의 선택입니다. 이것은 이벤트를 한 번 받을 때까지만 기다리고,
        thread를 나머지 시간동안 잠 자도록합니다. 그리고 받은 모든 이벤트들을 프로세싱합니다.
        */
        glfwPollEvents();

        /*
        glfw window는 기본적으로 double buffering을 사용한다고 합니다.
        이것은 각각의 window마다 두 개의 rendering buffer가 있는 것을 의미합니다.
        a front buffer, a back buffer라고 부릅니다.
        front buffer는 사용자에게 보이고 있는 것이고, back buffer는 우리가 rendering하고 있는 buffer입니다.
        만약 전체 frame이 다 rendering이 되면 두 개의 버퍼는 swap되어야 한다고 합니다.
        이전에 만들어진 것을 지우고, 새로 만들어진 것을 보여줘야지 에니메이션이 되는 것을 말하나 봅니다.
        그래서 back buffer가 front buffer가 되고, vice versa도 이루어 진다고 합니다.
        두 개의 buffer가 swap되는 시간 간격은 얼마나 많은 프레임들이 swap되기 전까지 기다리고 있는지를 나타냅니다.
        그리고 이 간격을 'vsync'라고 부른다고 합니다.
        기본적으로 vsync는 0입니다. 이것은 swap이 즉시 일어나는 것을 의미합니다. 만약 컴퓨터가 빠르다면,
        프래임들이 너무 빠르게 흘러가서 몇몇 프래임들은 눈에 보이지도 않을 것입니다.
        1초에 60-75번까지 swap이 일어날 수 있으니까요. 이것은 CPU, GPU모두에게 낭비입니다.
        우리의 눈은 이 프래임들을 다 보지 못하니까요.
        그래서 'glfwSwapInterval(1);'를 호출해서 적절하게 vsync를 조절합니다.
        */
        glfwSwapBuffers(window);
    }


    // Close OpenGL window and terminate GLFW.
    // glfw를 사용한 다음에 종료를 꼭 해주기. 
    // glfw 내부에서 생성된 자원들을 delete 해줌.
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