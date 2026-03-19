#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <notification/notification_messages.h>

typedef struct {
    FuriMutex* mutex;
    uint32_t last_capture_time;
    uint32_t interval_ms;
    bool capturing;
    char status_msg[32];
} BeaconGhostApp;

static void render_callback(Canvas* canvas, void* context) {
    BeaconGhostApp* app = context;
    furi_mutex_acquire(app->mutex, FuriWaitForever);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 12, "BEACON-GHOST V1.0");
    
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 5, 25, "Scanning 433.92MHz...");
    
    char interval_str[32];
    snprintf(interval_str, sizeof(interval_str), "Heartbeat: %lu ms", app->interval_ms);
    canvas_draw_str(canvas, 5, 40, interval_str);

    if(app->capturing) {
        canvas_draw_str(canvas, 5, 55, "> SIGNAL DETECTED <");
    } else {
        canvas_draw_str(canvas, 5, 55, "Waiting for pulse...");
    }

    furi_mutex_release(app->mutex);
}

static void input_callback(InputEvent* event, void* context) {
    BeaconGhostApp* app = context;
    if(event->type == InputTypeShort && event->key == InputKeyBack) {
        // App handles exit
    }
}

int32_t beacon_ghost_app(void* p) {
    BeaconGhostApp* app = malloc(sizeof(BeaconGhostApp));
    app->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    app->interval_ms = 0;
    app->capturing = false;

    // Open GUI and Viewport
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, render_callback, app);
    view_port_input_callback_set(view_port, input_callback, app);
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // MOCK PENTEST LOGIC (For simulation/testing)
    // In a full build, we would hook into furi_hal_subghz here.
    while(1) {
        // Logic to simulate signal detection for testing UI
        furi_delay_ms(100);
        view_port_update(view_port);
    }

    return 0;
}
