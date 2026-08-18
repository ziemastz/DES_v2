# Dokumentacja projektu DES_v2

Ten katalog zawiera dokumentację techniczną projektu **Decay Energy Spectra (DES)** przygotowaną na podstawie analizy kodu źródłowego.

## Zawartość

- `opis-projektu.md` – pełny opis celu projektu, architektury, przepływu danych i sposobu użycia.
- `analiza-fizyki.md` – opis modelu fizycznego zastosowanego w symulacji rozpadu i generowania cząstek.
- `weryfikacja-rozpadu-i-generacji.md` – weryfikacja poprawności implementacji wraz z listą wykrytych problemów i oceną ich wpływu.

## Zakres analizy

Analiza została wykonana metodą statyczną na podstawie kodu źródłowego znajdującego się głównie w modułach:

- `UI/DEC/Decay`
- `UI/DEC/Models`
- `UI/DEC/Controllers`
- `lib/WrapperENSDF`

W repozytorium nie znaleziono automatycznych testów fizycznych ani testów jednostkowych, dlatego wnioski opierają się na logice implementacji.
