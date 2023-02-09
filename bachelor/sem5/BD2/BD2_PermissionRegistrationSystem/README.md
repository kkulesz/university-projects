# BD2_PermissionRegistrationSystem

## Opis założeń

Zakładamy, że nasz system jest częścią większego systemu samoobsługi banku. Nasz projekt obejmuje dział systemu związany z rejestracją uprawnień pracowników i będzie realizowany przy pomocy technologii Java. W firmie można wyróżnić kilka stanowisk takich jak: szef banku, księgowy, programista. Każde z tych stanowisk posiada inny zakres uprawnień. Mogą to być na przykład uprawnienia dostępu, edycji, przeglądu. Zakładamy, że podział na typy uprawnień jest zmienny dlatego jest to odpowiednio uwzględnione w modelu jako encja słownikowa. 
Przykładowy scenariusz: programista wchodzi na stronę samoobsługi banku, gdzie chce sprawdzić dane dotyczące systemu informatycznego; aplikacja wysyła zapytanie do bazy danych, czy dany użytkownik może mieć dostęp do danych danego systemu informatycznego; okazuje się że ma on uprawnienie wiec może mieć dostęp do danych; następnie próbuje edytować wystawioną mu fakturę; po wysłaniu zapytania do bazy danych okazuje się, że nie ma on uprawnień do tego typu operacji. 
