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
#include "Treatment/houghTransform.h"
#include <err.h>
#include "Struct/neuralNetwork.h"
#include "Struct/matrix.h"
#include "Recognition/function.h"
#include "Input/file.h"
#include "Solver/solving.h"
#include "Treatment/square.h"
#include "Input/recompose.h"

#include "Recognition/recognition.h"

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
    gchar *path;
    gint ifsobel;
} UserInterface;

// atof() pour convertir en float ou strtod

void rotate_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    // on mets la progress bar à 15
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.2);
    // gtk_range_get_value(ui->scale);

    Image *image = importImage(ui->path);
    double angleRotation = (double)gtk_range_get_value(GTK_RANGE(ui->scale));
    g_print("Rotate the image (%f)\n", angleRotation);
    image = rotateImage(image, angleRotation);
    saveImage(image, ui->path);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), ui->path);
}

void line_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    const gchar *sText;
    UserInterface *ui = (UserInterface *)data;
    g_print("Apply houghTransform\n");
    // on mets la progress bar à 50
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.7);
    Image *image = importImage(ui->path);
    sText = gtk_entry_get_text(ui->entry);
    houghTransform(image, (int)ui->ifsobel, atof(sText));
    saveImage(image, ui->path);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), ui->path);

    // je te renvoie le seuil avec donc ui->entry
}

void traitement_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    g_print("Treatement\n");
    // on mets la progress bar à 25
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.4);
    Image *image = importImage(ui->path);
    grayscaleImage(image);
    otsuTresolding(image);
    saveImage(image, "gui.bmp");
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "gui.bmp");
}

void resolve_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    const gchar *sText;
    UserInterface *ui = (UserInterface *)data;
    g_print("Resolve Button\n");
    // on mets la progress bar à 100
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 1.0);
    Image *image = importImage(ui->path);
    sText = gtk_entry_get_text(ui->entry);
    Line** listeline = houghTransform(image, (int)ui->ifsobel, atof(sText));
    int ** initial = square(image, listeline);
    g_print("Export the 81 square from the sudoku\n");

    int** result = square(image, listeline);
    g_print("Recognize the number on the square\n");

    print_sudoku(result);
    g_print("Solve the solve_sudoku\n");
    solve_sudoku(result , 0, 0);
    g_print("Export the result in the image \"sudoku.png\"\n");

    write_sudoku_image("sudoku.png", result, initial);
    
    gtk_image_set_from_file(GTK_IMAGE(ui->image), "sudoku.png");
}

void change_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Loading the image\n");
    // on mets la progress bar à 10
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.1);

    g_print("%s \n", gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(widget)));

    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));

    // gchar *filename2 = filename + 1;
    Image *image = importImage(filename);
    
    image = resizeImage(image, 750);
    saveImage(image, "gui.bmp");
    

    gtk_image_set_from_file(GTK_IMAGE(ui->image), filename);

    ui->path = "gui.bmp";
}

void entry_changed(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    const gchar *sText;

    sText = gtk_entry_get_text(GTK_ENTRY(widget));
    g_print("Entry changed : %s\n", sText);

    ui->entry = GTK_ENTRY(widget);
}

void save_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    // on save avec saveImage() ui->image
    Image *image = importImage(ui->path);
    saveImage(image, "sudoku.png");
    g_print("Save the image in \"sudoku.png\"");
}

void blur_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    g_print("Aplly Blur\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.1);
    Image *image = importImage(ui->path);
    applyGaussianBlur(image);
    saveImage(image, ui->path);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), ui->path);
}

void sobel_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    g_print("Apply Sobel\n");
    gint newsobel = 1;
    ui->ifsobel = newsobel;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.55);

    Image *image = importImage(ui->path);
    saveImage(sobelOperator(image), ui->path);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), ui->path);
}

void modify_scale(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    // gtk_range_get_value(ui->scale);
    ui->scale = GTK_SCALE(widget);
    g_print("Rescale\n");
}

void moins90_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    g_print("Roation de - 90\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.3);
    Image *image = importImage(ui->path);
    double angleRotation = -90;
    image = rotateImage(image, angleRotation);
    saveImage(image, ui->path);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), ui->path);
}

void plus90_image(GtkWidget *widget, gpointer data)
{
    if (widget == 0){
        g_print("widget");
    }
    UserInterface *ui = (UserInterface *)data;
    g_print("Rotation de + 90\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.3);
    Image *image = importImage(ui->path);
    double angleRotation = 90;
    image = rotateImage(image,angleRotation);
    saveImage(image, ui->path);
    gtk_image_set_from_file(GTK_IMAGE(ui->image), ui->path);
}

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        // Image* image = importImage(argv[1]);
        // otsuTresolding(image);

        // int** test = square(image,line);
        // image = rotateImage(image, angleRotation);
        // saveImage(image, "rotation.bmp");
        SDL_Quit();
    }
    else 
    {
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
        GtkButton *moins90 = GTK_BUTTON(gtk_builder_get_object(builder, "degree1"));
        GtkButton *plus90 = GTK_BUTTON(gtk_builder_get_object(builder, "degree2"));
        GtkButton *traitement = GTK_BUTTON(gtk_builder_get_object(builder, "traitement"));
        GtkButton *resolve = GTK_BUTTON(gtk_builder_get_object(builder, "resolve"));
        GtkEntry *entry = GTK_ENTRY(gtk_builder_get_object(builder, "seuil"));

        GtkScale *rotation_scale = GTK_SCALE(gtk_builder_get_object(builder, "moov"));

        GtkFileChooserButton *filechooserbutton1 = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file-chooser"));

        gtk_range_set_range(GTK_RANGE(rotation_scale), -180, 180);
        gtk_range_set_value(GTK_RANGE(rotation_scale), 0);

        // progressbar
        GtkProgressBar *progressbar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progressbar"));
        // gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar), 0);
        gchar *chemin = "";
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
            .ifsobel = 0,
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

        g_signal_connect(moins90, "clicked", G_CALLBACK(moins90_image), &ui);
        g_signal_connect(plus90, "clicked", G_CALLBACK(plus90_image), &ui);

        g_signal_connect(rotation_scale, "value-changed", G_CALLBACK(modify_scale), &ui);

        // Runs the main loop.
        gtk_main();

        // Exits.
    }
    return 0;
}
