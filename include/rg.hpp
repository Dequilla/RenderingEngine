#pragma once

#ifdef __opengl__
#include "platform/opengl/opengl.hpp"
#endif

// GLM (Math)
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// System
#include "system/window.hpp"
#include "system/event.hpp"
#include "system/keyboard.hpp"
#include "system/keycode.hpp"
#include "system/clock.hpp"

// Graphics
#include "graphics/renderer.hpp"
#include "graphics/shader.hpp"
#include "graphics/model.hpp"
#include "graphics/color.hpp"
#include "graphics/camera.hpp"
