#include "SDCard.h"
#include <FS.h>
#include <SD_MMC.h>
#include <string>

// Handle SD card LilyGo TTGO T4_v1.3
SDCard::SDCard()
{
    // Serial.begin(115200);

    // if (!SD_MMC.begin())
    // {
    //     Serial.println("Card Mount Failed");
    //     return;
    // }
    // uint8_t cardType = SD_MMC.cardType();

    // if (cardType == CARD_NONE)
    // {
    //     Serial.println("No SD card attached");
    //     return;
    // }

    // Serial.print("SD Card Type: ");
    // if (cardType == CARD_MMC)
    // {
    //     Serial.println("MMC");
    // }
    // else if (cardType == CARD_SD)
    // {
    //     Serial.println("SDSC");
    // }
    // else if (cardType == CARD_SDHC)
    // {
    //     Serial.println("SDHC");
    // }
    // else
    // {
    //     Serial.println("UNKNOWN");
    // }

    // uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    // Serial.printf("SD Card Size: %lluMB\n", cardSize);

    // listDir(SD_MMC, "/", 0);
    // createDir(SD_MMC, "/mydir");
    // listDir(SD_MMC, "/", 0);
    // removeDir(SD_MMC, "/mydir");
    // listDir(SD_MMC, "/", 2);
    // writeFile(SD_MMC, "/hello.txt", "Hello ");
    // appendFile(SD_MMC, "/hello.txt", "World!\n");
    // readFile(SD_MMC, "/hello.txt");
    // deleteFile(SD_MMC, "/foo.txt");
    // renameFile(SD_MMC, "/hello.txt", "/foo.txt");
    // readFile(SD_MMC, "/foo.txt");
    // testFileIO(SD_MMC, "/test.txt");
    // Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
    // Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));
}

// SDCard::SDCard()
// {
// pinMode(SD_CS, OUTPUT); // Set the SD_CS pin as an output
// // digitalWrite(SD_CS, HIGH);
// SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

// if (!SD_MMC.begin(SD_CS))
// {
//     Serial.println("Error accessing microSD card!");
//     while (true)
//         ;
// }
// if (SD_MMC.begin(SD_CS))
// {
//     Serial.println("READ microSD card!");
//     while (true)
//         ;
// }
// }

void SDCard::init()
{
    // Initialization code here
}

void SDCard::listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                listDir(fs, file.name(), levels - 1);
            }
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void SDCard::createDir(fs::FS &fs, const char *path)
{
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path))
    {
        Serial.println("Dir created");
    }
    else
    {
        Serial.println("mkdir failed");
    }
}

void SDCard::removeDir(fs::FS &fs, const char *path)
{
    Serial.printf("Removing Dir: %s\n", path);
    if (fs.rmdir(path))
    {
        Serial.println("Dir removed");
    }
    else
    {
        Serial.println("rmdir failed");
    }
}

void SDCard::readFile(fs::FS &fs, const char *path)
{
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

void SDCard::writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("File written");
    }
    else
    {
        Serial.println("Write failed");
    }
    file.close();
}

void SDCard::appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        Serial.println("Message appended");
    }
    else
    {
        Serial.println("Append failed");
    }
    file.close();
}

void SDCard::renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2))
    {
        Serial.println("File renamed");
    }
    else
    {
        Serial.println("Rename failed");
    }
}

void SDCard::deleteFile(fs::FS &fs, const char *path)
{
    Serial.printf("Deleting file: %s\n", path);
    if (fs.remove(path))
    {
        Serial.println("File deleted");
    }
    else
    {
        Serial.println("Delete failed");
    }
}

void SDCard::testFileIO(fs::FS &fs, const char *path)
{
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if (file)
    {
        len = file.size();
        size_t flen = len;
        start = millis();
        while (len)
        {
            size_t toRead = len;
            if (toRead > 512)
            {
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    }
    else
    {
        Serial.println("Failed to open file for reading");
    }

    file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for (i = 0; i < 2048; i++)
    {
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}

char *SDCard::getFile(String path)
{
    return "{\"autoLocaleOfBrowser\": true,\"defaultLocale\":\"nl_NL\",\"screensaver\":false}";
}

;