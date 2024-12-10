#include <LiquidCrystal.h>

// Configurazione LCD
#define LCD_COLS 20
#define LCD_ROWS 4

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

// Variabili globali
byte data;
int col = 0;
int row = 0;
bool isFlagSet = false;

void setup() {
  // Inizializzazione LCD e Serial
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.begin(115200);

  Serial.println("LCD Serial Display Ready");
}

void loop() {
  // Gestione della comunicazione seriale
  if (Serial.available() > 0) {
    data = Serial.read();
    handleSerialData(data);
  }
}

// Funzione per gestire i comandi ricevuti via Serial
void handleSerialData(byte incomingData) {
  if (isFlagSet) {
    handleFlagCommand(incomingData);
    isFlagSet = false;
    return;
  }

  if (incomingData < 0x1F) {
    handleControlCommand(incomingData);
  } else {
    handleDisplayableCharacter(incomingData);
  }
}

// Gestisce i comandi speciali impostati da flag
void handleFlagCommand(byte colData) {
  col = constrain(colData, 0, LCD_COLS - 1);
  lcd.setCursor(col, row);
  Serial.print("Set column: ");
  Serial.println(col, HEX);
}

// Gestisce comandi di controllo
void handleControlCommand(byte command) {
  switch (command) {
    case 0x08: // Backspace
      handleBackspace();
      break;

    case 0x10: // Set column
      isFlagSet = true;
      break;

    case 0x0D: // Clear screen
    case 0x1F: // Alternate clear screen
      lcd.clear();
      Serial.println("LCD Cleared");
      col = 0;
      row = 0;
      break;

    case 0x09: // Tab
      handleTab();
      break;

    default:
      Serial.print("Unrecognized control command: ");
      Serial.println(command, HEX);
      break;
  }
}

// Gestisce caratteri displayabili
void handleDisplayableCharacter(byte character) {
  if (col < LCD_COLS) {
    lcd.setCursor(col, row);
    lcd.write(character);
    Serial.write(character);
    col++;
  } else {
    Serial.println("Reached end of line, ignoring character.");
  }
}

// Gestisce il comando backspace
void handleBackspace() {
  if (col > 0) {
    col--;
    lcd.setCursor(col, row);
    lcd.print(' ');
    lcd.setCursor(col, row); // Riposizionamento del cursore
    Serial.println("Backspace executed");
  } else {
    Serial.println("Cannot backspace, at start of line.");
  }
}

// Gestisce il comando tab
void handleTab() {
  col++;
  if (col >= LCD_COLS) {
    col = 0;
  }
  lcd.setCursor(col, row);
  lcd.print(' ');
  Serial.println("Tab executed");
}
