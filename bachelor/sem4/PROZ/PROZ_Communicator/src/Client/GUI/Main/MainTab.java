package Client.GUI.Main;

import Client.GUI.Notifications.NotificationPanel;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static Client.Client.*;



public class MainTab extends JPanel
{
    private DefaultListModel FriendList = new DefaultListModel();
    private JList FriendL = new JList(FriendList);
    private JScrollPane FriendScroll = new JScrollPane(FriendL);
    private DefaultListModel GroupList = new DefaultListModel();
    private JList GroupL = new JList(GroupList);
    private JScrollPane GroupScroll = new JScrollPane(GroupL);

    private JPanel AddFriend;
    private JPanel createGroup;
    private MainWindow referenceToMain;
    private JLabel state = new JLabel("");
    private JLabel loggedAs = new JLabel("");
    private JLabel FriendsText = new JLabel("Friends:");
    private JLabel GroupsText = new JLabel("Groups:");
    private JButton StartChatButton = new JButton("Start Chat");


    /**Once FriendList has changed, update those changes (new friends) to the panel*/
    public void refreshFriends()
    {
        for(String s: friends)
        {
            if(FriendList.indexOf(s)==-1)
            {
                FriendList.addElement(s);
            }
        }
    }
    /**Once GroupList has changed, update those changes (new groups) to the panel*/
    public void refreshGroups()
    {
        for(String s: groups)
        {
            if(GroupList.indexOf(s)==-1)
            {
                GroupList.addElement(s);
            }
        }

    }
    /**Set custom state text on panel
     * @param text content of a state
     * @param fg foreground color
     * */
    public void setState(Color fg,String text)
    {
        state.setForeground(fg);
        state.setText(text);
    }

    public MainTab(MainWindow upRef, String User)
    {
        referenceToMain=upRef;
        AddFriend = new AddFriendPanel(state);
        createGroup = new CreateGroupPanel(state,referenceToMain);
        setLayout(null);
        // Nie mo??na zaznaczac kilku na raz, grupy sie tworzy inaczej
        FriendL.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        GroupL.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        loggedAs.setText( "<html>LOGGED AS: <font size=\"+1\">"+User+"</font></html>");



        Border brd = BorderFactory.createMatteBorder(
                1, 1, 2, 2, Color.BLACK);
        FriendScroll.setBorder(brd);
        GroupScroll.setBorder(brd);
        //LISTA PRZYJACIOL

        for(String s: friends)
        {
         FriendList.addElement(s);
        }
        for(String s: groups)
        {
            GroupList.addElement(s);
        }

        FriendsText.setBounds(30,10,150,20);
        GroupsText.setBounds(200,10,150,20);
        FriendScroll.setBounds(30,30,150,270);
       GroupScroll.setBounds(200,30,150,270);

        loggedAs.setBounds(370,30,130,70);
        loggedAs.setVerticalAlignment(JLabel.TOP);

        StartChatButton.setBounds(375,400,140,75);
        AddFriend.setBounds(30,370,155,140);
        createGroup.setBounds(200,370,155,140);

        state.setBounds(30,320,200,60);
        state.setVerticalAlignment(JLabel.TOP);
        state.setForeground(Color.RED);


        FriendL.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e)
            {
                GroupL.clearSelection();
            }
        });

        GroupL.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                FriendL.clearSelection();
            }
        });

        StartChatButton.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                if(FriendL.isSelectionEmpty() && GroupL.isSelectionEmpty())
                {
                    state.setText("<html>Select at least one friend or group first!</html>");
                }
                else if(FriendL.isSelectionEmpty())
                {
                    state.setText("");
                    referenceToMain.OpenGroupChatWindow(GroupL.getSelectedValue().toString());

                    upRef.goToGroupTab(GroupL.getSelectedValue().toString());
                }
                else
                {
                    state.setText("");
                    referenceToMain.OpenChatWindow(FriendL.getSelectedValue().toString());
                    upRef.goToChatTab(FriendL.getSelectedValue().toString());

                }
            }
        });

        /*Add all previously prepared components to panel*/
        add(FriendsText);
        add(GroupsText);
        add(GroupScroll);
        add(createGroup);
        add(AddFriend);
        add(loggedAs);
        add(state);
        add(FriendScroll);
        add(StartChatButton);

    }
}
