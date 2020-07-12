#include "client.h"
#include "defines_client.h"

char **get_packs(char *rel_path) {
    int len = mx_dirlen(rel_path);
    char **strs = 0;

    if (len == -1) {
        fprintf(stderr, "cant open sticker folder\n");
        exit(0);
    }
    strs = mx_get_dir_filenames(rel_path);
    return strs;
}

void add_image(GtkWidget *grid, char *path_to_img, int index, t_info *info) {
    GtkWidget *img = 0;
    GdkPixbuf *pixbuf = 0;
    GtkWidget* event_box = 0;
    char *path_to_sticker = mx_strdup(path_to_img);

    event_box = gtk_event_box_new();
    pixbuf = gdk_pixbuf_new_from_file_at_size(path_to_img, 100, 100, 0);
    img = gtk_image_new_from_pixbuf(pixbuf);

    gtk_container_add(GTK_CONTAINER(event_box), img);
    gtk_grid_attach(GTK_GRID(grid), event_box, index, 0, 1, 1);
    g_object_set_data(G_OBJECT(event_box), "path_to_sticker", path_to_sticker);
    g_signal_connect(G_OBJECT(event_box), "button-press-event",
                     G_CALLBACK(mx_btn_send_sticker), info);
}

void fill_pack(GtkWidget *grid, char *name_dir, char *pack_name, t_info *info) {
    char **names_stickers = 0;
    int i = -1;
    int len_dir = mx_strlen(name_dir);

    names_stickers = mx_get_dir_filenames(name_dir);
    while (names_stickers[++i]) {
        if (names_stickers[i][0] != '.') {
            memset(&name_dir[len_dir], 0, 1024 - len_dir);
            mx_strcat(name_dir, names_stickers[i]);
            add_image(grid, name_dir, i, info);
        }
        
    }
    mx_del_strarr(&names_stickers);
}

GtkWidget* get_grid(char *name_of_pack, t_info *info) {
    GtkWidget *grid = gtk_grid_new();
    char name_dir[1024];

    memset(name_dir, 0, 1024);
    mx_strcat(name_dir, MX_DIR_STICKERS);
    mx_strcat(name_dir, name_of_pack);
    mx_strcat(name_dir, "/");
    fill_pack(grid, name_dir, name_of_pack, info);
    return grid;
}

GtkWidget* mx_get_stickers_notebook(GtkBuilder *builder, t_info *info) {
    GtkWidget *notebook = GTK_WIDGET(gtk_builder_get_object(builder, "notebook_stickers"));
    char **packs = get_packs(MX_DIR_STICKERS);
    int i = -1;

    while (packs[++i]) {
        if (packs[i][0] != '.') {
            GtkWidget *grid = get_grid(packs[i], info);
            gtk_notebook_append_page(GTK_NOTEBOOK(notebook), grid,
                              gtk_label_new(packs[i]));
        }
        
    }    
    gtk_widget_show_all(notebook);
    mx_del_strarr(&packs);
    return notebook;
}
