#include <GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<time.h>
#define PI 3.14f
#define w (1.5f/n)
using namespace std;

string dataStream;
int* inputSequence;
int opt2, logic, opt4, n;
char opt3;

// digital data generator
void generateRandomSequence(int* inputSequence)
{
    // TODO : ask user for no. of bits in sequence
    srand((unsigned int)time(0));

    for (int i = 0; i < n; i++)
    {
        inputSequence[i] = rand() % 2;
        dataStream.append(1, (char)(48 + inputSequence[i]));
    }
}

void generateFixedSubsequence(int* inputSequence)
{
    srand((unsigned int)time(0));
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || i == 1 || i == 6 || i == 15)
            inputSequence[i] = rand() % 2;

        else
            inputSequence[i] = rand() % 1;

        dataStream.append(1, (char)(48 + inputSequence[i]));
    }
}

string palidromeHavingMid(string str, int low, int high)
{
    while (low >= 0 && high < str.length() && (str[low] == str[high])) {
        low--;
        high++;
    }

    return str.substr(low + 1, high - low - 1);
}

// for finding the longest palindrome in given data stream
string findLongestPalindrome(string str)
{
 
    if (str.length() == 0) {
        return str;
    }

    string ans = "";
    string s;
    
    int l, length = 0;
    for (int i = 0; i < str.length(); i++)
    {
        // for odd palindrome
        s = palidromeHavingMid(str, i, i);
        l = s.length();

        if (l > length)
        {
            length = l;
            ans = s;
        }

        // for even palindrome
        s = palidromeHavingMid(str, i, i + 1);
        l = s.length();

        if (l > length)
        {
            length = l;
            ans = s;
        }
    }
    return ans;
}

void init() {

    // Set the current clear color to sky blue and the current drawing color to
    // white.
    glClearColor(0.1f, 0.39f, 0.88f, 1.0f);
    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // X and Y axes
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); glVertex3f(-0.8f, 0.0f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(0.8f, 0.0f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(-0.8f, 0.8f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(-0.8f, -0.8f, 0.0f);
    glEnd();

    // arrow on x axis
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1); glVertex3f(0.8f, 0.0f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(0.77f, 0.025f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(0.77f, -0.025f, 0.0f);
    glEnd();

    // arrow on +ve y axis
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1); glVertex3f(-0.8f, 0.8f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(-0.816f, 0.760f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(-0.784f, 0.760f, 0.0f);
    glEnd();

    // arrow on -ve y axis
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1); glVertex3f(-0.8f, -0.8f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(-0.816f, -0.760f, 0.0f);
    glColor3f(1, 1, 1); glVertex3f(-0.784f, -0.760f, 0.0f);
    glEnd();

    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(4, 0xAAAA);        // for drawing dashed lines
    glEnable(GL_LINE_STIPPLE);
    GLfloat a = -0.8f, b = (GLfloat)w;

    for (int i = 0; i < n; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(a+b, 0.3f, 0.0f);
        glVertex3f(a+b, -0.3f, 0.0f);
        glEnd();
        a = a + b;
    }

    glPopAttrib();
    glFlush();
}

void drawXLine(GLfloat x1, GLfloat x2, GLfloat y, GLfloat sign)
{
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); glVertex3f(x1, (sign) * y, 0);
    glColor3f(1, 1, 1); glVertex3f(x2, (sign) * y, 0);
    glEnd();
    glFlush();
}

void drawYLine(GLfloat x, GLfloat y1=0.2, GLfloat y2=-0.2)
{
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); glVertex3f(x, y1, 0);
    glColor3f(1, 1, 1); glVertex3f(x, y2, 0);
    glEnd();
    glFlush();
}

void NRZ_L(int* inputSeqeuence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w, sign = -1;

    if (logic == 1)
        sign = 1;

    else
        sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSeqeuence[i];
        if (prevBit == -1 && currBit == 1)
            drawXLine(x, x + y, 0.2f, sign*1);

        else if (prevBit == -1 && currBit == 0)
            drawXLine(x, x + y, 0.2f, sign*(-1));

        else if (prevBit == 0 && currBit == 0)
            drawXLine(x, x + y, 0.2f, sign*(-1));

        else if (prevBit == 0 && currBit == 1)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, sign*1);
        }

        else if (prevBit == 1 && currBit == 0)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, sign*(-1));
        }

        else if (prevBit == 1 && currBit == 1)
            drawXLine(x, x + y, 0.2f, sign*1);

        prevBit = currBit;
        x = x + y;
    }
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {

    // Code modified from function drawHollowCircle 
    // obtained from https://gist.github.com/linusthe3rd/803118

    
    int triangleAmount = 100;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.1f, 0.39f, 0.88f);
    glVertex3f(x, y, 0.0f); // center of circle

    for (int i = 0; i <= triangleAmount;i++) {
        glColor3f(0.1f, 0.39f, 0.88f);
        glVertex3f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)),
            0.0f
        );
    }
    glEnd();
    glFlush();

    int lineAmount = 100;
    glLineWidth(1);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= lineAmount;i++) {
        glColor3f(0, 0, 0);
        glVertex3f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount)),
            0
        );
    }
    glEnd();
    glFlush();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {

    // Code modified from function drawFilledCircle 
    // obtained from https://gist.github.com/linusthe3rd/803118

    int triangleAmount = 100;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
    glVertex3f(x, y, 0); // center of circle

    for (int i = 0; i <= triangleAmount;i++) {
        glColor3f(0, 0, 0);
        glVertex3f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)),
            0
        );
    }
    glEnd();
    glFlush();
}

