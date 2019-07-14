/* ****************************************************************
 * AppCore.h helps with shared app functions
 * ****************************************************************/

#ifndef APPCORE_H
#define APPCORE_H

#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>

class AppCore
{
public:
    AppCore() {};
    //getters
    int getMsgBoxWidth();
    //setters
    void setMsgBoxWidth(int width);
    void setWindowTitle(std::string);
    void setWindowColors();
    //others
    void clearDisplay();
    void drawStaightLine(int width);
    void drawMessageBox(std::string message);
    bool fileExists(const std::string &file);
    void showMenuResolutionMenu();

protected:

private:
    int msgBoxWidth = 80;
    std::string windowTitle = "Phone Resolution Tool";
    std::string centerConsoleMessage(std::string message, unsigned int consoleWidth);
    void applyDPI(std::string dpi);
    void applyResolution(std::string resolution);
    int customHeight = 0;
    int customWidth = 0;
    void drawBottomLeftCorner();
    void drawBottomRightCorner();
    void drawTopLeftCorner();
    void drawTopRightCorner();
    void drawVerticalLine();
    int promptDPI();
    int promptWidthPixels();
    int promptHeightPixels();
    void resetAll();
    bool showEnterCustomDPI();
    bool showEnterCustomResolution();
    void showMenuEndMenu();
    void showMenuDPIMenu();

};
/******************
* Getters
*******************/

// returns the width (character columns) currently set for the messageBox drawing functions
int AppCore::getMsgBoxWidth()
{
    return this->msgBoxWidth;
}

/******************
* Setters
*******************/

// sets the width (character columns) for drawing functions
void AppCore::setMsgBoxWidth(int width)
{
    this->msgBoxWidth = width;
}

// sets the App Window title
void AppCore::setWindowTitle(std::string title)
{
    this->windowTitle = title;
    std::system(("@Title " + title).c_str());
}

/******************
* Other functions
*******************/

// clears console display
void AppCore::clearDisplay()
{
    std::system("cls");
}

// draws a straight line for the specified number (width) of characters
void AppCore::drawStaightLine(int width)
{
    for (int i = 0; i < width; i++)
    {
        std::cout << "\xCD";
    }
}

// prints out a top left corner line
void AppCore::drawTopLeftCorner()
{
    std::cout << "\xC9";
}

// prints out a bottom right corner line
void AppCore::drawTopRightCorner()
{
    std::cout << "\xBB";
}

// prints out a bottom left corner line
void AppCore::drawBottomLeftCorner()
{
    std::cout << "\xC8";
}

// prints out a bottom right corner line
void AppCore::drawBottomRightCorner()
{
    std::cout << "\xBC";
}

// prints a single vertical line;
void AppCore::drawVerticalLine()
{
    std::cout << "\xBA";
}

// prints out a box with a centered message
void AppCore::drawMessageBox(std::string message)
{
    this->drawTopLeftCorner();
    this->drawStaightLine(this->msgBoxWidth - 2);
    this->drawTopRightCorner();
    if(this->msgBoxWidth < 80)
    {
        std::cout << std::endl;
    }
    this->drawVerticalLine();
    std::cout << this->centerConsoleMessage(message, (this->msgBoxWidth - 2));
    this->drawVerticalLine();
    if(this->msgBoxWidth < 80)
    {
        std::cout << std::endl;
    }
    this->drawBottomLeftCorner();
    this->drawStaightLine(this->msgBoxWidth - 2);
    this->drawBottomRightCorner();
    std::cout << std::endl;
}

// centers a message by padding the sides with spaces
std::string AppCore::centerConsoleMessage(std::string message, unsigned int consoleWidth)
{
    if(message.length() > consoleWidth)
    {
        return message;
    }
    int diff = consoleWidth - message.length();
    std::string tmpString = "";
    for(int i = 0; i < (diff/2); i++)
    {
        tmpString += " ";
    }
    std::string returnString = (tmpString + message + tmpString).c_str();
    if(returnString.length() < consoleWidth)
    {
        return returnString + " ";
    }
    return returnString;
}

// executes the ADB apply DPI command and shows exit menu
void AppCore::applyDPI(std::string dpi)
{
    this->clearDisplay();
    std::cout << "Applying " << dpi << " DPI..." << std::endl;
    std::cout << std::endl;
    system(("adb shell wm density " + dpi).c_str());
    this->showMenuEndMenu();
}
// executes the ADB apply resolution command and advances to show the DPI settings
void AppCore::applyResolution(std::string resolution)
{
    this->clearDisplay();
    std::cout << "Applying " << resolution << "..." << std::endl;
    std::cout << std::endl;
    system(("adb shell wm size " + resolution).c_str());
    this->showMenuDPIMenu();
}

