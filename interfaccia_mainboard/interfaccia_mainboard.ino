void setup() {
  // Configura la comunicazione seriale e i pin
  Serial.begin(115200);
  
  pinMode(2, OUTPUT); // Segnale di occupato (busy signal)
  pinMode(3, INPUT_PULLUP); // Pin di interrupt

  // Configura l'interrupt su pin 3 per il fronte di salita
  attachInterrupt(digitalPinToInterrupt(3), readData, RISING);
}

void readData() {
  // Segnala che il microcontrollore è occupato
  digitalWrite(2, HIGH);

  // Leggi i bit dai pin specifici
  byte data = readBits();

  // Pulisci i bit nei registri PINB e PIND
  clearBits();

  // Invia i dati letti via seriale
  Serial.write(data);

  // Segnala che il microcontrollore non è più occupato
  digitalWrite(2, LOW);
}

// Funzione per leggere i bit dai pin definiti
byte readBits() {
  return ((bitRead(PINB, 1) << 0) | // Leggi bit 0
          (bitRead(PINB, 0) << 1) | // Leggi bit 1
          (bitRead(PIND, 7) << 2) | // Leggi bit 2
          (bitRead(PIND, 6) << 3) | // Leggi bit 3
          (bitRead(PIND, 5) << 4) | // Leggi bit 4
          (bitRead(PIND, 4) << 5) | // Leggi bit 5
          (bitRead(PINB, 2) << 6) | // Leggi bit 6
          (bitRead(PINB, 3) << 7)); // Leggi bit 7
}

// Funzione per pulire i bit dai registri PINB e PIND
void clearBits() {
  bitClear(PINB, 0);
  bitClear(PINB, 1);
  bitClear(PINB, 2);
  bitClear(PINB, 3);
  bitClear(PINB, 4);
  bitClear(PIND, 4);
  bitClear(PIND, 5);
  bitClear(PIND, 6);
  bitClear(PIND, 7);
}

void loop() {
  // Il loop è vuoto, poiché tutto è gestito dall'interrupt
}
