# Zephyr

Zephyr is a powerful C++ game engine.
It is designed to be simple and easy to use for beginners and allow advanced users to have full control over the engine.

# Zephyr 0.14.0 - 23/02/2024

### Added Text rendering, Registry, Core and `resources` directory, upgrade rendering pipeline

* `zephyr::graphics`

    * New type `Font`

    * New type `Text`

    * New type `Image`

    * New type `Colorable`

* `zephyr::color::minecraft`

    * New color `dark_blue`
    
    * New color `dark_green`
    
    * New color `dark_aqua`
    
    * New color `dark_red`
    
    * New color `dark_purple`
    
    * New color `gold`
    
    * New color `gray`
    
    * New color `dark_gray`
    
    * New color `blue`
    
    * New color `green`
    
    * New color `aqua`
    
    * New color `red`
    
    * New color `light_purple`
    
    * New color `yellow`

* `zephyr::registry`

    * New type `Registry`

    * New type `RegistryKey`

* `zephyr::utils`

    * New type `VertexData`

* `zephyr`

    * New type `Core`

Updated the Pipeline to use `glVertexAttribFormat` instead of `glVertexAttribPointer`, the Pipeline now store the VAO instead of the Drawable,
allowing to store the format in the VAO on construction and just bind the VAO and the Buffer to draw when needed.

Added the `/resources` directory, allowing to store resources like fonts, pipelines, shaders, textures, etc.

# Zephyr 0.13.0 - 19/02/2024

### Added scissor on sprite

* `zephyr::graphics`

    * New type `StaticSprite`

    * New type `DynamicSprite`

    * New type `StreamSprite`

    * Remove type `Sprite`

    * New method `scissor()` to sprites

# Zephyr 0.12.0 - 19/02/2024

### Added Animation

* `zephyr::animation`

    * New type `Interpolation`

* `zephyr::animation::easing`

    * New function `linear()`

    * New function `quadraticIn()`

    * New function `quadraticOut()`

    * New function `quadraticInOut()`

    * New function `cubicIn()`

    * New function `cubicOut()`

    * New function `cubicInOut()`

    * New function `quarticIn()`

    * New function `quarticOut()`

    * New function `quarticInOut()`

    * New function `quinticIn()`

    * New function `quinticOut()`

    * New function `quinticInOut()`

    * New function `sineIn()`

    * New function `sineOut()`

    * New function `sineInOut()`

    * New function `circularIn()`

    * New function `circularOut()`

    * New function `circularInOut()`

    * New function `exponentialIn()`

    * New function `exponentialOut()`

    * New function `exponentialInOut()`

    * New function `elasticIn()`

    * New function `elasticOut()`

    * New function `elasticInOut()`

    * New function `backIn()`

    * New function `backOut()`

    * New function `backInOut()`

    * New function `bounceIn()`

    * New function `bounceOut()`

    * New function `bounceInOut()`

* `zephyr::math`

    * New type `rect`

    > *Experimental: `rect` is not fully implemented yet*

# Zephyr 0.11.0 - 23/01/2024

### Added `zephyr::graphics`

* `zephyr::graphics`

    * New type `color`

    * New type `Drawable`

    * New type `Projector`

    * New type `Sprite`

    * New type `Texture`

    * New type `Transformable`

    * New type `Window`

    * New pipeline `SpritePipeline`

    * New projector `OrthographicProjector`

* `zephyr::math`

    * New function `toRadians()`

    * New function `toDegrees()`

* `zephyr::gl`

    * Added copy constructor and copy assignment to `Buffer`

    * Added copy constructor and copy assignment to `Program`

    * Added copy constructor and copy assignment to `Texture`

    * New method `isValid()` in `Uniform`

    * New function `disableVertexAttribArray()` in `VertexArray`

* `zephyr::glfw`

    * New method `close()` in `Window`

* `zephyr::utils`

    * New type `Chunk`

    * New function `disableAll()` - Disable all vertex attrib arrays

# Zephyr 0.10.0 - 27/11/2023

### Added `zephyr::utils::lookAt`, Added `zephyr::math::normalize`

* `zephyr::utils`

    * New function `lookAt()` - Generate a lookAt matrix

* `zephyr::math`

    * New function `normalize()` - Normalize a vector

# Zephyr 0.9.2 - 27/11/2023

### Tested on PS4 and Switch Pro Controllers

> *Joystick has been testted with a PS4 and Switch Pro Controller*

# Zephyr 0.9.1 - 19/11/2023

### Update Clip functions

* `zephyr::utils`

    * `ortho()` - Change values to use Row-Major order matrix

    * `perspective()` - Change values to use Row-Major order matrix

# Zephyr 0.9.0 - 17/11/2023

### Added `zephyr::input::Mouse` and `zephyr::input::Joystick`

