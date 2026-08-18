# Analiza fizyki zastosowanej w projekcie

## 1. Zakres analizy

Analiza dotyczy modułów odpowiedzialnych za fizykę rozpadu i generowanie cząstek:

- `UI/DEC/Decay/decaysimulator.cpp`
- `UI/DEC/Decay/betasimulator.cpp`
- `UI/DEC/Decay/betaspectra.cpp`
- `UI/DEC/Decay/ecsimulation.cpp`
- `UI/DEC/Decay/cesimulation.cpp`
- `UI/DEC/Controllers/branchcontroller.cpp`
- `UI/DEC/mainwindow.cpp`

## 2. Model symulacji rozpadu

### 2.1. Losowanie gałęzi rozpadu

W `DecaySimulator::start()` tworzony jest rozkład prawdopodobieństwa na podstawie `branch.intensity`, a następnie losowana jest gałąź rozpadu.

Interpretacja fizyczna:

- założono, że intensywności gałęzi mogą być użyte bezpośrednio jako wagi losowania,
- normalizacja jest wykonywana automatycznie w `DataVector`.

To podejście jest poprawne jako uproszczony model Monte Carlo, o ile w zbiorze wejściowym znajdują się wyłącznie rzeczywiste gałęzie pierwotnego rozpadu radionuklidu.

### 2.2. Rozpad beta-

W `BetaSimulator` i `BetaSpectra` zaimplementowano:

- przestrzeń fazową,
- funkcję Fermiego,
- kilka klas zabronienia przejść,
- eksperymentalne współczynniki kształtu widma.

Model beta- jest koncepcyjnie poprawny: energia elektronu jest losowana z rozkładu budowanego na podstawie funkcji widma.

### 2.3. Wychwyt elektronowy i beta+

W `ECSimulation`:

- najpierw losowane jest, czy dla gałęzi typu EC zajdzie wychwyt elektronowy czy emisja beta+,
- dla EC losowana jest powłoka, z której przechwycono elektron,
- po utworzeniu wakansu uruchamiana jest relaksacja atomowa.

Fizycznie jest to dobry kierunek modelowania, ponieważ rozdziela część jądrową od późniejszych procesów atomowych.

### 2.4. Relaksacja atomowa po EC i konwersji wewnętrznej

W `ECSimulation` i `CESimulation` zaimplementowano:

- promieniowanie charakterystyczne X,
- elektrony Augera,
- przejścia Coster-Kroniga,
- kontrolę liczby dostępnych elektronów w powłokach.

To jest najmocniejszy fizycznie fragment projektu. Struktura algorytmu odpowiada standardowemu obrazowi kaskady relaksacji powłokowej po utworzeniu wakansu.

### 2.5. Emisja gamma i konwersja wewnętrzna

W `DecaySimulator` dla poziomu wzbudzonego losowane jest, czy zajdzie:

- emisja gamma,
- czy konwersja wewnętrzna.

Waga losowania jest budowana z użyciem:

- intensywności gamma,
- całkowitego współczynnika konwersji wewnętrznej.

To odpowiada fizycznemu założeniu, że przejście elektromagnetyczne może zostać zrealizowane przez emisję fotonu albo elektronu konwersji.

### 2.6. Czas rozdzielczy i czas martwy

Kod uwzględnia dodatkowo:

- czas rozdzielczy,
- czas martwy,
- półokres życia poziomu wzbudzonego.

To nie opisuje samej fizyki rozpadu jądrowego, ale modeluje wpływ detektora i akwizycji na rejestrowanie kaskady.

## 3. Co zostało zaimplementowane poprawnie

Za poprawne lub sensowne fizycznie należy uznać:

1. **Rozdzielenie danych jądrowych i atomowych** – schemat rozpadu i relaksacja atomowa są modelowane osobno.
2. **Losowanie zdarzeń Monte Carlo** – dobór gałęzi i przejść jest realizowany probabilistycznie.
3. **Obsługa relaksacji wakansów** – promieniowanie X, Auger i Coster-Kronig są uwzględnione.
4. **Model beta z funkcją Fermiego** – implementacja jest bardziej zaawansowana niż prosty rozkład liniowy.
5. **Obsługa kaskady gamma** – projekt próbuje śledzić zejście poziomu wzbudzonego do stanu podstawowego.

## 4. Uproszczenia i ograniczenia modelu

W kodzie widać także uproszczenia:

- brak jawnego modelowania neutrin,
- brak transportu cząstek w materiale,
- brak geometrii detektora,
- wynik jest listą energii emisji, a nie pełną odpowiedzią układu pomiarowego,
- poprawność zależy od spójności danych zapisanych w bazie.

Takie uproszczenia są akceptowalne dla generatora widm emisyjnych, ale ograniczają zastosowanie projektu do szybkich symulacji źródła, a nie pełnych symulacji detekcyjnych.

## 5. Ogólna ocena fizyczna

Projekt zawiera **sensowną bazę fizyczną** i poprawne ogólne idee modelowania:

- wybór gałęzi rozpadu,
- generację emisji beta,
- obsługę EC,
- relaksację powłokową,
- konkurencję gamma / konwersja wewnętrzna.

Jednocześnie implementacja nie jest w pełni spójna fizycznie i wymaga korekt w kilku miejscach krytycznych, opisanych w osobnym dokumencie weryfikacyjnym.
