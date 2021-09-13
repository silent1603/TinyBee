from conans import ConanFile, CMake, tools
import os,platform

class HelloConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    requires = "glfw/3.3.4","sdl/2.0.16","yaml-cpp/0.6.3","tinyxml2/8.0.0","fmt/7.1.3","spdlog/1.8.5","nlohmann_json/3.9.1","entt/3.7.1","openal/1.21.1","glad/0.1.34","freetype/2.10.4","glm/0.9.9.8","assimp/5.0.1","bullet3/3.17","stb/20200203","lua/5.4.1","catch2/2.13.6","box2d/2.4.1"

    generators = "cmake"

    build_policy = "missing"
   
    externalVendorPath = "../tinylb/external"


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self): 
        #include path
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="glfw",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="sdl",folder = False,keep_path = True)
        self.copy("*.*", dst=HelloConan.externalVendorPath, src="include",root_package="glad", folder=False, keep_path=True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="spdlog",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="nlohmann_json",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="entt",folder = False,keep_path = True)
        self.copy("*.*",dst =HelloConan.externalVendorPath,src = "include",root_package="openal",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="freetype",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="glm",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="assimp",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="lua",folder = True,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="bullet3",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="stb",folder = True,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="catch2",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="box2d",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="fmt",folder = False,keep_path = True)
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="tinyxml2",folder = True,keep_path = True) 
        self.copy("*.*",dst = HelloConan.externalVendorPath,src = "include",root_package="yaml-cpp",folder = True,keep_path = True)
        #licenses
        self.copy("*.*",dst = "../tinylb/licenses",src = "licenses",folder = True,keep_path = True)
        #lib path
        self.copy("*.dll", dst="./bin", src="bin", keep_path=False)
        self.copy("*.dylib", dst="./bin", src="lib", keep_path=False)
        self.copy("*.lib", dst="./lib", src="lib", keep_path=False)
