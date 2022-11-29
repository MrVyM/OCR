#include <gtk/gtk.h>
#include "Treatment/rotation.h"
#include "Struct/image.h"

//function when file is upload then show in the gtk image
gboolean on_file_set(GtkFileChooserButton *filechooserbutton, gpointer user_data)
{
    GtkImage *image = GTK_IMAGE(user_data);
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    gtk_image_set_from_file(image, filename);
    g_free(filename);
    return TRUE;
}

//function when button is clicked then rotate the image by 5 degree
void rotate_image(GtkButton *button, gpointer user_data)
{
    GtkImage *image = GTK_IMAGE(user_data);
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(image));
    Image *img = importImage(filename);
    img = rotateImage(img, 5);
    saveImage(img, "rotation.bmp");
    gtk_image_set_from_file(image, "rotation.bmp");
    freeImage(img);
    g_free(filename);
}


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
    //g_signal_connect(line, "clicked", G_CALLBACK(hough_line), NULL);
    //g_signal_connect(complete, "clicked", G_CALLBACK(complete_sudoku), NULL);
    g_signal_connect(fileupload, "file-set", G_CALLBACK(on_file_set), NULL);


    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
