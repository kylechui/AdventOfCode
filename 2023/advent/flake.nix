{
  description = "A development shell for Advent of Code 2023.";
  inputs = { nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11"; };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default =
        pkgs.mkShell { buildInputs = [ pkgs.dune_3 pkgs.ocaml ]; };
    };
}
