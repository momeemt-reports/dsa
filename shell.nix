{ pkgs ? import ./nix/pkgs.nix }:
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    llvmPackages_16.libcxxClang
    llvmPackages_16.clang-unwrapped
    gnumake
    gnuplot
    cunit
    doxygen
  ];
}
