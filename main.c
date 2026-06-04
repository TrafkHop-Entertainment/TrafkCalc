/*
 * ============================================================
 *  TrafkCalc – TrafkVerse Calculator
 *  All Formulars from MagicBook, UseCases and BasicsOfTheVerses
 *
 *  © 2026 TrafkHop Entertainment™
 * ============================================================
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

/* ── Prototypen ─────────────────────────────────────────── */
float NormalspellRequiredLevels(float volume_cm3, float attrSum, int hasHours, float hours);
float ManaRegenPerDay(float maxLevels);
float BodyManaEnhancement(float levelsInBody);
float AuraThickness_cm(float totalLevels);
float AnamMaxSpeed(float volume_m3);
float AnamSpellLevel(float manaVolume_cm3, float pushSpeed, int layers, int hasTime, float hoursOpen);
float PotionMaxDose(float baseLevels);

void  Separator(void);
void  PrintMenu(void);
float ReadFloat(const char *prompt);
int   ReadInt(const char *prompt);

void  HandleNormalSpell(void);
void  HandleManaRegen(void);
void  HandleBodyEnhancement(void);
void  HandleAura(void);
void  HandleAnamSpeed(void);
void  HandleAnamSpell(void);
void  HandlePotion(void);

/* ── Main ───────────────────────────────────────────────── */

int main(void)
{
    printf("\n==========================================\n");
    printf("   TrafkCalc – TrafkVerse Calculator\n");
    printf("   © 2026 TrafkHop Entertainment™\n");
    printf("==========================================\n");

    int choice = -1;
    while (choice != 0) {
        Separator();
        PrintMenu();
        scanf("%d", &choice);
        Separator();

        switch (choice) {
            case 1: HandleNormalSpell();     break;
            case 2: HandleManaRegen();       break;
            case 3: HandleBodyEnhancement(); break;
            case 4: HandleAura();            break;
            case 5: HandleAnamSpeed();       break;
            case 6: HandleAnamSpell();       break;
            case 7: HandlePotion();          break;
            case 0: printf("  Tschüss!\n");  break;
            default: printf("  Ungültige Eingabe.\n");
        }
    }
    return 0;
}

/* ── Hilfsfunktionen ────────────────────────────────────── */

void Separator(void)
{
    printf("\n──────────────────────────────────────────\n\n");
}

void PrintMenu(void)
{
    printf("  [1]  Normal-Zauber  – Mana-Kosten (LE)\n");
    printf("  [2]  Mana-Regen     – LE/Tag\n");
    printf("  [3]  Körper-Enhancement – Prozent\n");
    printf("  [4]  Aura-Dicke     – cm\n");
    printf("  [5]  Anam-Maximalgeschwindigkeit\n");
    printf("  [6]  Anam-Zauber    – LE-Kosten (Rift)\n");
    printf("  [7]  Trank-Überdosis-Grenze\n");
    printf("  [0]  Beenden\n\n");
    printf("Wahl: ");
}

float ReadFloat(const char *prompt)
{
    float val;
    printf("  %s: ", prompt);
    scanf("%f", &val);
    return val;
}

int ReadInt(const char *prompt)
{
    int val;
    printf("  %s: ", prompt);
    scanf("%d", &val);
    return val;
}

/* ── Formeln ────────────────────────────────────────────── */

/*
 * Normal-Zauber Kosten (MagicBook)
 *   Cost (LE) = Volume (cm³) × ( Summe(Attribut-Multiplikatoren) + Stunden )
 *
 * Stunden sind OPTIONAL – nur bei Dauerzaubern mit anhaltender Wirkung
 * (z. B. Luck-Boost, Heilung über Zeit), NICHT bei physischen Zaubern.
 * Stunden werden zur Summe ADDIERT (nicht multipliziert).
 */
float NormalspellRequiredLevels(float volume_cm3, float attrSum, int hasHours, float hours)
{
    float sum = attrSum;
    if (hasHours)
        sum += hours;
    return volume_cm3 * sum;
}

