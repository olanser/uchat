#include "client.h"
#include "defines_client.h"

static void change_value_adjustment(GtkAdjustment *adjustment, gpointer user_data) {
    static gdouble upper = 0;

    if (upper != gtk_adjustment_get_upper(adjustment)) {
        gtk_adjustment_set_value(adjustment,
            gtk_adjustment_get_upper(adjustment));
        upper = gtk_adjustment_get_upper(adjustment);
    }
}

void mx_set_adjustment_auto_down(GtkBuilder* builder) {
    GtkWidget* chat_scroll_window = mx_build_get(builder,
                                                 "chat_scroll_window");
    GtkAdjustment *vadjustment = gtk_scrolled_window_get_vadjustment(
        GTK_SCROLLED_WINDOW(chat_scroll_window));

    g_signal_connect(G_OBJECT(vadjustment), "changed",
        G_CALLBACK(change_value_adjustment), 0);
}
