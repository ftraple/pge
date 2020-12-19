pge = require 'libpge_lua'

pge.window_create("Lua Test", 320, 240, 2, 5, false)

while pge.window_is_running() do
    pge.window_clear(255, 161, 0, 255)
    pge.draw_set_current_color(0, 255, 0, 255)
    pge.draw_text(10, 10, 4, 0, "Text")
    pge.window_draw()
end

pge.window_destroy()