/*
 * Mana-Regeneration (MagicBook)
 *   10 LE pro 24h ("1 day per 10 Levels")
 *   Gibt die Regen-Rate zurück und gibt Zusatzinfos aus.
 */
float ManaRegenPerDay(float maxLevels)
{
    float regenPerDay = 10.0f;
    float daysToFull  = maxLevels / regenPerDay;
    printf("  Regen-Rate : %.2f LE/Tag\n", regenPerDay);
    printf("  Tage bis voll (%.0f LE): %.1f Tage\n", maxLevels, daysToFull);
    return regenPerDay;
}

/*
 * Körper-Enhancement durch Mana (MagicBook)
 *   Enhancement (%) = Level ÷ 10
 */
float BodyManaEnhancement(float levelsInBody)
{
    return levelsInBody / 10.0f;
}

/*
 * Aura-Dicke (MagicBook)
 *   1 cm / 1.000 LE  –  Beispiel: 50 LE → 0,05 cm
 */
float AuraThickness_cm(float totalLevels)
{
    return totalLevels / 1000.0f;
}

/*
 * Anam-Maximalgeschwindigkeit vor Explosion (MagicBook)
 *   MaxSpeed = 5 m/s × volume^(-0.1)   (volume in m³)
 *   Beispiel: 5 × 5^(-0.1) ≈ 4,2567 m/s
 */
float AnamMaxSpeed(float volume_m3)
{
    float result = -1.0f;
    if (volume_m3 <= 0.0f)
        printf("  Fehler: Volumen muss > 0 sein.\n");
    else
        result = 5.0f * powf(volume_m3, -0.1f);
    return result;
}

/*
 * Anam-Zauber / Rift-Kosten (MagicBook)
 *   LE = ManaVolumen (cm³) × (
 *          1.1            – Umwandlung Mana → Anam
 *        + pushSpeed      – m/s
 *        + layers         – Ziel-Layer (1 = gleiche Ebene, -1 = innen, 2 = außen, ...)
 *        + 2              – nur wenn Zeitobjekt als Ziel
 *        + hoursOpen      – Stunden offen
 *   )
 */
float AnamSpellLevel(float manaVolume_cm3, float pushSpeed,
                     int layers, int hasTime, float hoursOpen)
{
    float timeCost = hasTime ? 2.0f : 0.0f;
    float sum      = 1.1f + pushSpeed + (float)layers + timeCost + hoursOpen;
    return manaVolume_cm3 * sum;
}

/*
 * Trank-Überdosis-Grenze (UseCases)
 *   Overdose = Basis-LE × 3
 *   Nur aktive Tränke zählen; auslaufende Effekte nicht mehr.
 */
float PotionMaxDose(float baseLevels)
{
    return baseLevels * 3.0f;
}

/* ── Menü-Handler ───────────────────────────────────────── */

void HandleNormalSpell(void)
{
    float volume = ReadFloat("Volumen des Zaubers (cm³)");

    printf("\n  Attribute eingeben (Multiplikator-Wert, 0 zum Beenden):\n");
    printf("  Beispiele: Antigravity=9.81 | Push=m/s | Luck=Prozent | Erase=10000000\n");
    printf("  Soul Activated=1.05 | Soul Activated+=10 | Glow=1.1\n\n");

    float attrSum = 0.0f;
    for (int i = 0; i < 255; i++) {
        float a;
        printf("  Attribut %d (0 = fertig): ", i + 1);
        scanf("%f", &a);
        if (a == 0.0f) break;
        attrSum += a;
    }

    printf("\n  Ist das ein Dauerzauber mit anhaltender Wirkung?\n");
    printf("  (z.B. Luck-Boost, Heilung – NICHT bei physischen Zaubern)\n");
    int hasHours = ReadInt("Stunden relevant? (1=ja / 0=nein)");

    float hours = 0.0f;
    if (hasHours)
        hours = ReadFloat("Dauer (Stunden, z.B. 0.5 fuer 30min)");

    float cost = NormalspellRequiredLevels(volume, attrSum, hasHours, hours);
    printf("\n  ➜ Benötigte Mana-Level: %.4f LE\n", cost);

    if (hasHours)
        printf("  [Formel: %.2f cm³ × (%.4f Attr + %.2f h) = %.4f LE]\n",
               volume, attrSum, hours, cost);
    else
        printf("  [Formel: %.2f cm³ × %.4f Attr = %.4f LE]\n",
               volume, attrSum, cost);
}

