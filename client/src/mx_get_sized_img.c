#include "client.h"

GtkWidget* mx_get_sized_img(const char *path, int width, int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(path, width, height, 0);
    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    
    return image;
}
