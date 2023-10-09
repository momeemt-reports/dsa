{ pkgs ? import ./nix/pkgs.nix }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gcc
    gnumake
    cunit
  ];
}
