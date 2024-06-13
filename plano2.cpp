#include <GL/glut.h>
#include <iostream>
#include <sstream>

// Tamaño de la ventana
const int windowWidth = 800;
const int windowHeight = 600;

// Variables globales para las coordenadas
float x1, b1;
float x2, y2;
float m;  // Pendiente
float b;  // Intercepto

// Función para inicializar OpenGL
void initializeOpenGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Color de fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Coordenadas del plano cartesiano
}

// Función para dibujar el plano cartesiano
void drawCartesianPlane() {
    glColor3f(0.0, 0.0, 0.0); // Color negro

    glBegin(GL_LINES);

    // Eje X
    glVertex2f(-10.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);

    // Eje Y
    glVertex2f(0.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);

    glEnd();
}

// Función para dibujar la recta basada en dos puntos
void drawLine() {
    glColor3f(1.0, 0.0, 0.0); // Color rojo

    glBegin(GL_LINES);
    glVertex2f(x1, b1);
    glVertex2f(x2, y2);
    glEnd();
}

// Función para dibujar texto en la pantalla
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        ++text;
    }
}

// Función de visualización
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCartesianPlane();
    drawLine();

    // Crear la ecuación de la recta como texto
    std::ostringstream equation;
    equation << " Ecuacion de la recta y = " << m << "x + " << b;
    std::string equationStr = equation.str();
    const char* text = equationStr.c_str();

    // Dibujar la ecuación de la recta en la pantalla
    glColor3f(0.0, 0.0, 0.0); // Color negro para el texto
    drawText(text, -9.5, 9.0);

    // Dibujar la ecuación de y en la pantalla
    std::ostringstream equationY;
    equationY << "Pendiente de la recta = " << m;
    std::string equationYStr = equationY.str();
    const char* textY = equationYStr.c_str();
    drawText(textY, -9.5, 8.0);

    glFlush();
}

// Función principal
int main(int argc, char** argv) {
    // Pedir coordenadas al usuario
    std::cout << "Ingrese la primera coordenada (x1 b1): ";
    std::cin >> x1 >> b1;

    std::cout << "Ingrese la segunda coordenada (x2 y2): ";
    std::cin >> x2 >> y2;

    // Calcular la pendiente y el intercepto de la recta
    if (x2 - x1 != 0) {
        m = (y2 - b1) / (x2 - x1);
        b = b1 - m * x1;
        std::cout << "La pendiente de la recta es: " << m << std::endl;
        std::cout << "El intercepto en y es: " << b << std::endl;
    }
    else {
        std::cout << "La recta es vertical, la pendiente es indefinida." << std::endl;
        m = NAN;
        b = NAN;
    }

    // Inicializar GLUT y crear ventana
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Plano Cartesiano");

    initializeOpenGL();
    // Registrar función de visualización
    glutDisplayFunc(display);

    // Iniciar el bucle principal de GLUT
    glutMainLoop();

    return 0;
}