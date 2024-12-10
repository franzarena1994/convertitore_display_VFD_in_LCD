// Alphabet Arduino

#define WRITE 3
#define D0 5
#define D1 6
#define D2 7
#define D3 8
#define D4 9
#define D5 10
#define D6 11
#define D7 12

// Mappatura delle lettere, numeri e simboli
const byte CHARACTERS[] = {
    0b00100101, // Clear display
    0b01000001, // A
    0b01000010, // B
    0b01000011, // C
    0b01000100, // D
    0b01000101, // E
    0b01000110, // F
    0b01000111, // G
    0b01001000, // H
    0b01001001, // I
    0b01001010, // J
    0b01001011, // K
    0b01001100, // L
    0b01001101, // M
    0b01001110, // N
    0b01001111, // O
    0b01010000, // P
    0b01010001, // Q
    0b01010010, // R
    0b01010011, // S
    0b01010100, // T
    0b01010101, // U
    0b01010110, // V
    0b01010111, // W
    0b01011000, // X
    0b01011001, // Y
    0b01011010, // Z
    0b10110101, // :
    0b10000001, // !
    0b10110000, // 0
    0b10110001, // 1
    0b00101000  // Space
};

void setup() {
  // Configura i pin
  pinMode(WRITE, OUTPUT);
  for (int pin = D0; pin <= D7; pin++) {
    pinMode(pin, OUTPUT);
  }

  // Imposta tutti i pin in stato LOW inizialmente
  digitalWrite(WRITE, LOW);
  clearDisplay();
}

void loop() {
  // Visualizza ogni carattere con un ritardo
  for (byte character : CHARACTERS) {
    displayCharacter(character);
    delay(150); // Ritardo tra i caratteri
  }

  delay(1500); // Pausa tra cicli
}

// Funzione per impostare i pin dati
void setPins(byte data) {
  digitalWrite(D0, data & 0x01);
  digitalWrite(D1, (data >> 1) & 0x01);
  digitalWrite(D2, (data >> 2) & 0x01);
  digitalWrite(D3, (data >> 3) & 0x01);
  digitalWrite(D4, (data >> 4) & 0x01);
  digitalWrite(D5, (data >> 5) & 0x01);
  digitalWrite(D6, (data >> 6) & 0x01);
  digitalWrite(D7, (data >> 7) & 0x01);
}

// Funzione per visualizzare un carattere
void displayCharacter(byte character) {
  setPins(character);
  digitalWrite(WRITE, HIGH);
  delay(10); // Impulso per scrivere il carattere
  digitalWrite(WRITE, LOW);
}

// Funzione per cancellare il display
void clearDisplay() {
  displayCharacter(0b00100101); // Codice per clear display
}