// checks if specified file exists.
bool AppCore::fileExists(const std::string &file)
{
    struct stat buf;
    return (stat(file.c_str(), &buf) == 0);
}

// executes ADB command to reset all settings
void AppCore::resetAll()
{
    this->clearDisplay();
    std::cout << "Resetting..." << std::endl;
    std::cout << std::endl;
    system("adb shell wm size reset");
    system("adb shell wm density reset");
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Your resolution and DPI settings have been reset " << std::endl;
    std::cout << std::endl;
    this->showMenuEndMenu();
}

// prints out DPI settings Menu
void AppCore::showMenuDPIMenu()
{
    std::string userChoice;
    this->clearDisplay();
    this->drawMessageBox("Set DPI:");
    std::cout << " 1. 480" << std::endl;
    std::cout << " 2. 400" << std::endl;
    std::cout << " 3. 320" << std::endl;
    std::cout << " 4. 240" << std::endl;
    std::cout << " 5. 160" << std::endl;
    std::cout << std::endl;
    std::cout << " 6. Enter Custom DPI (Advanced Users only)" << std::endl;
    std::cout << " 7. Do not change DPI" << std::endl;
    std::cout << " 8. Back to Resolution Settings" << std::endl;
    this->drawStaightLine(this->msgBoxWidth);
    std::cout << std::endl;
    std::cout << "Enter a choice>" ;
    while (true)
    {
        userChoice = getch();
        if (userChoice == "1")
        {
            applyDPI("480");
            break;
        }
        if (userChoice == "2")
        {
            applyDPI("400");
            break;
        }
        if (userChoice == "3")
        {
            applyDPI("320");
            break;
        }
        if (userChoice == "4")
        {
            applyDPI("240");
            break;
        }
        if (userChoice == "5")
        {
            applyDPI("160");
            break;
        }
        if (userChoice == "6")
        {
            bool isEnteredCustomDPI = this->showEnterCustomDPI();
            if (isEnteredCustomDPI == true)
            {
                break;
            }
            else
            {
                this->showMenuDPIMenu();
                break;
            }
        }

        if (userChoice == "7")
        {
            this->clearDisplay();
            std::cout << "Your DPI will not be changed " << std::endl;
            std::cout << std::endl;
            system("pause");
            this->showMenuEndMenu();
            break;
        }

        if (userChoice == "8")
        {
            this->showMenuResolutionMenu();
            break;
        }
    };
}

// prints out the Application exit menu
void AppCore::showMenuEndMenu()
{
    std::string userChoice;
    system("color 0A");
    this->clearDisplay();
    this->drawMessageBox("ALL DONE!");
    std::cout << "Resolution:" << std::endl;
    system("adb shell wm size");
    std::cout << std::endl;
    std::cout << "DPI:" << std::endl;
    system("adb shell wm density");
    std::cout << std::endl;
    this->drawStaightLine(this->msgBoxWidth);
    std::cout << std::endl;
    std::cout << "Do you want to reboot your phone (yes recommended)? [Y/N]>";

    while (true)
    {
        userChoice = getch();
        if (userChoice == "y" || userChoice == "Y")
        {            
            this->clearDisplay();
            std::cout << "Rebooting..." << std::endl;
            system("adb reboot");
            break;
        }
        if (userChoice == "n" || userChoice == "N")
        {
            break;
        }
    }
    this->clearDisplay();
    system("exit");
}

// prints out the Resolution settings Menu
void AppCore::showMenuResolutionMenu()
{
    std::string userChoice;
    this->clearDisplay();
    this->drawMessageBox("Set RESOLUTION:");
    std::cout << " 1. 1080x1920" << std::endl;
    std::cout << " 2. 900x1600" << std::endl;
    std::cout << " 3. 720x1280" << std::endl;
    std::cout << " 4. 540x960" << std::endl;
    std::cout << " 5. 480x800" << std::endl;
    std::cout << " 6. Other (Custom) Resolution..." << std::endl;
    std::cout << std::endl;
    std::cout << " 7. Reset All (Resolution and DPI)" << std::endl;
    std::cout << " 8. Do not change resolution" << std::endl;
    this->drawStaightLine(this->msgBoxWidth);
    std::cout << std::endl;
    std::cout << "Enter a choices>";

    while (true)
    {
        userChoice = getch();
        if (userChoice == "1")
        {
            this->applyResolution("1080x1920");
            break;
        }
        if (userChoice == "2")
        {
            this->applyResolution("900x1600");
            break;
        }
        if (userChoice == "3")
        {
            this->applyResolution("720x1280");
            break;
        }
        if (userChoice == "4")
        {
            this->applyResolution("540x960");
            break;
        }
        if (userChoice == "5")
        {
            this->applyResolution("480x800");
            break;
        }
        if (userChoice == "6")
        {
            bool isEnteredCustomResolution = this->showEnterCustomResolution();
            if (isEnteredCustomResolution == true)
            {
                break;
            }
            else
            {
                this->showMenuResolutionMenu();
                break;
            }
        }
        if (userChoice == "7")
        {
            this->resetAll();
            break;
        }
        if (userChoice == "8")
        {
            this->showMenuDPIMenu();
            break;
        }
    }
}

