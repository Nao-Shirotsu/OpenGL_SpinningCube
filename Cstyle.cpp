#include <cstdlib>
#include <GL/glut.h>

void idle(){
    glutPostRedisplay();
}

void keyInput( const unsigned char key, const int x, const int y ){
	if( key == '\033' ){
		std::exit(0);
	}
    if( key == char( 0x20 ) ){ // ascii code of SPACE key
        glutIdleFunc(idle);
    }else{
        glutIdleFunc(0);
    }
}

void display(){
    constexpr GLbitfield COLOR = GL_COLOR_BUFFER_BIT;
    constexpr GLbitfield QUADS = GL_QUADS;
    constexpr GLenum DEPTH = GL_DEPTH_BUFFER_BIT;
    constexpr const GLdouble vertex[][3] = {
        { -0.5, -0.5, -0.5 }, /* A */
        { 0.5, -0.5, -0.5 }, /* B */
        { 0.5, 0.5, -0.5 }, /* C */
        { -0.5, 0.5, -0.5 }, /* D */
        { -0.5, -0.5, 0.5 }, /* E */
        { 0.5, -0.5, 0.5 }, /* F */
        { 0.5, 0.5, 0.5 }, /* G */
        { -0.5, 0.5, 0.5 }  /* H */
    };
    constexpr const int face[][4] = {
        { 0, 1, 2, 3 },
        { 1, 5, 6, 2 },
        { 5, 4, 7, 6 },
        { 4, 0, 3, 7 },
        { 4, 5, 1, 0 },
        { 3, 2, 6, 7 }
    };

    constexpr const GLdouble color[][3] = {
        { 0.0, 0.3, 0.3 },
        { 0.0, 0.4, 0.4 },
        { 0.0, 0.5, 0.5 },
        { 0.0, 0.6, 0.6 },
        { 0.0, 0.7, 0.7 },
        { 0.0, 0.8, 0.8 }
    };

    static int rotationAngle = 0;

    glClear( COLOR | DEPTH );

    glLoadIdentity();
    gluLookAt( 3.0, 2.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    glRotated( double( rotationAngle ), 0.0, 1.0, 0.0 );
    
	glBegin( QUADS );
    for( int i = 0; i < 6; ++i ){
        glColor3dv( color[i] );
        for( int j = 0; j < 4; ++j ){
            glVertex3dv( vertex[face[i][j]] );
        }
    }
	glEnd();

	glutSwapBuffers();
    if( ++rotationAngle >= 360 ){
        rotationAngle = 0;
    }
}

void resize( const int w, const int h ){
    glViewport( 0, 0, w, h );

    constexpr GLenum PROJECTION = GL_PROJECTION;
    constexpr GLenum MODELVIEW = GL_MODELVIEW;
    glMatrixMode( PROJECTION );
    glLoadIdentity();
    gluPerspective( 30.0, double( w ) / double( h ), 1.0, 100.0 );
    glMatrixMode( MODELVIEW );
}

void mouse( const int button, const int state, const int x, const int y ){
    switch ( button ) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN){
                glutIdleFunc(idle);
            }else{
                glutIdleFunc(0);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

void init(){
    constexpr GLenum DEPTH = GL_DEPTH_TEST;
    constexpr GLenum CULLFACE = GL_CULL_FACE;
    constexpr GLenum BACK = GL_FRONT;

	glClearColor( 1, 1, 1, 1 );
    glEnable( DEPTH );
    glEnable( CULLFACE );
    glCullFace( BACK );
}

int main( int argc, char* argv[] ){
    glutInit( &argc, argv );

    constexpr GLenum DEPTH = GLUT_DEPTH;
    constexpr GLbitfield RGBA = GLUT_RGBA;
    constexpr GLbitfield DOUBLE = GLUT_DOUBLE;
    glutInitDisplayMode( RGBA | DOUBLE | DEPTH );

	glutCreateWindow( "Spinning Cube" );
    glEnable( DEPTH );
	glutDisplayFunc( display );
    glutReshapeFunc( resize );
	glutKeyboardFunc( keyInput );
    init();
    glutMainLoop();
}