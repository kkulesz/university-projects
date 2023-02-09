package ReportApp.Tests;

import ReportApp.Database.DatabaseHandler;

import java.util.Objects;

public class Test1 extends Test{

    public boolean performTest(){

        DatabaseHandler databaseHandler = new DatabaseHandler();
        String[] actionList = {"Potwierdzenie faktury","Wypelnienie dokument", "Wyslanie dokumentu do urzedu",
                "Wykonanie przelewu","Zakup na potrzeby firmy","Usunięcie konta użytkownika","Dodanie konta użytkownika",
                "Zawieszenie konta użytkownika","Zarawcie umowy z klientem","Przekazanie produktu klientowi",
                "Przeprowadzenie spotkania z kandydatem","Podpisanie umowy z nowym pracownikiem",
                "Awans pracownika","Zwolnienie pracownika","Podwyżka pensji pracownika"
        };
        String[] departmentList = {"IT","Finansowy","Zarzadzanie","Marketing"};
        String[] permissionTypeList = {"Zarzadzanie dokumentami finansowymi","Zarządzanie rachunkiem firmowym", "Dostęp do systemu X",
                "Dostęp do systemu Y","Dostęp do systemu X z pełnym zakresem","Dostęp do systemu Y z pełnym zakresem","Prowadzenie negocjacji z klientem",
                "Dostęp do tajemnicy X","Dostęp do tajemnicy Y","Zarządzanie rekturacją",
                "Zarządzanie zasobami ludzkimi","Zarządzanie aktywami firmy",
        };

        int actionIndex = 0;
        int departmentIndex = 0;
        int permissionTypeIndex = 0;
        int accountID = 0;
        int insertIterations = 1;

        String textBefore = databaseHandler.generateActionCounterReport(
                false,true ,false,
                actionList[actionIndex], departmentList[departmentIndex]);
        System.out.println("Before insert: \n"+textBefore);

        for(int i = 0; i<insertIterations; i++)
            Test.insertActionHistory(actionIndex, permissionTypeIndex, accountID);

        String textAfter = databaseHandler.generateActionCounterReport(
                false,true ,false,
                actionList[actionIndex], departmentList[departmentIndex]);
        System.out.println("After insert: \n"+textAfter);

        if(Objects.equals(textBefore,textAfter))
            return false;


        return true;
    }

}