> *Joystick has only been tested with a Xbox 360 Controller, need further testing*

* `zephyr::input`

    * New enum `MouseButton`

    * New enum `Joystick`

    * New enum `JoystickAxis`

    * New enum `JoystickFullAxis`

    * New enum `JoystickButton`

    * New struct `JoystickDeadZone` - Allows to set deadzones for joystick and triggers (experimental)

    > *Experimental: Triggers dead zones have not been implemented yet*

* `zephyr::glfw`

    * New method `isMouseButtonPressed()`

    * New method `isMouseButtonReleased()`

    * New method `getMousePos()`

    * New method `setMousePos()`

    * New method `getMouseScroll()`

    * New method `isJoystickConnected()`

    * New method `isJoystickButtonPressed()`
    
    * New method `isJoystickButtonReleased()`
    
    * New method `getJoystickAxis()`
    
    * New method `getJoystickAxis()`

# Zephyr 0.8.0 - 17/11/2023

### Changed Input handling

* `zephyr::glfw::window`

    * New method `isKeyPressed()`

    * New method `isKeyReleased()`

* `zephyr::input`

    * Removed function `isKeyPressed()`

    * Removed function `isKeyReleased()`

# Zephyr 0.7.0 - 16/11/2023

### Added `zephyr::input`

* `zephyr::input`

    * New enum `Key`

    * New function `isKeyPressed()`

    * New function `isKeyReleased()`

* General

    * New function `construct()` - Construction function, marked with **__attribute((constructor))**

    * New function `destruct()` - Destruction function, marked with **__attribute((destructor))**

    * Added `glfwTerminate()` in `destruct()`

# Zephyr 0.6.0 - 16/11/2023

### Added Projection Function

* `zephyr::utils`

    * New function `ortho()` - Generate a orthonormal projection matrix

    * New function `perspective()` - Generate a persepctive projection matrix

# Zephyr 0.5.2 - 16/11/2023

### Added Viewport automatic resizing

* `zephyr::glfw`

    * `Window` - Automaticaly resizes viewport when window is resized

* `zephyr::math`

    * `vector`
        
        - Copy & Move Assignment didn't compile, added default implementation

        - Added constructor `vector(const vector<T, N>&)` on `vector1`, `vector2`, `vector3` and `vector4` to allow construction from greater vectors

# Zephyr 0.5.1 - 16/11/2023

### Changed Window Implementation

* `zephyr::glfw`

    * `Window` - Automaticaly calls `glewInit()` when first window is created

# Zephyr 0.5.0 - 13/11/2023

### Added define `ZEPHYR_DEBUG`

* New define `ZEPHYR_DEBUG` - enables debug messages

* `zephyr::utils`

    * New function `loadProgram()` - load multiple shader to make a Program

    * `loadShader()` - added Debug message

    * `loadTexture()` - added Debug message

# Zephyr 0.4.3 - 09/11/2023

### Changed `zephyr::math::matrix`

* `zephyr::math`
    
    * `matrix` - remove some templates constraints

# Zephyr 0.4.2 - 08/11/2023

### Added define `ZEPHYR_USE_ANONYMOUS`

* New define `ZEPHYR_USE_ANONYMOUS` - enables anonymous structs and unions

# Zephyr 0.4.1 - 08/11/2023

### Added define `ZEPHYR_EXPERIMENTAL`

* New define `ZEPHYR_EXPERIMENTAL` - enables experimental features such as `std::experimental::simd`

* `zephyr::math`

    * Changed `vector` implementation to use `std::experimental::simd` if `ZEPHYR_EXPERIMENTAL` is defined

# Zephyr 0.4.0 - 22/10/2023

### Added `zephyr::math::matrix`

* `zephyr::math`

    * New type `matrix` (experimental)

# Zephyr 0.3.0 - 21/10/2023

### Changed Vector Implementation

* `zephyr::math`

    * Usage of `std::experimental::simd` for parallelization

    * New function `swizzle()` - returns a new vector with the specified components

    * Removed type `dynamic_vector`

    * Removed `operator[]` and  for `vector` type

# Zephyr 0.2.0 - 18/10/2023

### Simple GL Wrapper

* Added Internal Library `gl`

* Added Internal Library `utils`

* `zephyr::gl`

    * New type `Buffer`

    * New type `Program`

    * New type `Shader`

    * New type `Texture`

    * New type `Uniform`

    * New type `VertexArray`

* `zephyr::utils`

    * New function `loadTexture()` - loads a 2D Texture from a file

    * New function `loadShader()`

# Zephyr 0.1.0 - 16/10/2023

### Simple GLFW Window Wrapper

* Added Internal Library `glfw`

* Added Internal Library `math`

* `zephyr::glfw`

    * New type `Window`
