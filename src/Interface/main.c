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
    GtkButton *moov;
    GtkButton *line;
    GtkButton *traitement;
    GtkButton *resolve;
    GtkProgressBar *progress;
    GtkEntry *entry;
    GtkScale *scale;
    gchar* path;
} UserInterface;


//atof() pour convertir en float

void rotate_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Rotate\n");
    // on mets la progress bar à 15
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.2);
    //gtk_range_get_value(ui->scale);

    Image* image = importImage(ui->path);
    double angleRotation = (double)gtk_range_get_value(ui->scale);
    image = rotateImage(image, angleRotation);
    saveImage(image, "rotation.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "rotation.bmp");

}

void line_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Line\n");
    // on mets la progress bar à 50
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.7);
    Image* image = importImage(ui->path);

    houghTransform(image);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "hough.bmp");


    //je te renvoie le seuil avec donc ui->entry
}

void traitement_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Traitement\n");
    // on mets la progress bar à 25
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.4);
    Image* image = importImage(ui->path);
    otsuTresolding(image);
    saveImage(image, "thresolding.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "thresolding.bmp");
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

    //gchar *filename2 = filename + 1;
    Image *image = importImage(filename);
    if (image->height > 1000 || image->width > 1000){
    	image = resizeImage(image, 1000000);
	saveImage(image, );
    }


    gtk_image_set_from_file(GTK_IMAGE(ui->image), filename);

    ui->path = filename;

}

void entry_changed(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    const gchar *sText;

    sText = gtk_entry_get_text(GTK_ENTRY(widget));
    g_print("Entry changed : %s\n", sText);

    ui->entry = GTK_ENTRY(widget);
}

void save_image(GtkWidget *widget, gpointer data){
    UserInterface *ui = (UserInterface *)data;
    // on save avec saveImage() ui->image
    Image* image = importImage(ui->path);
    saveImage(image,"sudoku.bmp");
    g_print("save");
}

void blur_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Blur\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.1);
    Image* image = importImage(ui->path);
    applyGaussianBlur(image);
    saveImage(image,"blur.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "blur.bmp");
}

void sobel_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Sobel\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.55);
    
    Image* image = importImage(ui->path);
    saveImage(sobelOperator(image),"sobel.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "sobel.bmp");

}

void modify_scale(GtkWidget *widget, gpointer data){
    UserInterface *ui = (UserInterface *)data;
    //gtk_range_get_value(ui->scale);
    ui->scale = GTK_SCALE(widget);
    g_print("scale");
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
    GtkButton *quit = GTK_BUTTON(gtk_builder_get_object(builder, "quit"));
    GtkButton *blur = GTK_BUTTON(gtk_builder_get_object(builder, "blur"));
    GtkButton *sobel = GTK_BUTTON(gtk_builder_get_object(builder, "sobel"));
    GtkButton *save = GTK_BUTTON(gtk_builder_get_object(builder, "save"));
    GtkButton *line = GTK_BUTTON(gtk_builder_get_object(builder, "line"));
    GtkButton *traitement = GTK_BUTTON(gtk_builder_get_object(builder, "traitement"));
    GtkButton *resolve = GTK_BUTTON(gtk_builder_get_object(builder, "resolve"));
    GtkEntry*entry = GTK_ENTRY(gtk_builder_get_object(builder, "seuil"));

    GtkScale *rotation_scale = GTK_SCALE(gtk_builder_get_object(builder, "moov"));

    GtkFileChooserButton *filechooserbutton1 = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file-chooser"));

    gtk_range_set_range(GTK_RANGE(rotation_scale), -180, 180);
    gtk_range_set_value(GTK_RANGE(rotation_scale), 0);

    // progressbar 
    GtkProgressBar *progressbar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progressbar"));
    //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), 0);
    const gchar* chemin;
    // Creates the "Game" structure.
    UserInterface ui =  
    {
        .window = window,
        .image = image,
        .rotate = rotate,
        .line = line,
        .traitement = traitement,
        .resolve = resolve,
        .progress = progressbar,
        .entry = entry,
        .scale = rotation_scale,
	.path = chemin,
    };
    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(rotate, "clicked", G_CALLBACK(rotate_image), &ui);
    g_signal_connect(quit, "clicked", G_CALLBACK(gtk_main_quit), &ui);
    g_signal_connect(blur, "clicked", G_CALLBACK(blur_image), &ui);
    g_signal_connect(sobel, "clicked", G_CALLBACK(sobel_image), &ui);
    g_signal_connect(save, "clicked", G_CALLBACK(save_image), &ui);
    g_signal_connect(line, "clicked", G_CALLBACK(line_image), &ui);
    g_signal_connect(traitement, "clicked", G_CALLBACK(traitement_image), &ui);
    g_signal_connect(resolve, "clicked", G_CALLBACK(resolve_image), &ui);
    g_signal_connect(filechooserbutton1, "file-set", G_CALLBACK(change_image), &ui);
    g_signal_connect(entry, "activate", G_CALLBACK(entry_changed), &ui);

    g_signal_connect(rotation_scale, "value-changed", G_CALLBACK(modify_scale), &ui);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
