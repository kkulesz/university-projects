package ReportApp.GUI.Main;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class MainWindow extends JFrame
{
    private JTabbedPane tabs = new JTabbedPane();
    private JPanel tab1 = new MainTab();
    private JPanel tab2 = new EmployeePermissionReport();
    private JPanel tab3 = new HistoryOfPermission();
    private JPanel tab4 = new CountingActionsInMonth();
    private JPanel tab5 = new JPanel();
    private JPanel tab6 = new JPanel();
    private JPanel tab7 = new JPanel();
    private String user;




    public MainWindow(String user)
    {
        addWindowListener(new WindowAdapter()
        {
            @Override
            public void windowClosing(WindowEvent e)
            {
                super.windowClosing(e);
                dispose();
            }
        });
        this.user = user;
        tabs.addTab("Raport ilości czynności pracowników",tab1);
        tabs.addTab("Raport ilości pracowników z rodzajem uprawnienia", tab2);
        tabs.addTab("Generowanie historii nadawania uprawnień pracownikowi", tab3);
        tabs.addTab("Raport ilości czynności w czasie", tab4);
//        tabs.addTab("Raport uprawnien danego dnia", tab5);
//        tabs.addTab("Raport ilości pracowników z uprawnieniem", tab6);
//        tabs.addTab("Raport ilości pracownikó z rodzajem uprawnienia", tab3);
        add(tabs);

    }

}
