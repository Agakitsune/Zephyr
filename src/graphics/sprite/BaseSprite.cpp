
#include "graphics/sprite/BaseSprite.hpp"
#include "graphics/Pipeline.hpp"
#include "graphics/Window.hpp"

namespace zephyr::graphics {
    
    void BaseSprite::setupBuffer() {
        math::vec2u textureSize = _texture.size();
        setupBuffer(math::rect<int>(0, 0, textureSize.x, textureSize.y), textureSize);
    }

    void BaseSprite::setupBuffer(const zephyr::math::rect<int> &rect) {
        math::vec2u textureSize = _texture.size();
        setupBuffer(rect, textureSize);
    }

    void BaseSprite::setupBuffer(const zephyr::math::rect<int> &rect, const zephyr::math::vec2u &textureSize) {
        // _array.bind();
        _buffer.bind(gl::BufferTarget::ArrayBuffer);

        math::rect<float> uv = math::rect(
            static_cast<float>(rect.getLeft()) / textureSize.x,
            static_cast<float>(rect.getTop()) / textureSize.y,
            static_cast<float>(rect.getWidth()) / textureSize.x,
            static_cast<float>(rect.getHeight()) / textureSize.y
        );

        float vertices[] = {
            0.0f, 0.0f,                                                                                                             uv.getLeft(), uv.getTop(),
            static_cast<float>(rect.getWidth() - rect.getLeft()), 0.0f,                                                             uv.getWidth(), uv.getTop(),
            0.0f, static_cast<float>(rect.getHeight() - rect.getTop()),                                                             uv.getLeft(), uv.getHeight(),
            static_cast<float>(rect.getWidth() - rect.getLeft()), static_cast<float>(rect.getHeight() - rect.getTop()),             uv.getWidth(), uv.getHeight()
        };//Position                                                                                                                UV

        _buffer.data(vertices, _usage);
    }

    BaseSprite::BaseSprite(const BaseSprite &other) : _texture(other._texture), _usage(other._usage) {
        _buffer.bind(gl::BufferTarget::ArrayBuffer);
        _buffer.data(other._buffer.getData().data(), other._buffer.size(), _usage);
    }

    BaseSprite::BaseSprite(BaseSprite &&other) noexcept : _texture(std::move(other._texture)), _usage(other._usage) {}

    BaseSprite::BaseSprite(const Texture &texture, gl::BufferUsage usage) : _texture(texture), _usage(usage) {
        setupBuffer();
    }

    BaseSprite::BaseSprite(Texture &&texture, gl::BufferUsage usage) : _texture(std::move(texture)), _usage(usage) {
        setupBuffer();
    }

    BaseSprite::BaseSprite(const char *path, gl::BufferUsage usage) : _usage(usage) {
        _texture = Texture(path);
        setupBuffer();
    }

    BaseSprite::BaseSprite(const std::string &path, gl::BufferUsage usage) : _usage(usage) {
        _texture = Texture(path);
        setupBuffer();
    }

    BaseSprite::BaseSprite(const std::filesystem::path &path, gl::BufferUsage usage) : _usage(usage) {
        _texture = Texture(path);
        setupBuffer();
    }

    BaseSprite::~BaseSprite() {}

    BaseSprite &BaseSprite::operator=(const BaseSprite &other) {
        _texture = other._texture;
        setupBuffer();
        setPosition(other.getPosition());
        setRotation(other.getRotation());
        setScale(other.getScale());
        setOrigin(other.getOrigin());
        return *this;
    }

    BaseSprite &BaseSprite::operator=(BaseSprite &&other) noexcept {
        _texture = std::move(other._texture);
        _buffer = std::move(other._buffer);
        setPosition(other.getPosition());
        setRotation(other.getRotation());
        setScale(other.getScale());
        setOrigin(other.getOrigin());
        return *this;
    }

    void BaseSprite::setPosition(const float x, const float y) {
        Transformable::setTranslation(x, y);
    }

    void BaseSprite::setPosition(const math::vec2f &position) {
        Transformable::setTranslation(position);
    }

    void BaseSprite::move(const float x, const float y) {
        Transformable::translate(x, y);
    }

    void BaseSprite::setRotation(const float angle) {
        Transformable::setRotation(angle);
    }

    void BaseSprite::rotate(const float angle) {
        Transformable::rotate(angle);
    }

    void BaseSprite::setScale(const float x, const float y) {
        Transformable::setScale(x, y);
    }

    void BaseSprite::setScale(const math::vec2f &scale) {
        Transformable::setScale(scale);
    }

    void BaseSprite::scale(const float x, const float y) {
        Transformable::scale(x, y);
    }

    void BaseSprite::setOrigin(const float x, const float y) {
        Transformable::setOrigin(x, y);
    }

    void BaseSprite::setOrigin(const math::vec2f &origin) {
        Transformable::setOrigin(origin);
    }

    void BaseSprite::setTexture(const Texture &texture) {
        _texture = texture;
    }

    void BaseSprite::setTexture(Texture &&texture) {
        _texture = std::move(texture);
    }

    void BaseSprite::setTexture(const char *path) {
        _texture = Texture(path);
    }

    void BaseSprite::setTexture(const std::string &path) {
        _texture = Texture(path);
    }

    void BaseSprite::setTexture(const std::filesystem::path &path) {
        _texture = Texture(path);
    }

    void BaseSprite::scissor(const int x, const int y, const int width, const int height) {
        setupBuffer(zephyr::math::rect<int>(x, y, width, height));
    }

    void BaseSprite::scissor(const zephyr::math::vec2i &position, const zephyr::math::vec2i &size) {
        setupBuffer(zephyr::math::rect<int>(position, size));
    }

    void BaseSprite::scissor(const zephyr::math::rect<int> &rect) {
        setupBuffer(rect);
    }

    math::vec2f BaseSprite::getPosition() const {
        return math::swizzle<math::arg::X, math::arg::Y>(Transformable::getTranslation());
    }

    math::vec2f BaseSprite::getScale() const {
        return math::swizzle<math::arg::X, math::arg::Y>(Transformable::getScale());
    }

    math::vec2f BaseSprite::getOrigin() const {
        return math::swizzle<math::arg::X, math::arg::Y>(Transformable::getOrigin());
    }

    float BaseSprite::getRotation() const {
        return Transformable::getRotation().z;
    }

    const Texture &BaseSprite::getTexture() const {
        return _texture;
    }

    void BaseSprite::draw(const Window &window, const Pipeline &pipeline) const {
        pipeline.set("Z", 0.f);
        window.drawPrimitive(gl::DrawMode::TriangleStrip, 0, 4);
    }

    void BaseSprite::draw(const Window &window, const float z, const Pipeline &pipeline) const {
        pipeline.set("Z", z);
        window.drawPrimitive(gl::DrawMode::TriangleStrip, 0, 4);
    }

    void BaseSprite::setup(const Pipeline &pipeline) const {
        auto model = getModel();
        _texture.slot(0);
        
        pipeline.set4x4("model", 1, true, &model[0][0]);
        pipeline.set("Texture", 0);

        _buffer.bindVertex(0, 0, 32);
    }

} // namespace zephyr::graphics
