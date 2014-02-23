#include <gtk/gtk.h>


static void button_clicked(GtkWidget *widget, gpointer data) {

    g_print("Hello! \n");

}

int main(int argc, char *argv[]) {
   
   GtkBuilder *builder;
   GtkWidget *window;
   GtkWidget *button;
   
   gtk_init(&argc, &argv);
   
   // Widget creation: Main window
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "Tiny chat");
   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
   
   // Widget creation: button   
   button = gtk_button_new_with_label("Click!");
   g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);
   gtk_container_add(GTK_CONTAINER(window), button);

   gtk_widget_show(button);
   gtk_widget_show(window);
  
   gtk_main();
  
   return 0;
 
}
