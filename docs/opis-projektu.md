# Pełen opis projektu DES_v2

## 1. Cel projektu

Projekt **DES_v2** to desktopowa aplikacja Qt służąca do:

- importu danych o rozpadach radionuklidów z formatu **ENSDF**,
- zapisu schematów rozpadu do lokalnej bazy danych,
- edycji gałęzi rozpadu i przejść gamma,
- generowania widm energii emitowanych cząstek i promieniowania.

Z opisu w `UI/DEC/main.cpp` wynika, że aplikacja została przygotowana do generowania widm energii dla rozpadu promieniotwórczego, a kolejne wersje rozszerzały obsługę beta, beta+ oraz danych z ENSDF.

## 2. Architektura rozwiązania

Repozytorium ma strukturę projektu Qt typu `subdirs` i składa się z kilku głównych części:

### 2.1. Aplikacja UI

Katalog: `UI/DEC`

Najważniejsze elementy:

- `main.cpp` – uruchomienie aplikacji Qt.
- `mainwindow.cpp/.h` – główne okno, import ENSDF, ładowanie danych, zapis do bazy i uruchamianie symulacji.
- `generatespectrumdialog.cpp/.h` – okno konfiguracji liczby rozpadów, czasu rozdzielczego i czasu martwego.
- `editbranchdialog.cpp/.h` – edycja danych gałęzi rozpadu.
- `editgammadialog.cpp/.h` – edycja przejść gamma.

### 2.2. Warstwa modelu danych

Katalog: `UI/DEC/Models`

Modele opisują fizyczny schemat rozpadu:

- `DecaySchemeModel` – cały schemat dla radionuklidu.
- `BranchModel` – pojedyncza gałąź rozpadu.
- `GammaModel` – przejście gamma wraz z współczynnikiem konwersji wewnętrznej.
- `BetaTransitionModel` – parametry przejścia beta.
- `ECModel` – parametry wychwytu elektronowego i gałęzi beta+.
- `LevelModel`, `NuclideModel` – poziomy energetyczne i dane nuklidów.

### 2.3. Warstwa kontrolerów i baza danych

Katalogi:

- `UI/DEC/Controllers`
- `lib/Database`

Warstwa ta odpowiada za:

- odczyt i zapis danych rozpadu,
- mapowanie rekordów SQL na modele C++,
- pobieranie danych atomowych potrzebnych do relaksacji powłokowej.

Szczególnie ważny jest `BranchController`, który składa pełny model gałęzi na podstawie tabel bazy danych.

### 2.4. Parser ENSDF

Katalog: `lib/WrapperENSDF`

Moduł ten odczytuje rekordy ENSDF i udostępnia dane potrzebne do zbudowania modelu rozpadu:

- rodzaj przejścia,
- intensywności,
- energie poziomów,
- energie beta, alfa i gamma,
- parametry EC/beta+.

## 3. Przepływ danych w aplikacji

1. Użytkownik importuje plik ENSDF.
2. `WrapperENSDF` odczytuje rekordy i udostępnia informacje o rodzicu, córce, poziomach i przejściach.
3. `MainWindow::on_import_ensdf_pushButton_clicked()` buduje w pamięci `DecaySchemeModel`.
4. Dane mogą zostać zapisane do lokalnej bazy przez `BranchController::updateBranches(...)`.
5. Dla wybranego radionuklidu użytkownik uruchamia `GenerateSpectrumDialog`.
6. `DecaySimulator` generuje zdarzenia rozpadu i zapisuje wyniki do plików tekstowych:
   - `*_emittedElectrons.txt`
   - `*_emittedGammas.txt`
   - `*_Tags.txt`

## 4. Sposób generowania widm

Symulacja jest realizowana zdarzeniowo:

- najpierw losowana jest gałąź rozpadu na podstawie intensywności,
- następnie w zależności od typu przejścia generowane są cząstki pierwotne,
- później obsługiwane są emisje gamma, elektrony konwersji, promieniowanie X i elektrony Augera,
- opcjonalnie uwzględniany jest czas rozdzielczy i czas martwy.

Wynikiem nie jest histogram końcowy, lecz lista energii wygenerowanych cząstek przypisanych do numeru zdarzenia.

## 5. Obsługiwane mechanizmy fizyczne

Na podstawie kodu projekt obsługuje:

- rozpad **beta-**,
- wychwyt elektronowy **EC**,
- gałąź **beta+** w ramach rekordu EC,
- emisję **gamma**,
- **konwersję wewnętrzną**,
- relaksację powłokową prowadzącą do emisji:
  - promieniowania X,
  - elektronów Augera,
  - przejść Coster-Kroniga.

Dane o przejściach atomowych są pobierane przez `AtomicDataController`.

## 6. Wejście i wyjście

### Wejście

- plik ENSDF wskazany przez użytkownika,
- dane zapisane w lokalnej bazie SQL,
- parametry symulacji podane w oknie dialogowym.

### Wyjście

Symulator tworzy trzy pliki tekstowe w katalogu roboczym:

- lista energii elektronów,
- lista energii fotonów gamma / promieniowania X,
- lista znaczników opisujących typ emisji.

## 7. Technologie

- C++
- Qt Widgets
- Qt SQL
- własne biblioteki pomocnicze projektu

Konfiguracja budowy znajduje się w:

- `/DES.pro`
- `UI/DEC/DEC.pro`
- `lib/Database/Database.pro`
- `lib/ToolWidget/ToolWidget.pro`
- `lib/WrapperENSDF/WrapperENSDF.pro`

## 8. Budowanie projektu

W repozytorium nie znaleziono gotowych testów automatycznych. Z konfiguracji `.pro` wynika, że standardowy sposób budowy to:

```bash
qmake DES.pro
make
```

## 9. Ograniczenia obecnej wersji

Na podstawie analizy kodu obecna wersja projektu jest wartościowym szkieletem symulatora, ale wymaga dalszej walidacji fizycznej. Najważniejsze ograniczenia:

- brak automatycznych testów,
- brak osobnej dokumentacji fizycznej,
- niepełna zgodność niektórych ścieżek emisji z fizyką rozpadu,
- silne powiązanie poprawności wyników z jakością danych ENSDF i danych atomowych w bazie.
