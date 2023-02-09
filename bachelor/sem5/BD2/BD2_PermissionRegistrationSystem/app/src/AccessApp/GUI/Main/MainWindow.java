package AccessApp.GUI.Main;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.Connection;
import java.sql.SQLException;

public class MainWindow extends JFrame
{
    private JTabbedPane tabs = new JTabbedPane();
    private JPanel tab1;
    private JPanel tab2;
    private String user;
    private Connection conn;



    public MainWindow(String user,Connection conn)
    {
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        addWindowListener(new WindowAdapter()
        {
            @Override
            public void windowClosing(WindowEvent e)
            {
                try {
                    conn.close();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
                System.out.println("KONIEC");
                super.windowClosing(e);
                dispose();
            }
        });

        this.user = user;
        tab1 = new AddTab(conn);
        tab2 = new DeleteTab(conn);
        tabs.addTab("Dodawanie uprawnienia", tab1);
        tabs.addTab("Usuwanie uprawnienia", tab2);
        add(tabs);

    }

}