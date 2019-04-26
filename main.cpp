#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <windows.h>
#include <fmod.hpp>
#include "ShaderLoader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"
#include "Input.h"
#include "ObjectManager.h"


using namespace std;

ShaderLoader m_shader;
GLuint program = NULL;

GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint texture;
GLuint texture1;
GLfloat currentTime;



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HIGHT = 600;
//deltatime

Audio1 audio;
Input input;
ObjectManager objectmanager;



glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat vertices[]
{	//pos                    //colour
	-0.5f,	-0.5f,	0.0f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,//bot left
	0.5f,	0.5f,	0.0f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,// top right
	-0.5f,	0.5f,	0.0f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f, //top left
	0.5f,	-0.5f,	0.0f,	 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, //bot right
};

GLuint indices[] = 
{
	0,1,2,	//1 
	0,3,1,	//2
};



void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);


	glUseProgram(program);

	//camera
	//glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(50.0f * currentTime), glm::vec3(0, 1, 0));
	//glm::vec4 newPos = rotMat * glm::vec4(0, 0, 3, 1);
	//camPos = glm::vec3(newPos); 

	//view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);
	glm::mat4 view;
	glm::vec3 camTar = glm::vec3(0.0f, 0.0f, 0.0f);
	view = glm::lookAt(camPos, camTar, camUpDir);

	glm::mat4 proj;
	proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HIGHT, 0.1f, 100.0f);

	//movement
	glm::vec3 objPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	objPosition += objectmanager.GetObjectPos();
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);

	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotationAngle = 45;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	glm::vec3 objscale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objscale);

	glm::mat4 model = translationMatrix * rotationZ * scaleMatrix;

	glm::mat4 mvp = proj * view * model;
	GLuint mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));


	//picture
	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");//gluint?
	glUniform1f(currentTimeLoc, currentTime);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "Tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program, "Tex1"), 1);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void Update()
{
	input.processInput();

	//<sound
	audio.update();
	

	currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.001f;
	
	//GLfloat deltaTime = currentTime - pasttime;
	//pasttime = currentTime;
	//currentTime = deltaTime;
	//system("cls");
	//cout << currentTime;


	glutPostRedisplay();

}

int main(int argc, char **argv) 
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("(0) : error C5145: must write to gl_Position");
	
	if (glewInit() != GLEW_OK)
	{
		cout << "somthin wrong cheif" << endl;
		system("pause");
	}


	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

	program = ShaderLoader::CreateProgram("shader.vs", "shader.fs");

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	int width, height;
	unsigned char* image = SOIL_load_image("ass/pics/doge.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image2 = SOIL_load_image("ass/pics/garf3.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0 ,3 ,GL_FLOAT ,GL_FALSE , (8 * (sizeof(GLfloat))), (GLvoid*) 0 );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)(3 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, (8*(sizeof(GLfloat))), (GLvoid*)(6 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(2);


	// <sound
	audio.AudioInit();
	audio.Create("ass/sounds/Tron Legacy - Soundtrack OST - 03 The Son of Flynn - Daft Punk.mp3", 1);
	audio.Create("ass/Sounds/Thump.wav", 2);
	audio.playSound(1);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);

	glutSpecialFunc(Input::specialCharDown);
	glutSpecialUpFunc(Input::specialCharUp);

	glutMainLoop();
	return 0;
}