void NRZ_I(int* inputSequence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w, sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSequence[i];
        if (prevBit == -1 && logic == 1 && currBit == 1)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, -1);
            drawFilledCircle(x, -sign * 0.2f, 0.01f);
            sign = -1;
        }

        else if (prevBit == -1 && logic != 1 && currBit == 1)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, 1);
            drawFilledCircle(x, sign * 0.2f, 0.01f);
            sign = 1;
        }

        else if (prevBit == -1 && logic == 1 && currBit == 0)
        {
            drawXLine(x, x + y, 0.2f, 1);
            sign = 1;
        }

        else if (prevBit == -1 && logic != 1 && currBit == 0)
        {
            drawXLine(x, x + y, 0.2f, -1);
            sign = -1;
        }

        else if (prevBit != -1 && currBit == 0)
        {
            drawXLine(x, x + y, 0.2f, sign);
            drawHollowCircle(x, sign*0.2f, 0.01f);
        }

        else if (prevBit != -1 && currBit == 1)
        {
            drawYLine(x);
            sign = (-1) * sign;
            drawXLine(x, x + y, 0.2f, sign);
            drawFilledCircle(x, -sign*0.2f, 0.01f);
        }

        prevBit = currBit;
        x = x + y;
    }
}

void manchester(int* inputSequence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w/2, z=w, sign = -1;

    if (logic == 1)
        sign = 1;

    else
        sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSequence[i];
        if (prevBit == -1 && currBit == 1)
        {
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x+y);
            drawXLine(x+y, x+z, 0.2f, -sign);

        }

        else if (prevBit == -1 && currBit == 0)
        {
            drawXLine(x, x + y, 0.2f, -sign);
            drawYLine(x+y);
            drawXLine(x + y, x + z, 0.2f, sign);
        }

        else if (prevBit == 0 && currBit == 0)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, -sign);
            drawYLine(x+y);
            drawXLine(x + y, x + z, 0.2f, sign);
        }

        else if (prevBit == 0 && currBit == 1)
        {
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x+y);
            drawXLine(x + y, x + z, 0.2f, -sign);
        }

        else if (prevBit == 1 && currBit == 0)
        {
            drawXLine(x, x + y, 0.2f, -sign);
            drawYLine(x+y);
            drawXLine(x + y, x + z, 0.2f, sign);
        }

        else if (prevBit == 1 && currBit == 1)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x+y);
            drawXLine(x + y, x + z, 0.2f, -sign);
        }

        prevBit = currBit;
        x = x + z;
    }
}

