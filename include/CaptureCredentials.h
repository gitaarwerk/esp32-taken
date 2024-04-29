#include <string>

class CaptureCredentials
{
private:
public:
    CaptureCredentials();

    void initScreen();
    
    void offScren();

    void storeCaptive(String ssid, String portalId, String username, String password);
};