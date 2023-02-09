
package AccessApp.GUI.StartingScreen;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class RegisterScreenDialog extends JDialog
{
    private final int WIDTH=110;
    private final int HEIGHT=25;
    private final int BUTTON_WIDTH =100;
    private JPanel panel = new JPanel();
    private JButton register_button = new JButton("REGISTER");
    private JButton close_button = new JButton("CLOSE");
    private JLabel userText = new JLabel("Login");
    private JTextField userName = new JTextField(20);
    private JLabel passwordText = new JLabel("Haslo");
    private JLabel passwordConfirmText = new JLabel("Potwierdz haslo");
    private JPasswordField userPassword = new JPasswordField(20);
    private JPasswordField userConfirmPassword = new JPasswordField(20);
    private JLabel nameText = new JLabel("Imie");
    private JTextField name = new JTextField(20);
    private JLabel surnameText = new JLabel("Nazwisko");
    private JTextField surname = new JTextField(20);
    private JLabel status = new JLabel("");

    String[] positionList = {"Stażysta","Mlodszy programista frontend","Mlodszy programista backend","Starszy programista frontend",
    "Starszy programista backend", "Marketingowiec", "Asystent głównego ksiegowego" ,"Administrator" ,"Kierownik zespołu programistow" ,
            "Czlonek rady nadzorczej" ,"Główny ksiegowy", "Ekspert ds. rynku", "Prezes"};
    private JComboBox positionComboBox = new JComboBox(positionList);
    String login = "";
    String password = "";
    String inputName = "";
    String inputSurname = "";
    String position = "";

    /**
     * Checks entered data (login and pass)
     */
    private void EnterData()
    {
        if(userName.getText().isEmpty() || userName.getText().length()<3)
        {
            status.setText("Invalid Login!");
        }
        else if(userPassword.getText().length()<3)
        {
            status.setText("Password too short");
        }
        else if(userPassword.getText().equals(userConfirmPassword.getText()))
        {
            login = userName.getText();
            password = userPassword.getText();
            inputName = name.getText();
            inputSurname = surname.getText();
            position = (String) positionComboBox.getSelectedItem();
            dispose();
        }
        else
        {
            status.setText("Passwords don't match");
        }
    }


    public RegisterScreenDialog(JFrame parent)
    {
        super(parent, "Register Screen", true);

        setLocationRelativeTo(null);
        status.setForeground(Color.RED);
        //status.setEnabled(false);

        register_button.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                EnterData();
            }
        });

        close_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose(); // Closes the dialog
            }
        });

        userPassword.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e)
            {
                super.keyPressed(e);
                if(e.getKeyCode() == KeyEvent.VK_ENTER)
                {
                    EnterData();
                }

            }
        });
        userConfirmPassword.addKeyListener(new KeyAdapter()
        {
            @Override
            public void keyPressed(KeyEvent e)
            {
                super.keyPressed(e);
                if(e.getKeyCode() == KeyEvent.VK_ENTER)
                {
                    EnterData();
                }

            }
        });

        userName.addKeyListener(new KeyAdapter()
        {
            @Override
            public void keyPressed(KeyEvent e) {
                super.keyPressed(e);
                if(e.getKeyCode() == KeyEvent.VK_ENTER)
                {
                    login = userName.getText();
                    password = userPassword.getText();
                    dispose();
                }

            }
        });
        /*LABELS*/
        userText.setBounds(10,20,WIDTH,HEIGHT);
        passwordText.setBounds(10,50,WIDTH,HEIGHT);
        passwordConfirmText.setBounds(10,80,WIDTH,HEIGHT);
        nameText.setBounds(10,110,WIDTH,HEIGHT);
        surnameText.setBounds(10,140,WIDTH,HEIGHT);
        status.setBounds(15,110,2*WIDTH,HEIGHT);
        /*TEXTFIELDS*/
        userName.setBounds(130,20,WIDTH,HEIGHT);

        userPassword.setBounds(130,50,WIDTH,HEIGHT);
        userConfirmPassword.setBounds(130,80,WIDTH,HEIGHT);
        name.setBounds(130,110,WIDTH,HEIGHT);
        surname.setBounds(130,140,WIDTH,HEIGHT);

        /*BUTTONS*/
        register_button.setBounds(120,250,BUTTON_WIDTH,HEIGHT);
        close_button.setBounds(10,250,BUTTON_WIDTH,HEIGHT);

        panel.setLayout(null);
        panel.add(userName);
        panel.add(userText);
        panel.add(nameText);
        panel.add(surnameText);
        panel.add(name);
        panel.add(surname);
        panel.add(userPassword);
        panel.add(passwordText);
        panel.add(register_button);
        panel.add(close_button);
        panel.add(userConfirmPassword);
        panel.add(passwordConfirmText);
        panel.add(status);

        positionComboBox.setBounds(80,200,150,40);

        add(positionComboBox);


        add(panel);
    }
    String getLogin()
    {return  login;}
    String getPassword()
    {return  password;}
    String getInputName()
    {return  inputName;}
    String getSurname()
    {return  inputSurname;}
    String getPosition()
    {return  position;}


}
