#include <GL/glut.h>
#include <cmath>

// ویژگی‌های دایره
float circleX = 50;         // موقعیت افقی اولیه (بالا سمت چپ)
float circleY = 450;        // موقعیت عمودی اولیه
float shoa_dayere = 30;    // شعاع دایره

// ویژگی‌های حرکت
float jazebe = -0.12;       // گرانش
float sorat_Y = 5.0;        // سرعت عمودی اولیه
float sorat_X = 2.0;        // سرعت افقی
float kahesh_energy = 0.8;  // ضریب کاهش انرژی

bool stopped = false;       // متغیری برای نشان دادن آیا حرکت افقی متوقف شده است یا خیر

// تابع نقاشی دایره
void drawCircle() {
    glColor3f(0.72963, 0.67859, 0.197357); // رنگ سفید
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float radian = i * 3.14159265358979323846 / 180.0;
        glVertex2f(circleX + shoa_dayere * cos(radian), circleY + shoa_dayere * sin(radian));
    }
    glEnd();
}

// تابع نمایش
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
    glutSwapBuffers();
}

// تابع بروزرسانی و حرکت دایره
void update(int value) {
    // اگر حرکت افقی متوقف نشده باشد
    if (!stopped) {
        sorat_Y += jazebe;       // افزایش سرعت عمودی به عنوان اثر گرانش
        circleY += sorat_Y;      // حرکت عمودی دایره
        circleX += sorat_X;     // حرکت افقی دایره
    }
    // اگر دایره به زمین برخورد کرد
    if (circleY - shoa_dayere < 0) {
        sorat_Y = -sorat_Y * kahesh_energy;  // برگشت به بالا با کاهش انرژی
        sorat_X *= kahesh_energy;      // کاهش سرعت افقی

        if ((sorat_Y) <0.1) {     // اگر ارتفاع حرکت عمودی به حدی پایین رسید که می‌خواهید متوقف شود
            stopped = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(8.5, update, 0);
}

// تابع تنظیم مقادیر به حالت اولیه
void reset() {
    circleX = 50;
    circleY = 450;
    sorat_Y = 5.0;
    sorat_X = 2.0;
    stopped = false;
}

// تابع کیبرد برای پاسخ به کلیدهای کیبورد
void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        reset();
    }
}

// تابع اصلی
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Ball");

    glOrtho(0, 1000, 0, 600, -1, 1);
    glutDisplayFunc(display);
    glutTimerFunc(1250, update, 0);
    glutKeyboardFunc(keyboard);  // افزودن تابع کیبرد به لیست توابع

    glutMainLoop();
    return 0;
}

