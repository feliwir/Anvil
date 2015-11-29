--
-- Created by IntelliJ IDEA.
-- User: stephan
-- Date: 27.10.15
-- Time: 10:36
-- To change this template use File | Settings | File Templates.
--
local game = require("script.bindings")

print("Starting HPSE ")
print("System Information:")
print("Operating System: " .. jit.os)
print("Architecture: " .. jit.arch)
game.PrintRenderer();

-- Load our gui
--game.gui.LoadFile("./ui/index.html")
game.gui.LoadFile("ui/mainMenu.html")

game.AddTextureDir("textures")
game.AddModelDir("models")
game.AddMapDir("maps")
