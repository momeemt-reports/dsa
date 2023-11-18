{ pkgs ? import ./nix/pkgs.nix }:
pkgs.stdenv.mkDerivation rec {
  pname = "dsa";
  version = "0.0.1";

  src = ./.;
  
  buildInputs = with pkgs; [
    llvmPackages_16.libcxxClang
    llvmPackages_16.clang-unwrapped
    gnumake
    gnuplot
    cunit
  ];

  buildPhase = ''
    make test
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp test/bin/* $out/bin
  '';

  meta = {
    description = "A simple package that just runs make.";
    license = pkgs.lib.licenses.mit;
  };
}
