#include <gtk/gtk.h>
//#include "main_window_glade.h"

GtkBuilder *builder;
GObject *login_window;

void init_gui(int *argc, char **argv[]) {
    
    gtk_init(argc, argv);
    
    builder = gtk_builder_new();
    //guint build_error = gtk_builder_add_from_string(builder, main_window_glade, sizeof(main_window_glade), NULL);
    guint build_error = gtk_builder_add_from_file(builder, "login_window.ui", NULL);
    
    login_window = gtk_builder_get_object(builder, "login_window");
    g_signal_connect(login_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
}

void event_loop() {
   gtk_main();
}

void create_message_dialog(const char *message) {

   GtkWidget *message_dialog;
   
   message_dialog = gtk_message_dialog_new ((GtkWindow*)login_window,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 message);
   gtk_dialog_run (GTK_DIALOG (message_dialog));
   gtk_widget_destroy (message_dialog);

}
