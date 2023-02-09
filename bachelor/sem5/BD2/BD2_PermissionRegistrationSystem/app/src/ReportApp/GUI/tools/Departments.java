package ReportApp.GUI.tools;

public enum Departments {
    IT,FINANSOWY,ZARZADZANIE,MARKETING;

    static public Departments intToDepartment(int number){
        switch (number){
            case 0:
                return IT;
            case 1:
                return FINANSOWY;
            case 2:
                return ZARZADZANIE;
            case 3:
                return MARKETING;
            default:
                return IT;
        }
    }
}
