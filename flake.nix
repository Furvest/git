{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
      dependencies = with pkgs; [
        cmake
        libgl
        libxkbcommon
        pipewire
        sdl3
        vulkan-headers
        vulkan-loader
        wayland

        xorg.libX11
        xorg.libxcb
        xorg.libXScrnSaver
        xorg.libXcursor
        xorg.libXext
        xorg.libXfixes
        xorg.libXi
        xorg.libXrandr
      ];
    in
    {
      devShell = pkgs.mkShell {
        buildInputs = dependencies;
        PKG_CONFIG_PATH = "${pkgs.SDL3.dev}/lib/pkgconfig";
      };

      packages.default = pkgs.stdenv.mkDerivation {
        pname = "SDLGame";
        version = "0.1.0";

        src = ./.; # assumes source files are in the flake root
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
          "-DSDL3_DIR=${pkgs.SDL3}/lib/cmake/SDL3"
        ];

        buildPhase = ''
          cmake -S . -B build
          cmake --build build
        '';

        buildInputs = dependencies;
      };
    };
}