void diffManchester(int* inputSequence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w/2, z=w, sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSequence[i];
        if (prevBit == -1 && logic == 1 && currBit == 0)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, -1);
            drawYLine(x + y);
            drawXLine(x + y, x + z, 0.2f, 1);
            drawFilledCircle(x, -sign * 0.2f, 0.01f);
            sign = 1;
        }

        else if (prevBit == -1 && logic != 1 && currBit == 0)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, 1);
            drawYLine(x + y);
            drawXLine(x + y, x + z, 0.2f, -1);
            drawFilledCircle(x, sign * 0.2f, 0.01f);
            sign = -1;
        }

        else if (prevBit == -1 && logic == 1 && currBit == 1)
        {
            drawXLine(x, x + y, 0.2f, 1);
            drawYLine(x + y);
            drawXLine(x + y, x + z, 0.2f, -1);
            sign = -1;
        }

        else if (prevBit == -1 && logic != 1 && currBit == 1)
        {
            drawXLine(x, x + y, 0.2f, -1);
            drawYLine(x + y);
            drawXLine(x + y, x + z, 0.2f, 1);
            sign = 1;
        }

        else if (prevBit != -1 && currBit == 1)
        {
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x + y);
            drawXLine(x + y, x + z, 0.2f, -sign);
            drawHollowCircle(x, sign * 0.2f, 0.01f);
            sign = -sign;
        }

        else if (prevBit != -1 && currBit == 0)
        {
            drawYLine(x);
            drawXLine(x, x + y, 0.2f, -sign);
            drawYLine(x + y);
            drawXLine(x + y, x + z, 0.2f, sign);
            drawFilledCircle(x, sign * 0.2f, 0.01f);
        }

        prevBit = currBit;
        x = x + z;
    }
}

void AMI(int* inputSequence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w, sign = -1;

    if (logic == 1)
        sign = 1;

    else
        sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSequence[i];
        if (prevBit == -1 && currBit == 1)
        {
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x + y, 0.0f, sign * 0.2f);
            sign = -sign;
        }

        else if (currBit == 0)
            drawXLine(x, x + y, 0, 1);

        else if (currBit == 1)
        {
            drawYLine(x, 0, sign * 0.2f);
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x + y, 0, sign * 0.2f);
            sign = -sign;
        }

        prevBit = currBit;
        x = x + y;
    }
}

void find8ConsecZeroes(string dataStream, vector<int>& v)
{
    int index = dataStream.find("00000000");

    while (index != -1)
    {
        v.push_back(index);
        index = dataStream.find("00000000", index + 8);
    }
}

void B8ZS(int* inputSequence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w, sign = -1;
    bool consec8zeroes = false;              // 8 consecutive zeroes are present or not

    vector<int> v;

    find8ConsecZeroes(dataStream, v);
    
    int j = 0;
    int start = v[j];

    if (v.empty())                   // if no consecutive 4 zeroes are present
    {                                // then simply do AMI
        AMI(inputSequence);
        return;
    }

    if (logic == 1)
        sign = 1;

    else
        sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSequence[i];

        if (i == start)
        {
            drawXLine(x, x + y, 0, 1);           // 0
            x = x + y;

            drawXLine(x, x + y, 0, 1);           // 0
            x = x + y;

            drawXLine(x, x + y, 0, 1);           // 0
            x = x + y;

            drawYLine(x, 0, -sign * 0.2f);       // V
            drawXLine(x, x + y, 0.2f, -sign);
            drawYLine(x + y, 0, -sign * 0.2f);
            x = x + y;

            drawYLine(x, 0, sign * 0.2f);        // B
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x + y, 0, sign * 0.2f);
            x = x + y;
            sign = -sign;

            drawXLine(x, x + y, 0, 1);           // 0
            x = x + y;

            drawYLine(x, 0, -sign * 0.2f);       // V
            drawXLine(x, x + y, 0.2f, -sign);
            drawYLine(x + y, 0, -sign * 0.2f);
            x = x + y;

            drawYLine(x, 0, sign * 0.2f);        // B
            drawXLine(x, x + y, 0.2f, sign);
            drawYLine(x + y, 0, sign * 0.2f);
            sign = -sign;

            j++;
            if (j < v.size())
                start = v[j];

            i = i + 7;
        }

        else
        {
            if (prevBit == -1 && currBit == 1)
            {
                drawXLine(x, x + y, 0.2f, sign);
                drawYLine(x + y, 0.0f, sign * 0.2f);
                sign = -sign;
            }

            else if (currBit == 0)
                drawXLine(x, x + y, 0, 1);

            else if (currBit == 1)
            {
                drawYLine(x, 0, sign * 0.2f);
                drawXLine(x, x + y, 0.2f, sign);
                drawYLine(x + y, 0, sign * 0.2f);
                sign = -sign;
            }
        }
        prevBit = currBit;
        x = x + y;
    }
}

void find4ConsecZeroes(string dataStream, vector<int> &v)
{
    int index = dataStream.find("0000");
    
    while (index != -1)
    {
        v.push_back(index);
        index = dataStream.find("0000", index + 4);
    }
}

