{
  description = "ffetch";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs, ... }: {
    packages.x86_64-linux."ffetch" = nixpkgs.stdenv.mkDerivation {
      name = "ffetch";
      src = ./.;

      nativeBuildInputs = [ nixpkgs.make ];
      buildInputs = [ nixpkgs.sol2 ];

      buildPhase = ''
        make
      '';

      installPhase = ''
        sudo make install
      '';
    };
  };
}
