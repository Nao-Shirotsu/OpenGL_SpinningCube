#include <cstdlib>
#include <GL/glut.h>

#include "GLManager.hpp"

int GLManager::rotationAngle = 0;

GLManager::GLManager( int& argc, char* argv[] ){
    constexpr GLenum DEPTH = GLUT_DEPTH;
    constexpr GLbitfield RGBA = GLUT_RGBA;
    constexpr GLbitfield DOUBLE = GLUT_DOUBLE;
    glutInit( &argc, argv );
    glutInitDisplayMode( RGBA | DOUBLE | DEPTH );
    glutInitWindowSize( 600, 600 );
	glutCreateWindow( "Spinning Cube - press Esc to quit" );
}

void GLManager::Update(){
    constexpr GLenum DEPTH = GLUT_DEPTH;
    glEnable( DEPTH );
	glutDisplayFunc( DisplayConfig );
    glutReshapeFunc( ObjectsConfig );
	glutKeyboardFunc( CatchKeyInput );
    OtherConfig();
}

void GLManager::Continue(){
    glutMainLoop();
}

void GLManager::CatchKeyInput( const unsigned char key, const int x, const int y ){
    if( key == '\033' ){
		std::exit(0);
	}
}

void GLManager::DisplayConfig(){
    constexpr GLbitfield COLOR = GL_COLOR_BUFFER_BIT;
    constexpr GLbitfield QUADS = GL_QUADS;
    constexpr GLenum DEPTH = GL_DEPTH_BUFFER_BIT;
    constexpr const GLdouble vertex[][3] = {
        { -1.0, -1.0, -1.0 }, /* A */
        { 1.0, -1.0, -1.0 }, /* B */
        { 1.0, 1.0, -1.0 }, /* C */
        { -1.0, 1.0, -1.0 }, /* D */
        { -1.0, -1.0, 1.0 }, /* E */
        { 1.0, -1.0, 1.0 }, /* F */
        { 1.0, 1.0, 1.0 }, /* G */
        { -1.0, 1.0, 1.0 }  /* H */
    };
    constexpr const int face[][4] = {
        { 0, 1, 2, 3 },
        { 1, 5, 6, 2 },
        { 5, 4, 7, 6 },
        { 4, 0, 3, 7 },
        { 4, 5, 1, 0 },
        { 3, 2, 6, 7 }
    };

    constexpr const GLdouble normal[][3] = {
        { 0.0, 0.0,-1.0 },
        { 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0 },
        {-1.0, 0.0, 0.0 },
        { 0.0,-1.0, 0.0 },
        { 0.0, 1.0, 0.0 }
    };

    glClear( COLOR | DEPTH );

    glLoadIdentity();
    gluLookAt( 5.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    glRotated( double( rotationAngle ), 0.0, 1.0, 0.0 );
    
	glBegin( QUADS );
    for( int i = 0; i < 6; ++i ){
        glNormal3dv( normal[i] );
        for( int j = 0; j < 4; ++j ){
            glVertex3dv( vertex[face[i][j]] );
        }
    }
	glEnd();

    glutPostRedisplay();

	glutSwapBuffers();
    if( ++rotationAngle >= 360 ){
        rotationAngle = 0;
    }
}

void GLManager::ObjectsConfig( const int w, const int h ){
    constexpr GLenum PROJECTION = GL_PROJECTION;
    constexpr GLenum MODELVIEW = GL_MODELVIEW;
    
    glViewport( 0, 0, w, h );
    glMatrixMode( PROJECTION );
    glLoadIdentity();
    gluPerspective( 30.0, double( w ) / double( h ), 1.0, 100.0 );
    glMatrixMode( MODELVIEW );
}

void GLManager::OtherConfig(){
    constexpr GLenum DEPTH = GL_DEPTH_TEST;
    constexpr GLenum CULLFACE = GL_CULL_FACE;
    constexpr GLenum BACK = GL_FRONT;
    constexpr GLenum LIGHTING = GL_LIGHTING;
    constexpr GLenum LIGHT0 = GL_LIGHT0;

	glClearColor( 0, 0, 0, 0 );
    glEnable( DEPTH );
    glEnable( CULLFACE );
    glCullFace( BACK );
    glEnable( LIGHTING );
    glEnable( LIGHT0 );
}