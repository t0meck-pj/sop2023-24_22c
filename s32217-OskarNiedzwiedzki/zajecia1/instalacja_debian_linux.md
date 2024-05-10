# Instalacja debiana na maszynie wirtualnej praktyczny tutorial

## Wymogi
- Komputer lub też inne urządzenie z możliwością bootowania obrazów
- [Obraz Debiana](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-12.5.0-amd64-netinst.iso)
- [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
- [Spotify](https://www.spotify.com/pl/download/windows/) (Żeby nie zasnąć)

## Virtual Box
- Odpalamy VB
- Tworzymy nową maszynę 
- [Klikamy Tryb Eksprerta](#tryb-eksperta)
- Wybieramy sobie nasz nowo pobrany obraz oraz nadajemy mu śmieszną nazwę
- Wybieramy sobie katalog na naszą maszynkę, należy pamiętać o wystarczającej ilości miejsca
- Jako profesjonaliści zaznaczamy ```Skip Unattended Installation``` -> Pozwoli to nam kontrolować każdy szczegół naszej instalacji

### Tryb Eksperta
Proponowane tutaj ustawienia można dostosować do swoich potrzeb
#### Hardware
- ```RAM: 4096MB```
- ```Processors: 4```
- [x] ```Enable EFI``` -> Wymagane dla niektórych systemów operacyjnych
#### Hard Disk
- ```Ścieżka jak ścieżka byleby było miejsce```
- ```Rozmiar: 20GB``` -> 10GB to minimum wymagane, więcej miejsca można sobie zarezerwować stwierdzimy, że potrzebujemy
- ```Hard Disk File Type and Variant: VDI``` -> [Więcej opcji](https://www.virtualbox.org/manual/ch05.html#vdidetails)
- [x] ```Pre-allocate Full Size``` -> miejsce zostanie zarezerwowane przez VB przy tworzeniu maszyny    
Możemy także wybrać istniejący dysk wirtualny albo wcale go nie dodawać

Klikamy zakończ i zaczynamy zabawę   

## Instalacja systemu
Gdy już utworzymy obraz w maszynie wirtualnej i wszystko jest gotowe, możemy przejść do instalacji samego systemu

### Menu
Pierwsze co nam się ukaże to menu, z którego do wyboru mamy kilka opcji:  
- ```👎 Graphical Install``` -> Instalacja z interfejsem graficznym, wygodna dla początkujących
- ```👎 Install``` -> Instaluje nam system z podstawowymi ustawieniami (my chcemy sobie podrasować naszego debiana, więc tego unikamy)
- [```👍 Advanced Install```](#advanced-install) -> Opcja dla prawdziwych wyjadaczy, naturalnie że chcemy mieć kontrolę nad wszystkim
-  ```👍 Accessible dark contrast installer menu``` -> ciemne menu dla kretów
-  ```🎶 Install with speech synthesis``` -> opcja dla niewidzących, analfabetów (odkrywają ją metodą prób i błędów) oraz słuchaczy polskiego rapu
-  ```🙏 C``` -> odpala konsolkę -> [```Komendy```](https://www.gnu.org/software/grub/manual/legacy/Command_002dline-and-menu-entry-commands.html)
-  ```🙏 E``` -> Opcje bootowania
#### Advanced Install
- [```👍 Graphical expert install```](#installer-menu-instalacja-graficzna) -> zaawansowana instalacja z prostym interfejsem
- ```🙏 Graphical rescue mode``` -> Bootuje nas do chwilowego systemu, pozwala zdiagnozować i usunąć problemy związane z systemem min. problemy z siecią, czy też reset hasła
- ```👎 Graphical automated install``` -> Automatyczna instalacja, instaluje system przy użyciu pliku konfiguracji, możemy go zmienić wpisując w opcjach bootowania (\*Click* E) ```debian-installer/add-kernel-opts preseed/file=/path/to/.cfg```, gdzie ```/path/to/.cfg``` zamieniamy na ścieżkę z plikiem konfiguracji. Opcja bardzo wygodna do szybkiej instalacji systemu z predefiniowanymi zaawansowanymi ustawieniami -> [```Jak pisać piliki konfiguracji```](https://www.debian.org/releases/stable/amd64/apb.en.html)
- ```👍 Expert install``` -> To samo co ```Graphical expert install```, ale bez interfejsu, wszystko wpisujemy do konoslki, dobra opcja jeśli z jakiegoś powodu mamy problemy z grafiką
- ``` 🙏 Rescue mode``` -> To samo co ```Graphical rescue mode```, ale w konsolce
- ```👎 Automated install``` -> To samo co ```Graphical automated install```, ale w konsolce
## Installer menu (Instalacja Graficzna)
### Troubleshooting
Jeśli instalacja graficzna z jakiegoś powodu nam nie działa, to możemy wybrać instalację bez interfejsu w konsoli.   
Jeśli wyskakuje nam dziwny błąd czasami, że nie można uruchomić instalatora:   
- ```Przed Kliknięciem w opcję wciskamy klawisz E (Select Edit)```
- ```Dodajemy na końcu linijki zaczynającej się od linux``` -> ```fb=false``` Opcja ta wyłącza nam framebuffer i przynajmniej w moim przypadku sprawiła, że udało mi się poprawnie uruchomić instalator
### Opcje
Wystarczy kliknąć w opcję, żeby zobaczyć jej dalsze ustawienia
- [```Select a language```](#select-a-language)-> wybieramy sobie język instalatora, wybrany język przy okazji będzie też podstawowym językiem w naszym systemie
- ```Access software for a blind person using a braille display``` -> opcja dla niewidomych, nie będę się w nią zagłębiał
- ```Configure the speech synthesizer voice``` -> ustawienia syntezatora mowy instalatora, także nie będę się zbytnio zagłębiał w nie
- [```Configure the keyboard```](#configure-the-keyboard) -> Pozwala nam wybrać jakiego zestawu znaków będziemy używać
- [```Detect and mount installation media```](#detect-and-mount-installation-media) -> Pozwala nam wybrać skąd nasz instalator ma wziąć sobie potrzebne mu pliki. W przypadku instalacji przy użyciu Virtual Boxa opcja która nam się ukaże jest zależna od ustawień Virtual Boxa i można je sobie zmienić ```Standardowo jest to wirtualne USB, ale można sobie zmienić na CD/DVD```
- [```Change debconf priority```](#change-debconf-priority) -> Czasami przy instalacji pakietów będziemy mieli opcje do wyboru, zmiana tego parametru sprawi, że będziemy mieli dostęp do bardzo wrażliwych opcji ```Zalecane dla najbardziej zaawansowanych```
- ```Check the integrity of installation media``` -> Przed instalacją możemy sprawdzić, czy wszystko jest OK ```Nie ma m.in wadliwych lub nieoryginalnych plików```
- ```Save debug logs``` -> Pozwala nam zapiać logi z naszego instalatora. Możemy je przesłać na:
   + Serwer
   + Nośnik danych (USB, Płyta CD/DVD)
   + Dyskietkę !!   
W tę opcję zbytnio się nie zagłębiam, bo nie mam potrzeby zapisywać logów
- ```Execute a shell``` -> Konsolka ```Dostępne komendy można dostać wpisując help```   
W konsoli możemy ustawić najbardziej zaawansowane ustawienia, mamy dostęp do plików naszego instalatora. Niestety wymaga dużej wiedzy i doświadczenia, więc nie zagłębiałem się dalej
- ```Abort the installation``` -> Przerywa instalację, bezpieczny sposób na przerwanie instlacji   

Kiedy wybierzemy sobie nasze podstawowe ustawienia, możemy kliknąć w ```Load installer components from installation media```. To sprawi, że nasz instalator będzie mógł zainstalować podstawowy system. Zanim przejdziemy dalej możemy wybrać sobie [```dodatkowe komponenty instalatora do instalacji```](#load-installer-compnent-from-installation-media)   
Po wybraniu dodatkowych komponentów będziemy mieli dostęp do dodatkowych opcji (oprócz tych które już były)   
- ```Detect network hardware``` -> Klikamy i instalator automatycznie nam wyszuka urządzenie, które połączy się z siecią (kartę sieciową w większości przypadków)
- [```Configure the network```](#configure-the-network) ->  Konfiguracja i połączenie z siecią
- [```Configure the clock```](#configure-the-clock) -> Tutaj możemy skonfigurować zegar systemowy, konfiguracja odbywa się prawie automatycznie, nie możemy sobie wybrać serwera NTP :(
- ```Detect Disks``` -> Automatycznie wykrywa dyski
- [```Partition disks```](#partition-disks) -> Partycjonowanie dysków i przydzielanie miejsca na poszególne komponenty
- [```Install the base system```](#install-the-base-system) -> Jak sama nazwa wskazuje instaluje bazowy system
- [```Configure the package manager```](#configure-the-package-manager) -> Konfiguruje package managera ```apt```, pozwala także na wybranie nakładki graficznej
- [x] ```Install the GRUB boot loader``` -> [```GRUB```](https://en.wikipedia.org/wiki/GNU_GRUB) -> Bootloader dla systemów opartych na linuxie. Ceniony za elastyczność i kompleksowość 
- [x] ```Finish the installation``` -> Wielki test, czy zainstalowaliśmy linuxa według naszych preferencji
- [```Ups coś nie dziala```](#problemy)
- [```Koniec```](#koniec) 


#### Select a language
- [x] **English**
  + [x] Select your location -> **Other**
  + [x] Select your location -> **Europe**  
  + [x] Select your location -> **Poland**
- [x] Configure locales -> **United States** -> Od parametru locale zależy między innymi separator dziesiętny, w Polsce jest to przecinek, w Stanach kropka. Ze względu na przyzwyczajenia wybrałem Stany Zjednoczone
- Po wybraniu locales pojawia nam się menu, pozwalające pobrać nam dodatkowe *locales*. Można tam znaleźć między innymi ```pl_PL```. Ja zbytnio nie potrzebuję polskiego w moim systemie, więc sobie pominąłęm tę opcję klikając ```Continue```   
[```Powrót```](#opcje)

#### Configure the keyboard
- [x] Polish   
[```Powrót```](#opcje)

#### Detect and mount installation media
- [x] usb-storage   
[```Powrót```](#opcje)
#### Change debconf priority
- [x] medium -> Nie chcę przejmować się zbyt zaawansowanymi opcjami przy instalacji pakietów   
[```Powrót```](#opcje)
#### Load installer compnent from installation media
Opiszę tutaj tylko te najciekawsze z mojego punktu widzenia
- [x] choose-mirror -> Pozwala nam wybrać *mirror* do instalacji naszego systemu
- [x] openssh-client-udeb -> Pozwala nam korzystać z ```ssh``` m.in do pobierania plików
- [x] network-console -> Pozwala nam na instalację systemu zdalnie przy użyciu ```ssh```
- [x] load-media -> Pozwala na instalację komponentów instalatora z nośnika zewnętrznego
- [x] rescue-mode -> Pozwala nam na załadowanie konkretnej partycji i odpalenie na niej tymczasowego systemu w trybie ```rescue-mode```. Użyteczne, jeśli jedna z partycji odmawia nam posłuszeństwa   
Oraz kilka innych, które można sobie sprawdzić w internecie   
[```Powrót```](#opcje)

#### Configure the network
- [x] Tutaj wybrałem autokonfigurację, jeśli mamy taką potrzebę, możemy manualnie podpiąć się do hosta poprzez adres IPV4
- [x] Hostname -> nazwa hosta, tak będziemy widoczni w ustawieniach naszego routera -> ```debian-install```
- [x] Domain name -> nazwa domeny (np.: .pl, .com., .de) -> ```Tutaj zostawiłem puste, nie mam potrzeby tego ustawiać```   
[```Powrót```](#opcje)

#### Configure the clock
- [x] Set the clock using NTP -> ```Yes```
- [x] Select your time zone -> ```Europe/Warsaw```   
[```Powrót```](#opcje)
#### Partition disks
Przed rozpoczęciem partycjonowania mamy do wyboru kilka opcji z pomocą -> ```guided```. Możemy wybrać ```Manual```, żeby mieć nad wszystkim kontrolę, jednak lepiej jest wybrać ```guided``` jeśli stawiamy zwykły system dla nas do użytku, gdyż automatycznie zostaną utworzone wszystkie najważniejsze partycje. W innym wypadku musimy stworzyć je sami, w tym partycję EFI (do bootowania systemu), roota oraz inne.
- [x] Partitioning method -> [```Guided - use entire disk and set up LVM```](#guided)
- [x] Manual -> [```Manual```](#manual)   
[```Powrót```](#opcje)
##### Guided
- [x] Wybieramy nasz dysk i tworzymy z niego nową partycję
- [x] Partitioning scheme -> ```Separate /home, var and /tmp partitions```
- [x] Amount of volume group for guided partitioning -> ```100%``` -> Wartość tę możemy zmienić, jeśli planujemy w przyszłości ręcznie rozszerzać partycje za pomocą narzędzia [```mount```](https://manpages.ubuntu.com/manpages/jammy/pl/man8/mount.8.html)
- [x] Możemy zmienić rozmiary partycji oraz ich systemy plików wybierając je enterem, więcej opcji opisanych jest w [```Manual```](#manual)   
[```Powrót```](#partition-disks)

##### Manual
- [x] Wybieramy nasz dysk i tworzymy z niego nową partycję
  + Configure software RAID -> [RAID](https://pl.wikipedia.org/wiki/RAID) -> Nie wybieram tej opcji, ponieważ mam tylko jeden dysk twardy
  + Configure the Logical Volume Manager -> [LVM](https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux))
  + Wybieramy sobie dysk z którego chcemy stworzyć nową grupę (Volume Group)
  + Możemy sobie stworzyć wiele wolumenów wybierając opcję ```Create logical volume```, wybieramy na której grupie (Volume Group) chcemy stworzyć wolumen
  + Wpisujemy sobie rozmiar naszego nowego wolumenu
- ```Create logical group``` -> ```Create logical volume (nazwa)``` -> ```(Rozmiar)MB```
- [x] Configure encrypted volumes -> Tworzy zaszyfrowane wolumeny, pomijam
- [x] Configure iSCISI volumes -> [iSCSI](https://pl.wikipedia.org/wiki/ISCSI) -> Dyski sieciowe  
Wybieramy nasz nowo utworzony LV, do wyboru mamy kolejne opcje:
- ```Use As``` -> [```Systemy plików```](https://www.kingston.com/en/blog/personal-storage/understanding-file-systems) [```Więcej systemów plików```](https://en.wikipedia.org/wiki/List_of_file_systems)
   + [x] W przypadku linuxa interesują nas głównie systemy ```Ext```
- Mount point -> możemy sobie wybrać czy nas LV będzie np. rootem, albo ```/home```
- Mount options -> Opcje naszego wolumenu
   + Ciekawe opcje:
   + ```ro``` -> ```read-only``` -> wolumen jest tylko do odczytu, nie można nic zapisywać na nim
   + ```noexec``` -> nie pozwala na wykonywanie żadnych plików binarnych, skryptów
   + [```Więcej opcji i ich opis```](https://manpages.debian.org/stretch/mount/mount.8.en.html) -> ```Ctrl+F``` i szukamy sobie
- Label -> ```root``` -> etykieta naszego wolumenu ```tak jak w windowsie np. C:```
- Reserved blocks -> ```10%```-> procent wolumenu zarezerwowany dla roota (super-user)
- Typical usage -> ```standard``` -> wielkość klastra informacji, większe klastry mogą sprawiać, że jeżeli nasz dysk typowo przechowuje bardzo duże pliki, to operacje na nich będą szybsze, minimalizuje także defragmentację dysku. Niestety jeśli nasze pliki będą miały małe rozmiary, a rozmiar klastra będzie duży, będzie to powodowało znaczną defragmentację dysku, przez co odczujemy znaczne braki miejsca po czasie, pomimo że nasze pliki ważą mało
- [x] Swap space ->```1.5GB``` -> [```Partycja Wymiany```](https://pl.wikipedia.org/wiki/Partycja_wymiany), możemy dodać sobie tę partycję, na niej będą przechowywane dane w przypadku, gdy zabraknie RAMu. Zadania z mniejszym priorytetem także są zapisywane na partycji wymiany.
- [x] Partycje które musimy utworzyć, żeby skonfigurować poprawnie system:
  + [x] Root ```/```
  + [x] EFI ```Bootowanie systemu```    
[```Powrót```](#partition-disks)
#### Install the base system
- [x] Kernel to install -> ```linux-image-6.1.0-18-amd64``` -> Kernele mogą się różnić w zależności od obrazu, którego używamy
- [x] Drivers to include:
   + [x] generic -> ```Wszystkie sterowniki```
   + targeted -> ```Minimum do działania systemu```   
[```Powrót```](#opcje)
#### Configure the package manager
- [x] http -> Poland -> task.pg.gda.pl
   + Możemy także wybrać ```https```, lub [```Serwer FTP```](https://tldp.org/HOWTO/Polish-HOWTO-2.html)   
Wszystko nam się elegancko pobierze, wyskoczy też kilka błędów na temat serwerów, jednak nie wiem jak sprawić, żeby się nie pojawiły. Serwery ftp niestety też mają trochę problemy i nie udało mi się z nich skorzystać, dlatego polecam  zwykłe ```http```
- ```web server``` -> utility do zarządzania serwerem
- [x] ```SSH Server``` -> narzędzia i pochodne ```ssh```
- [x] ```standard system utilities``` -> Tak    
[```Powrót```](#opcje)
##### Nakładki Graficzne
- Debian desktop environment
- GNOME
- [x] Xfce -> Jestem biedny w miejsce na dysku
- GNOME Flashback
- KDE Plasma -> Jestem bogaty w miejsce na dysku
- Cinnamon
- MATE
- LXDE
- LXQt   
Wszystkie elegancko opisane ze screenami możemy znaleźć [```Tutaj```](https://debian-handbook.info/browse/stable/sect.graphical-desktops.html). Wybieramy sobie nasz ulubiony   
[```Powrót```](#opcje)

### Problemy
- Nie da się zalogować (nie pamiętam hasła do roota)
  + W bootloaderze klikamy 'E'
  + na koncu linijki z ```linux``` dodajemy ```init=/bin/bash```
  + ```Ctrl + X```
  + ```mount -n -o iforgor,rw /```
  + passwd -> ustawiamy haslo
  + ```Ctrl + Alt + Del```
  + (Opcjonalnie) Możemy odpalić obraz naszego debiana w ```Rescue mode```
- Więcej można dodać tutaj
  
# Koniec
Mam nadzieję, że moja dokumentacja spełnia swoje potrzeby. Bardzo dużo czasu zajęło mi sprawdzanie rzeczy, większość testowałem ręcznie, tudzież korzystając z oficjalnej dokumentacji debiana. Nie chciałem kopiować masy tekstu, dlatego do niektórych rzeczy są dodane linki do oficjalnej dokumentacji, które do najmniejszego szczegółu opisują wszystko. Mam nadzieję także, że ładnie wygląda i jest użyteczna.    
Ogólnie bardzo wiele nauczyłem się pisząc tę dokumentację. Kolejne etapy instalacji systemu są bardziej dla mnie zrozumiałe, rozumiem także poszczególne etapy konfiguracji. Pisanie tego zmusiło mnie także do przeczytania masy dokumentacji, co jeszcze bardziej pogłębiło moją wiedzę

   