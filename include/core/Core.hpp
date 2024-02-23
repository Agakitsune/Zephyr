
#pragma once

#include <memory>
#include <fstream>
#include <filesystem>

#include "graphics/Window.hpp"
#include "graphics/font/Font.hpp"
#include "graphics/Text.hpp"
#include "graphics/projector/OrthographicProjector.hpp"
#include "graphics/pipeline/SpritePipeline.hpp"

#include "registry/Registry.hpp"
#include "registry/Registries.hpp"
#include "registry/Pipelines.hpp"
#include "registry/Fonts.hpp"

#include "json.hpp"

namespace zephyr {

    class Core {
        static std::unique_ptr<Core> _instance;
        static std::filesystem::path _resources;

        graphics::Window _window;
        int width, height;

        int tps;
        unsigned int ticks = 0;
        unsigned int frames = 0;

        bool isDebug = false;
        graphics::Text _tick;
        graphics::Text _frame;

        registry::Registry<registry::UnknownRegistry> _root;

        const graphics::OrthographicProjector projector = graphics::OrthographicProjector(800, 600);

        Core(const std::string &project);
        Core(int width, int height, const std::string &title, int tps);
        Core(int width, int height, std::string &&title, int tps);
        Core(int width, int height, const char *title, int tps);

        void bootstrap();
        void debug();

        void _run();

        template<typename T>
        requires std::is_base_of_v<graphics::Pipeline, T>
        graphics::Pipeline &registerPipeline(const std::string &name) {
            const std::string &ns = registry::RegistryKey::getDefaultNamespace();
            
            std::filesystem::path path = _resources / "assets" / ns / "pipeline" / (name + ".json");
            
            return PIPELINE->registerValue(registry::RegistryKey::of(name), T(path));
        }

        template<typename T>
        requires std::is_base_of_v<graphics::Projector, T>
        graphics::Projector &registerProjector(const std::string &name, T &&projector) {
            return PROJECTOR->registerValue(registry::RegistryKey::of(name), std::move(projector));
        }

        template<typename T>
        requires std::is_base_of_v<graphics::Font, T>
        graphics::Font &registerFont(const std::string &name) {
            const std::string &ns = registry::RegistryKey::getDefaultNamespace();
            
            std::filesystem::path path = _resources / "assets" / ns / "font" / (name + ".json");

            return FONT->registerValue(registry::RegistryKey::of(name), T(path));
        }

        template<typename T>
        requires std::is_base_of_v<registry::UnknownRegistry, T>
        registry::UnknownRegistry &registerRegistry(const std::string &name, T &&registry) {
            return _root.registerValue(registry::RegistryKey::of(name), std::move(registry));
        }

        void registerDefaultPipelines();
        void registerDefaultProjectors();
        void registerDefaultFonts();
        void registerDefaultRegistries();
        void freezeRegistries();

        public:
            Core(const Core &other) = delete;
            Core(Core &&other) noexcept = delete;

            ~Core();

            Core &operator=(const Core &other) = delete;
            Core &operator=(Core &&other) noexcept = delete;

            static void init();
            static void init(const std::string &project);
            static void init(int width, int height, const std::string &title, int tps);
            static void init(int width, int height, std::string &&title, int tps);
            static void init(int width, int height, const char *title, int tps);
            
            static void run();

            static Core &instance();
            static const std::filesystem::path &resources();
    };

}
