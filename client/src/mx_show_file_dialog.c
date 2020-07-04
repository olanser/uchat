#include "client.h"

char *mx_show_file_dialog(t_info *info) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    char *filename = 0;

    dialog = gtk_file_chooser_dialog_new (
        "Open File",
        GTK_WINDOW(info->objs->chat_win->chat_win),
        action,
        ("_Cancel"),
        GTK_RESPONSE_CANCEL,
        ("_Upload"),
        GTK_RESPONSE_OK,
        NULL);
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_OK)
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
    gtk_widget_destroy (dialog);
    return filename;
}
