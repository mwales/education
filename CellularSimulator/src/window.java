//window.java
//Jeffrey Miller
//October 29, 2000
//Version 0.5

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import javax.swing.text.html.*;
import java.net.*;
//import pane;
//import SizeDialog;
//import HelpDialog;
//import SizeHolder;
//import ImageMap;
//import SerializeIn;
//import SerializeOut;


//Main window class
class window extends JFrame implements ActionListener
{
   TransitionWindow TW;
   StateList SL;
   MenuBar mbar;
   Menu fileMenu;
   Menu helpMenu;
   Menu EditMenu;
   String FileName;
   String FileDirectory;
   String File;
   pane SimPane;
   JPanel BlankPane;
   SizeHolder XYSize;
   SerializeOut WriteOut;
   SerializeIn ReadIn;
   pane mypane;
   boolean WindowLimiter;

   public window()
   {
      super("Cellular Simulator");
      frameInit();

      //sets the look and feel                                             
      setLookandFeel();

      setCurrentMenuBar();

       //creates the FileMenu, and adds its action listeners
      createFileMenu();

      //creates Edit menu
      createEditMenu();

      //creates help menu, and add its action listeners
      createHelpMenu();

      //adds the menus to the current menu bar
      addMenustoCurrentbar();

      createStateList();
     
      
      BlankPane= new JPanel();
      BlankPane.setPreferredSize(new Dimension(800,600));
      setContentPane(BlankPane);
   }

      public void actionPerformed(ActionEvent evt)
      {
          String action = evt.getActionCommand();

          //checks to see if a file should open
          if(action.equals("Open File"))
          {
             FileDialog fd = new FileDialog(this,"Open File");
             fd.show();
             FileName = fd.getFile();
             if(FileName != null)
             {
             FileDirectory= fd.getDirectory();
             File = FileDirectory + FileName;
             ReadIn = new SerializeIn();
             ReadIn.openStream(File);
             ImageMap Map = ReadIn.readObject();
             int x = Map.getXPix();
             int y = Map.getYPix();
             SL = Map.getStateList();
             ReadIn.closeStream();
             SimPane = new pane(SL, Map, x , y);
             setContentPane(SimPane);
             pack();
             }
          }

          if(action.equals("Save File"))
          {
             if(getContentPane() == BlankPane)
             {
            JOptionPane.showMessageDialog(this,"You must make a map before you can save one"
         ,     "Error", JOptionPane.ERROR_MESSAGE);
            }
            else
            {
             FileDialog fd = new FileDialog(this,"Save File");
             fd.setMode(fd.SAVE);
             fd.show();
             FileName = fd.getFile();
             FileDirectory = fd.getDirectory();
             File = FileDirectory + FileName;
             WriteOut = new SerializeOut();
             WriteOut.openStream(File);
             WriteOut.writeObject(SimPane.getImageMap());
             WriteOut.closeStream();
             }
          }

          //checks to see if close file was called
          if(action.equals("Close File"))
          {
              remove(getContentPane());
              setContentPane(BlankPane);
              pack();
          }

          //Checks to see if exit was requested
          if(action.equals("Exit Sim"))
          {
             System.exit(0);
          }

          //checks to see if the edit trans window should be opened                                        
          if(action.equals("EditTrans"))
          {
            if(WindowLimiter == false)
            {
             WindowLimiter = true;
             TW = new TransitionWindow( SL );
             TW.showGUI();
            }

          }

          if(action.equals("New Sim"))
          {
             if(SL.getSize() == 0)
             {
            JOptionPane.showMessageDialog(this,"You add at least one transition before you make a map"
         ,     "Error", JOptionPane.ERROR_MESSAGE);
            }
             else
             {

             SizeDialog SizeEntry = new SizeDialog(this,"Size Entry Dialog Box",true);
             SizeEntry.setBounds(50,50,100,100);
             SizeEntry.pack();
             SizeEntry.show();
             XYSize = new SizeHolder();
             XYSize.setSize(SizeEntry.getText1(),SizeEntry.getText2());
             SimPane = new pane(SL,XYSize.getXSize(),XYSize.getYSize());
             setContentPane(SimPane);
             pack();
             SizeEntry.dispose();
             }
          }
          if(action.equals("About"))
          {
            HelpDialog HelpMe = new HelpDialog(this, "Help Dialog Box", false);
            HelpMe.pack();
            HelpMe.show();
            
          };
        };


      private void setCurrentMenuBar()
      {
         mbar = new MenuBar();
         setMenuBar(mbar);
      };


      private void setLookandFeel()
      {
         try
         {
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
         }
         catch(Exception e)
         {
            System.err.println("Can't set look and feel: "+e);
         }
      };


      private void createFileMenu()
      {
         fileMenu = new Menu("File");
         addNew();
         addOpen();
         addSave();
         addClose();
         addExit();
      };

      //adds open to the file menu, and sets its action command
      private void addOpen()
      {
         MenuItem Open=new MenuItem("Open...");
         Open.setActionCommand("Open File");
         Open.addActionListener(this);
         fileMenu.add(Open);
      };

      //adds new to the file menu, and sets its action command
      private void addNew()
      {
        MenuItem New= new MenuItem("New...");
        New.setActionCommand("New Sim");
        New.addActionListener(this);
        fileMenu.add(New);
      };

      //adds save to the file menu, and sets its action command
      private void addSave()
      {
         MenuItem Save = new MenuItem("Save As...");
         Save.setActionCommand("Save File");
         Save.addActionListener(this);
         fileMenu.add(Save);
      };

      //adds close to the file menu, and sets its action command
      private void addClose()
      {
         MenuItem Close = new MenuItem("Close");
         Close.setActionCommand("Close File");
         Close.addActionListener(this);
         fileMenu.add(Close);
      };

      //adds exit to the file menu, and sets its action command
      private void addExit()
      {
         MenuItem Exit = new MenuItem("Exit");
         Exit.setActionCommand("Exit Sim");
         Exit.addActionListener(this);
         fileMenu.add(Exit);
      };


      private void createHelpMenu()
      {
         helpMenu = new Menu("Help");
         addAbout();
      };


      private void addAbout()
      {
        MenuItem About= new MenuItem("Help");
        About.setActionCommand("About");
        About.addActionListener(this);
        helpMenu.add(About);
      };


      private void createEditMenu()
      {
         EditMenu= new Menu("Edit");
         addEditTrans();
      };


      private void addEditTrans()
      {
         MenuItem Trans = new MenuItem("Edit Transitions...");
         Trans.setActionCommand("EditTrans");
         Trans.addActionListener(this);
         EditMenu.add(Trans);
      };


      private void addMenustoCurrentbar()
      {
         mbar.setHelpMenu(helpMenu);
         mbar.add(fileMenu);
         mbar.add(EditMenu);
         mbar.add(helpMenu);
         
      };



      private void createStateList()
      {
         SL = new StateList();
      };

      public void dispose()
      {
         TW.TransitionsFrame.dispose();
      }

      public void setNewStateList(StateList tempsl)
      {

         WindowLimiter = false;
         if(getContentPane() != BlankPane)
         {
         remove(getContentPane());
         SL = tempsl;
         SimPane = new pane(SL,SimPane.getImageMap(),(SimPane.getImageMap()).getXPix(),
         (SimPane.getImageMap()).getYPix());
         setContentPane(SimPane);
         pack();
         }
         else
         {
            SL = tempsl;
         }
       }

}