// prompts user to enter custom DPI
int AppCore::promptDPI()
{
    int custdpi;
    this->clearDisplay();
    this->drawMessageBox("CUSTOM DPI");
    std::cout << std::endl;
    std::cout << "Enter custom DPI. Min 120, Max 640>";
    std::cin >> custdpi;
    if (std::cin.fail() || custdpi < 120 || custdpi > 640)
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        this->promptDPI();
    }
    else
    {
        this->clearDisplay();
        std::cout << std::endl;
        this->drawMessageBox("CUSTOM DPI");
        std::cout << "Selected DPI :" << custdpi << std::endl;
        applyDPI(std::to_string(custdpi));
    }
    return custdpi;
}

// prints out the Enter Custom DPI menu
bool AppCore::showEnterCustomDPI()
{
    std::string userChoice;
    system("color 0C");
    this->clearDisplay();
    this->drawMessageBox("CAUTION!");
    std::cout << std::endl;
    std::cout << "Entering custom DPI is recommended only for Advanced Users." << std::endl;
    std::cout << std::endl;
    this->drawStaightLine(this->msgBoxWidth);
    std::cout << std::endl;
    std::cout << "Are you sure you want to continue? [Y/N]>";
    while (true)
    {
        userChoice = getch();
        system("color 0F");
        if (userChoice == "y" || userChoice == "Y")
        {
            this->promptDPI();
            return true;
            break;
        }
        if (userChoice == "n" || userChoice == "N")
        {
            return false;
            break;
        }
    }
    return false;
}

// prompts user to enter width in pixels
int AppCore::promptWidthPixels()
{
    this->clearDisplay();
    this->drawMessageBox("CUSTOM RESOLUTION");
    std::cout << "Enter custom width in pixels. Min 240, Max 2960>";
    std::cin >> this->customWidth;
    if (std::cin.fail() || this->customWidth < 240 || this->customWidth > 2960)
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        return this->promptWidthPixels();
    }
    else
    {
        return this->customWidth;
    }
}

// prompts user to enter height in pixels
int AppCore::promptHeightPixels()
{
    this->clearDisplay();
    this->drawMessageBox("CUSTOM RESOLUTION");
    std::cout << "Selected width:" << this->customWidth << std::endl;
    std::cout << std::endl;
    std::cout << "Enter custom height in pixels. Min 240, Max 2960>" ;
    std::cin >> this->customHeight;
    if (std::cin.fail() || this->customHeight < 240 || this->customHeight > 2960)
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        return this->promptHeightPixels();
    }
    else
    {
        return this->customHeight;
    }
}

// prints out the Enter Custom Resolution menu
bool AppCore::showEnterCustomResolution()
{
    std::string userChoice;
    system("color 0C");
    this->clearDisplay();
    this->drawMessageBox("CAUTION!");
    std::cout << "Entering custom resolutions is recommended only for Advanced Users." << std::endl;
    std::cout << std::endl;
    this->drawStaightLine(this->msgBoxWidth);
    std::cout << std::endl;
    std::cout << "Are you sure you want to continue? [Y/N]>" ;
    while (true)
    {
        userChoice = getch();
        system("color 0F");
        if (userChoice == "y" || userChoice == "Y")
        {
            this->promptWidthPixels();
            this->promptHeightPixels();
            this->clearDisplay();
            std::cout << std::endl;
            this->drawMessageBox("CUSTOM RESOLUTION");
            std::cout << "Selected width :" << this->customWidth << std::endl;
            std::cout << "Selected height :" << this->customHeight << std::endl;
            applyResolution(std::to_string(this->customWidth) + "x" + std::to_string(this->customHeight));
            return true;
            break;
        }
        if (userChoice == "n" || userChoice == "N")
        {
            return false;
            break;
        }
    };
    return false;
}

#endif // AppCore_H
