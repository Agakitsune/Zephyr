
#include "core/Core.hpp"

#include "graphics/Color.hpp"

#ifdef ZEPHYR_DEBUG
    #include "utils/Debug.hpp"
#endif

namespace zephyr {

    Core::Core(const std::string &project) {
        std::filesystem::path path = project;
        path = std::filesystem::canonical(path);

        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Core") << "Loading from: " << path << std::endl;
        #endif

        std::ifstream file(path);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + path.string());

        nlohmann::json json;
        file >> json;
        file.close();

        std::string name = json["name"];
        std::string ns = name;

        if (json.contains("namespace")) {
            ns = json["namespace"];
        }

        for (auto &c : ns) {
            if (c == ' ')
                c = '_';
            c = std::tolower(c);
        }

        width = json["window"]["width"];
        height = json["window"]["height"];
        std::string title = name;
        if (json["window"].contains("title")) {
            title = json["window"]["title"];
        }

        tps = json["tps"];

        _window.create(width, height, title);

        _tick = graphics::Text();
        _frame = graphics::Text();

        registry::RegistryKey::setDefaultNamespace(ns);

        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Core") << "Creating {width: " << width << ", height: " << height << ", title: " << title << ", tps: " << tps << std::endl;
        #endif

        _resources = path.parent_path().string();

        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Core") << "Resources path: " << _resources << std::endl;
        #endif

        bootstrap();
    }

    Core::Core(int width, int height, const std::string &title, int tps)
        : _window(width, height, title), width(width), height(height), tps(tps)
    {
        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Core") << "Creating {width: " << width << ", height: " << height << ", title: " << title << ", tps: " << tps << std::endl;
        #endif
        bootstrap();
    }

    Core::Core(int width, int height, std::string &&title, int tps)
        : _window(width, height, title), width(width), height(height), tps(tps)
    {
        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Core") << "Creating {width: " << width << ", height: " << height << ", title: " << title << ", tps: " << tps << std::endl;
        #endif
        bootstrap();
    }

    Core::Core(int width, int height, const char *title, int tps)
        : _window(width, height, title), width(width), height(height), tps(tps)
    {
        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Core") << "Creating {width: " << width << ", height: " << height << ", title: " << title << ", tps: " << tps << std::endl;
        #endif
        bootstrap();
    }

    Core::~Core() {}

    void Core::bootstrap() {
        registerDefaultRegistries();
        registerDefaultPipelines();
        registerDefaultProjectors();
        registerDefaultFonts();
        freezeRegistries();

        _tick.setFont(DEFAULT);
        _frame.setFont(DEFAULT);

        _tick.setText("TPS: " + std::to_string(ticks));
        _frame.setText("FPS: " + std::to_string(frames));

        _tick.setColor(graphics::minecraft::green);
        _frame.setColor(graphics::minecraft::green);

        _window.useProjector(PROJECTOR->get("orthographic"));
        _window.usePipeline(SPRITE);
    }

    void Core::debug() {
        _tick.setTranslation(10, 10);
        _tick.setScale(2, 2);
        _window.draw(_tick);

        _frame.setTranslation(10, 42);
        _frame.setScale(2, 2);
        _window.draw(_frame);
    }

    void Core::_run() {
        const double tickrate = 1.0 / tps;
        double current = 0;
        double timer = 0;
        double all = 0;

        double last = glfwGetTime();

        while (_window.isOpen()) {
            current = glfwGetTime();
            timer += current - last;
            all += current - last;
            ++frames;
            if (timer >= tickrate) {
                ++ticks;
                timer -= tickrate;
            }
            if (all >= 1.0) {
                if (isDebug) {
                    _tick.setText("TPS: " + std::to_string(ticks));
                    _frame.setText("FPS: " + std::to_string(frames));
                }
                frames = 0;
                ticks = 0;
                all -= 1.0;
            }
            last = current;

            _window.clear(zephyr::graphics::black_olive);

            if (_window.isKeyJustPressed(input::Key::F3)) {
                isDebug = !isDebug;
            }

            if (isDebug)
                debug();
            
            _window.display();
            _window.pollEvents();
        }
        _window.destroy();
    }

    void Core::registerDefaultPipelines() {
        SPRITE = &registerPipeline<graphics::SpritePipeline>("sprite");
    }

    void Core::registerDefaultProjectors() {
        registerProjector("orthographic", graphics::OrthographicProjector(width, height));
    }

    void Core::registerDefaultFonts() {
        DEFAULT = &registerFont<graphics::Font>("default");
    }

    void Core::registerDefaultRegistries() {
        PIPELINE = &(registerRegistry("pipeline", registry::Registry<graphics::Pipeline>()).as<graphics::Pipeline>());
        PROJECTOR = &(registerRegistry("projector", registry::Registry<graphics::Projector>()).as<graphics::Projector>());
        FONT = &(registerRegistry("font", registry::Registry<graphics::Font>()).as<graphics::Font>());
    }

    void Core::freezeRegistries() {
        for (auto &[key, value] : _root) {
            value->freeze();
        }
        _root.freeze();
    }

    void Core::init() {
        init("./resources/project.json");
    }

    void Core::init(const std::string &project) {
        if (_instance != nullptr)
            throw std::runtime_error("Core already initialized");
        _instance = std::unique_ptr<Core>(new Core(project));
    }

    void Core::init(int width, int height, const std::string &title, int tps) {
        if (_instance != nullptr)
            throw std::runtime_error("Core already initialized");
        _instance = std::unique_ptr<Core>(new Core(width, height, title, tps));
    }

    void Core::init(int width, int height, std::string &&title, int tps) {
        if (_instance != nullptr)
            throw std::runtime_error("Core already initialized");
        _instance = std::unique_ptr<Core>(new Core(width, height, title, tps));
    }

    void Core::init(int width, int height, const char *title, int tps) {
        if (_instance != nullptr)
            throw std::runtime_error("Core already initialized");
        _instance = std::unique_ptr<Core>(new Core(width, height, title, tps));
    }

    void Core::run() {
        instance()._run();
    }

    Core &Core::instance() {
        if (_instance == nullptr)
            throw std::runtime_error("Core not initialized");
        return *_instance;
    }

    const std::filesystem::path &Core::resources() {
        return _resources;
    }

    std::unique_ptr<Core> Core::_instance = nullptr;
    std::filesystem::path Core::_resources = "/";

}
