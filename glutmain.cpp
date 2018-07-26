#include "GLManager.hpp"

int main( int argc, char* argv[] ){
    GLManager glmanager( argc, argv );
    glmanager.Update();
    glmanager.Continue();
}