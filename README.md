# Sistem de Alarmă cu Arduino 🚨

Acesta este un proiect DIY de securitate bazat pe Arduino Uno. Sistemul folosește un senzor de mișcare (PIR) pentru a detecta intrușii și o tastatură matricială pentru armare/dezarmare cu cod PIN.

## 📸 Poze Proiect
*(Aici vor apărea pozele încărcate de tine în repository)*

## 🛠 Componente Folosite
* **Placă:** Arduino Uno
* **Senzori:** Senzor de mișcare PIR (HC-SR501)
* **Input:** Tastatură Matricială 4x4
* **Output:**
    * Buzzer (Sirenă)
    * LED Roșu (Alarmă / Armat)
    * LED Verde (Siguranță / Dezarmat)
* Rezistențe 220 Ohm, Breadboard și fire.

## 🔌 Schema de Conectare (Pini)

| Componentă | Pin Arduino | Note |
| :--- | :--- | :--- |
| **Senzor PIR** | Pin 12 | Firul de mijloc (galben) |
| **Buzzer** | Pin 11 | Polul Pozitiv (+) |
| **LED Verde** | Pin 10 | Indică sistem dezarmat |
| **LED Roșu** | Pin 13 | Indică alarmă activă |
| **Tastatură (Rânduri)** | 9, 8, 7, 6 | De la stânga la dreapta |
| **Tastatură (Coloane)** | 5, 4, 3, 2 | De la stânga la dreapta |

## ⚙️ Cum Funcționează

### 1. Stare Inițială (Safe)
* Sistemul pornește dezarmat.
* **LED-ul Verde** este aprins.
* Senzorul de mișcare este ignorat.

### 2. Armarea Sistemului
* Se introduce codul secret: `1234` (default).
* Se apasă tasta `#` (Enter).
* Sistemul oferă **3 secunde** timp de ieșire (LED-urile clipesc).
* După armare, **LED-ul Roșu** rămâne aprins.

### 3. Declanșarea Alarmei
* Dacă senzorul PIR detectează mișcare în timp ce sistemul este armat:
    * Buzzer-ul începe să sune intermitent.
    * Pe Monitorul Serial apare mesajul `!!! MISCARE DETECTATA !!!`.

### 4. Dezarmarea (Oprirea)
* Pentru a opri alarma, se introduce din nou codul `1234` urmat de `#`.
* Sistemul revine la starea sigură (LED Verde).

---
*Proiect realizat în 2024.*
