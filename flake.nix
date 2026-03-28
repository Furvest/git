{
  description = "Игра, созданная лучшими разработчиками (по мнению разработчиков) группы ПМИ24";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      dependencies = with pkgs; [
        # normal dependencies
        cmake
        libxkbcommon
        pipewire
        sdl3
        tinyxml
        vulkan-headers
        vulkan-loader
        wayland

        # TODO: get rid of autism and switch to wl/pipewire/libinput
        # autism
        libX11
        libxcb
        libXScrnSaver
        libXcursor
        libxext
        libXtst
        libXfixes
        libXi
        libXrandr
      ];
    in
    {
      devShell = pkgs.mkShell {
        buildInputs = dependencies;
      };

      packages.${system}.default = pkgs.stdenv.mkDerivation {
        pname = "SDLGame";
        version = "0.1.0";

        src = ./.;
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Release"
        ];

        buildInputs = dependencies;
        buildPhase = ''
          cmake -S . -B build
          cmake --build build
        '';
      };
    };
}
