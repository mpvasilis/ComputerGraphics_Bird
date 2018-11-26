#include "visuals.h"


// Camera positions
float xpos = 10, ypos = 50, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float ambient_0[4]={0.9,0.9,0.9,1.0};
float specular_0[4]={0.9,0.9,0.9,1.0};
float diffuse_0[4]={0.9,0.9,0.9,1.0};

// Camera mode
int cameraMode = CAM_C_PERSPECTIVE;
int lastWidth;
int lastHeight;

GLdouble dim=500;

// Azimuth and elevation of view angle
int th=0;
int ph=0;

// Animate Bird
int animate_bird = TRUE;

void setCameraMode()
{
    if(cameraMode == CAM_B_FRONT)
    {
        // rotate our camera on the x-axis (left and right)
        glRotatef(xrot,1.0,0.0,0.0);

        // rotate our camera on the y-axis (up and down)
        glRotatef(yrot,0.0,1.0,0.0);

        // translate the screen to the position of our camera
        glTranslated(-xpos,-ypos,-zpos);
    }
    else if(cameraMode == CAM_A_SIDE)
    {

        glTranslated(0,
            THIRD_PERSON_CAMERA_Y_OFFEST,
            THIRD_PERSON_CAMERA_Z_OFFEST
        );
        glRotatef(xrot,1.0,0.0,0.0);
        
 
        glRotatef(yrot,0.0,1.0,0.0);
        glTranslated(-xpos,-ypos,-zpos);
    }
}

void display()
{
    int i;

    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Reset view
    glLoadIdentity();

	if (cameraMode == CAM_C_PERSPECTIVE)
	{
		double Ex = -2 * dim * trig_rad_sin(th) * trig_rad_cos(ph);
		double Ey = 4 * dim * trig_rad_sin(ph);
		double Ez = 2 * dim * trig_rad_cos(th) * trig_rad_cos(ph);
		gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, trig_rad_cos(ph), 0);
	}
	else if (cameraMode == CAM_A_SIDE || cameraMode == CAM_B_FRONT)
	{
		setCameraMode();
	}
	else
	{
		glRotatef(ph, 1, 0, 0);
		glRotatef(th, 0, 1, 0);
	}


    glScalef(1.8,1.8,1.8);
    glTranslatef(0,-100,10);


	glEnable(GL_CULL_FACE);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);


	//Set up light source
	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat lightPos[] = { -20.0, 20.0, 150.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	// polygon rendering mode and material properties
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	// Set materials
	float emission_material[4] = { 0,0,0,1 };
	float specular_material[4] = { 0.2,0.2,0.2,1.0 };
	float ambient_material[4] = { 0.1,0.1,0.1,1.0 };
	float shiny_material[1] = { 0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny_material);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_material);

	// Draw bird
	bird_draw(&bird);

    // Display current weights
    glColor3f(1,1,1);


    // Render scene and flip buffers
    glFlush();
    glutSwapBuffers();
}



void animate()
{
	bird_step(&bird, &bird_physics, 1, 1);

    glutPostRedisplay();
    glutTimerFunc(UPDATE_FREQUENCY, animate, 0);

}


void setCameraPerspective()
{

   //set the viewport to the current window specifications
   glViewport (0, 0, (GLsizei)lastWidth, (GLsizei)lastHeight);

   //set the matrix to projection
   glMatrixMode (GL_PROJECTION);

   glLoadIdentity ();
   //set the perspective (angle of sight, width, height, , depth)
   double w2h = (lastHeight>0) ? (double)lastWidth/lastHeight : 1;
   gluPerspective (60, w2h, dim/16, 16*dim);

   //set the matrix back to model
   glMatrixMode (GL_MODELVIEW);
}



void MenuSelect(int choice) 
{

	switch (choice) {
	case START_ANIMATION:
		animate_bird = TRUE;
		break;
	case STOP_ANIMATION:
		animate_bird = FALSE;
		break;
	case CHANGE_CAMERA:
		if (cameraMode == CAM_A_SIDE)
		{
			cameraMode = CAM_B_FRONT;
			setCameraMode();
			printf("CAM_B_FRONT\n");
		}
		else if (cameraMode == CAM_B_FRONT)
		{
			cameraMode = CAM_C_PERSPECTIVE;
			setCameraPerspective();
			printf("CAM_C_PERSPECTIVE\n");

		}
		else if (cameraMode == CAM_C_PERSPECTIVE)
		{
			cameraMode = CAM_A_SIDE;
			setCameraMode();
			printf("CAM_A_SIDE\n");

		}
		break;
	case EXIT:
		exit(0);
		break;
	}

}



void handleReshape(int width,int height)
{
   lastWidth = width;
   lastHeight = height;
   setCameraPerspective();
}


int main(int argc,char* argv[])
{

    int i=1;

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   
    glutInitWindowSize(WIDTH, HEIGHT);
    lastWidth = WIDTH;
    lastHeight = HEIGHT;
   
    glutCreateWindow(WINDOW_TITLE);

    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

	Bird_physics_init(&bird_physics, 0, 0, 0);
	bird_initBird(&bird, &bird_physics);
	bird_setParams(&bird);

	glShadeModel(GL_SMOOTH); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	glEnable(GL_CULL_FACE);

	glEnable(GL_NORMALIZE);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
 
	setCameraPerspective();

    glutDisplayFunc(display);

    glutReshapeFunc(handleReshape);

    glutTimerFunc(25,animate,0);

	glutCreateMenu(MenuSelect);
	glutAddMenuEntry("Start Animation", 1);
	glutAddMenuEntry("Stop Animation", 2);
	glutAddMenuEntry("Change Camera", 3);
	glutAddMenuEntry("Exit", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
    return 0;
}