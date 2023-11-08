# Zephyr 0.5.1 - 08/11/2023

### Added define `ZEPHYR_USE_ANONYMOUS`

* New define `ZEPHYR_USE_ANONYMOUS` - enables anonymous structs and unions

# Zephyr 0.5.0 - 08/11/2023

### Added define `ZEPHYR_EXPERIMENTAL`

* New define `ZEPHYR_EXPERIMENTAL` - enables experimental features such as `std::experimental::simd`

* `zephyr::math`

    * Changed `vector` implementation to use `std::experimental::simd` if `ZEPHYR_EXPERIMENTAL` is defined

# Zephyr 0.4.0 - 22/10/2023

### Added `zephyr::math::matrix`

* `zephyr::math`

    :green_circle: New type `matrix` (experimental) [^1]

# Zephyr 0.3.0 - 21/10/2023

### Changed Vector Implementation

* `zephyr::math`

    :green_circle: Usage of `std::experimental::simd` for parallelization

    :green_circle: New function `swizzle()` - returns a new vector with the specified components

    :red_circle: Removed type `dynamic_vector`

    :red_circle: Removed `operator[]` and  for `vector` type

# Zephyr 0.2.0 - 18/10/2023

### Simple GL Wrapper

:green_circle: Added Internal Library `gl`

:green_circle: Added Internal Library `utils`

* `zephyr::gl`

    :green_circle: New type `Buffer`

    :green_circle: New type `Program`

    :green_circle: New type `Shader`

    :green_circle: New type `Texture`

    :green_circle: New type `Uniform`

    :green_circle: New type `VertexArray`

* `zephyr::utils`

    :green_circle: New function `loadTexture()` - loads a 2D Texture from a file

    :green_circle: New function `loadShader()`

# Zephyr 0.1.0 - 16/10/2023

### Simple GLFW Window Wrapper

:green_circle: Added Internal Library `glfw`

:green_circle: Added Internal Library `math`

* `zephyr::glfw`

    :green_circle: New type `Window`

[^1]: This feature may not work completely
