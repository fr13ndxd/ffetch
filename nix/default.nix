{
  lib,
  pkgs,
  stdenv,
}:
stdenv.mkDerivation (
  finalAttrs: {
    pname = "ffetch";
    version = "0.1";

    src = ../.;

    nativeBuildInputs = [ pkgs.cmake pkgs.sol2 pkgs.lua ];

    buildPhase = ''
       make
    '';

    installPhase = ''
       mkdir -p $out/bin
       cp -r ffetch $out/bin/ffetch
    '';

  }
)