void HDB3(int* inputSequence)
{
    int prevBit = -1, currBit = -1;
    GLfloat x = -0.8f, y = w, sign = -1;
    int count = 0;                      // no. of non-zero pulses
    vector<int> v;

    find4ConsecZeroes(dataStream, v);
    
    int j = 0;
    int start = v[j];

    if (v.empty())                    // if no consecutive 4 zeroes are present
    {                                 // then simply do AMI
        AMI(inputSequence);           
        return;
    }

    if (logic == 1)
        sign = 1;

    else
        sign = -1;

    for (int i = 0; i < n; i++)
    {
        currBit = inputSequence[i];

        if (i == start)
        {

            if (count % 2 == 0)
            {
                drawYLine(x, 0, sign * 0.2f);        // B
                drawXLine(x, x + y, 0.2f, sign);
                drawYLine(x + y, 0, sign * 0.2f);
                x = x + y;
                sign = -sign;
                ++count;

                drawXLine(x, x + y, 0, 1);           // 0
                x = x + y;

                drawXLine(x, x + y, 0, 1);           // 0
                x = x + y;

                drawYLine(x, 0, -sign * 0.2f);       // V
                drawXLine(x, x + y, 0.2f, -sign);
                drawYLine(x + y, 0, -sign * 0.2f);
                ++count;
            }

            else if (count % 2 == 1)
            {
                drawXLine(x, x + y, 0, 1);           // 0
                x = x + y;

                drawXLine(x, x + y, 0, 1);           // 0
                x = x + y;

                drawXLine(x, x + y, 0, 1);           // 0
                x = x + y;

                drawYLine(x, 0, -sign * 0.2f);       // V
                drawXLine(x, x + y, 0.2f, -sign);
                drawYLine(x + y, 0, -sign * 0.2f);
                ++count;
            }

            j++;
            if(j<v.size())
                start = v[j];

            i = i + 3;
        }

        else
        {
            if (prevBit == -1 && currBit == 1)
            {
                drawXLine(x, x + y, 0.2f, sign);
                drawYLine(x + y, 0.0f, sign * 0.2f);
                sign = -sign;
                ++count;
            }

            else if (currBit == 0)
            {
                drawXLine(x, x + y, 0, 1);
            }

            else if (currBit == 1)
            {
                drawYLine(x, 0, sign * 0.2f);
                drawXLine(x, x + y, 0.2f, sign);
                drawYLine(x + y, 0, sign * 0.2f);
                sign = -sign;
                ++count;
            }
        }
        prevBit = currBit;
        x = x + y;

    }
}

void display()
{
    init();

    if (opt3 == 'y')             // do scrambling
    {
        if (opt4 == 1)
            B8ZS(inputSequence);

        else
            HDB3(inputSequence);

        return;
    }

    switch (opt2)
    {
    case 1:
        NRZ_L(inputSequence);
        break;

    case 2:
        NRZ_I(inputSequence);
        break;

    case 3:
        manchester(inputSequence);
        break;

    case 4:
        diffManchester(inputSequence);
        break;

    case 5:
        AMI(inputSequence);
        break;

    }
}


int main(int argc, char** argv) {

    int enroll = 49 + 23;
    inputSequence = &enroll;

    int opt1;
    printf("Choose a option from the following:\n1.Completely random sequence\n2.Random sequence with fixed sub-sequences\n");
    scanf_s("%d", &opt1);
    
    printf("\nHow many bits do you want in the data stream?\n");
    scanf_s("%d", &n);

    switch (opt1)
    {
    case 1:
        generateRandomSequence(inputSequence);
        break;

    case 2:
        generateFixedSubsequence(inputSequence);
        break;

    }
   
    printf("\n\nWhich of the following line coding schemes do you want to implement?\n1.NRZ-L\n2.NRZ-I\n3.Manchester\n4.Differential Manchester\n5.AMI\n");
    scanf_s("%d", &opt2);

    printf("\nChoose a option from the following:\n1.Positive logic\n2.Negative logic\n");
    scanf_s("%d", &logic);

    if (opt2 == 5)
    {
        printf("\nDo you want to do scrambling?\n(y/n)\n");
        cin >> opt3;

        if (opt3 == 'y')
        {
            printf("\n\nWhich of the following scrambling techniques do you want to implement?\n1.B8ZS\n2.HDB3\n");
            scanf_s("%d", &opt4);
        }
    }

    string input = dataStream;

    cout << "\n\nDigital data stream given : " << dataStream << endl;
    cout << "Longest palindrome in given data stream : " << findLongestPalindrome(input);
    cout << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Digital/Scrambled signal produced");
    glutDisplayFunc(display);
    glutMainLoop();

}