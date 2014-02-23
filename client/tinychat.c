#include <gtk/gtk.h>
#include "gui.h"


static void button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Hello! \n");
}


int main(int argc, char *argv[]) {

   init_gui(&argc, &argv);
   event_loop();
  
   return 0;
 
}
