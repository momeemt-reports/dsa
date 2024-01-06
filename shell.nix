{ pkgs ? import ./nix/pkgs.nix }:
let
  libcIncludeDir = if pkgs.stdenv.isDarwin then
    "${pkgs.darwin.Libsystem}/include"
  else
    "${pkgs.glibc.dev}/include";
in
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    llvmPackages_16.libcxxClang
    llvmPackages_16.clang-unwrapped
    gnumake
    cmake
    gnuplot
    cunit
    doxygen
    nil
  ] ++ pkgs.lib.optional pkgs.stdenv.isDarwin pkgs.darwin.Libsystem
    ++ pkgs.lib.optional (!pkgs.stdenv.isDarwin) pkgs.glibc.dev;

  CUNIT_INCLUDE_DIR = "${pkgs.cunit}/include";
  LIBC_INCLUDE_DIR = libcIncludeDir;
  CLANG_INCLUDE_DIR = "${pkgs.llvmPackages_16.libcxxClang}/resource-root/include";
}
