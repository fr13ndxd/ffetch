{ stdenv, cargo, pkgs }:

stdenv.mkDerivation rec {
  pname = "ffetch";
  version = "0.0.1";

  src = ../.;

  nativeBuildInputs = [ pkgs.cargo pkgs.rustc ];

  buildPhase = ''
    cargo build --release
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp target/release/ffetch $out/bin/
  '';
}