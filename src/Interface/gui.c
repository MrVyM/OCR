#include <gtk/gtk.h>


//function when file is upload then show in the gtk image

// Main function.
int main (int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Loads the UI description and builds the UI.
    // (Exits if an error occurs.)
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "gui.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets.
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.duel"));
    // button for rotate the image
    GtkButton* rotate = GTK_BUTTON(gtk_builder_get_object(builder, "rotate"));
    // button for show hough line in the image
    GtkButton* line = GTK_BUTTON(gtk_builder_get_object(builder, "line"));
    // button that complete the sudoku
    GtkButton* complete = GTK_BUTTON(gtk_builder_get_object(builder, "complete"));
    // gtkfileupload
    GtkFileChooserButton* fileupload = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "upload"));

    // Connects the signals handler

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(rotate, "clicked", G_CALLBACK(rotate_image), NULL);
    g_signal_connect(line, "clicked", G_CALLBACK(hough_line), NULL);
    g_signal_connect(complete, "clicked", G_CALLBACK(complete_sudoku), NULL);
    g_signal_connect(fileupload, "file-set", G_CALLBACK(upload_image), NULL);


    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
