#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
#include "Treatment/blur.h"
#include "Treatment/rotation.h"
#include "Treatment/resize.h"
#include "Treatment/thresolding.h"
#include "Treatment/sobel.h"
#include "Treatment/morph.h"
#include "Treatment/contrast.h"
#include "Treatment/gamma.h"
#include "Treatment/hough.h"
#include <err.h>
#include "Struct/neuralNetwork.h"
#include "Xor/xor.h"
#include "Struct/matrix.h"
#include "Xor/function.h"

typedef struct UserInterface
{
    GtkWindow *window;           
    GtkImage *image;        
    GtkButton *rotate;     
    GtkButton *line;
    GtkButton *traitement;
    GtkButton *resolve;
    GtkProgressBar *progress;
} UserInterface;

void rotate_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Rotate\n");
    // on mets la progress bar à 15
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.15);

    image = rotateImage(image, 10);
    saveImage(image, "rotation.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "rotation.bmp");
}

void line_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Line\n");
    // on mets la progress bar à 50
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.5);

}

void traitement_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Traitement\n");
    // on mets la progress bar à 25
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.25);

    grayscaleImage(image);
    saveImage(image, "grayscale.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "grayscale.bmp");
}

void resolve_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Resolve\n");
    // on mets la progress bar à 100
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 1.0);
}

void change_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Change\n");
    // on mets la progress bar à 10
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.1);

    g_print("%s \n",gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(widget)));
    
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));

    gtk_image_set_from_file(GTK_IMAGE(ui->image), filename);

}

int main(int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(&argc, &argv);

    // Constructs a GtkBuilder instance.
    GtkBuilder *builder = gtk_builder_new();

    // Loads the UI description.
    // (Exits if an error occurs.)
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "ui.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets.
    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "window.sudoku"));
    GtkImage *image = GTK_IMAGE(gtk_builder_get_object(builder, "image"));
    GtkButton *rotate = GTK_BUTTON(gtk_builder_get_object(builder, "rotate"));
    GtkButton *line = GTK_BUTTON(gtk_builder_get_object(builder, "line"));
    GtkButton *traitement = GTK_BUTTON(gtk_builder_get_object(builder, "traitement"));
    GtkButton *resolve = GTK_BUTTON(gtk_builder_get_object(builder, "resolve"));

    GtkFileChooserButton *filechooserbutton1 = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file-chooser"));

    // progressbar 
    GtkProgressBar *progressbar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progressbar"));

    
    // Creates the "Game" structure.
    UserInterface ui =  
    {
        .window = window,
        .image = image,
        .rotate = rotate,
        .line = line,
        .traitement = traitement,
        .resolve = resolve,
        .progress = progressbar
    };
    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(rotate, "clicked", G_CALLBACK(rotate_image), &ui);
    g_signal_connect(line, "clicked", G_CALLBACK(line_image), &ui);
    g_signal_connect(traitement, "clicked", G_CALLBACK(traitement_image), &ui);
    g_signal_connect(resolve, "clicked", G_CALLBACK(resolve_image), &ui);
    g_signal_connect(filechooserbutton1, "file-set", G_CALLBACK(change_image), &ui);


    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
