#include <gtk/gtk.h>


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
} UserInterface;


//atof() pour convertir en float

void rotate_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Rotate\n");
    // on mets la progress bar à 15
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.2);
    //on rotate l'image de 10 degré
}

void line_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Line\n");
    // on mets la progress bar à 50
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.7);

    //je te renvoie le seuil avec donc ui->entry
}

void traitement_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Traitement\n");
    // on mets la progress bar à 25
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.4);
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

    gchar *filename2 = filename + 1;
    g_print("%s \n",filename2);

    gtk_image_set_from_file(GTK_IMAGE(ui->image), filename);

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
    g_print("save");
}

void blur_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Blur\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.1);
}

void sobel_image(GtkWidget *widget, gpointer data)
{
    UserInterface *ui = (UserInterface *)data;
    g_print("Sobel\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui->progress), 0.55);
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
