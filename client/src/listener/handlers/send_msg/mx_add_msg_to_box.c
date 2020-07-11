#include "client.h"
#include "libmx.h"

void mx_add_msg_to_box(GtkWidget*listbox, GtkWidget*widget, int index) {
    gtk_list_box_insert(GTK_LIST_BOX(listbox), widget, index);
}
