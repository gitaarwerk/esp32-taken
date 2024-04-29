#include <Arduino.h>
#include <string>
#include <FS.h>
#include <SD_MMC.h>

#ifndef SDCARD_H
#define SDCARD_H

class SDCard
{
private:
public:
    SDCard();

    void init();

    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
    void createDir(fs::FS &fs, const char *path);
    void removeDir(fs::FS &fs, const char *path);
    void readFile(fs::FS &fs, const char *path);
    void writeFile(fs::FS &fs, const char *path, const char *message);
    void appendFile(fs::FS &fs, const char *path, const char *message);
    void renameFile(fs::FS &fs, const char *path1, const char *path2);
    void deleteFile(fs::FS &fs, const char *path);
    void testFileIO(fs::FS &fs, const char *path);

    char *getFile(String path);
}

#endif
;