void HandleManaRegen(void)
{
    float max = ReadFloat("Dein Mana-Höchstwert (LE)");
    Separator();
    ManaRegenPerDay(max);
}

void HandleBodyEnhancement(void)
{
    float levels = ReadFloat("Mana-Level im Körper (LE)");
    float pct    = BodyManaEnhancement(levels);
    printf("\n  ➜ Körper-Enhancement: +%.2f %%\n", pct);
    if (pct >= 100.0f)
        printf("  ➜ Körper ist doppelt so stark/schnell/präzise wie ohne Mana.\n");
    if (levels >= 1000000.0f)
        printf("  ➜ Alterung kommt praktisch zum Stillstand.\n");
}

void HandleAura(void)
{
    float levels = ReadFloat("Gesamt-Mana-Level (LE)");
    float cm     = AuraThickness_cm(levels);
    printf("\n  ➜ Aura-Dicke: %.4f cm\n", cm);
    printf("  [Formel: %.0f LE ÷ 1.000 = %.4f cm]\n", levels, cm);
}

void HandleAnamSpeed(void)
{
    float vol = ReadFloat("Anam-Volumen (m³)");
    float spd = AnamMaxSpeed(vol);
    if (spd > 0.0f) {
        printf("\n  ➜ Maximale Geschwindigkeit vor Explosion: %.4f m/s\n", spd);
        printf("  [Formel: 5 × %.4f^(-0.1) = %.4f m/s]\n", vol, spd);
    }
}

void HandleAnamSpell(void)
{
    float vol   = ReadFloat("Mana-Volumen für Umwandlung (cm³)");
    float speed = ReadFloat("Push-Geschwindigkeit des Anam (m/s)");

    printf("\n  Ziel-Layer (laut MagicBook):\n");
    printf("   1 = gleiche Ebene          (Minimum)\n");
    printf("  -1 = eine Ebene nach innen  (tiefer im Bubble-Stack)\n");
    printf("   2 = eine Ebene nach außen\n");
    printf("  usw. (kein 0)\n");
    int   layers  = ReadInt  ("Layer-Ziel");
    int   hasTime = ReadInt  ("Zeitobjekt als Ziel? (1=ja / 0=nein)");
    float hours   = ReadFloat("Stunden offen bleiben");

    float cost = AnamSpellLevel(vol, speed, layers, hasTime, hours);
    printf("\n  ➜ Anam-Zauber Kosten: %.4f LE\n", cost);
    printf("  [Formel: %.2f × (1.1 + %.2f m/s + %d Layer%s + %.2f h) = %.4f LE]\n",
           vol, speed, layers, hasTime ? " + 2 Zeit" : "", hours, cost);
}

void HandlePotion(void)
{
    float base  = ReadFloat("Basis-LE des Charakters");
    float limit = PotionMaxDose(base);
    printf("\n  ➜ Maximale aktive Trank-Level gleichzeitig: %.2f LE\n", limit);
    printf("  [Formel: %.0f LE × 3 = %.2f LE]\n", base, limit);
    printf("  (Auslaufende Effekte zählen nicht mehr dazu!)\n");

    printf("\n  Aktive Tränke berechnen? (1=ja / 0=nein): ");
    int check;
    scanf("%d", &check);
    if (check) {
        float total = 0.0f;
        int   n     = ReadInt("Anzahl aktiver Tränke");
        for (int i = 0; i < n; i++) {
            char buf[48];
            sprintf(buf, "Level von Trank %d", i + 1);
            total += ReadFloat(buf);
        }
        printf("\n  Summe aktiver Trank-Level: %.2f LE\n", total);
        if (total > limit)
            printf("  ➜ ÜBERDOSIS! (%.2f LE über Grenze)\n", total - limit);
        else
            printf("  ➜ Sicher. (%.2f LE Spielraum)\n", limit - total);
    }
}
