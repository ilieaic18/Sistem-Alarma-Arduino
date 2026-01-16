#include <Keypad.h>

// --- CONFIGURARE PINI ---
const int PIN_PIR = 12;
const int PIN_BUZZER = 11;
const int PIN_LED_VERDE = 10;
const int PIN_LED_ROSU = 13;

// --- CONFIGURARE TASTATURA ---
const byte RANDURI = 4; 
const byte COLOANE = 4; 
// Definim harta tastelor
char keys[RANDURI][COLOANE] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Pinii unde ai legat tastatura (verifica sa fie ordinea buna)
byte piniRanduri[RANDURI] = {9, 8, 7, 6}; 
byte piniColoane[COLOANE] = {5, 4, 3, 2}; 

Keypad tastatura = Keypad( makeKeymap(keys), piniRanduri, piniColoane, RANDURI, COLOANE );

// --- VARIABILE SISTEM ---
String codCorect = "1234"; // <--- AICI POTI SCHIMBA CODUL
String codIntrodus = "";
boolean sistemArmat = false;
boolean alarmaDeclansata = false;

void setup() {
  // Pornim comunicarea cu Laptopul (Monitorul Serial)
  Serial.begin(9600);

  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROSU, OUTPUT);
  
  // Stare initiala: totul oprit, doar Verde aprins
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED_ROSU, LOW);
  digitalWrite(PIN_LED_VERDE, HIGH); 
  
  Serial.println("\n\n-------------------------------");
  Serial.println("   SISTEM DE ALARMA ARDUINO    ");
  Serial.println("-------------------------------");
  Serial.println("Stare: DEZARMAT (Safe)");
  Serial.println("Tasteaza codul si apasa # pentru armare.");
}

void loop() {
  char tasta = tastatura.getKey();
  
  // 1. LOGICA TASTATURA
  if (tasta) {
    // Facem un mic bip cand apesi o tasta
    digitalWrite(PIN_BUZZER, HIGH); delay(50); digitalWrite(PIN_BUZZER, LOW);
    
    if (tasta == '#') { 
      // Tasta # inseamna ENTER -> verificam codul
      verificaCod();
    } else if (tasta == '*') { 
      // Tasta * sterge tot ce ai scris
      codIntrodus = "";
      Serial.println("\n[STERGERE] Introdu codul de la zero:");
    } else {
      // Adaugam cifra la cod
      codIntrodus += tasta;
      Serial.print("*"); // Afisam o steluta pe laptop pt securitate
    }
  }

  // 2. LOGICA ALARMA (Doar daca e armat)
  if (sistemArmat) {
    if (digitalRead(PIN_PIR) == HIGH) {
      // Daca senzorul vede miscare
      if (!alarmaDeclansata) {
         Serial.println("\n!!! MISCARE DETECTATA !!!");
         Serial.println("!!! ALARMA ACTIVA !!!");
      }
      alarmaDeclansata = true;
    }
  }

  // 3. DECLANSARE SIRENA SI LUMINI
  if (alarmaDeclansata) {
    digitalWrite(PIN_BUZZER, HIGH);
    digitalWrite(PIN_LED_ROSU, HIGH);
    delay(100);
    digitalWrite(PIN_BUZZER, LOW);
    digitalWrite(PIN_LED_ROSU, LOW);
    delay(100);
  }
}

void verificaCod() {
  Serial.println(); // Trecem la rand nou pe ecran
  
  if (codIntrodus == codCorect) {
    // Daca codul e bun, schimbam starea (Armat <-> Dezarmat)
    
    if (sistemArmat == false) {
      // CAZUL 1: Vrem sa ARMAM
      sistemArmat = true;
      Serial.println(">> COD CORECT -> SE ARMEAZA IN 3 SECUNDE...");
      
      // Numaratoare inversa cu sunet
      for(int i=0; i<3; i++) {
        digitalWrite(PIN_BUZZER, HIGH); delay(100); digitalWrite(PIN_BUZZER, LOW); delay(900);
        Serial.print(". ");
      }
      
      digitalWrite(PIN_LED_VERDE, LOW); // Stingem verde
      digitalWrite(PIN_LED_ROSU, HIGH); // Aprindem rosu (armat)
      Serial.println("\n>> SISTEM ARMAT! Senzorul PIR este acum activ.");
      
    } else {
      // CAZUL 2: Vrem sa DEZARMAM (oprim alarma)
      sistemArmat = false;
      alarmaDeclansata = false; 
      Serial.println(">> COD CORECT -> SISTEM DEZARMAT.");
      
      digitalWrite(PIN_LED_VERDE, HIGH); // Aprindem verde
      digitalWrite(PIN_LED_ROSU, LOW);   // Stingem rosu
      digitalWrite(PIN_BUZZER, LOW);     // Oprim sirena
    }
  } else {
    // Daca codul e gresit
    Serial.println(">> EROARE: Cod gresit! Incearca 1234.");
    // Bip lung de eroare
    digitalWrite(PIN_BUZZER, HIGH); delay(500); digitalWrite(PIN_BUZZER, LOW);
  }
  
  codIntrodus = ""; // Resetam codul tastat
}