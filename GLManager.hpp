
class GLManager{
public:
    GLManager( int& argc, char* argv[] );
    void Update();
    void Continue();

private:
    static void CatchKeyInput( const unsigned char key, const int x, const int y );
    static void DisplayConfig();
    static void ObjectsConfig( const int w, const int h );
    void OtherConfig();

    static int rotationAngle;
};