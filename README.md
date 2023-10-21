# Zephyr 0.0.3 - 21/10/2023

### Changed Vector Implementation

* `zephyr::math`

    :green_circle: Usage of `std::experimental::simd` for parallelization

    :green_circle: New function `swizzle()` - returns a new vector with the specified components

    :red_circle: Removed type `dynamic_vector`

    :red_circle: Removed `operator[]` and  for `vector` type

# Zephyr 0.0.2 - 18/10/2023

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

# Zephyr 0.0.1 - 16/10/2023

### Simple GLFW Window Wrapper

:green_circle: Added Internal Library `glfw`

:green_circle: Added Internal Library `math`

* `zephyr::glfw`

    :green_circle: New type `Window`
