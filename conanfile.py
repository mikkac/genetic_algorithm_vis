from conans import ConanFile, CMake


class PocoTimerConan(ConanFile):
    requires = "cli11/2.3.1", "spdlog/1.10.0", "catch2/3.1.0"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
