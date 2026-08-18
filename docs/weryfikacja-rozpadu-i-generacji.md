# Weryfikacja procesu rozpadu radionuklidu i generowania cząstek

## 1. Wniosek końcowy

Proces rozpadu radionuklidu i generowanie cząstek w obecnej wersji projektu są **napisane częściowo poprawnie**, ale **nie można uznać ich za w pełni zweryfikowane fizycznie**. Kod zawiera poprawne elementy modelu Monte Carlo, lecz wykryto także błędy i niespójności, które mogą istotnie zniekształcać wyniki.

## 2. Elementy zgodne z założeniami fizycznymi

### 2.1. Losowanie gałęzi

`DecaySimulator` losuje gałąź na podstawie intensywności. To jest poprawne, jeśli wejściowa lista gałęzi zawiera tylko rzeczywiste kanały rozpadu pierwotnego.

### 2.2. Widmo beta-

`BetaSpectra` implementuje:

- przestrzeń fazową,
- funkcję Fermiego,
- klasy zabronienia,
- dodatkowe współczynniki kształtu.

Sam kierunek implementacji jest prawidłowy i wystarczająco zaawansowany jak na generator widma.

### 2.3. Wychwyt elektronowy i relaksacja powłok

`ECSimulation` oraz `CESimulation` poprawnie modelują ideę:

- utworzenia wakansu,
- dalszej relaksacji przez promieniowanie X,
- emisję Augera,
- przejścia Coster-Kroniga.

To jest ważna i wartościowa część projektu.

## 3. Wykryte problemy krytyczne

### 3.1. Brak generacji cząstek dla rozpadu alfa

**Stan:** błąd funkcjonalny

Gałęzie typu `ALPHA` są:

- importowane z ENSDF,
- zapisywane do modelu,
- zapisywane do bazy,

ale w `UI/DEC/Decay/decaysimulator.cpp` nie ma logiki generującej cząstkę alfa. Symulator obsługuje tylko:

- `BETA-`,
- `EC`,
- gamma / konwersję wewnętrzną.

**Skutek:** dla radionuklidów alfa-promieniotwórczych wyniki symulacji są niepełne lub błędne, ponieważ pierwotna cząstka alfa w ogóle nie jest emitowana.

### 3.2. Błędna generacja energii dla beta+

**Stan:** błąd fizyczny i implementacyjny

W `UI/DEC/Decay/betasimulator.cpp` dla przejścia `EC` konfiguracja widma beta+ korzysta z:

- `branch.ec.betaPlus` przy konfiguracji spektrum,

ale siatka energii do losowania jest budowana z:

- `branch.beta.endpoint_energy_keV`

zamiast z:

- `branch.ec.betaPlus.endpoint_energy_keV`.

**Skutek:** dla beta+ histogram energii jest budowany z niewłaściwego pola i może degenerować się do błędnego rozkładu, w praktyce nawet do energii bliskiej zeru.

To oznacza, że generowanie pozytonów nie zostało zaimplementowane poprawnie.

### 3.3. Brak fotonów anihilacyjnych 511 keV dla beta+

**Stan:** brak ważnego procesu fizycznego

W `ECSimulation`, jeśli zajdzie beta+, do listy elektronów dodawana jest energia pozytonu i znacznik `Beta+`, ale kod nie generuje dwóch fotonów anihilacyjnych po 511 keV.

**Skutek:** widmo fotonowe dla emiterów beta+ jest fizycznie niepełne.

Jeżeli celem projektu jest generowanie widm emitowanych cząstek i fotonów, brak anihilacji jest istotnym brakiem.

### 3.4. Potraktowanie przejść GAMMA/IT jako gałęzi pierwotnych

**Stan:** błąd w logice schematu rozpadu

W `UI/DEC/mainwindow.cpp` podczas importu ENSDF tworzone są także wpisy gałęzi o typie:

- `GAMMA`
- `IT`

gdy poziom nie ma bezpośrednio rozpoznanego przejścia beta, alfa lub EC.

Następnie `DecaySimulator` losuje gałąź z całej listy `decay.branches`.

**Skutek:** przejścia deekscytacyjne mogą zostać potraktowane jak pierwotne kanały rozpadu radionuklidu. To prowadzi do niepoprawnych prawdopodobieństw startowych i może podwójnie liczyć emisje gamma.

To jest jedna z najpoważniejszych niespójności całego modelu.

### 3.5. Dane elektronów konwersji są przypisywane do całej gałęzi, a nie do konkretnego gamma

**Stan:** błąd struktury danych

W `BranchController::getBranches(...)` dane z tabeli `gamma_ce` są pobierane zapytaniem:

```sql
WHERE id_branch = %1
```

i wykonywane jest to wewnątrz pętli po wszystkich przejściach gamma tej samej gałęzi.

W efekcie każde przejście gamma w danej gałęzi dostaje ten sam zestaw danych `conversion_electrons`.

**Skutek:** jeśli gałąź zawiera więcej niż jedno przejście gamma, rozkład elektronów konwersji może zostać przypisany do niewłaściwego przejścia. To zniekształca wybór podpowłoki i energię emitowanych elektronów.

## 4. Problemy średniej wagi i uproszczenia

### 4.1. Korekta odrzutu w widmie beta jest nadpisywana

W `BetaSpectra::config()` i `BetaSpectra::value()` najpierw liczona jest korekta związana z odrzutem jądra, ale później wynik zostaje nadpisany prostszym wzorem.

**Skutek:** fragment bardziej zaawansowanego modelu jest obliczany, ale nie wpływa na wynik końcowy. Nie jest to awaria programu, ale obniża wierność fizyczną modelu.

### 4.2. Brak testów weryfikujących fizykę

W repozytorium nie znaleziono testów jednostkowych ani zestawów referencyjnych porównujących wyniki z ENSDF lub danymi eksperymentalnymi.

**Skutek:** nawet poprawnie wyglądające algorytmy nie są numerycznie potwierdzone.

## 5. Ocena końcowa poprawności

### Ocena ogólna

- **Koncepcja modelu:** dobra
- **Struktura kodu:** dobra
- **Relaksacja atomowa:** dobra
- **Kompletność emisji cząstek:** niepełna
- **Spójność logiki schematu rozpadu:** niewystarczająca
- **Walidacja numeryczna:** brak

## 6. Odpowiedź na pytanie, czy proces został napisany prawidłowo

**Nie w pełni.**

Kod zawiera poprawne podstawy fizyczne, ale nie można uznać, że:

- proces rozpadu radionuklidu,
- generowanie cząstek,
- oraz przejście od danych ENSDF do kompletnego zdarzenia fizycznego

zostały zaimplementowane całkowicie prawidłowo.

Najważniejsze powody:

1. brak obsługi emisji alfa,
2. błędna ścieżka beta+,
3. brak fotonów anihilacyjnych,
4. mieszanie gałęzi pierwotnych z przejściami deekscytacyjnymi,
5. niejednoznaczne przypisywanie danych konwersji wewnętrznej do przejść gamma.

## 7. Rekomendowana kolejność poprawek

1. Rozdzielić gałęzie pierwotnego rozpadu od przejść gamma / IT.
2. Dodać pełną obsługę rozpadu alfa w `DecaySimulator`.
3. Naprawić generację beta+ w `BetaSimulator`.
4. Dodać fotony anihilacyjne 511 keV dla beta+.
5. Przebudować model danych `gamma_ce`, aby dane były przypisane do konkretnego przejścia gamma.
6. Dodać testy porównujące wyniki symulacji z wybranymi danymi referencyjnymi.
