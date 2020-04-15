/* ****************************************************************
 * @author: "github.com/nadchif"
 * @app name: "Phone resolution and DPI tool"
 * @app desc: "Change phone resolution and DPI without root"
 * ****************************************************************/

#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include "AppCore.h"

int main()
{
    int consoleWidth = 80;
    // set console window size to windows console defaults , just to override custom settings
    std::system("MODE CON COLS=80 LINES=25");
    AppCore appCore;

    //turn off echo
    std::system("@echo off");

    //set message box width
    appCore.setMsgBoxWidth(consoleWidth);

    //set window title
    appCore.setWindowTitle("Resolution and DPI Set Tool 2.1.0");

    //check requirements
    if (!appCore.fileExists("adb.exe"))
    {
        appCore.clearDisplay();
        std::system("color 0C");
        appCore.drawMessageBox("OOPS! Missing ADB");
        std::cout << std::endl;
        std::cout << "Failed to find 'adb.exe' " << std::endl
                  << "Please make sure you have placed this tool in the same directory where adb.exe is located." << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::system("PAUSE");
        appCore.clearDisplay();
        return EXIT_SUCCESS;
    }
    //initialize
    appCore.clearDisplay();
    system("color 09");
    std::cout << "Initializing..." << std::endl;
    std::cout << std::endl;
    system("adb devices");
    system("color F4");
    appCore.clearDisplay();
    appCore.drawMessageBox("IMPORTANT! READ THROUGH FIRST:");
    std::cout << std::endl;
    std::cout << "1. This tool was initially designed for the developers' personal use." << std::endl
              << " However, you may use it freely and at your own risk, if you find it helpful." << std::endl;
    std::cout << std::endl;
    std::cout << "2. The tool relies on ADB to apply the settings. " << std::endl;
    std::cout << std::endl;
    std::cout << "3. Make sure this app has been placed in the same folder as ADB and fast boot. " << std::endl;
    std::cout << std::endl;
    std::cout << "4. Make sure you have enabled Developer Mode and USB Debugging on your phone and you have authorized this PC" << std::endl;
    std::cout << std::endl;
    std::cout << "5. Attach only ONE Android device at a time prior to using the tool" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    appCore.drawStaightLine(consoleWidth);
    std::cout << std::endl;
    std::cout << "(C) 2019 dchif Solutions. " << std::endl;
    std::cout << std::endl;
    system("Pause");

    //show current settings
    system("color F0");
    appCore.clearDisplay();
    std::cout << std::endl;
    std::cout << "CURRENT Settings detected:" << std::endl;
    appCore.drawStaightLine(consoleWidth);
    std::cout << std::endl;
    system("adb devices");
    std::cout << "Resolution:" << std::endl;
    system("adb shell wm size");
    std::cout << std::endl;
    std::cout << "DPI:" << std::endl;
    system("adb shell wm density");
    std::cout << std::endl;
    appCore.drawStaightLine(consoleWidth);
    std::cout << std::endl;
    std::cout << "TAKE NOTE of the settings.  I DO NOT RECOMMEND setting resolution or dpi higher than Physical size shown above." << std::endl;
    std::cout << std::endl;
    std::cout << "If you get a 'device not found' error make sure you have followed the requirements listed on the previous screen." << std::endl;
    std::cout << std::endl;
    system("pause");
    system("color 0F");
    appCore.clearDisplay();

    appCore.showMenuResolutionMenu();

    return EXIT_SUCCESS;
}
