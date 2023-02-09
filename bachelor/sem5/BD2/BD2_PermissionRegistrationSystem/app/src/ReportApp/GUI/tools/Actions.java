package ReportApp.GUI.tools;

public enum Actions {
    POTWIERDZENIE_FAKTURY,WYPELNIENIE_DOKUMENT, WYSLANIE_DOKUMENTU_DO_URZEDU,
    WYKONANIE_PRZELEWU,ZAKUP_NA_POTRZEBY_FIRMY,USUNIĘCIE_KONTA_UŻYTKOWNIKA,DODANIE_KONTA_UŻYTKOWNIKA,
    ZAWIESZENIE_KONTA_UŻYTKOWNIKA,ZARAWCIE_UMOWY_Z_KLIENTEM,PRZEKAZANIE_PRODUKTU_KLIENTOWI,
    PRZEPROWADZENIE_SPOTKANIA_Z_KANDYDATEM,PODPISANIE_UMOWY_Z_NOWYM_PRACOWNIKIEM,
    AWANS_PRACOWNIKA,ZWOLNIENIE_PRACOWNIKA,PODWYŻKA_PENSJI_PRACOWNIKA;


    static public Actions intToAction(int number){
        switch (number){
            case 0:
                return POTWIERDZENIE_FAKTURY;
            case 1:
                return WYPELNIENIE_DOKUMENT;
            case 2:
                return WYSLANIE_DOKUMENTU_DO_URZEDU;
            case 3:
                return WYKONANIE_PRZELEWU;
            case 4:
                return ZAKUP_NA_POTRZEBY_FIRMY;
            case 5:
                return USUNIĘCIE_KONTA_UŻYTKOWNIKA;
            case 6:
                return DODANIE_KONTA_UŻYTKOWNIKA;
            case 7:
                return ZAWIESZENIE_KONTA_UŻYTKOWNIKA;
            case 8:
                return ZARAWCIE_UMOWY_Z_KLIENTEM;
            case 9:
                return PRZEKAZANIE_PRODUKTU_KLIENTOWI;
            case 10:
                return PRZEPROWADZENIE_SPOTKANIA_Z_KANDYDATEM;
            case 11:
                return PODPISANIE_UMOWY_Z_NOWYM_PRACOWNIKIEM;
            case 12:
                return AWANS_PRACOWNIKA;
            case 13:
                return ZWOLNIENIE_PRACOWNIKA;
            case 14:
                return PODWYŻKA_PENSJI_PRACOWNIKA;
            default:
                return POTWIERDZENIE_FAKTURY;
        }
    }

    static public int actionToInt(Actions action){
        switch (action){
            case POTWIERDZENIE_FAKTURY:
                return 0;
            case WYPELNIENIE_DOKUMENT:
                return 1;
            case WYSLANIE_DOKUMENTU_DO_URZEDU:
                return 2;
            case WYKONANIE_PRZELEWU:
                return 3;
            case ZAKUP_NA_POTRZEBY_FIRMY:
                return 4;
            case USUNIĘCIE_KONTA_UŻYTKOWNIKA:
                return 5;
            case DODANIE_KONTA_UŻYTKOWNIKA:
                return 6;
            case ZAWIESZENIE_KONTA_UŻYTKOWNIKA:
                return 7;
            case ZARAWCIE_UMOWY_Z_KLIENTEM:
                return 8;
            case PRZEKAZANIE_PRODUKTU_KLIENTOWI:
                return 9;
            case PRZEPROWADZENIE_SPOTKANIA_Z_KANDYDATEM:
                return 10;
            case PODPISANIE_UMOWY_Z_NOWYM_PRACOWNIKIEM:
                return 11;
            case AWANS_PRACOWNIKA:
                return 12;
            case ZWOLNIENIE_PRACOWNIKA:
                return 13;
            case PODWYŻKA_PENSJI_PRACOWNIKA:
                return 14;
            default:
                return 0;
        }
    }
}
