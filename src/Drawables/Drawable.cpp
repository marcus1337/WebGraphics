#include "Drawable.h"

Drawable::Drawable(Engine& _engine) : engine(_engine), graphics(_engine.graphics), mouse(_engine.window.mouse)
{};