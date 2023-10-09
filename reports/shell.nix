{ pkgs ? import ../nix/pkgs.nix }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    satysfi
  ];
}
