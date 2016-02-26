/*
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 50
 ** MISO - pin 51
 ** CLK - pin 52
 ** CS - pin 53
 */
#include <SPI.h>
#include <SD.h>

File root;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega, 14 on the Leonardo) must be left as an output
  // or the SD library functions will not work.

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }

  Serial.println("initialization done.");
  root = SD.open("SDTest.txt", FILE_WRITE);

  if (root) {
    Serial.print("Writing to test.txt...");
    root.println("Testing...");
    root.close();
    Serial.println("done");
  } else {
    Serial.println("error opening test.txt");
  }

  root = SD.open("SDTest.txt");

  if (root) {
    Serial.println("SDTest.txt:");

    while (root.available()) {
      Serial.write(root.read());
    }

    root.close();
  } else {
    Serial.println("Error opening SDTest.txt");
  }

  Serial.println("Done. Exiting...");
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}